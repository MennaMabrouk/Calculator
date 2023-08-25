#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

#define KPD_PORT  		    Port_D

#define KPD_NO_PRESSED_KEY  0xFF

// Define pins

#define KPD_COLUMN_0  Pin0
#define KPD_COLUMN_1  Pin1
#define KPD_COLUMN_2  Pin2
#define KPD_COLUMN_3  Pin3

#define KPD_ROW_0	  Pin4
#define KPD_ROW_1  	  Pin5
#define KPD_ROW_2  	  Pin6
#define KPD_ROW_3  	  Pin7

//ROW AND COLUMN NUMBERS (array) matrix -> 4*4

#define ROW_NUM    4
#define COLUMN_NUM 4

//VALUES OF ARRAY (keypad)

#define KPD_ARR_VAL {{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'C',0,'=','+'}}


#endif
