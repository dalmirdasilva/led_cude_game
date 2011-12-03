/**
 * LedCube Project
 * 
 * interrupt.h
 */

#ifndef __PIC_LEDCUBE_INTERRUPT_H
#define __PIC_LEDCUBE_INTERRUPT_H 1 

#include <signal.h>

DEF_INTHIGH(high_interrupt_vector)
    DEF_HANDLER(SIG_TMR0, timer_0_handler)
END_DEF

uint16_t ps = 0;
uint8_t layer = 0;

/*
 * Multiplexer/framebuffer routine
 * 
 * This function is called by an interrupt generated by timer 0.
 */
SIGHANDLER(timer_0_handler) {
  
    // Loop control
    unsigned char i;
  
    // Clear interrupt flag
    INTCONbits.T0IF = 0;

    // Toggle led 0 every 1000 interruptions
    if(ps++ == 1000) {
        LED0 ^= 1;
        ps = 0;
    }
            
    // Disabling all layers. 
    LAYER_ENABLE_PIN = 0;

    // Increment the curren_layer counter so that the next layer is
    // drawn the next time this function runs.
    LAYER_SELECT_PORT++;

    // Loop through all 8 bytes of data in the current layer
    // and latch it onto the cube.
    for(i = 0; i < 8; i++) {
          
        // Send the data on the data-bus of the latch array.
        DATA_BUS = cube[LAYER_SELECT_PORT & 0x07][(i + 1) & 0x07];

        // Select the latch
        LATCH_SELECT_PORT++;
    }


    // Enable layers. 
    LAYER_ENABLE_PIN = 1;
}

#endif // __PIC_LEDCUBE_INTERRUPT_H

