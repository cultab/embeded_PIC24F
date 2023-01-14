#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    LED_NONE,
    LED_D3,
    LED_D4,
    LED_D5,
    LED_D6,
    LED_D7,
    LED_D8,
    LED_D9,
    LED_D10
} LED;

#define LED_COUNT 8

#define LED_ON  1
#define LED_OFF 0

void LED_On(LED led);
void LED_Off(LED led);
void LED_Toggle(LED led);
bool LED_Get(LED led);
void LED_Enable(LED led);
void LED_Enable_all();
void LEDS_Set(uint16_t val_);

