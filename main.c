/*
 * 
 * TODO:
 * Buzzer pin on P34 (pin34 aka register RB10)
 * Secondary led for alarm
 * 
 * 
 * 
 * 
 * NOTES:
 * - temp
 * - timer 10 or 1?
 * - pins for buzzer
 * - adc.h thing
 * 
 * 
 */

#include <xc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
// #include <libpic30.h>

// define system clock at 4MHz (for LCD and TMR{1-3})
#define SYSTEM_PERIPHERAL_CLOCK 4000000


#include "src/led.h"
#include "src/button.h"
#include "src/timer.h"
#include "src/adc.h"
#include "src/lcd.h"
#include "src/uart2.h"
#include "src/pins.h"


#define MAX_SECONDS 600 /* 600 seconds = 10 minutes */

#define BUTTON_EVENT_TIME    10 /* ms */
#define LCD_UPDATE_TIME     500 /* ms */
#define ONE_SECOND         1000 /* ms */

#define BUZZER_FREQUENCY    500 /* Hz */
#if ( BUZZER_FREQUENCY > 1000 ) /* at most 1000Hz aka 1ms period */
#define BUZZER_FREQUENCY 1000
#endif

#define forever for(; ;) /* fun */

#define MAX_SNOOZE   5                 /* amount of times user has to snooze for alarm to stop */
#define SNOOZE_TIME 10                 /* 10 second snooze */
#ifndef SNOOZE_TIME                    /* if no time set */
#define SNOOZE_TIME SECONDS_SELECTED   /* use user selected long snooze */
#endif

static uint16_t SECONDS_REMAINING = 0; /* seconds user has currently selected */
static uint16_t SECONDS_SELECTED =  0; /* seconds timer is at, when counting down */
static uint16_t SNOOZE_COUNT =      0; /* how many times the user has snoozed the alarm */

/*
 * State of the alarm,
 * SELECT_TIME:   the user is selecting the time for the alarm
 * COUNTING_DOWN: the timer is counting down
 * SNOOZED:       the timer is counting down after the alarm has gone off and the user snoozed it
 * ALARM:         the timer counted down and is now going off (buzzer sounds and led blinks)
 */
static enum State {
    SELECT_TIME,
    COUNTING_DOWN,
    SNOOZED,
    ALARM,
} STATE = SELECT_TIME;

/*
 * Convert enum to string
 */
static const char * const STATE_STRING[] = {
	[SELECT_TIME] = "Select",
	[COUNTING_DOWN] = "Cntdwn",
	[SNOOZED] = "Snooze",
	[ALARM] = "Alarm"
};


static void  update_state(void);  // update state
static void  check_buttons(void); // check for pressed buttons
static void  start_alarm(void);   // register handlers in timer for led blink and buzzer
static void  stop_alarm(void);    // unregister tick and turn led off
static void  blink_led(void);     // blink led
static void  buzz_buzzer(void);   // make sound
static void  update_lcd(void);    // update information on LCD
static float adc_to_celcius(int mV); // convert temperature sensor output from adc to celsius


int main(void) {
    // initialize the device
//     initU2(); /* for debugging */
    LCD_Initialize();
    init_button(BUTTON_EVENT_TIME * 10); // debounce of 10 cycles

    // init ADC
    ADC_SetConfiguration(ADC_CONFIGURATION_DEFAULT);
    // enable temperature sensor channel
    ADC_ChannelEnable(ADC_CHANNEL_TEMPERATURE_SENSOR);

    // init and enable LED and Speaker pins
    {
        LED_EX_TRIS = PIN_OUTPUT;
        LED_EX_REG = 1;
        BUZZER_TRIS = PIN_OUTPUT;
        BUZZER_REG = 0;
    }
    
    // enable the status led
    LED_Enable(LED_D3);

    // setup timers
    TIMER_SetConfiguration(TIMER_CONFIGURATION_1MS);
    TIMER_RequestTick(&update_state, ONE_SECOND);
    TIMER_RequestTick(&check_buttons, BUTTON_EVENT_TIME);
    TIMER_RequestTick(&update_lcd, LCD_UPDATE_TIME);

    forever { /* do nothing */  }
}

static void update_state(void) {
    LED_Toggle(LED_D3);
    // printf("Remaining: %d seconds\n" "State: %s\n", SECONDS_REMAINING, STATE_STRING[STATE]); /* for debugging */
    
    switch(STATE) {
    case COUNTING_DOWN: {
        if (SECONDS_REMAINING) {
            SECONDS_REMAINING--;
        } else {
            start_alarm();
            STATE = ALARM;
        }
        break;
    }
    case SNOOZED: {
        /* if snoozed 5 times,
         * go back to SELECT_TIME
         * and reset SECONDS_REMAINING and SNOOZE_COUNT
         */
        if (SNOOZE_COUNT == 5) {
            STATE = SELECT_TIME;
            SECONDS_REMAINING = 0;
            SNOOZE_COUNT = 0;
        } else if (SECONDS_REMAINING) {
        // else if there is still time, count down
            SECONDS_REMAINING--;
        } else {
        // else start the alarm
            start_alarm();
            STATE = ALARM;
            SNOOZE_COUNT++;
        }
        break;    
    }
    case ALARM:       /* fallthrough */
    case SELECT_TIME: /* fallthrough */
    default:
        break;
    }
                
}

