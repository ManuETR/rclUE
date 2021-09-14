// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/TwistStamped.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "geometry_msgs/msg/twist_stamped.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2TwistStampedMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSTwistStamped
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector twist_linear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector twist_angular;

	

	void SetFromROS2(const geometry_msgs__msg__TwistStamped& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		twist_linear.X = in_ros_data.twist.linear.x;
		twist_linear.Y = in_ros_data.twist.linear.y;
		twist_linear.Z = in_ros_data.twist.linear.z;

		twist_angular.X = in_ros_data.twist.angular.x;
		twist_angular.Y = in_ros_data.twist.angular.y;
		twist_angular.Z = in_ros_data.twist.angular.z;

		
	}

	void SetROS2(geometry_msgs__msg__TwistStamped& out_ros_data) const
	{
    	out_ros_data.header.stamp.sec = header_stamp_sec;

		out_ros_data.header.stamp.nanosec = header_stamp_nanosec;

		{
			FTCHARToUTF8 strUtf8( *header_frame_id );
			int32 strLength = strUtf8.Length();
			if (out_ros_data.header.frame_id.data != nullptr)
		{
			free(out_ros_data.header.frame_id.data);
		}
		out_ros_data.header.frame_id.data = (decltype(out_ros_data.header.frame_id.data))malloc((strLength+1)*sizeof(decltype(*out_ros_data.header.frame_id.data)));
		memcpy(out_ros_data.header.frame_id.data, TCHAR_TO_UTF8(*header_frame_id), (strLength+1)*sizeof(char));
			out_ros_data.header.frame_id.size = strLength;
			out_ros_data.header.frame_id.capacity = strLength + 1;
		}

		out_ros_data.twist.linear.x = twist_linear.X;
		out_ros_data.twist.linear.y = twist_linear.Y;
		out_ros_data.twist.linear.z = twist_linear.Z;

		out_ros_data.twist.angular.x = twist_angular.X;
		out_ros_data.twist.angular.y = twist_angular.Y;
		out_ros_data.twist.angular.z = twist_angular.Z;

		
	}
};

UCLASS()
class RCLUE_API UROS2TwistStampedMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSTwistStamped& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSTwistStamped& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	geometry_msgs__msg__TwistStamped twist_stamped_msg;
};