/*--------------------------------------------------------------------
    File: statemachine.c
    Type: source
    PROJ: Walzensteuerung
		ENG: 	MOC, 09.05.2018
                      
--------------------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_hal.h"
#include "statemachine.h"

/* Private variables ---------------------------------------------------------*/
static TStateTransMatrixRow atStateMatrix[] = {
		// currState	// event		// nextState
	{ ST_OFF,				EV_ON,			ST_HALT},				//  0
	
	{ ST_HALT,			EV_N,				ST_FORW},				//  1
	{	ST_HALT,			EV_NE,			ST_FORWRIGHT},	//  2
	{ ST_HALT,			EV_E,				ST_RIGHT},			//  3
	{ ST_HALT,			EV_SE,			ST_BACKRIGHT},	//  4
	{ ST_HALT,			EV_S,				ST_BACK},				//  5
	{ ST_HALT,			EV_SW,			ST_BACKLEFT},		//  6
	{ ST_HALT,			EV_W,				ST_LEFT},				//  7
	{ ST_HALT,			EV_NW,			ST_FORWLEFT},		//  8
	
	{ ST_FORW,			EV_NE,			ST_FORWRIGHT},	//  9
	{ ST_FORWRIGHT, EV_E,				ST_RIGHT},			// 10
	{ ST_RIGHT,			EV_SE,			ST_BACKRIGHT},	// 11
	{ ST_BACKRIGHT, EV_S,				ST_BACK},				// 12
	{ ST_BACK,			EV_SW,			ST_BACKLEFT},		// 13
	{ ST_BACKLEFT,	EV_W,				ST_LEFT},				// 14
	{ ST_LEFT,			EV_NW,			ST_FORWLEFT},		// 15
	{ ST_FORWLEFT,	EV_N,				ST_FORW},				// 16
	
	{ ST_FORWRIGHT, EV_N,				ST_FORW},				// 17
	{ ST_RIGHT,			EV_NE,			ST_FORWRIGHT},	// 18
	{ ST_BACKRIGHT,	EV_E,				ST_RIGHT},			// 19
	{ ST_BACK,			EV_SE,			ST_BACKRIGHT},	// 20
	{ ST_BACKLEFT,	EV_S,				ST_BACK},				// 21
	{ ST_LEFT,			EV_SW,			ST_BACKLEFT},		// 22
	{ ST_FORWLEFT, 	EV_W,				ST_LEFT},				// 23
	{ ST_FORW,			EV_NW,			ST_FORWLEFT},		// 24
	
	{ ST_FORW,			EV_IDLE,		ST_HALT},				// 25
	{ ST_FORWRIGHT,	EV_IDLE,		ST_HALT},				// 26
	{ ST_RIGHT,			EV_IDLE,		ST_HALT},				// 27
	{ ST_BACKRIGHT,	EV_IDLE,		ST_HALT},				// 28
	{ ST_BACK,			EV_IDLE,		ST_HALT},				// 29
	{ ST_BACKLEFT,	EV_IDLE,		ST_HALT},				// 30
	{ ST_LEFT,			EV_IDLE,		ST_HALT},				// 31
	{ ST_FORWLEFT,	EV_IDLE,		ST_HALT},				// 32
	
	{ ST_FORW,			EV_N,				ST_FORW},				// 33
	{ ST_FORWRIGHT,	EV_NE,			ST_FORWRIGHT},	// 34
	{ ST_RIGHT,			EV_E,				ST_RIGHT},			// 35
	{ ST_BACKRIGHT,	EV_SE,			ST_BACKRIGHT},	// 36
	{ ST_BACK,			EV_S,				ST_BACK},				// 37
	{ ST_BACKLEFT,	EV_SW,			ST_BACKLEFT},		// 38
	{ ST_LEFT,			EV_W,				ST_LEFT},				// 39
	{ ST_FORWLEFT,	EV_NW,			ST_FORWLEFT},		// 40
	
	{ ST_HALT,			EV_OFF,			ST_OFF},				// 41
	{ ST_HALT,			EV_IDLE,		ST_HALT},				// 42
	
	{ ST_OFF,				EV_OFF,			ST_OFF},				// 43
	{ ST_OFF,				EV_N,				ST_OFF},				// 44
	{ ST_OFF,				EV_NE,			ST_OFF},				// 45
	{ ST_OFF,				EV_E,				ST_OFF},				// 46
	{ ST_OFF,				EV_SE,			ST_OFF},				// 47
	{ ST_OFF,				EV_S,				ST_OFF},				// 48
	{ ST_OFF,				EV_SW,			ST_OFF},				// 49
	{ ST_OFF,				EV_W,				ST_OFF},				// 50
	{ ST_OFF,				EV_NW,			ST_OFF},				// 51
	{ ST_OFF,				EV_IDLE,		ST_OFF} 				// 52
};

