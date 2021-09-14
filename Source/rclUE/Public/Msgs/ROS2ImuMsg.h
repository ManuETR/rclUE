// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/Imu.msg - do not modify

#pragma once

#include <CoreMinimal.h>

#include "sensor_msgs/msg/imu.h"

#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

#include "ROS2ImuMsg.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSImu
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int header_stamp_sec;

	unsigned int header_stamp_nanosec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString header_frame_id;

	double orientation_x;

	double orientation_y;

	double orientation_z;

	double orientation_w;

	TArray<double> orientation_covariance;

	double angular_velocity_x;

	double angular_velocity_y;

	double angular_velocity_z;

	TArray<double> angular_velocity_covariance;

	double linear_acceleration_x;

	double linear_acceleration_y;

	double linear_acceleration_z;

	TArray<double> linear_acceleration_covariance;

	

	void SetFromROS2(const sensor_msgs__msg__Imu& in_ros_data)
	{
    	header_stamp_sec = in_ros_data.header.stamp.sec;

		header_stamp_nanosec = in_ros_data.header.stamp.nanosec;

		header_frame_id.AppendChars(in_ros_data.header.frame_id.data, in_ros_data.header.frame_id.size);

		orientation_x = in_ros_data.orientation.x;

		orientation_y = in_ros_data.orientation.y;

		orientation_z = in_ros_data.orientation.z;

		orientation_w = in_ros_data.orientation.w;

		for (int i = 0; i < 9; i++)
		{
			orientation_covariance[i] = in_ros_data.orientation_covariance[i];
		}

		angular_velocity_x = in_ros_data.angular_velocity.x;

		angular_velocity_y = in_ros_data.angular_velocity.y;

		angular_velocity_z = in_ros_data.angular_velocity.z;

		for (int i = 0; i < 9; i++)
		{
			angular_velocity_covariance[i] = in_ros_data.angular_velocity_covariance[i];
		}

		linear_acceleration_x = in_ros_data.linear_acceleration.x;

		linear_acceleration_y = in_ros_data.linear_acceleration.y;

		linear_acceleration_z = in_ros_data.linear_acceleration.z;

		for (int i = 0; i < 9; i++)
		{
			linear_acceleration_covariance[i] = in_ros_data.linear_acceleration_covariance[i];
		}

		
	}

	void SetROS2(sensor_msgs__msg__Imu& out_ros_data) const
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

		out_ros_data.orientation.x = orientation_x;

		out_ros_data.orientation.y = orientation_y;

		out_ros_data.orientation.z = orientation_z;

		out_ros_data.orientation.w = orientation_w;

		for (int i = 0; i < 9; i++)
		{
			out_ros_data.orientation_covariance[i] = orientation_covariance[i];
		}

		out_ros_data.angular_velocity.x = angular_velocity_x;

		out_ros_data.angular_velocity.y = angular_velocity_y;

		out_ros_data.angular_velocity.z = angular_velocity_z;

		for (int i = 0; i < 9; i++)
		{
			out_ros_data.angular_velocity_covariance[i] = angular_velocity_covariance[i];
		}

		out_ros_data.linear_acceleration.x = linear_acceleration_x;

		out_ros_data.linear_acceleration.y = linear_acceleration_y;

		out_ros_data.linear_acceleration.z = linear_acceleration_z;

		for (int i = 0; i < 9; i++)
		{
			out_ros_data.linear_acceleration_covariance[i] = linear_acceleration_covariance[i];
		}

		
	}
};

UCLASS()
class RCLUE_API UROS2ImuMsg : public UROS2GenericMsg
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Fini() override;

	virtual const rosidl_message_type_support_t* GetTypeSupport() const override;
	
  	UFUNCTION(BlueprintCallable)
	void SetMsg(const FROSImu& Input);
	
  	UFUNCTION(BlueprintCallable)
	void GetMsg(FROSImu& Output) const;
	
	virtual void* Get() override;

private:
	virtual FString MsgToString() const override;

	sensor_msgs__msg__Imu imu_msg;
};