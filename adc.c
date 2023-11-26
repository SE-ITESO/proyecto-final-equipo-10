/*
 * adc.c
 *
 *  Created on: 20 nov. 2023
 *      Author: gabyd
 */
#include "fsl_debug_console.h"
#include "fsl_adc16.h"

#define ADC_INSTANCE         ADC0
#define ADC_CHANNEL_GROUP    0U
#define ADC_USER_CHANNEL     12U //PTB2


void ADC_Init(void)
{
    adc16_config_t adc16ConfigStruct;
    ADC16_GetDefaultConfig(&adc16ConfigStruct);

#ifdef BOARD_ADC_USE_ALT_VREF
    adc16ConfigStruct.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
#endif

    ADC16_Init(ADC_INSTANCE, &adc16ConfigStruct);
    ADC16_EnableHardwareTrigger(ADC_INSTANCE, false);

#if defined(FSL_FEATURE_ADC16_HAS_CALIBRATION) && FSL_FEATURE_ADC16_HAS_CALIBRATION
    if (kStatus_Success == ADC16_DoAutoCalibration(ADC_INSTANCE))
    {
        // Calibración exitosa
    }
    else
    {
        // Error en la calibración
    }
#endif /* FSL_FEATURE_ADC16_HAS_CALIBRATION */
}

uint16_t ADC_Read(void)
{
    adc16_channel_config_t adc16ChannelConfigStruct;

    adc16ChannelConfigStruct.channelNumber                        = ADC_USER_CHANNEL;
    adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

    ADC16_SetChannelConfig(ADC_INSTANCE, ADC_CHANNEL_GROUP, &adc16ChannelConfigStruct);

    while (0U == (kADC16_ChannelConversionDoneFlag &
                  ADC16_GetChannelStatusFlags(ADC_INSTANCE, ADC_CHANNEL_GROUP)))
    {
        // Espera a que la conversión esté completa
    }

    return ADC16_GetChannelConversionValue(ADC_INSTANCE, ADC_CHANNEL_GROUP);
}
