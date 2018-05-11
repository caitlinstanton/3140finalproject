#include "connections.h"

typedef struct {	
} taskTable; 

//performs the scanning function and collects the complete instantaneous key pad state (which keys are presently pressed and which are presently released//
static void fnUpdateInputs(void) {  
	DRIVE_COLUMN_1();
	fnGetCol(0);
	RELEASE_COLUMN_1();
}

//dispatches events for changes that occur
char fnCheckKeyChanges() {
	if (KEY_COL_OUT_1 && KEY_ROW_IN_1) {
		return 1;
	}
}


//polls the system
void fnKey (taskTable *ptrTaskTable) {   //key scan task
	fnUpdateInputs();      //update the present input stage
	fnCheckKeyChanges();   //generate events on changes
}
