/*
 * File:   main.c
 * Author: panos
 *
 * Created on November 1, 2019, 6:54 PM
 */

#include "xc.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "bsp/buttons.h"
#include "bsp/leds.h"
#include "bsp/timer_1ms.h"
#include "bsp/uart2.h"
#include <libpic30.h>

#define MAX_SECONDS 600 /* 10 minutes */
#define BUTTON_EVENT_TIME 10 /* ms */


static uint16_t BUTTON_DEBOUNCE[5] = {0};
static uint16_t BUTTON_DEBOUNCE_TIME = BUTTON_EVENT_TIME * 2; /* multiples of 10 ms */

static uint16_t TIMER_TIME = 100;

static uint16_t SECONDS_REMAINING = 0;

static enum State {
    SELECT_TIME,
    COUNTING_DOWN,
    SNOOZED,
    ALARM,
} STATE;

static const char * const STATE_STRING[] = {
	[SELECT_TIME] = "Selecting Time",
	[COUNTING_DOWN] = "Counting Down",
	[SNOOZED] = "Snoozed",
	[ALARM] = "Alarm"
};


static uint16_t SNOOZE_COUNT = 0;


static void timer_check(void);
static void button_event(void);
static void start_alarm(void);
static void stop_alarm(void);


int main(void) {
    initU2(); /* for debugging */

    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    TIMER_RequestTick(&timer_check, TIMER_TIME);
    TIMER_RequestTick(&button_event, BUTTON_EVENT_TIME);

    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S4);
    BUTTON_Enable(BUTTON_S5);
    
    while (1) {
    }
}

static void timer_check(void) {
    LED_Toggle(LED_D3);
    printf("Remaining: %d seconds"
           "\nState: %s\n",
            SECONDS_REMAINING,
            STATE_STRING[STATE]);
    
    switch(STATE) {
    case COUNTING_DOWN: {
        if (SECONDS_REMAINING) {
            SECONDS_REMAINING--;
        } else {
            STATE = ALARM;
        }
        break;
    }
    case SNOOZED: {
        if (SNOOZE_COUNT == 5) {
            STATE = SELECT_TIME;
            SECONDS_REMAINING = 0;
            SNOOZE_COUNT = 0;
        } else if (SECONDS_REMAINING) {
            SECONDS_REMAINING--;
        } else {
            STATE = ALARM;
            SNOOZE_COUNT++;
        }
        break;    
    }
    case ALARM: {
        start_alarm();
    }
    case SELECT_TIME: /* fallthrough */
    default:
        break;
    }
                
}

static void start_alarm(void) {
    /* enable some pin */
}

static void stop_alarm(void) {
    /* disable some pin */
}

/* check if button is pressed and not debounced */
static bool check_button_pressed(BUTTON btn) {
    if (BUTTON_IsPressed(btn) && BUTTON_DEBOUNCE[btn] == 0) {
        BUTTON_DEBOUNCE[btn] = BUTTON_DEBOUNCE_TIME;
        return true;

    }
    
    /* always subtract from debounce */
    if (BUTTON_DEBOUNCE[btn] > 0) {
        BUTTON_DEBOUNCE[btn] -= 1;
    }
    
    return false;
}

static void button_event(void) {
    if (check_button_pressed(BUTTON_S3)) {
        /* do UP action*/
        if (SECONDS_REMAINING < MAX_SECONDS)
            SECONDS_REMAINING += 10;
        printf("S3, %d\n", SECONDS_REMAINING);
    }

    if (check_button_pressed(BUTTON_S4)) {
        /* do DOWN action*/
        if (SECONDS_REMAINING > 0)
            SECONDS_REMAINING -= 10;
        printf("S4, %d\n", SECONDS_REMAINING);
    }

    if (check_button_pressed(BUTTON_S5)) {
        /* do ENTER/SNOOZE action*/
        switch (STATE) {
            case SELECT_TIME: {
                STATE = COUNTING_DOWN;
                break;
            }
            case ALARM: {
                stop_alarm();
                SECONDS_REMAINING = 10;
                STATE = SNOOZED;
                SNOOZE_COUNT++;
            }
            default:
                break;
        }
  
        printf("S5, %d\n", SECONDS_REMAINING);
    }
}
