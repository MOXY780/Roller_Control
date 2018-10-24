/*--------------------------------------------------------------------
    File: statemachine.h
    Type: header
    PROJ: Walzensteuerung
		ENG: 	MOC, 09.05.2018
                      
--------------------------------------------------------------------*/

#ifndef __STATEMACHINE_H
#define __STATEMACHINE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private define ------------------------------------------------------------*/
typedef enum {
		STATE_OK	=		0,
		STATE_ERROR =	1
} TState_Status;

typedef enum {
		ST_OFF,
		ST_HALT,
		ST_FORW,
		ST_FORWRIGHT,
		ST_RIGHT,
		ST_BACKRIGHT,
		ST_BACK,
		ST_BACKLEFT,
		ST_LEFT,
		ST_FORWLEFT
} TState;

typedef enum {
		EV_OFF,
		EV_ON,
		EV_N,
		EV_NE,
		EV_E,
		EV_SE,
		EV_S,
		EV_SW,
		EV_W,
		EV_NW,
		EV_IDLE
} TEvent;

typedef enum {
		B_OFF = 0x00U,
		B_ON  = 0x01U,
} TButtonOnOff;

typedef enum {
		B_SLOW = 0x00U,
		B_FAST = 0x01U,
} TButtonFastSlow;

typedef enum {
		B_NORMAL = 0x00U,
		B_VIBR   = 0x01U,
} TButtonVibr;

typedef struct {
		TState 					Joystick;
		TButtonOnOff 		Ign;
		TButtonFastSlow Drivespeed;
		TButtonVibr			Drivemode;
} TRemote;

typedef struct {
		TState	currState;
		TEvent	event;
		TState	nextState;
}	TStateTransMatrixRow;

typedef struct {
		const char* name;
		void (*func)(TRemote *tremote);
}	TStateFuntionRow;

typedef struct {
		TState currState;
} TStateMachine;

/* Private Prototypes --------------------------------------------------------*/
void InitState(TStateMachine *tstateMachine);
TState_Status RunStateIteration(uint8_t *data, TStateMachine *tstateMachine, TRemote *tremote);
void FindEvent(uint8_t *data, TEvent *event, TRemote *tremote);
void Remote_Init(TRemote *remote);

#endif // __STATEMACHINE_H
