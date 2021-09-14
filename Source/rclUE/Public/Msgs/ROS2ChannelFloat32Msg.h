// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/ChannelFloat32.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "sensor_msgs/msg/channel_float32.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2ChannelFloat32Msg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSChannelFloat32
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> values;

	

	void SetFromROS2(const sensor_msgs__msg__ChannelFloat32& in_ros_data)
	{
    	name.AppendChars(in_ros_data.name.data, in_ros_data.name.size);

		for (int i = 0; i < in_ros_data.values.size; i++)
		{
			values[i] = in_ros_data.values.data[i];
		}

		
	}

	void SetROS2(sensor_msgs__msg__ChannelFloat32& out_ros_data) const
	{
    	{
			FTCHARToUTF8 strUtf8( *name );
			int32 strLength = strUtf8.Length();
			if (out_ros_data.name.data != nullptr)
		{
			free(out_ros_data.name.data);
		}
		out_ros_data.name.data = (decltype(out_ros_data.name.data))malloc((strLength+1)*sizeof(decltype(*out_ros_data.name.data)));
		memcpy(out_ros_data.name.data, TCHAR_TO_UTF8(*name), (strLength+1)*sizeof(char));
			out_ros_data.name.size = strLength;
			out_ros_data.name.capacity = strLength + 1;
		}

		if (out_ros_data.values.data != nullptr)
		{
			free(out_ros_data.values.data);
		}
		out_ros_data.values.data = (decltype(out_ros_data.values.data))malloc((values.Num())*sizeof(decltype(*out_ros_data.values.data)));
		
		for (int i = 0; i < values.Num(); i++)
		{
			out_ros_data.values.data[i] = values[i];
		}

		out_ros_data.values.size = values.Num();
		out_ros_data.values.capacity = values.Num();

		
	}
};

UCLASS()
class RCLUE_API UROS2ChannelFloat32Msg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSChannelFloat32& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSChannelFloat32& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	sensor_msgs__msg__ChannelFloat32 channel_float32_msg;
};