#include "mbed.h"
#include "Keypad.h"
#include "TextLCD.h"
#include "voter.h"

//host PC communication channels
Serial pc(USBTX, USBRX); //tx, rx
//i2c communication
I2C i2c_lcd(I2C_SDA, I2C_SCL); //SDA, SCL
//LCD instantiation
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD20x4);

DigitalOut ledBlue(LED_BLUE);

//define key number at main routine
unsigned int identifier[11];
char passcode[6];
/*char keys[4][4] = { {*"D",*"C",*"B",*"A"},
                    {*"#",*"9",*"6",*"3"},
                    {*"0",*"8",*"5",*"2"},
                    {*"*",*"7",*"4",*"1"}
                    };
enum State {Off_state, Off_to_on_transient, On_state, On_to_off_transient};*/
char *const key_table = "?123A456B789C*0#D"; //key_table[0] isn't used --> ?

int registering = 0;
int voting = 0;

int Avotes = 0;
int Bvotes = 0;

void getPhoneInput() {
    Keypad key = Keypad(D7, D6, D5, D4, D11, D10, D9, D8); //columns, rows
    //lcd.printf("enter #");
    int identifier_count = 11;
    char identifier[11] = "";
    uint32_t key_num;
    int count = 0;
    char value;
    lcd.cls();
    lcd.printf("To register, you must input your phone number!");
    lcd.cls();
    wait(2);
    lcd.printf("Press * when done\nPress # to restart\n");
    while(1) {
        while((key_num = key.read()) != 0) {
            value = *(key_table+key_num);
            switch(value) {
                case '*':
                {
                    ledBlue = 0;
                    char *const pass = voter_init(identifier);
                    lcd.cls();
                    lcd.printf("Thanks for registering!");
                    wait(1);
                    lcd.cls();
                    lcd.printf("Here is your passcode for 3 seconds:\n%s",pass);
                    wait(3);
                    registering = 0;
                    voting = 0;
                    lcd.cls();
                    break;
                }
                case '#':
                {
                    lcd.cls();
                    getPhoneInput();
                    break;
                }
                default:
                {
                    if(count < identifier_count) {
                        if (value != *"#" && value != *"*" && value != *"A" && value != *"B" && value != *"C" && value != *"D" && key_num != 0) {
                            identifier[count] = value;
                            count++;
                            lcd.printf("%c",value);
                        } else {
                            count = identifier_count + 1;
                        }
                    }
                    break; 
                }
                
            }
            wait(0.5);
        }
    }
}

void castVote() {
    if (value == *'A') {
        voting = voting + 1;
        Avotes = Avotes + 1;
        //increment voter_num in voter.c 
        lcd.print("You have cast your \n vote for option A");
    }
    voting = voting + 1;
    Bvotes = Bvotes + 1;
    //increment voter_num in voter.c
    lcd.print("You have cast your \n vote for option B")
}

void displayVotes() {
    lcd.print("Votes for A : %a \n Votes for B: %a ", Avotes, Bvotes)

}

void getPasscode() {
    lcd.cls();
    Keypad key = Keypad(D7, D6, D5, D4, D11, D10, D9, D8); //columns, rows
    //lcd.printf("enter #");
    int passcode_count = 6;
    char passcode[6] = "";
    uint32_t key_num;
    int count = 0;
    char value;
    lcd.printf("Press # when done \ninputting your \npasscode\n");  
    while(1) {
        while((key_num = key.read()) != 0) {
            value = *(key_num + key_table);
            switch(value) {
                case '#':
                    int valid = passcode_validate(passcode);
                    if (valid == 2) {
                        displayVotes();
                    } elif (valid == 1) {
                        castVote();
                    } elif (valid == 0) {
                        lcd.printf("Invalid password!");
                        getPasscode();
                    }
                default:
                    while(count < passcode_count) {
                        key_num = key.read();
                        int value = int(*(key_table + key_num));
                        if (value != *"#" && value != *"*" && key_num != 0) {
                            passcode[count] = value;
                            count++;
                            lcd.printf("%c",value);
                        } else if (value == *"#") {
                            count = passcode_count + 1;   
                        }
                    }
            }   
        }   
    }  
    
    lcd.cls();
    lcd.printf("Get ready to cast your vote!\nInput A or B");
    int usertype= passcode_validate(passcode);
    if (usertype != 0) {
        lcd.cls();
        if (usertype == 2) {
            lcd.printf("Admin access-Vote totals:\nA: %d\nB: %d",Avotes,Bvotes);
        } else {
            lcd.printf("\nCast your vote! A or B?");
            while(1){
                key_num = key.read();
                value = *(key_table + key_num);
                if (value == *"A") {
                    Avotes++;
                } else if (value == *"B") {
                    Bvotes++;
                }
                lcd.cls();
                lcd.printf("Thanks for voting!");
            }
        }
    } else {
        lcd.printf("Invalid passcode!");
    }
}

int main() {
    lcd.setBacklight(TextLCD::LightOn);
    lcd.printf("Press * to receive your code\nPress # to vote");
    Keypad key = Keypad(D7, D6, D5, D4, D11, D10, D9, D8); //columns, rows
    uint32_t key_num;
    char value; 
    while(1) {
        while((key_num = key.read()) != 0) {
            lcd.printf("lol");
            ledBlue = !ledBlue;
            value = *(key_table + key_num);
            switch(value) {
                case '*':
                    char const* pass = passcode_init(6);
                    lcd.cls();
                    lcd.printf("Here is your passcode for 3 seconds:\n%s",pass);
                    wait(3);
                    lcd.cls();
                    lcd.printf("Make sure you don't forget it!");
                    break;
                case '#':
                    getPasscode();
                    break;
                default:
                    lcd.printf("other");   
            }
        }
        wait(0.5);   
    }
}