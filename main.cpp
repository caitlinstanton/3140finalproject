/* Hello World! for the TextLCD Enhanced Library*/

#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"
#include "voter.h"
 
// Host PC Communication channels
Serial pc(USBTX, USBRX); // tx, rx
 
// I2C Communication
I2C i2c_lcd(I2C_SDA,I2C_SCL); // SDA, SCL
 
// SPI Communication
//SPI spi_lcd(p5, NC, p7); // MOSI, MISO, SCLK

// LCD instantiation 
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD16x2, TextLCD::WS0010); // I2C exp: I2C bus, PCF8574 Slaveaddress, LCD Type, Ctrl Type

//DigitalOut myled(LED1); 

DigitalOut ledBlue(LED_BLUE);

// every 2ms runs 6uS for key detection(CPU occupancy is 0.3%/Nucleo-F446RE)
//       output port  W  X  Y  Z
//       Input A      *  0  #  D
//       Input B      7  8  9  C
//       Input C      4  5  6  B
//       Input D      1  2  3  A

//         W   X   Y   Z    A    B   C   D   OUT(WXYZ), IN(ABCD)

Keypad key(D7, D6, D5, D4, D11, D10, D9, D8); //columns, rows
// define key number at main routine
char *const key_table = "?123A456B789C*0#D";  // key_table[0]=? is not used!

int main() {   
   lcd.printf("* to register\n# to enter your passcode and vote");
   lcd.setBacklight(TextLCD::LightOn);
   uint32_t key_num;
   
   while(1) {
        while ((key_num = key.read()) != 0){
            
            char identifier[11] = ""; //limited to 11 chars because thats the max length for a phone number
            int identifier_count = 0; //only incremented when registering new user
            char pass[6] = ""; //limited to 6 chars because thats the max length for passcode
            int pass_count = 0; //only incremented when inputting passcode
            char value = *(key_table + key_num);
            
            if (value == *"*") {
                if ((identifier_count == 0) && (pass_count == 0)) {
                    lcd.printf("Welcome new voter! Enter your phone number to register and press # when done");
                    while ((key_num = key.read()) != 0 && *(key_table + key_num) != *"#") {
                        value = *(key_table + key_num);
                        identifier[identifier_count] = value;   
                    } 
                    //voter_init function    
                }
            } else if (value == *"#") {  
                lcd.printf("Enter your passcode and press # to confirm");
                //call passcode verify function
            }    
            lcd.printf("%c", value);
        }
        wait(0.5);   //for debouncing
    }
}




