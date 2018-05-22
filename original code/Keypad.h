/*
 * Mbed Library / Akizuki AE-KIT45-KEYPAD4X3
 *  http://akizukidenshi.com/catalog/g/gK-12229/
 *
 * Copyright (c) 2017 Kenji Arai / JH1PJL
 *  http://www.page.sannet.ne.jp/kenjia/index.html
 *  http://mbed.org/users/kenjiArai/
 *      Created:    September 27th, 2017
 *      Revised:    December  22nd, 2017
 *
 * 4x4 Fork: Henri Clarke
 *      May 16th, 2018
 *  Updated for ECE 3140 by Caitlin Stanton and Orby Egboga
 *  May 2018
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "mbed.h"

#define  CHNG_CNT       3

class Keypad {
public:
    /** 4x4 keypad interface:
     *  @param key input port           A,B,C,D
     *  @param key output(scan) port    W,X,Y,Z
     */
    Keypad(PinName kw, PinName kx, PinName ky, PinName kz,
           PinName ka, PinName kb, PinName kc, PinName kd);
                    
    /** Read key data into buffer
     *  @param none
     *  @return key number by ASCII code
     */
    uint8_t read(void);

protected:
    DigitalIn   *k_in[4];
    DigitalOut  *k_out[4];
    Ticker      tk;

    // key control
    enum State {Off_state, Off_to_on_transient, On_state, On_to_off_transient};
    volatile State  key_state[4][4];
    volatile int8_t key_transent_cntr[4][4];
    void key_scan(void);
    
    // buffer control
    #define BF_SIZE 16
    uint8_t         read_addr;
    uint8_t         write_addr;
    uint8_t         buf[BF_SIZE];
    void bf_put (char dat);
    int8_t bf_get (void);

};

#endif // KEYPAD_H
