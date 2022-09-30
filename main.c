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
void main(void)
{
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
    
    printf("\r\n\r\nCoucou, c'est le PIC18F25K80 qui te parle !\r\n");
    printf("Est-ce que la DEL verte clignote 5 fois ? ");
    
    __delay_ms(2000);
    
    for (int i=0; i<5 ; i++) {
        IO_RA5_SetHigh();
        __delay_ms(200);
        IO_RA5_SetLow();
        __delay_ms(200);
    }
    
    // Message d'accueil qui permet de v�rifier l'�mission
    printf("(O/N)\r\n\r\n");

    while (rxChecked == false) {
        // On �coute les message en reception
        if (EUSART1_is_rx_ready()) {
            rxData = EUSART1_Read();

            // On v�rifie que le caract�re re�u est un O ou un o
            if (rxData == 'o' || rxData == 'O') {
                rxChecked = true;
                ledChecked = true;
            }
            // On v�rifie que le caract�re re�u est un O ou un o
            else if (rxData == 'n' || rxData == 'N') {
                rxChecked = true;
                ledChecked = false;
            }
            // Si un autre caract�re est re�u, on demande une nouvelle entr�e
            else {
                printf("Tu dois taper la touche O si la DEL verte clignote 5 fois, N sinon.\r\n");
            }
        }
        __delay_ms(10);
    }

    if (ledChecked) {
        // Message qui indique qu'on a v�rifier le RX et le TX
        printf("Excellent, si tu lis ce message, ta carte et ta configuration sont correctes.\r\n");
        printf("La DEL a bien clignote, le PIC est capable d'envoyer et de recevoir des messages sur la liaison serie.\r\n");
        printf("Amuse-toi bien...\r\n\r\n");
    }
    else {
        // Message qui indique qu'on a v�rifier le RX et le TX
        printf("Le PIC est capable d'envoyer et de recevoir des messages sur la liaison serie.\r\n");
        printf("Par contre, tu n'as pas vu la DEL verte clignoter.\r\n");
        printf("Appuye sur le bouton Reset ou debranche et rebranche l'alimentation de ta carte.");
        printf("Si le probleme persiste, demande de l'aide.\r\n\r\n");
    }
    
    // Programme termin�, faire clignoter la DEL lentement
    while (1) {
        IO_RA5_SetHigh();
        __delay_ms(50);
        IO_RA5_SetLow();
        __delay_ms(950);
        
        printf("Fin du programme.\r\n");
    }
    
}
/**
 End of File
*/