// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/PointField.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "sensor_msgs/msg/point_field.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2PointFieldMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSPointField
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;

	unsigned int offset;

	uint8 datatype;

	unsigned int count;

	

	void SetFromROS2(const sensor_msgs__msg__PointField& in_ros_data)
	{
    	name.AppendChars(in_ros_data.name.data, in_ros_data.name.size);

		offset = in_ros_data.offset;

		datatype = in_ros_data.datatype;

		count = in_ros_data.count;

		
	}

	void SetROS2(sensor_msgs__msg__PointField& out_ros_data) const
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

		out_ros_data.offset = offset;

		out_ros_data.datatype = datatype;

		out_ros_data.count = count;

		
	}
};

UCLASS()
class RCLUE_API UROS2PointFieldMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSPointField& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSPointField& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	sensor_msgs__msg__PointField point_field_msg;
};