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
 *  Updated for ECE 3140 by Caitlin Stanton and Orby Egboga
 *  May 2018
 */
#include "mbed.h"
#include "Keypad.h"

//extern Serial pc;
//extern DigitalOut my_led;

Keypad::Keypad(
    PinName kw, PinName kx, PinName ky, PinName kz,
    PinName ka, PinName kb, PinName kc, PinName kd
)
{
    k_in[0]  = new DigitalIn (ka, PullUp);
    k_in[1]  = new DigitalIn (kb, PullUp);
    k_in[2]  = new DigitalIn (kc, PullUp);
    k_in[3]  = new DigitalIn (kd, PullUp);
    k_out[0] = new DigitalOut (kw);
    k_out[1] = new DigitalOut (kx);
    k_out[2] = new DigitalOut (ky);
    k_out[3] = new DigitalOut (kz);
    *k_out[0] = 1;
    *k_out[1] = 1;
    *k_out[2] = 1;
    *k_out[3] = 1;
    uint8_t j,i;
    for (j = 0; j < 4; j++){
        for(i = 0; i < 4; i++){
            key_transent_cntr[j][i] = CHNG_CNT;
            key_state[j][i] = Off_state;
        }
    }
    for(i = 0; i < BF_SIZE; i++){
        buf[i] = 0;
    }
    read_addr = 0;
    write_addr = 0;
    tk.attach_us(callback(this, &Keypad::key_scan), 2000);     // 2mS
}

void Keypad::key_scan(void)
{
    //my_led = 1;
    for (int32_t j = 0; j < 4; j++){
        *k_out[0] = 1;   *k_out[1] = 1;  *k_out[2] = 1; *k_out[3] = 1;
        *k_out[j] = 0;
        wait_us(1);
        for (int32_t i = 0; i < 4; i++){
            switch (key_state[j][i]){
                case Off_state:
                    //my_led = 1;
                    if (*k_in[i] == 0){ // key on
                        key_state[j][i] = Off_to_on_transient;
                        key_transent_cntr[j][i] = CHNG_CNT;
                    }
                    break;
                case Off_to_on_transient:
                    //my_led = 1;
                    if (*k_in[i] == 0){ // key on
                        if (--key_transent_cntr[j][i] < -CHNG_CNT){
                            //my_led = 1;
                            bf_put(j * 4 + i + 1); // save data into buffer
                            key_state[j][i] = On_state;
                        }
                    } else {    // key off
                        if (++key_transent_cntr[j][i] > CHNG_CNT){
                            key_state[j][i] = Off_state;
                        }
                    }
                    break;
                case On_state:
                    //my_led = 1;
                    if (*k_in[i] == 1){ // key off
                        key_state[j][i] = On_to_off_transient;
                        key_transent_cntr[j][i] = -CHNG_CNT;
                    }
                    break;
                case On_to_off_transient:
                    //my_led = 1;
                    if (*k_in[i] == 0){ // key on
                        if (--key_transent_cntr[j][i] < -CHNG_CNT){
                            key_state[j][i] = On_state;
                        }
                    } else {    // key off
                        if (++key_transent_cntr[j][i] > CHNG_CNT){
                            key_state[j][i] = Off_state;
                        }
                    }
                    break;
                default:    // just in case
                    key_state[j][i] = Off_state;
                    break;
            }
            //my_led = 0;
        }
    }
    *k_out[0] = 1;   *k_out[1] = 1;  *k_out[2] = 1; *k_out[3] = 1;
    //my_led = 0;
}

uint8_t Keypad::read(void)
{
    return bf_get();
}

void Keypad::bf_put(char dt)
{
    uint8_t next = write_addr + 1;
    if (next == BF_SIZE) {
        next = 0;
    }
    buf[write_addr] = dt;
    write_addr = next;
}

int8_t Keypad::bf_get (void){
    if (read_addr == write_addr){
        return 0;
    }
    uint8_t dt = buf[read_addr];
    ++read_addr;
    if (read_addr == BF_SIZE){
        read_addr = 0;
    }
    return dt;
}
