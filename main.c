/*
 * File:   main.c
 * Author: panos
 *
 * Created on November 1, 2019, 6:54 PM
 */

// #include "xc.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// #include <libpic30.h>

#include "src/led.h"
#include "src/button.h"
#include "src/timer.h"
#include "src/adc.h"

#define MAX_SECONDS 600 /* 10 minutes */

#define BUTTON_EVENT_TIME   25 /* ms */
#define LCD_UPDATE_TIME    100 /* ms */
#define TIMER_TIME        1000 /* ms */

#define forever for(; ;)


static uint16_t SECONDS_REMAINING = 0;
static float TEMPERATURE = 0.0f;

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
static void update_lcd(void);
static void update_temperature(void);
static float adc_to_celcius(int mV);


int main(void) {
    // initialize the device
    // initU2(); /* for debugging */
    init_button(BUTTON_EVENT_TIME);

    // init ADC
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    ADC_ChannelEnable(ADC_CHANNEL_TEMPERATURE_SENSOR);

    // setup timers
    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    TIMER_RequestTick(&timer_check, TIMER_TIME);
    TIMER_RequestTick(&button_event, BUTTON_EVENT_TIME);
    TIMER_RequestTick(&update_lcd, LCD_UPDATE_TIME);

    forever { /* do nothing */  }
}

static void timer_check(void) {
    LED_Toggle(LED_D3);
    // printf("Remaining: %d seconds\n" "State: %s\n", SECONDS_REMAINING, STATE_STRING[STATE]); /* for debugging */
    
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

static void update_lcd(void) {
    uint16_t value = ADC_Read12bit(ADC_CHANNEL_TEMPERATURE_SENSOR);
    float temp = adc_to_celcius(value);

    printf("\f"); // clear screen
    printf("171014, %5.2f%cC\n", temp, 0xb0); // print AM and temperature
    printf("Remaining time[%s%c]: %d\n", STATE_STRING[STATE], SNOOZE_COUNT == 0 ? SNOOZE_COUNT + '0' : ' ', SECONDS_REMAINING); // print state and remaining time
}

static void button_event(void) {
    if (debounce_button_pressed(BUTTON_S3)) {
        /* do UP action*/
        if (SECONDS_REMAINING < MAX_SECONDS)
            SECONDS_REMAINING += 10;
        printf("S3, %d\n", SECONDS_REMAINING);
    }

    if (debounce_button_pressed(BUTTON_S4)) {
        /* do DOWN action*/
        if (SECONDS_REMAINING > 0)
            SECONDS_REMAINING -= 10;
        printf("S4, %d\n", SECONDS_REMAINING);
    }

    if (debounce_button_pressed(BUTTON_S5)) {
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

/* 
 * TC1047/TC1047A temperature sensor 
 *
 * See: https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21498D.pdf
 *
 */
static float adc_to_celcius(int value) {
    /*
     * adc / 4096 = mV / (Vref+ - Vref-)
     * mV = (adc / 4096) * (Vref+ - Vref-) (1)
     *
     * Vout(mV) = 10mV * temp(C) + 500
     * temp(C) = (Vout(mV) - 500) / 10 (2)
     *
     * from (1), (2)
     *
     * temp(C) = {[(adc/4096) * (Vref+ - Vref-)] - 500} / 10
     *
     */
    const float Vrefp = 5.0f;
    const float Vrefn = 0.0f;
    const float adc_stages = 4096.f;
    return (((value/adc_stages) * (Vrefp - Vrefn)) - 500) / 10
    // return (mV - 500) / 10.f;
}
