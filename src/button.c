
// #include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#include "button.h"
#include "pins.h"

static uint16_t BUTTON_DEBOUNCE[5] = {0};
static uint16_t DEBOUNCE_TIME = 0; /* no init */

/* initialize buttons and set debounce time */
void init_button(uint16_t timer_ms) {
    BUTTON_Enable(BUTTON_S3);
    BUTTON_Enable(BUTTON_S4);
    BUTTON_Enable(BUTTON_S5);

    DEBOUNCE_TIME = timer_ms * 2;
}
    
/* check if button is pressed and not debounced */
bool debounce_button_pressed(BUTTON btn) {
    if (BUTTON_IsPressed(btn) && BUTTON_DEBOUNCE[btn] == 0) {
        BUTTON_DEBOUNCE[btn] = DEBOUNCE_TIME;
        return true;

    }
    
    /* always subtract from debounce */
    if (BUTTON_DEBOUNCE[btn] > 0) {
        BUTTON_DEBOUNCE[btn] -= 1;
    }
    
    return false;
}


/*********************************************************************
 * Function: bool BUTTON_IsPressed(BUTTON button);
 *
 * Overview: Returns the current state of the requested button
 *
 * PreCondition: button configured via BUTTON_SetConfiguration()
 *
 * Input: BUTTON button - enumeration of the buttons available in
 *        this demo.  They should be meaningful names and not the names
 *        of the buttons on the silk-screen on the board (as the demo
 *        code may be ported to other boards).
 *         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
 *
 * Output: true if pressed; false if not pressed.
 *
 ********************************************************************/
bool BUTTON_IsPressed ( BUTTON button )
{
    switch(button)
    {
        case BUTTON_S3:
            return ( (S3_PORT == BUTTON_PRESSED) ? true : false);

        case BUTTON_S6:
            return ( (S6_PORT == BUTTON_PRESSED) ? true : false);

        case BUTTON_S5:
            return ( ( S5_PORT == BUTTON_PRESSED ) ? true : false ) ;

        case BUTTON_S4:
            return ( ( S4_PORT == BUTTON_PRESSED ) ? true : false ) ;

        default:
            return false;
    }
    
    return false;
}

/*********************************************************************
* Function: void BUTTON_Enable(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names
*        of the buttons on the silk-screen on the board (as the demo
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: None
*
********************************************************************/
void BUTTON_Enable(BUTTON button)
{
    switch(button)
    {
        case BUTTON_S3:
            S3_TRIS = PIN_INPUT ;
            S3_ANSEL = DIGITAL ;
            break ;

        case BUTTON_S6:
            S6_TRIS = PIN_INPUT;
            S6_ANSEL = DIGITAL ;
            break;

        case BUTTON_S5:
            S5_TRIS = PIN_INPUT ;
            S5_ANSEL = DIGITAL ;
            break ;

        case BUTTON_S4:
            S4_TRIS = PIN_INPUT ;
            //No ANSEL required for D13
            break ;

        default:
            break ;
    }
}

