 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
� [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

/* Simple sensor monitor: RA1, RA2, RC0..RC5, in that order.
 * Connect RA5/TX to a 3.3 V USB-UART adapter RX and share ground.
 * Monitor: 115200 baud, 8 data bits, no parity, 1 stop bit, no flow control.
 * Raw single-ended ADC counts use VDD as the reference (0..4095).
 * Keep application changes here; MCC owns mcc_generated_files.
 */
#define SENSOR_COUNT 8U

static const adc_channel_t sensorChannels[SENSOR_COUNT] = {
    ADC_CHANNEL_ANA1, ADC_CHANNEL_ANA2,
    ADC_CHANNEL_ANC0, ADC_CHANNEL_ANC1, ADC_CHANNEL_ANC2,
    ADC_CHANNEL_ANC3, ADC_CHANNEL_ANC4, ADC_CHANNEL_ANC5
};

/* Also available in a debugger watch window when execution is halted. */
volatile uint16_t sensorValues[SENSOR_COUNT];

static void Monitor_WriteChar(char value)
{
    while (!EUSART1_IsTxReady())
    {
    }
    EUSART1_Write((uint8_t)value);
}

static void Monitor_WriteText(const char *text)
{
    while (*text != '\0')
    {
        Monitor_WriteChar(*text++);
    }
}

/* Fixed-width decimal avoids the code and RAM overhead of printf. */
static void Monitor_WriteValue(uint16_t value)
{
    Monitor_WriteChar((char)('0' + value / 1000U));
    Monitor_WriteChar((char)('0' + (value / 100U) % 10U));
    Monitor_WriteChar((char)('0' + (value / 10U) % 10U));
    Monitor_WriteChar((char)('0' + value % 10U));
}

int main(void)
{
    uint8_t sensor;

    SYSTEM_Initialize();
    /* TX uses the generated interrupt-driven UART driver. RX is unused. */
    EUSART1_ReceiveDisable();
    EUSART1_ReceiveInterruptDisable();
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();

    __delay_ms(100);
    Monitor_WriteText("\r\nCuff sensor test - raw ADC counts\r\n");

    while (1)
    {
        for (sensor = 0; sensor < SENSOR_COUNT; sensor++)
        {
            ADC_ChannelSelect(sensorChannels[sensor]);
            /* MCC acquisition time is zero; allow settling after switching.
             * High-impedance sensors may need a longer delay or buffering.
             */
            __delay_us(50);
            ADC_ConversionStart();
            while (!ADC_IsConversionDone())
            {
            }
            sensorValues[sensor] = (uint16_t)ADC_ConversionResultGet();
        }

        for (sensor = 0; sensor < SENSOR_COUNT; sensor++)
        {
            Monitor_WriteChar('R');
            Monitor_WriteChar(sensor < 2U ? 'A' : 'C');
            Monitor_WriteChar((char)('0' + (sensor < 2U ? sensor + 1U : sensor - 2U)));
            Monitor_WriteChar('=');
            Monitor_WriteValue(sensorValues[sensor]);
            Monitor_WriteChar(sensor == SENSOR_COUNT - 1U ? '\r' : ' ');
        }
        Monitor_WriteChar('\n');

        __delay_ms(250);
    }
}
