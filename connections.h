#define KEY_ROWS         				4
#define KEY_COLUMNS      				4

#define KEYPAD_PARTNER_TASK   	TASK_APPLICATION

#define KEY_COL_OUT_1    				PORTC_BIT2
#define KEY_COL_OUT_2    				PORTC_BIT0
#define KEY_COL_OUT_3    				PORTC_BIT4
#define KEY_COL_OUT_4    				PORTC_BIT12

#define KEY_ROW_IN_1    				PORTD_BIT5
#define KEY_ROW_IN_2    				PORTD_BIT7
#define KEY_ROW_IN_3    				PORTD_BIT0
#define KEY_ROW_IN_4    				PORTD_BIT9 

#define INIT_KEY_SCAN()         _CONFIG_PORT_INPUT(D, (KEY_ROW_IN_1 | KEY_ROW_IN_2 | KEY_ROW_IN_3 | KEY_ROW_IN_4));  \
                                GPIOPUR_E |= (KEY_ROW_IN_1 | KEY_ROW_IN_2 | KEY_ROW_IN_3 | KEY_ROW_IN_4);  \
																_CONFIG_PORT_INPUT(C, (KEY_COL_IN_1 | KEY_COL_IN_2 | KEY_COL_IN_3 | KEY_COL_IN_4));
																
#define DRIVE_COLUMN_1()        _DRIVE_PORT_OUTPUT_VALUE(C, KEY_COL_OUT_1, 0)  //drive column 1 output low
#define RELEASE_COLUMN_1()      _SETBITS(C, KEY_COL_OUT_1); \
																_FLOAT_PORT(C, KEY_COL_OUT_1)
#define DRIVE_COLUMN_2()        _DRIVE_PORT_OUTPUT_VALUE(C, KEY_COL_OUT_2, 0)  //drive column 2 output low
#define RELEASE_COLUMN_2()      _SETBITS(C, KEY_COL_OUT_2); \
																_FLOAT_PORT(C, KEY_COL_OUT_2)
#define DRIVE_COLUMN_3()        _DRIVE_PORT_OUTPUT_VALUE(C, KEY_COL_OUT_3, 0)  //drive column 3 output low
#define RELEASE_COLUMN_3()      _SETBITS(C, KEY_COL_OUT_3); \
																_FLOAT_PORT(C, KEY_COL_OUT_3)
#define DRIVE_COLUMN_4()        _DRIVE_PORT_OUTPUT_VALUE(C, KEY_COL_OUT_4, 0)  //drive column 4 output low
#define RELEASE_COLUMN_4()      _SETBITS(C, KEY_COL_OUT_4); \
																_FLOAT_PORT(C, KEY_COL_OUT_4)