/*
 * STATE must be set to ALARM just after calling
 * to make sure the handlers don't get Requested more than once from the timer
 * 
 * Schedules handlers to toggle the LED and sound the buzzer/speaker.
 * 
 */
static void start_alarm(void) {
    if (STATE != ALARM) {
        TIMER_RequestTick(&blink_led, ONE_SECOND);
        TIMER_RequestTick(&buzz_buzzer, 1000/BUZZER_FREQUENCY); /* T(sec) = 1/f(Hz) */
    }
}

/*
 * Removes LED toggle and buzzer handlers
 * and turns the LED and buzzer off.
 */
static void stop_alarm(void) {
    TIMER_CancelTick(&blink_led);
    TIMER_CancelTick(&buzz_buzzer);
    LED_EX_LATCH = 0;
    BUZZER_LATCH = 0;
}

// toggles led's latch
static void blink_led(void) {
    LED_EX_LATCH ^= 1;
}

// toggles buzzer's latch
static void buzz_buzzer(void) {
    BUZZER_LATCH ^= 1;
}

// degree character hex value
#define CHAR_DEGREE 0xDF

static void update_lcd(void) {
    // read from ADC
    uint16_t value = ADC_Read12bit(ADC_CHANNEL_TEMPERATURE_SENSOR);
    // convert adc value to temperature
    float temp = adc_to_celcius(value);

    printf("\f"); // clear screen
    printf("171014, %5.2f%cC\n\r", (double)temp, CHAR_DEGREE); // print AM, temperature and degree symbol, cast to double to silence warning
    printf("%s", STATE_STRING[STATE]);                 // print state
    switch(STATE) {
        case SELECT_TIME: {
            printf(": %ds", SECONDS_SELECTED);          // print selected time
            break;
        }
        case SNOOZED: {
            printf(" %d/%d: %ds", SNOOZE_COUNT + 1, MAX_SNOOZE, SECONDS_REMAINING); // print snooze count and remaining time
            break;
        }
        default: {
            printf(": %ds", SECONDS_REMAINING);         // print remaining time
            break;
        }
    }
    
}
/*
 * S5 (RA7) increase timer
 * S4(RD13) decrease timer
 * S3 (RD6) enter
 */
static void check_buttons(void) {
    if (debounce_button_pressed(BUTTON_S5)) {
        /* do UP action*/
        if (SECONDS_SELECTED < MAX_SECONDS)
            SECONDS_SELECTED += 10;
    }

    if (debounce_button_pressed(BUTTON_S4)) {
        /* do DOWN action*/
        if (SECONDS_SELECTED > 0)
            SECONDS_SELECTED -= 10;
    }

    if (debounce_button_pressed(BUTTON_S3)) {
        /* do ENTER/SNOOZE action*/
        switch (STATE) {
            // if we are selecting the time, ENTER starts the countdown
            case SELECT_TIME: {
                STATE = COUNTING_DOWN;
                SECONDS_REMAINING = SNOOZE_TIME;
                break;
            }
            // if we are sounding the alarm, ENTER snoozes the alarm
            case ALARM: {
                stop_alarm();
                SECONDS_REMAINING = SNOOZE_TIME;
                STATE = SNOOZED;
            }
            default:
                break;
        }
    }
}

/* 
 * TC1047/TC1047A temperature sensor 
 *
 * See: https://ww1.microchip.com/downloads/aemDocuments/documents/APID/ProductDocuments/DataSheets/21498D.pdf
 * 
 * adc(int) / 4096 = mV / (Vref+ - Vref-)
 * mV = (adc / 4096) * (Vref+ - Vref-) (1)
 *
 * Vout(mV) = 10mV * T(C) + 500
 * temp(C) = (Vout(mV) - 500) / 10 (2)
 *
 * 
 * from (1), (2)
 *
 * T(C) = {[(adc/4096) * (Vref+ - Vref-)] - 500} / 10
 *
 */
static float adc_to_celcius(int value) {
    const float Vrefp = 3300.0f; // mV
    const float Vrefn = 0.0f;    // mV
    const float adc_stages = 4096.f; // for 12bit mode of adc
    float mV = (value * Vrefp - Vrefn) / adc_stages; // convert adc output to millivolts
    return (mV - 500) / 10;                          // convert millivolts to Celcius
}
