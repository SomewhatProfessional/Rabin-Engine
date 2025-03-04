#pragma once

// Include all node headers in this file

// Example Control Flow Nodes
#include "ControlFlow/C_ParallelSequencer.h"
#include "ControlFlow/C_RandomSelector.h"
#include "ControlFlow/C_Selector.h"
#include "ControlFlow/C_Sequencer.h"

// Student Control Flow Nodes


// Example Decorator Nodes
#include "Decorator/D_Delay.h"
#include "Decorator/D_InvertedRepeater.h"
#include "Decorator/D_RepeatFourTimes.h"

// Student Decorator Nodes
#include "Decorator/D_IsBeingChased.h"
#include "Decorator/D_TargetIsTiger.h"
#include "Decorator/D_RepeatTwoTimes.h"

// Example Leaf Nodes
#include "Leaf/L_CheckMouseClick.h"
#include "Leaf/L_Idle.h"
#include "Leaf/L_MoveToFurthestAgent.h"
#include "Leaf/L_MoveToMouseClick.h"
#include "Leaf/L_MoveToRandomPosition.h"
#include "Leaf/L_PlaySound.h"

// Student Leaf Nodes
#include "Leaf/L_CheckIfNearGrass.h"
#include "Leaf/L_EatNearestGrass.h"
#include "Leaf/L_CheckIfNearDeer.h"
#include "Leaf/L_EatNearestDeer.h"
#include "Leaf/L_Flee.h"
#include "Leaf/L_FindMouse.h"
#include "Leaf/L_RotateToMouse.h"
#include "Leaf/L_MoveForward.h"
#include "Leaf/L_CheckForTarget.h"
#include "Leaf/L_AimAtTarget.h"
#include "Leaf/L_LeadTarget.h"
#include "Leaf/L_Shoot.h"
#include "Leaf/L_CheckForCollision.h"
