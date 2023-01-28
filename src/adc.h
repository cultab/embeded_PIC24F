#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>
#include "pins.h"

/*** ADC Channel Definitions *****************************************/
#define ADC_CHANNEL_POTENTIOMETER ADC_CHANNEL_5
#define ADC_CHANNEL_TEMPERATURE_SENSOR ADC_CHANNEL_4

// reference voltage source
#define ADC_POSITIVE_VREF_SOURCE                      AD1CON2bits.PVCFG
#define ADC_POSITIVE_VREF_SOURCE_INTERNAL_VRH2        0b11
#define ADC_POSITIVE_VREF_SOURCE_INTERNAL_VRH1        0b10
#define ADC_POSITIVE_VREF_SOURCE_EXTERNAL             0b01
#define ADC_POSITIVE_VREF_SOURCE_AVDD                 0b00

// why 0xFF? 0100 0000 and up are reserved???
#define ADC_CONV_CLOCK                                AD1CON3bits.ADCS 
#define ADC_CONV_CLOCK_VALUE                          0xFF

#define ADC_SAMPLE_CLOCK_SOURCE_BITS                  AD1CON1bits.SSRC
// setting to disable automatic sample clock clear
#define ADC_SAMPLE_CLOCK_SOURCE_MANUAL_SOFTWARE_CLEAR 0x0

#define ADC_AUTO_SAMPLE                               AD1CON3bits.SAMC
// number of adc cycles to wait until sampling
#define ADC_AUTO_SAMPLE_16_ADC_CYCLES                 0b10000

// adc output value formatting
#define ADC_FORMAT                                    AD1CON1bits.FORM
#define ADC_FORMAT_FRAC_SIGN_LEFT                     0b11
#define ADC_FORMAT_ABSOLUTE_FRAC_UNSIGN_LEFT          0b10
#define ADC_FORMAT_DECIMAL_SINGED_RIGHT               0b11
#define ADC_FORMAT_ABSOLUTE_DECIMAL_UNSIGNED_RIGHT    0b00

#define ADC_INTERUPT_SAMPLE                           AD1CON2bits.SMPI
// interupt for every sample FIX: do we actually use this interupt?
#define ADC_INTERUPT_SAMPLE_FOR_EVERY_SAMPLE          0x0

// enable the adc
#define ADC_ON                                        AD1CON1bits.ADON

// operation mode/output size
#define ADC_OPERATION_MODE                            AD1CON1bits.MODE12
#define ADC_OPERATION_MODE_12BIT                      0b1
#define ADC_OPERATION_MODE_10BIT                      0b0

// sample enable bit
#define ADC_SAMPLE_ENABLE_BIT                         AD1CON1bits.SAMP
// conversion status bit
#define ADC_CONVERSION_STATUS_BIT                     AD1CON1bits.DONE

// register that sets the channel to use
#define ADC_CHANNEL_REG                               AD1CHS
// buffer containing the converted result value
#define ADC_RESULT_BUFFER                             ADC1BUF0

typedef enum
{
    ADC_CHANNEL_5 = 5,
    ADC_CHANNEL_4 = 4
} ADC_CHANNEL;

typedef enum
{
    ADC_CONFIGURATION_DEFAULT
} ADC_CONFIGURATION;



uint8_t ADC_ReadPercentage(ADC_CHANNEL channel);
uint16_t ADC_Read12bit(ADC_CHANNEL channel);
bool ADC_ChannelEnable(ADC_CHANNEL channel);
bool ADC_SetConfiguration(ADC_CONFIGURATION configuration);

#endif  //ADC_H
