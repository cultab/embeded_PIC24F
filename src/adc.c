
// #include <xc.h>

#include <stdint.h>
#include <stdbool.h>

#include "adc.h"

/*********************************************************************
* Function: ADC_ReadPercentage(ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the percentage 
*            of that conversions result (0-100%).
*
* PreCondition: channel is configured via the ADCConfigure() function
*
* Input: ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and 
*        not the names of the ADC pins on the device (as the demo code 
*        may be ported to other boards).
*         i.e. ADC_ReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint8_t indicating the percentage of the result 0-100% or
*         0xFF for an error
*
********************************************************************/
uint8_t ADC_ReadPercentage( ADC_CHANNEL channel )
{
    uint8_t percent;

    switch(channel)
    {
        case ADC_CHANNEL_5:
            break;
      
        case ADC_CHANNEL_4:
            break ;

        default:
            return 0xFF;
    }
    
    //A very crude percentage calculation
    percent = (ADC_Read10bit(channel) / 10);

    if(percent > 100)
    {
        percent = 100;
    }
    return percent;
}

/*********************************************************************
* Function: ADC_Read12bit(ADC_CHANNEL channel);
*
* Overview: Reads the requested ADC channel and returns the 10-bit
*           representation of this data.
*
* PreCondition: channel is configured via the ADCConfigure() function
*
* Input: ADC_CHANNEL channel - enumeration of the ADC channels
*        available in this demo.  They should be meaningful names and
*        not the names of the ADC pins on the device (as the demo code
*        may be ported to other boards).
*         i.e. - ADCReadPercentage(ADC_CHANNEL_POTENTIOMETER);
*
* Output: uint16_t the right adjusted 10-bit representation of the ADC
*         channel conversion or 0xFFFF for an error.
*
********************************************************************/
uint16_t ADC_Read12bit(ADC_CHANNEL channel)
{
    uint16_t i;
    
    switch(channel)
    {
        case ADC_CHANNEL_5:
            break;

        case ADC_CHANNEL_4:
            break ;

        default:
            return 0xFFFF;
    }

    ADC_CHANNEL_REG = channel ;

    // Get an ADC sample
    ADC_SAMPLE_ENABLE_BIT = 1; // start sampling
    for(i=0;i<1000;i++)
    {
        Nop(); //Sample delay, conversion start automatically
    } 

    ADC_SAMPLE_ENABLE_BIT = 0;           //stop sampling
    for(i=0;i<1000;i++)
    {
        Nop(); //Sample delay, conversion start automatically
    }

    while(!ADC_CONVERSION_STATUS_BIT);       //Wait for conversion to complete

    return ADC_RESULT_BUFFER;
}

/*********************************************************************
* Function: bool ADC_ChannelEnable(ADC_CHANNEL channel, ADC_CONFIGURATION configuration);
*
* Overview: Configures the ADC module to specified setting
*
* PreCondition: none
*
* Input: ADC_CHANNEL channel - the channel to enable
*        ADC_CONFIGURATION configuration - the mode in which to run the ADC
*
* Output: bool - true if successfully configured.  false otherwise.
*
********************************************************************/
bool ADC_ChannelEnable(ADC_CHANNEL channel)
{
    switch(channel)
    {
        case ADC_CHANNEL_5:
            ANSBbits.ANSB5 = ANALOG ;

        case ADC_CHANNEL_4:
            ANSBbits.ANSB4 = ANALOG ;
            return true ;

        default:
            return false;
    }
    
    return false;
}

/*********************************************************************
* Function: bool ADC_SetConfiguration(ADC_CONFIGURATION configuration)
*
* Overview: Configures the ADC module to specified setting
*
* PreCondition: none
*
* Input: ADC_CONFIGURATION configuration - the mode in which to run the ADC
*
* Output: bool - true if successfully configured.  false otherwise.
*
********************************************************************/
bool ADC_SetConfiguration(ADC_CONFIGURATION configuration)
{
    if(configuration == ADC_CONFIGURATION_DEFAULT)
    {
        ADC_POSITIVE_VREF_SOURCE = ADC_POSITIVE_VREF_SOURCE_AVDD;
        ADC_CONV_CLOCK = ADC_CONV_CLOCK_VALUE; // see header file
        ADC_SAMPLE_CLOCK_SOURCE_BITS = ADC_SAMPLE_CLOCK_SOURCE_MANUAL_SOFTWARE_CLEAR;
        ADC_AUTO_SAMPLE = ADC_AUTO_SAMPLE_16_ADC_CYCLES;
        ADC_FORMAT = ADC_FORMAT_ABSOLUTE_DECIMAL_UNSIGNED_RIGHT;
        ADC_INTERUPT_SAMPLE = ADC_INTERUPT_SAMPLE_FOR_EVERY_SAMPLE;
        ADC_ON = 1;
        ADC_OPERATION_MODE = ADC_OPERATION_MODE_12BIT;

        return true;
    }
		
    return false;
}
