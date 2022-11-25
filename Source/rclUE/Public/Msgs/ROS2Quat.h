// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from geometry_msgs/msg/Quaternion.msg - do not modify

#pragma once

// UE
#include "CoreMinimal.h"

// ROS
#include "geometry_msgs/msg/quaternion.h"

// rclUE
#include "Msgs/ROS2GenericMsg.h"
#include "rclcUtilities.h"

// Generated Msg/Srv/Action(can be empty)

// Generated
#include "ROS2Quat.generated.h"

USTRUCT(Blueprintable)
struct RCLUE_API FROSQuat
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    double X = 0.f;

    UPROPERTY(EditAnywhere)
    double Y = 0.f;

    UPROPERTY(EditAnywhere)
    double Z = 0.f;

    UPROPERTY(EditAnywhere)
    double W = 0.f;

    FROSQuat()
    {
    }

    void SetFromROS2(const geometry_msgs__msg__Quaternion& in_ros_data)
    {
        X = in_ros_data.x;

        Y = in_ros_data.y;

        Z = in_ros_data.z;

        W = in_ros_data.w;
    }

    void SetROS2(geometry_msgs__msg__Quaternion& out_ros_data) const
    {
        out_ros_data.x = X;

        out_ros_data.y = Y;

        out_ros_data.z = Z;

        out_ros_data.w = W;
    }
};

UCLASS()
class RCLUE_API UROS2QuatMsg : public UROS2GenericMsg
{
    GENERATED_BODY()

public:
    virtual void Init() override;
    virtual void Fini() override;

    virtual const rosidl_message_type_support_t* GetTypeSupport() const override;

    UFUNCTION(BlueprintCallable)
    void SetMsg(const FROSQuat& Input);

    UFUNCTION(BlueprintCallable)
    void GetMsg(FROSQuat& Output) const;

    virtual void* Get() override;

private:
    virtual FString MsgToString() const override;

    geometry_msgs__msg__Quaternion quaternion_msg;
};