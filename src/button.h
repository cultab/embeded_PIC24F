#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#define BUTTON_PRESSED 0
#define BUTTON_NOT_PRESSED 1

typedef enum {
    BUTTON_NONE,
    BUTTON_S3,
    BUTTON_S6,
    BUTTON_S5,
    BUTTON_S4
        // S1 is MCLR
} BUTTON;

void BUTTON_Enable(BUTTON button);
void init_button(uint16_t timer_ms);
bool debounce_button_pressed(BUTTON btn);
bool BUTTON_IsPressed(BUTTON button);

#endif // BUTTON_H
