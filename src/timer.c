
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "timer.h"

#define SYSTEM_PERIPHERAL_CLOCK 8000000

#ifndef SYSTEM_PERIPHERAL_CLOCK
#define SYSTEM_PERIPHERAL_CLOCK 16000000
#pragma message "This module requires a definition for the peripheral clock frequency.  Assuming 16MHz Fcy (32MHz Fosc).  Define value if this is not correct."
#endif


/* Definitions *****************************************************/
// stop while idle (?)
#define STOP_TIMER_IN_IDLE_MODE     0x2000
// oscillator source
#define TIMER_SOURCE_INTERNAL       0x0000
#define TIMER_SOURCE_EXTERNAL       0x0002
// turn timer on
#define TIMER_ON                    0x8000
// (?)
#define GATED_TIME_DISABLED         0x0000

// we use 16bit mode, 32bit mode actually uses 2 timers
#define TIMER_16BIT_MODE            0x0000
#define TIMER_32BIT_MODE            0x0004

// oscillator postscaler or timer prescaler
#define TIMER_PRESCALER_1           0x0000
#define TIMER_PRESCALER_8           0x0010
#define TIMER_PRESCALER_64          0x0020
#define TIMER_PRESCALER_256         0x0030
#define TIMER_INTERRUPT_PRIORITY    0x0001
#define TIMER_INTERRUPT_PRIORITY_4  0x0004

// no prescaler
#define CLOCK_DIVIDER TIMER_PRESCALER_1
// period = 1 / (SYSTEM_PERIPHERAL_CLOCK/ 1000 / 4) = 0.001 sec = 1ms
#define TMR3_PERIOD_SETTING (SYSTEM_PERIPHERAL_CLOCK/TIMER_TICK_INTERVAL_MICRO_SECONDS/4)

#if 0 // disabled, we know that TMR3_PERIOD_SETTING is < 0xFFFF
#if (TMR3_PERIOD_SETTING > 0xFFFF)
#undef CLOCK_DIVIDER
#undef TMR3_PERIOD_SETTING
#define CLOCK_DIVIDER TIMER_PRESCALER_8
#define TMR3_PERIOD_SETTING (SYSTEM_PERIPHERAL_CLOCK/1000/8)
#endif

#if (TMR3_PERIOD_SETTING > 0xFFFF)
#undef CLOCK_DIVIDER
#undef TMR3_PERIOD_SETTING
#define CLOCK_DIVIDER TIMER_PRESCALER_64
#define TMR3_PERIOD_SETTING (SYSTEM_PERIPHERAL_CLOCK/1000/64)
#endif

#if (TMR3_PERIOD_SETTING > 0xFFFF)
#undef CLOCK_DIVIDER
#undef TMR3_PERIOD_SETTING
#define CLOCK_DIVIDER TIMER_PRESCALER_256
#define TMR3_PERIOD_SETTING (SYSTEM_PERIPHERAL_CLOCK/1000/256)
#endif
#endif

/* Compiler checks and configuration *******************************/
#ifndef TIMER_MAX_1MS_CLIENTS
    #define TIMER_MAX_1MS_CLIENTS 10
#endif


/* Type Definitions ************************************************/
typedef struct
{
    TICK_HANDLER handle;
    uint32_t rate;
    uint32_t count;
} TICK_REQUEST;

/* Variables *******************************************************/
static TICK_REQUEST requests[TIMER_MAX_1MS_CLIENTS];
static bool configured = false;

/*********************************************************************
* Function: void TIMER_CancelTick(TICK_HANDLER handle)
*
* Overview: Cancels a tick request.
*
* PreCondition: None
*
* Input:  handle - the function that was handling the tick request
*
* Output: None
*
********************************************************************/
void TIMER_CancelTick(const TICK_HANDLER handle)
{
    uint8_t i;

    for(i = 0; i < TIMER_MAX_1MS_CLIENTS; i++)
    {
        if(requests[i].handle == handle)
        {
            requests[i].handle = NULL;
        }
    }
}

/*********************************************************************
 * Function: bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate)
 *
 * Overview: Requests to receive a periodic event.
 *
 * PreCondition: None
 *
 * Input:  handle - the function that will be called when the time event occurs
 *         rate - the number of ticks per event.
 *
 * Output: bool - true if successful, false if unsuccessful
 *
 ********************************************************************/
bool TIMER_RequestTick ( TICK_HANDLER handle , uint32_t rate )
{
    uint8_t i;
	
    if(configured == false) // early return if unconfigured
    {
        return false;
    }

    for(i = 0; i < TIMER_MAX_1MS_CLIENTS; i++)
    {
        if(requests[i].handle == NULL)
        {
            requests[i].handle = handle;
            requests[i].rate = rate;
            requests[i].count = 0;

            return true;
        }
    }

    return false;
}

/*********************************************************************
 * Function: bool TIMER_SetConfiguration(TIMER_CONFIGURATIONS configuration)
 *
 * Overview: Initializes the timer.
 *
 * PreCondition: None
 *
 * Input:  None
 *
 * Output: bool - true if successful, false if unsuccessful
 *
 ********************************************************************/
bool TIMER_SetConfiguration ( TIMER_CONFIGURATIONS configuration )
{
    switch(configuration)
    {
        case TIMER_CONFIGURATION_1MS:
            memset(requests, 0, sizeof(requests));
            
            TMR3_INTERUPT_PRIORITY = TIMER_INTERRUPT_PRIORITY; // set interrupt priority
            TMR3_INTERUPT_FLAG = 0; // no interrupt right now

            TMR3_COUNT_REGISTER = 0; // reset register to 0

            TMR3_PERIOD_REGISTER = TMR3_PERIOD_SETTING; // set period
            TMR3_CONTROL_REGISTER = TIMER_ON | // set control bits
                    STOP_TIMER_IN_IDLE_MODE |
                    TIMER_SOURCE_INTERNAL |
                    GATED_TIME_DISABLED |
                    TIMER_16BIT_MODE |
                    CLOCK_DIVIDER;

            TMR3_INTERUPT_ENABLE = 1; // enable interrupt

            configured = true;
            return true;

        case TIMER_CONFIGURATION_OFF:
            TMR3_INTERUPT_ENABLE = 0; // disable interrupt
            configured = false;
            return true;
    }

    return false;
}

/****************************************************************************
  Function:
    void __attribute__((__interrupt__, auto_psv)) _T3Interrupt(void)

  Description:
    Timer ISR, used to update application state. If no transfers are pending
    new input request is scheduled.
  Precondition:
    None

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
void __attribute__((__interrupt__, auto_psv)) _T3Interrupt( void )
{
    uint8_t i;

    // for each request, run the handler if .count = .rate
    for(i = 0; i < TIMER_MAX_1MS_CLIENTS; i++)
    {
        if(requests[i].handle != NULL)
        {
            requests[i].count++;
            
            if(requests[i].count == requests[i].rate)
            {
                requests[i].handle();
                requests[i].count = 0;
            }
        }
    }
    
    TMR3_INTERUPT_FLAG = 0;
}
