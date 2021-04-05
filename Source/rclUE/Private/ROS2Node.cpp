// Fill out your copyright notice in the Description page of Project Settings.


#include "ROS2Node.h"
#include "ROS2Subsystem.h"
#include "ROS2Publisher.h"

#include <rcl/graph.h>
#include "Kismet/GameplayStatics.h"


// Sets default values
AROS2Node::AROS2Node()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

AROS2Node::~AROS2Node()
{
	UE_LOG(LogTemp, Error, TEXT("UROS2LaserScanMsg::~UROS2LaserScanMsg"));
}

// Called when the game starts or when spawned
void AROS2Node::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Node BeginPlay"));
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Node BeginPlay - Done"));
}

void AROS2Node::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// this is called before the components
	UE_LOG(LogTemp, Warning, TEXT("Node EndPlay"));

	for (auto& s : subs)
	{
		RCSOFTCHECK(rcl_subscription_fini(&s.Value, &node));
	}

	// this is better done with the component registering itself to the owner at creation
	TArray<UActorComponent*> pubComponents;
	GetComponents(UROS2Publisher::StaticClass(), pubComponents, true);
	for (auto& c : pubComponents)
	{
		UROS2Publisher* pub = Cast<UROS2Publisher>(c);
		if (pub != nullptr)
		{
			pub->Destroy();
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Node EndPlay - rcl_node_fini"));
	RCSOFTCHECK(rcl_node_fini(&node));

	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("Node EndPlay - Done"));
}

// Called every frame
void AROS2Node::Tick(float DeltaTime)
{
	check(State == UROS2State::Initialized);

	Super::Tick(DeltaTime);

	if (NSubscriptions > 0)
	{
		SpinSome();
	}
}

// this stuff can't be placed in BeginPlay as the order of rcl(c) instructions is relevant
void AROS2Node::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Node Init"));

	if (State == UROS2State::Created)
	{
		if (!rcl_node_is_valid(&node)) // ensures that it stays safe when called multiple times
		{
			context = GWorld->GetGameInstance()->GetSubsystem<UROS2Subsystem>()->GetContext();
			
			UE_LOG(LogTemp, Warning, TEXT("Node Init - rclc_node_init_default"));
			RCSOFTCHECK(rclc_node_init_default(&node, TCHAR_TO_ANSI(*Name), Namespace != FString() ? TCHAR_TO_ANSI(*Namespace) : "", &context->Get()));
		}

		State = UROS2State::Initialized;
	}

	UE_LOG(LogTemp, Warning, TEXT("Node Init - Done"));
}

UROS2Context* AROS2Node::GetContext()
{
	return context;
}

rcl_node_t* AROS2Node::GetNode()
{
	return &node;
}

void AROS2Node::Subscribe()
{
	check(State == UROS2State::Initialized);
			
	UE_LOG(LogTemp, Warning, TEXT("Subscribe"));
	for (auto& e : TopicsToSubscribe)
	{
		UROS2GenericMsg *TopicMessage = NewObject<UROS2GenericMsg>(this, e.Value);

		if (ensure(IsValid(TopicMessage)))
		{
			TopicMessage->Init();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Topic (%s) is nullptr!"), *e.Key);
		}

		if (!subs.Contains(TopicMessage))
		{
			subs.Add(TopicMessage, rcl_get_zero_initialized_subscription());
			FSubscriptionCallback *cb = TopicsToCallback.Find(e.Key);

			if (ensure(cb))
			{
				callbacks.Add(TopicMessage, *cb);
			}

			const rosidl_message_type_support_t * type_support = TopicMessage->GetTypeSupport();
			rcl_subscription_options_t sub_opt = rcl_subscription_get_default_options();
			RCSOFTCHECK(rcl_subscription_init(&subs[TopicMessage], &node, type_support, TCHAR_TO_ANSI(*e.Key), &sub_opt));
			NSubscriptions++;
		}
	}

	// invalidate wait_set
	if (rcl_wait_set_is_valid(&wait_set))
	{
    	RCSOFTCHECK(rcl_wait_set_fini(&wait_set));
    }

	UE_LOG(LogTemp, Warning, TEXT("Subscribe - Done"));
}

