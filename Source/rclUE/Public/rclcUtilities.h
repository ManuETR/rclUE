// Copyright (c) 2020 Rapyuta Robotics Co., Ltd.

#pragma once

#include <rclc/rclc.h>
#include <rcl/wait.h>
#include <rcl_action/wait.h>
#include <rcl/graph.h>
#include <cstdlib>
#include "Kismet/KismetSystemLibrary.h"

#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){ UE_LOG(LogTemp, Error, TEXT("Failed status on line %d (function %s): %d. Continuing."),__LINE__, *FString(__FUNCTION__),(int)temp_rc);}}
//#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){ UE_LOG(LogTemp, Error, TEXT("Failed status on line %d: %d. Terminating."),__LINE__,(int)temp_rc); QuitGame();}}

UENUM()
enum UROS2State
{
    Created         UMETA(DisplayName="Created"),
    Initialized     UMETA(DisplayName="Initialized"),
};