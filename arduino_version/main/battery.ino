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

/*ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
static float main_battery_volt_est = 0;
/*ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
static float backup_battery_volt_est = 0;

/*EDIT THESE PARAMETERS (If needed ...) 
 * NOTE the pins are 3.3v tolerant so make sure to keep the calculations in check for max pin voltage else it WILL BURN DOWN THE MCU PERIOD.
 */
static const float MAIN_max_cell_voltage = 4.2;
static const float MAIN_min_cell_voltage = 3.3;

#ifdef DEBUG
static const float MAIN_no_of_cells = 3.0; /*SERIES */
#endif
#ifndef DEBUG
static const float MAIN_no_of_cells = 4.0; /*SERIES */
#endif

static const float MAIN_step_down_factor = 6.0;

static const float BACKUP_max_cell_voltage = 4.2;
static const float BACKUP_min_cell_voltage = 3.5;   /*ALTHOUGH 3.3v using rhis for a safer option*/
static const float BACKUP_no_of_cells = 4.0; /*SERIES */
static const float BACKUP_step_down_factor = 2.0;

/*suggested not to modify beyond 3 to 4 percent*/
static const float percent_tolerance = 2.0; /*BOTH MAX AND MIN used accordingly*/
/*ie for 2 percent max 4.28v and 3.23v min per cell*/


/*DO NOT TOUCH THESE PARAMETERS edit other parameters to change these*/
static const float MAIN_max_pin_voltage = ((MAIN_no_of_cells*MAIN_max_cell_voltage)/(MAIN_step_down_factor))*(1.0+percent_tolerance*0.01);
static const float MAIN_min_pin_voltage = ((MAIN_no_of_cells*MAIN_min_cell_voltage)/(MAIN_step_down_factor))*(1.0-percent_tolerance*0.01);

static const float BACKUP_max_pin_voltage = ((BACKUP_no_of_cells*BACKUP_max_cell_voltage)/(BACKUP_step_down_factor))*(1.0+percent_tolerance*0.01);
static const float BACKUP_min_pin_voltage = ((BACKUP_no_of_cells*BACKUP_min_cell_voltage)/(BACKUP_step_down_factor))*(1.0-percent_tolerance*0.01);


void batteries_init(void){
    /*cause 3.3v max voltage for pin*/
    if(MAIN_max_pin_voltage > 3.2){
        #ifdef DEBUG
        Serial.println("Calculations for max Main battery pin voltage exceed 3.2v");
        Serial3.println("Calculations for max Main battery pin voltage exceed 3.2v");
        
        #endif  
        
        raise_error_signal();
        
    }
 
    pinMode(MAIN_BAT_VOLT_PIN,INPUT_ANALOG);
    pinMode(BACKUP_BAT_VOLT_PIN,INPUT_ANALOG);
    /*SEE IF BACKUP BATTERY IS ALL RIGHT ESTIMATE OF ACTUAL BATTERY VOLTAGE*/
    backup_battery_volt_est = (analogRead(BACKUP_BAT_VOLT_PIN)*ADC_ref_voltage*BACKUP_step_down_factor)/(ADC_resolution);
    if(backup_battery_volt_est < BACKUP_min_cell_voltage){
        
        #ifdef DEBUG
        Serial.println("Struck at backup battery init backup est");
        Serial.println(backup_battery_volt_est);
        Serial3.println("Struck at backup battery init backup est");
        Serial3.print(backup_battery_volt_est);
        Serial3.println(" volts ");
        
        #endif
    
        raise_error_signal();
        
    }
    
    /*SEE IF MAIN BATTERY IS ALL RIGHT ie within range*/
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage*MAIN_step_down_factor)/(ADC_resolution);
    if((main_battery_volt_est <= 3.2*MAIN_step_down_factor) AND (main_battery_volt_est > MAIN_max_pin_voltage*MAIN_step_down_factor) ){
        
        #ifdef DEBUG
        Serial.println("Struck at main battery init");
        Serial3.println("Struck at main battery init");
        #endif
        
    }
}

void check_main_battery_volt(void){
    main_battery_volt_est = (analogRead(MAIN_BAT_VOLT_PIN)*ADC_ref_voltage*MAIN_step_down_factor)/(ADC_resolution);
    #ifdef DEBUG 
    Serial.print("Current main battery voltage");
    Serial.println(main_battery_volt_est);
    #endif
    if(main_battery_volt_est <= MAIN_min_pin_voltage*MAIN_step_down_factor ){
        BATTERY_MAYDAY = true;
    }
    
}
