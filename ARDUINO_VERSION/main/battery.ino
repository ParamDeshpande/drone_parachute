/*
*  @brief: monitors status of the 2 batteries. IE main and the backup battery.
*
*
*   @param: NULL
*
*/
#define DEBUG

#include "include/battery.h"
#include "include/commons.h"
#include "include/red_pencil.h"

/*GLOBAL VARS*/
bool BATTERY_MAYDAY = false;

/*PRIVATE VARS*/
static const float ADC_resolution = 4096.0; 
static const float ADC_ref_voltage = 3.3; 


static float main_battery_volt_est = 0;
static float backup_battery_volt_est = 0;

/*EDIT THESE PARAMETERS (If needed ...) 
 * NOTE the pins are 3.3v tolerant so make sure to keep the calculations in check for max pin voltage else it WILL BURN DOWN THE MCU PERIOD.
 */
static const float MAIN_max_cell_voltage = 4.2;
static const float MAIN_min_cell_voltage = 3.3;
static const float MAIN_no_of_cells = 4.0; /*SERIES */
static const float MAIN_step_down_factor = 6.0;

static const float BACKUP_max_cell_voltage = 4.2;
static const float BACKUP_min_cell_voltage = 3.5;   /*ALTHOUGH 3.3v using rhis for a safer option*/
static const float BACKUP_no_of_cells = 4.0; /*SERIES */
static const float BACKUP_step_down_factor = 2.0;

/*suggested not to modify beyond 3 to 4 percent*/
static const float percent_tolerance = 2.0; /*BOTH MAX AND MIN used accordingly*/
/*ie for 2 percent max 4.28v and 3.23v min per cell*/


/*DO NOT TOUCH THESE PARAMETERS*/
static const float max_pin_voltage = ((MAIN_no_of_cells*MAIN_max_cell_voltage)/(MAIN_step_down_factor))*(1.0+percent_tolerance*0.01);
static const float min_pin_voltage = ((MAIN_no_of_cells*MAIN_min_cell_voltage)/(MAIN_step_down_factor))*(1.0-percent_tolerance*0.01);

void batteries_init(void){
    /*cause 3.3v max voltage for pin*/
    if(max_pin_voltage > 3.2){
        #ifdef DEBUG
        Serial.println("Calculations for max Main battery pin voltage exceed 3.2v");
        #endif  
        
        raise_error_signal();
        
    }

    pinMode(MAIN_BAT_VOLT_PIN,INPUT_ANALOG);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT_ANALOG);
    /*SEE IF BACKUP BATTERY IS ALL RIGHT*/
    //backup_battery_volt_est = (analogRead(BACKUP_BAT_VOLT_PIN)*ADC_ref_voltage)/(ADC_resolution);
    //if(backup_battery_volt_est < BACKUP_min_cell_voltage){
    //    
    //    #ifdef DEBUG
    //    Serial.println("Struck at backup battery init");
    //    #endif
    //
    //    raise_error_signal();
    //    
    //}
    
    /*SEE IF MAIN BATTERY IS ALL RIGHT*/
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage)/(ADC_resolution);
    if((main_battery_volt_est <= 3.2) AND (main_battery_volt_est > max_pin_voltage) ){
        
        #ifdef DEBUG
        Serial.println("Struck at main battery init");
        #endif
        
        raise_error_signal();
        
    }
}

void check_main_battery_volt(void){
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage)/(ADC_resolution);
    #ifdef DEBUG 
    Serial.print("Current main battery voltage");
    Serial.println(main_battery_volt_est);
    #endif
    if(main_battery_volt_est <= min_pin_voltage ){
        BATTERY_MAYDAY = true;
    }
    
}
