//Author: Kuldip Maharjan
//Email : kuldipmaharjan@gmail.com
//Anyone can use this code if it helps in their projects or
//for learning programing in mbed besides for commercial purposes


//Simple program for getting message from bluetooth module and printing them on pc terminal
#include "mbed.h"

Serial window_app(D1, D0); // tx, rx
Serial pc(USBTX, USBRX); // tx, rx
int main()
{
    pc.baud(115200);
    window_app.baud(9600);
    pc.printf("start");
    uint8_t buf[128];

    while(1) {
        wait(1);
        if (window_app.readable()) {
            pc.printf("\rsomething is there\n");
            //window_app.scanf("%s", buf);
            //pc.printf("%s",buf);
            while (window_app.readable()) {
                pc.printf("%c",window_app.getc());
            }
            pc.printf("\n");
        } else {
            pc.printf("\rnothing is there\n");
            window_app.printf("payo\r");
            window_app.printf("smart mug\r");
            window_app.printf("vostro\r");
            window_app.printf("there is a mug\r");
        }
    }

}