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



static void TimerEventHandler(void);
static void button_event(void);

static uint16_t BUTTON_DEBOUNCE[5] = {0};
static uint16_t BUTTON_DEBOUNCE_TIME = BUTTON_EVENT_TIME * 2; /* multiples of 10 ms */


static bool COUNTING_DOWN = false;
static uint16_t SECONDS_REMAINING = 0;

int main(void) {
    initU2(); /* for debugging */

    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    TIMER_RequestTick(&TimerEventHandler, 1000);
    TIMER_RequestTick(&button_event, BUTTON_EVENT_TIME);

    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S4);
    BUTTON_Enable(BUTTON_S5);
    
    while (1) {
//        printf("while(1)\n");
    }
}

static void TimerEventHandler(void) {
    LED_Toggle(LED_D3);
    printf("Remaining %d\n", SECONDS_REMAINING);
    if (COUNTING_DOWN && SECONDS_REMAINING) {
        SECONDS_REMAINING--;
    } else if (!SECONDS_REMAINING) {
        /* timer ended */
        COUNTING_DOWN = false;
        // TODO: sound buzzer and blink LED
    }
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

//static bool check_button_pressed(BUTTON btn) {
//    return BUTTON_IsPressed(btn);
//}

static void button_event(void) {
    if (check_button_pressed(BUTTON_S3)) {
        /* do S3 action*/
        if (SECONDS_REMAINING < MAX_SECONDS)
            SECONDS_REMAINING += 10;
        printf("S3, %d\n", SECONDS_REMAINING);
    }

    if (check_button_pressed(BUTTON_S4)) {
        /* do S4 action*/
        if (SECONDS_REMAINING > 0)
            SECONDS_REMAINING -= 10;
        printf("S4, %d\n", SECONDS_REMAINING);
    }

    if (check_button_pressed(BUTTON_S5)) {
        /* do S5 action*/
        COUNTING_DOWN = true;
        printf("S5, %d\n", SECONDS_REMAINING);
    }
}
