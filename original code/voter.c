<<<<<<< HEAD:original code/voter.c
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
unsigned int check_keypad(){

}

//function to generate unique passcode
char * passcode_init(size_t length) { //in the future, allow admin to toggle this
	static char charset[] = "ABCD0123456789*#";
	char *randomString = NULL;
	if (length) {
		randomString = malloc(sizeof(char)*(length+1));
		if (randomString) {
			for (int i = 0; i < length; i++) {
				int key = rand() % (int)(sizeof(charset) - 1);
				randomString[i] = charset[key];
			}
			randomString[length] = '\0';
		}
	}
	return randomString;
}

//admin creation
void admin_init(unsigned int number, unsigned int keypad_input) {
	//voter* database = *realloc(database, keypad_input * sizeof(voter));
	voter_num = keypad_input; //specify on display that this includes admin
	voter *admin = (voter*) malloc(sizeof(voter));
	admin->number = number;
	admin->isAdmin = 1;
	admin->passcode = passcode_init(6);
	database[voter_num] = *admin;
	voters_registered++;
}

//new voter
void voter_init(unsigned int number) {
	//check keypad input
	unsigned int keypad_input = check_keypad();
	if (keypad_input != 1111) { //check if keypad input isn't equal to admin_init passcode
		if (voters_registered < 1) {
			//display need an admin
		} else if (voters_registered < voter_num) {
			//display all voters registered
		} else {
			voter *newvoter = (voter*) malloc(sizeof(voter));
			newvoter->number = number;
			newvoter->isAdmin = 0;
			newvoter->passcode = passcode_init(6);
			database[voters_registered] = *newvoter;
			voters_registered++;
		} 
	} else { //initialize admin
		admin_init(number, keypad_input);
	}
}


//verification for new voter validity
//no other voter has that number
//verification for new voter validity. Check that no other voter has that number
unsigned int voter_validate(unsigned int num) {
    int i;
    int result;
    for (i = 0; i < database->length; i = i + 1) {
        if (database[i].number == num) {
            result = 0; 
        }
        else {
            result = 1;
        }
        return result;

//verification of correct passcode

//creation of new random passcode
=======
#include <fsl_device_registers.h> //INCLUDE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
unsigned int check_keypad(){

}

//function to generate unique passcode
char * passcode_init(size_t length) { //in the future, allow admin to toggle this
	static char charset[] = "ABCD0123456789*#";
	char *randomString = NULL;
	if (length) {
		randomString = malloc(sizeof(char)*(length+1));
		if (randomString) {
			for (int i = 0; i < length; i++) {
				int key = rand() % (int)(sizeof(charset) - 1);
				randomString[i] = charset[key];
			}
			randomString[length] = '\0';
		}
	}
	return randomString;
}

//admin creation
void admin_init(unsigned int number, unsigned int keypad_input) {
	//voter* database = *realloc(database, keypad_input * sizeof(voter));
	voter_num = keypad_input; //specify on display that this includes admin
	voter *admin = (voter*) malloc(sizeof(voter));
	admin->number = number;
	admin->isAdmin = 1;
	admin->passcode = passcode_init(6);
	database[voter_num] = *admin;
	voters_registered++;
}

//new voter
void voter_init(unsigned int number) {
	//check keypad input
	unsigned int keypad_input = check_keypad();
	if (keypad_input != 1111) { //check if keypad input isn't equal to admin_init passcode
		if (voters_registered < 1) {
			//display need an admin
		} else if (voters_registered < voter_num) {
			//display all voters registered
		} else {
			voter *newvoter = (voter*) malloc(sizeof(voter));
			newvoter->number = number;
			newvoter->isAdmin = 0;
			newvoter->passcode = passcode_init(6);
			database[voters_registered] = *newvoter;
			voters_registered++;
		} 
	} else { //initialize admin
		admin_init(number, keypad_input);
	}
}


//verification for new voter validity
//no other voter has that number
//verification for new voter validity. Check that no other voter has that number
unsigned int voter_validate(unsigned int num) {
    int i;
    int result;
    for (i = 0; i < database->length; i = i + 1) {
        if (database[i].number == num) {
            result = 0; 
        }
        else {
            result = 1;
        }
        return result;

//verification of correct passcode

//creation of new random passcode
>>>>>>> 654f689233e03483a46a5a179e6c33db6b422169:voter.c
