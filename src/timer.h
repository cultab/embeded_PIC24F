// #include <xc.h>
//
#ifndef TIMER_H
#define TIMER_H TIMER_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define TIMER_TICK_INTERVAL_MICRO_SECONDS 1000

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

// interupt priority
#define TMR3_INTERUPT_PRIORITY IPC2bits.T3IP
// whether an interupt is happening
#define TMR3_INTERUPT_FLAG     IFS0bits.T3IF
// enable/disable interupt from timer
#define TMR3_INTERUPT_ENABLE   IEC0bits.T3IE

// register that contains counter for timer
#define TMR3_COUNT_REGISTER   TMR3
// register that contains period value
#define TMR3_PERIOD_REGISTER  PR3
// control register
#define TMR3_CONTROL_REGISTER T3CON

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
