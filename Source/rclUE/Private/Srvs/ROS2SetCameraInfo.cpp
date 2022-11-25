// Copyright 2021 Rapyuta Robotics Co., Ltd.
// This code has been autogenerated from sensor_msgs/srv/SetCameraInfo.srv - do not modify

#include "Srvs/ROS2SetCameraInfo.h"

const rosidl_service_type_support_t* UROS2SetCameraInfoSrv::GetTypeSupport() const
{
    return ROSIDL_GET_SRV_TYPE_SUPPORT(sensor_msgs, srv, SetCameraInfo);
}

void UROS2SetCameraInfoSrv::Init()
{
    sensor_msgs__srv__SetCameraInfo_Request__init(&SetCameraInfo_req);
    sensor_msgs__srv__SetCameraInfo_Response__init(&SetCameraInfo_res);
}

void UROS2SetCameraInfoSrv::Fini()
{
    sensor_msgs__srv__SetCameraInfo_Request__fini(&SetCameraInfo_req);
    sensor_msgs__srv__SetCameraInfo_Response__fini(&SetCameraInfo_res);
}

void UROS2SetCameraInfoSrv::SetRequest(const FROSSetCameraInfoReq& Request)
{
    Request.SetROS2(SetCameraInfo_req);
}

void UROS2SetCameraInfoSrv::GetRequest(FROSSetCameraInfoReq& Request) const
{
    Request.SetFromROS2(SetCameraInfo_req);
}

void UROS2SetCameraInfoSrv::SetResponse(const FROSSetCameraInfoRes& Response)
{
    Response.SetROS2(SetCameraInfo_res);
}

void UROS2SetCameraInfoSrv::GetResponse(FROSSetCameraInfoRes& Response) const
{
    Response.SetFromROS2(SetCameraInfo_res);
}

void* UROS2SetCameraInfoSrv::GetRequest()
{
    return &SetCameraInfo_req;
}

void* UROS2SetCameraInfoSrv::GetResponse()
{
    return &SetCameraInfo_res;
}

FString UROS2SetCameraInfoSrv::SrvRequestToString() const
{
    /* TODO: Fill here */
    checkNoEntry();
    return FString();
}

FString UROS2SetCameraInfoSrv::SrvResponseToString() const
{
    /* TODO: Fill here */
    checkNoEntry();
    return FString();
}