void AROS2Node::SpinSome()
{
	//NSpinCalls++;
	if (!rcl_wait_set_is_valid(&wait_set))
	{
    	RCSOFTCHECK(rcl_wait_set_fini(&wait_set));
		wait_set = rcl_get_zero_initialized_wait_set();
		RCSOFTCHECK(rcl_wait_set_init(&wait_set,
									NSubscriptions, NGuardConditions, NTimers, NClients, NServices, NEvents, 
									&context->Get().context, rcl_get_default_allocator()));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Spin Some - %d subscriptions"), wait_set.size_of_subscriptions);
	
	RCSOFTCHECK(rcl_wait_set_clear(&wait_set));

	for (auto& pair : subs)
	{
		RCSOFTCHECK(rcl_wait_set_add_subscription(&wait_set, &pair.Value, nullptr));
	}

	rcl_ret_t rc = rcl_wait(&wait_set, 0);
  	RCLC_UNUSED(rc);

	// based on _rclc_default_scheduling
	TMap<UROS2GenericMsg *, rcl_subscription_t> readySubs;
	for (int i=0; i<wait_set.size_of_subscriptions; i++)
	{
		if (wait_set.subscriptions[i]) // need to iterate on all subscriptions instead? since there's no index
		{
			const rcl_subscription_t* currentSub = wait_set.subscriptions[i];
			for (auto& pair : subs)
			{
				if (&pair.Value == currentSub)
				{
					readySubs.Add(pair);
				}
			}
		}
	}

	for (auto& pair : readySubs)
	{	
		// NSubMsgGets++;
		// UE_LOG(LogTemp, Warning, TEXT("Values - #spins: %d\t\t#gets: %d"), NSpinCalls, NSubMsgGets);
		void * data = pair.Key->Get();
		rmw_message_info_t messageInfo;
		rc = rcl_take(&pair.Value, data, &messageInfo, NULL);

		// callback here
		//pair.Key->PrintSubToLog(rc, Name);
		FSubscriptionCallback *cb = callbacks.Find(pair.Key);

		if (cb)
		{
			cb->ExecuteIfBound(pair.Key);
		}
	}
	//UE_LOG(LogTemp, Warning, TEXT("Spin Some - Done"));
}

void AROS2Node::AddSubscription(FString TopicName, TSubclassOf<UROS2GenericMsg> MsgClass, FSubscriptionCallback Callback)
{
	TopicsToSubscribe.Add(TopicName, MsgClass);
	TopicsToCallback.Add(TopicName, Callback);
}

void AROS2Node::AddPublisher(UROS2Publisher* Publisher)
{
	check(IsValid(Publisher));

	Publisher->RegisterComponent();
	Publisher->ownerNode = this;
	// why are these not allowed?
	//Publisher->SetupAttachment(RootComponent);
	//Publisher->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	pubs.Add(Publisher);
}


TMap<FString, FString> AROS2Node::GetListOfNodes()
{
	TMap<FString, FString> Result;

	rcutils_string_array_t NodeNames = rcutils_get_zero_initialized_string_array();
	rcutils_string_array_t NodeNamespaces = rcutils_get_zero_initialized_string_array();

	RCSOFTCHECK(rcl_get_node_names(&node, rcl_get_default_allocator(), &NodeNames, &NodeNamespaces));
	
	check(NodeNames.size == NodeNamespaces.size);
	for (int i=0; i<NodeNames.size; i++)
	{
		if (NodeNames.data[i] != nullptr && NodeNamespaces.data[i] != nullptr && NodeNames.data[i][0] != '_')
		{
			Result.Add(FString(NodeNames.data[i]), FString(NodeNamespaces.data[i]));
		}
	}

	for (auto& pair : Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Node: %s - Namespace: %s"), *pair.Key, *pair.Value);
	}

	RCSOFTCHECK(rcutils_string_array_fini(&NodeNames));
	RCSOFTCHECK(rcutils_string_array_fini(&NodeNamespaces));

	return Result;
}

// need a way to convert the message type as well
TMap<FString, FString> AROS2Node::GetListOfTopics()
{
	TMap<FString, FString> Result;

	rcl_names_and_types_t TopicNamesAndTypes = rcl_get_zero_initialized_names_and_types();
	rcl_allocator_t Allocator = rcl_get_default_allocator();

	RCSOFTCHECK(rcl_get_topic_names_and_types(&node, &Allocator, false, &TopicNamesAndTypes));

	for (int i=0; i<TopicNamesAndTypes.names.size; i++)
	{
		if (TopicNamesAndTypes.names.data[i] != nullptr &&
		    TopicNamesAndTypes.types != nullptr && 
			TopicNamesAndTypes.types->data[i] != nullptr && 
			TopicNamesAndTypes.types->size >= i)
		{
			Result.Add(FString(TopicNamesAndTypes.names.data[i]), FString(TopicNamesAndTypes.types->data[i]));
		}
	}

	for (auto& pair : Result)
	{
		UE_LOG(LogTemp, Warning, TEXT("Topic: %s - MsgTypes: %s"), *pair.Key, *pair.Value);
	}

	RCSOFTCHECK(rcl_names_and_types_fini(&TopicNamesAndTypes));

	return Result;
}