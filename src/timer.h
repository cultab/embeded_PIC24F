// #include <xc.h>
//
#ifndef TIMER_H
#define TIMER_H TIMER_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

// was 1000 but timers were x10 faster than expected
#define TIMER_TICK_INTERVAL_MICRO_SECONDS 10000

/* 
 * Timer
 *
 * See: https://ww1.microchip.com/downloads/en/DeviceDoc/39704a.pdf
 *
 */

#ifdef __clang__/*{{{*/
struct {
    int T3IP;
} IPC2bits;
struct {
    int T3IF;
} IFS0bits;
int TMR3;
int PR3;
int T3CON;
struct {
    int T3IE;
} IEC0bits;
#endif/*}}}*/

#define TMR3_INTERUPT_PRIORITY IPC2bits.T3IP
#define TMR3_INTERUPT_FLAG     IFS0bits.T3IF
#define TMR3_INTERUPT_ENABLE   IEC0bits.T3IE

#define TMR3_COUNT_REGISTER   TMR3
#define TMR3_PERIOD_REGISTER  PR3
#define TMR3_CONTROL_REGISTER T3CON

/* Type Definitions ***********************************************/
typedef void (*TICK_HANDLER)(void);

typedef enum
{
    TIMER_CONFIGURATION_1MS,
    TIMER_CONFIGURATION_OFF
} TIMER_CONFIGURATIONS;

void TIMER_CancelTick(const TICK_HANDLER handle);
bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate);
bool TIMER_SetConfiguration(TIMER_CONFIGURATIONS configuration);

#endif //TIMER_H
