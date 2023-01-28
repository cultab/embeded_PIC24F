#ifndef PINS_H
#define PINS_H
// #include "p24FJ1024GB610.h"

/*
 * HACK: Stop clangd from yelling about undeclared identifiers.
 *
 * dummy definitions so static analisis tools don't freak out
 */
#ifdef __clang__/*{{{*/
struct {
    int LATA0;
    int LATA1;
    int LATA2;
    int LATA3;
    int LATA4;
    int LATA5;
    int LATA6;
    int LATA7;
} LATAbits;

struct {
    int TRISA0;
    int TRISA1;
    int TRISA2;
    int TRISA3;
    int TRISA4;
    int TRISA5;
    int TRISA6;
    int TRISA7;

} TRISAbits;
struct {
    int TRISB8;
    int TRISB9;

} TRISBbits;
struct {
    int TRISD6;
    int TRISD7;
    int TRISD13;
} TRISDbits;

struct {
    int RA7;
} PORTAbits;
struct {
    int RD6;
    int RD7;
    int RD13;
} PORTDbits;

struct {
    int ANSD6;
    int ANSD7;
} ANSDbits;
struct {
    int ANSA7;
} ANSAbits;
struct {
    int ADON;
    int SSRC;
    int FORM;
    int MODE12;
    int SAMP;
    int DONE;
} AD1CON1bits;
struct {
    int SMPI;
    int PVCFG;
} AD1CON2bits;
struct {
    int SAMC;
    int ADCS;
} AD1CON3bits;
int AD1CHS;
int ADC1BUF0;
struct {
    int ANSB5;
    int ANSB4;
} ANSBbits;


#endif/*}}}*/



// input and output pins configuration value
#define PIN_INPUT   1
#define PIN_OUTPUT  0

// analog and digital pins configuration value
#define ANALOG      1
#define DIGITAL     0

// LED latches
#define LED_D3_LAT      LATAbits.LATA0
#define LED_D4_LAT      LATAbits.LATA1
#define LED_D5_LAT      LATAbits.LATA2
#define LED_D6_LAT      LATAbits.LATA3
#define LED_D7_LAT      LATAbits.LATA4
#define LED_D8_LAT      LATAbits.LATA5
#define LED_D9_LAT      LATAbits.LATA6
#define LED_D10_LAT     LATAbits.LATA7      //Overlaps with S5
#define LEDs            PORTAbits

#define LED_D3_TRIS     TRISAbits.TRISA0
#define LED_D4_TRIS     TRISAbits.TRISA1
#define LED_D5_TRIS     TRISAbits.TRISA2
#define LED_D6_TRIS     TRISAbits.TRISA3
#define LED_D7_TRIS     TRISAbits.TRISA4
#define LED_D8_TRIS     TRISAbits.TRISA5
#define LED_D9_TRIS     TRISAbits.TRISA6
#define LED_D10_TRIS    TRISAbits.TRISA7    //Overlaps with S5

// Buttons
//      S1  is MCLR button
#define S3_PORT  PORTDbits.RD6       // pullup
#define S6_PORT  PORTDbits.RD7       // no pullup, noisy
#define S5_PORT  PORTAbits.RA7       // no pullup, settels to up after one press, Overlaps with D10, 
#define S4_PORT  PORTDbits.RD13      // pullup

#define S3_TRIS  TRISDbits.TRISD6
#define S6_TRIS  TRISDbits.TRISD7
#define S5_TRIS  TRISAbits.TRISA7
#define S4_TRIS  TRISDbits.TRISD13

#define S3_ANSEL ANSDbits.ANSD6
#define S6_ANSEL ANSDbits.ANSD7
#define S5_ANSEL ANSAbits.ANSA7
//      S4_ANSEL D13 doesn't have an ANSEL
//

// Extra LED and  buzzer
#define LED_EX_REG   PORTBbits.RB8
#define LED_EX_LATCH LATBbits.LATB8
#define LED_EX_TRIS  TRISBbits.TRISB8

#define BUZZER_REG   PORTBbits.RB9
#define BUZZER_LATCH LATBbits.LATB9
#define BUZZER_TRIS  TRISBbits.TRISB9

#endif // PINS_H
