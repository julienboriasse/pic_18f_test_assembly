/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K80
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // Initialisation des variables
    uint8_t temps = 0;
    uint8_t rxData;
    uint8_t rxChecked = false;
    uint8_t ledChecked = false;

    for (int i = 0; i < 5; i++) {
        IO_RA5_SetHigh();
        __delay_ms(100);
        IO_RA5_SetLow();
        __delay_ms(100);
    }

    printf("\r\n\r\nCoucou, c'est le PIC18F25K80 qui te parle !\r\n");
    printf("Est-ce que tu peux lire ce message ? (O/N)\r\n\r\n");

    while (rxChecked == false) {
        rxData = EUSART1_Read();

        // On vérifie que le caractère reçu est un O ou un o
        if (rxData == 'o' || rxData == 'O') {
            rxChecked = true;
        } else {
            printf("Tu dois taper la touche O si tu peux lire ce message.\r\n");
        }
    }

    printf("Super, maintenant appuye sur n'importe quelle touche et observe la DEL verte.\r\n");
    printf("Elle devrait clignoter 5 fois.\r\n\r\n");

    while (EUSART1_Read() == 1);

    for (int i = 0; i < 5; i++) {
        IO_RA5_SetHigh();
        __delay_ms(200);
        IO_RA5_SetLow();
        __delay_ms(200);
    }

    printf("Est-ce que la DEL a clignote 5 fois ? (O/N)\r\n\r\n");

    while (ledChecked == false) {
        rxData = EUSART1_Read();

        // On vérifie que le caractère reçu est un O ou un o
        if (rxData == 'o' || rxData == 'O') {
            ledChecked = true;
        } else if (rxData == 'n' || rxData == 'N') {
            printf("Si la DEL n'a pas clignote, demande de l'aide.\r\n");
            printf("Reessayons encore une fois...\r\n");

            for (int i = 0; i < 5; i++) {
                IO_RA5_SetHigh();
                __delay_ms(200);
                IO_RA5_SetLow();
                __delay_ms(200);
            }
            
            printf("Est-ce que la DEL a clignote 5 fois ? (O/N)\r\n\r\n");            
        }
        else {
            printf("Tu dois taper la touche O si la DEL a clignote.\r\n");
        }
    }


    // Message de succès
    printf("Excellent, ta carte fonctionne bien !\r\n");
    printf("Dorenavant, si tu appuyes sur le bouton RB0, la DEL verte s'allume.\r\n");
    printf("Amuse-toi bien...\r\n\r\n");

    while (1) {
        IO_RA5_LAT = !IO_RB0_GetValue();
    }

}
/**
 End of File
 */