/* Private function prototypes -----------------------------------------------*/
void SetOff(TRemote *tremote);
void SetHalt(TRemote *tremote);
void SetForw(TRemote *tremote);
void SetForwright(TRemote *tremote);
void SetRight(TRemote *tremote);
void SetBackright(TRemote *tremote);
void SetBack(TRemote *tremote);
void SetBackleft(TRemote *tremote);
void SetLeft(TRemote *tremote);
void SetForwleft(TRemote *tremote);

static TStateFuntionRow atStateFunction[] = {
		// NAME					// Functionn
	{	"ST_OFF",				&SetOff },
	{	"ST_HALT",			&SetHalt },
	{	"ST_FORW",			&SetForw },
	{	"ST_FORWRIGHT",	&SetForwright },
	{	"ST_RIGHT",			&SetRight },
	{	"ST_BACKRIGHT",	&SetBackright },
	{	"ST_BACK",			&SetBack },
	{	"ST_BACKLEFT",	&SetBackleft },
	{	"ST_LEFT",			&SetLeft },
	{	"ST_FORWLEFT",	&SetForwleft }
};

/* User functions -----------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
///
/// Function to run through the State Machine 
///
///	@param 	Ptr to the buffer of data input
/// @param  Ptr to Struct tstateMachine
/// @param  Ptr to Struct tremote
///
/// @return STATE_OK	=		0, STATE_ERROR =	1
/*---------------------------------------------------------------------------*/
TState_Status RunStateIteration(uint8_t *data, TStateMachine *tstateMachine, TRemote *tremote)
{
	int i;
	TEvent tevent;
	
	FindEvent(data, &tevent, tremote);
	
	for(i=0; i < sizeof(atStateMatrix) / sizeof(atStateMatrix[0]); i++)
	{
		if(atStateMatrix[i].currState == tstateMachine->currState)
		{
			if(atStateMatrix[i].event == tevent)
			{
				tstateMachine->currState = atStateMatrix[i].nextState;
				
				(atStateFunction[tstateMachine->currState].func)(tremote);
				return STATE_OK;
			}
		}
	}
	
	tstateMachine->currState = ST_OFF;  // set state of State Machine to default value
																			// because incorrect event occured
	
	(atStateFunction[tstateMachine->currState].func)(tremote);
	
	return STATE_ERROR;
}

