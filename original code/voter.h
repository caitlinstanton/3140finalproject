#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char * passcode; //uniquely generated passcode
    unsigned int number; //identifying information
    unsigned int isAdmin; //1 -> admin, 0 -> not admin
} voter;

static unsigned int voters_registered = 0; //global variable to track the number of voters registered
static unsigned int voter_num; //global variable initialized to the total number of voters expected
voter database [1]; //array used to hold all voter objects that have been registered

//function to check keypad input
unsigned int check_keypad();

//function to generate unique passcode
char * passcode_init(size_t length);

//admin creation
void admin_init(unsigned int number, unsigned int keypad_input);

//new voter
void voter_init(unsigned int number);


//verification for new voter validity
//no other voter has that number
//verification for new voter validity. Check that no other voter has that number
unsigned int voter_validate(unsigned int num);