/*---------------------------------------------------------------------------*/
///
/// Function to find out the event from input
///
///	@param 	Ptr to the buffer of data input
///	@param 	Ptr to tevent
///	@param 	Ptr to struct of remote
///
/// @return Event which is identified
/*---------------------------------------------------------------------------*/
void FindEvent(uint8_t *data, TEvent *tevent, TRemote *tremote)
{
	uint8_t temp_buf[1];
	
	temp_buf[0] = *data;
	
	if(temp_buf[0] & ON)
	{
		if(tremote->Ign == B_OFF)	// first press of On Buttton
		{													// used to set Event to On (EV_ON)
			*tevent = EV_ON;
			tremote->Ign = B_ON;
			return;
		}
		tremote->Ign = B_ON;
	}
	else											// press of Off Buttton
	{		
		*tevent = EV_OFF;
		tremote->Ign = B_OFF;
		tremote->Joystick = ST_OFF;
		return;
	}
	
	if(temp_buf[0] & FAST)
		tremote->Drivespeed = B_FAST;
	else
		tremote->Drivespeed = B_SLOW;
	
	if(temp_buf[0] & VIBR)
		tremote->Drivemode = B_VIBR;
	else
		tremote->Drivemode = B_NORMAL;
	
	temp_buf[0] &= JOYSTICK;
				
	switch(temp_buf[0]) 
	{
		case	FORW:
			*tevent = EV_N;
			break;
		case FORWR:
			*tevent = EV_NE;
			break;
		case	RIGTH:
			*tevent = EV_E;
			break;
		case	BACKR:
			*tevent = EV_SE;
			break;
		case	BACK:
			*tevent = EV_S;
			break;
		case	BACKL:
			*tevent = EV_SW;
			break;
		case	LEFT:
			*tevent = EV_W;
			break;
		case	FORWL:
			*tevent = EV_NW;
			break;
		case	HALT:
			*tevent = EV_IDLE;
			break;
		default:
			*tevent = EV_IDLE;
			break;	
	}
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and stop the engine
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetOff(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_RESET); 			// ativate IGN Output
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);			// turn LED 2 off
	HAL_GPIO_WritePin(EN_OUT_GPIO_Port, EN_OUT_Pin, GPIO_PIN_RESET);// Disable Outputs
	
	HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
	HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_RESET); 	//

	HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and stop
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetHalt(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);				// turn LED 2 on
//	HAL_GPIO_WritePin(EN_OUT_GPIO_Port, EN_OUT_Pin, GPIO_PIN_SET);	// Enable Outputs
	HAL_GPIO_WritePin(EN_OUT_GPIO_Port, EN_OUT_Pin, GPIO_PIN_RESET);// Disable Outputs // defect

	HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
	HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
	HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
		
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive forward
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetForw(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive forward right 
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetForwright(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive right
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetRight(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
		
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive back right
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetBackright(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive back
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetBack(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//	
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive back left 
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetBackleft(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_RESET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive left
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetLeft(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_SET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
/// Function to set outputs and drive forward left 
///
///	@param 	Ptr to struct of remote
///
/// @return None
/*---------------------------------------------------------------------------*/
void SetForwleft(TRemote *tremote)
{
	HAL_GPIO_WritePin(IGN_GPIO_Port, IGN_Pin, GPIO_PIN_SET); 				// ativate IGN Output
	
	if(tremote->Drivespeed == B_SLOW)
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	else
	{
		HAL_GPIO_WritePin(INP_1_GPIO_Port, INP_1_Pin, GPIO_PIN_SET); 	// 
		HAL_GPIO_WritePin(INP_2_GPIO_Port, INP_2_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_4_GPIO_Port, INP_4_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_5_GPIO_Port, INP_5_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_6_GPIO_Port, INP_6_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_7_GPIO_Port, INP_7_Pin, GPIO_PIN_RESET); 	//
		HAL_GPIO_WritePin(INP_8_GPIO_Port, INP_8_Pin, GPIO_PIN_SET); 	//
	}
	
	if(tremote->Drivemode == B_VIBR)
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_SET); 	//
	else
		HAL_GPIO_WritePin(INP_3_GPIO_Port, INP_3_Pin, GPIO_PIN_RESET); 	//
}

/*---------------------------------------------------------------------------*/
///
///  This function init Struct of Remote.
///  @param  Struct of Remote
///  @return None
/*---------------------------------------------------------------------------*/
void Remote_Init(TRemote *remote)
{
	remote->Ign = B_OFF;
	remote->Drivespeed = B_SLOW;
	remote->Drivemode = B_NORMAL;
	remote->Joystick = ST_HALT;
	
	return;
}

/*****END OF FILE****/
