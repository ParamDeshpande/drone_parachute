/*
Andy Morgan
Auburn REU on SMART UAVs 2016
Research Director: Dr. Richard Chapman

NOTE: Thank you for your interest in the ballistic parachute recovery system. This project was designed as a maker project for open source utilization
on Unmanned Aerial Systems. Please feel free to change the code available in this file. Each chunk of code is commented for easy changes. This code 
could also use different optimizations according to components use. Please change hardcoded thresholds at your discretion for calibration.
Happy Making!
*/




#include <SoftwareSerial.h>
#include <Servo.h> 


//Voltage Sensor Setup
#define MOTOR_CUTOFF_VOLTAGE 9.5 //voltage at which we will claim our battery to be depleted

// GPS Setup
#define rxGPS 2
#define txGPS 3
#define INSIDE_FLIGHT_ZONE_SIZE 20 //this value is in meters and determines how large our flight zone should be

// Accelerometer Thresholds - THIS DEPENDS ON YOUR POWER SOURCE. YOU HAVE TO CHANGE THESE ACCORDINGLY
#define FREE_FALL_LOW_THRESH 310
#define FREE_FALL_HIGH_THRESH 355

//Servo Motor Attachment
#define SERVO_PIN 4

//Relay Attachments
#define RELAY_ON 1  //This will be used to turn relay on (Active Low)
#define RELAY_OFF 0 //Used to turn the relay off
#define RELAY_PIN 5 

//Build Serial Comm to the GPS
SoftwareSerial serialGPS = SoftwareSerial(rxGPS, txGPS);
Servo myservo;
bool AllowToAttach = true; // allow system to attach to servo

//GPS Location Variables
double NLatitude;
double WLongitude;
double StartingNLatitude;
double StartingWLongitude;
double LatitudeThreshold;
double LongitudeThreshold;
String stringGPS = "";
char bufferIn;

// these constants describe the pins.
const int groundpin = A5;             // analog input pin 4 -- ground
const int powerpin = A1;              // analog input pin 1 -- voltage
const int xpin = A2;                  // x-axis of the accelerometer
const int ypin = A3;                  // y-axis
const int zpin = A4;                  // z-axis (only on 3-axis models)
int xval=0; //values obtained through accelerometer
int yval=0;
int zval=0;

//Voltage Read Variables
const int analogInput = A7;           // voltage from the voltage sensor
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; //  resistor values inside of the voltage sensor (may need calibrated per sensor)
float R2 = 8250.0; // 
int value = 0;

void setup() {
    //Declare pins for GPS communication
    pinMode(rxGPS, INPUT);
    pinMode(txGPS, OUTPUT);
  
    //Initialize Pins so relays are inactive at reset
    digitalWrite(RELAY_PIN, RELAY_OFF);
  
    //THEN set pins as outputs  
    pinMode(RELAY_PIN, OUTPUT);   
    digitalWrite(RELAY_PIN, RELAY_OFF); //used for redundancy purposes
    
    //Serial Out Setup
    Serial.begin(9600);
    Serial.println("Started");
  
    // GPS Setup
    serialGPS.begin(38400);
    digitalWrite(txGPS,HIGH);
  
    // Attach the needed power to the accelerometer
    pinMode(groundpin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    digitalWrite(groundpin, LOW); //we can do this since our accelerometer does not need much juice. To be more consistent, we can connect ground and power to
    digitalWrite(powerpin, HIGH); //the main 5V and GND from the arduino to keep from calibration. 
  
    //Voltage Sensor Setup
    pinMode(analogInput, INPUT);
  
    // Attach servo pin to the board
    myservo.attach(SERVO_PIN);
    myservo.write(80);  // set servo to closed
    delay(300); // allow it to fully close
    myservo.detach(); 
    //the arduino nano used for this project does not have the computational power to maintain a strict
    //pwm signal and a serial communications signal (for the GPS). We will detach it due to this fact, then reattach later when utilized
  
    //Setup GPS and wait for signal. Calculate Airpsace requirements
    calibrateGPS(); 
  
    //Allow power to the UAV
    digitalWrite(RELAY_PIN, RELAY_ON); //enable UAV to power up
} // end setup

void loop()
{

      getGPSData();
      getAccelValues();
    
    
      //Determine if parachute needs to be deployed... Deployed When:
      // - In free fall
      // - Outside of flight zone
      // - Battery voltage is too low
    if((xval<FREE_FALL_HIGH_THRESH &&xval >FREE_FALL_LOW_THRESH) &&  (yval<FREE_FALL_HIGH_THRESH &&yval >FREE_FALL_LOW_THRESH) && (zval<FREE_FALL_HIGH_THRESH &&zval >FREE_FALL_LOW_THRESH)){ 
               Serial.println("We are in freefall..."); 
               delay(200);
               getAccelValues();
               if((xval<FREE_FALL_HIGH_THRESH &&xval >FREE_FALL_LOW_THRESH) &&  (yval<FREE_FALL_HIGH_THRESH &&yval >FREE_FALL_LOW_THRESH) && (zval<FREE_FALL_HIGH_THRESH &&zval >FREE_FALL_LOW_THRESH))
                     deployParachute();
      }
    
    if((NLatitude > StartingNLatitude+LatitudeThreshold || NLatitude < StartingNLatitude-LatitudeThreshold) || (WLongitude > StartingWLongitude+LongitudeThreshold || WLongitude < StartingWLongitude-LongitudeThreshold)){
               Serial.println("We are outside our airspace..."); 
               deployParachute();
      }
    
    if( getBatteryVoltage() < MOTOR_CUTOFF_VOLTAGE ){
               Serial.println("Battery low..."); 
               deployParachute();  
      }

  
} //end loop

//--------------------------------------------------------------------
//                         Servo Functions
//--------------------------------------------------------------------
//Here we will deploy parachute and cut power to the motors on the drone
void deployParachute(){
   if(AllowToAttach){
        myservo.attach(SERVO_PIN);
        myservo.write(0);  // set servo to open
        digitalWrite(RELAY_PIN, RELAY_OFF); //turn power off to the UAV so that only the backup system is running
        delay(300);
        myservo.detach(); 
        AllowToAttach=false;
      }
}

//--------------------------------------------------------------------
//                    Voltage Sensor Functions
//--------------------------------------------------------------------
//We will determine the current voltage of the battery
float getBatteryVoltage(){
         // read the value at analog input
         value = analogRead(analogInput);
         vout = (value * 5.0) / 1024.0; // see literature on arduino nano
         vin = vout / (R2/(R1+R2)); 
         
         //Serial.print("INPUT V= ");
         //Serial.println(vin,2);
}

//--------------------------------------------------------------------
//                     Acclerometer Functions
//--------------------------------------------------------------------
void getAccelValues(){ // I recommend leaving prints available for calibration
          // print the sensor values:
          xval = analogRead(xpin);
          yval = analogRead(ypin);
          zval = analogRead(zpin);
          Serial.print(xval);
          // print a tab between values:
          Serial.print("\t");
          Serial.print(yval);
          // print a tab between values:
          Serial.print("\t");
          Serial.print(zval);
          
          Serial.println();
}


//--------------------------------------------------------------------
//                          GPS Functions
//--------------------------------------------------------------------

//Check GPS and see if we can grab data. If we can, fill string for use
//There are GPS libraries available, but this requires less overhead for the nano
void getGPSData (){
          // Find dollar sign '$' that will tell us beginning of GPS sequence
         stringGPS = ""; //clear string so that we can append
         if(serialGPS.available()){
            bufferIn = serialGPS.read();
            }
        
        //Grab beginnning sequence from GPS signal    
        if( bufferIn =='$'){
            stringGPS= (String)bufferIn;
            for(int i=0; i<5; i++){
               bufferIn = serialGPS.read();
               stringGPS+= (String)bufferIn;
                }
            }
        
        //We are only going to get data from this sequence beginning. We are not worrying about the othes
        if( stringGPS == "$GPGGA"){
            Serial.println("Sequence: $GPGGA");
            stringGPS = fillGPSString( 74, stringGPS); //size of sequence for $GPGGA is 74 after beginning sequence
            NLatitude = stringGPS.substring(18,27).toFloat(); // This grabs the characters --the last number is the index (0 based +1) - we know this based on form of output
            WLongitude = stringGPS.substring(30,40).toFloat(); // This grabs the characters --the last number is the index (0 based +1)
            Serial.print("Current Coodinates: ");Serial.print(NLatitude); Serial.print("    "); Serial.println(WLongitude);
          }
 
}

// Get data from GPS signal according to the amount of data we need for each sequence
String fillGPSString(int sizeOfSequence, String GPSSequence){
        for(int i=0; i<sizeOfSequence; i++){
               bufferIn = serialGPS.read();
               GPSSequence+= (String)bufferIn;
                }
        return GPSSequence;
}

// Function is called to start our gps coordinate position. This pauses the program until a GPS signal is found and available. 
void calibrateGPS(){
        // Wait for GPS to become available
        while(!serialGPS.available()){
          Serial.println("GPS not available");
          delay (1000);
          }
        Serial.println("GPS available");
        
        
        getGPSData(); 
        while(NLatitude == 0.00 && WLongitude == 0.00){
          getGPSData(); 
          Serial.println("Searching Signal");
        }
        Serial.println("GPS Calibrated");
        //Determine starting coordinates
        
        StartingNLatitude = NLatitude;
        StartingWLongitude = WLongitude;
        LatitudeThreshold = (INSIDE_FLIGHT_ZONE_SIZE/30.79) / 60; //There are 30.79 meters in a Latitude minute, and 60 seconds in a minute
        LongitudeThreshold = (INSIDE_FLIGHT_ZONE_SIZE/24.39) / 60; //There are  meters in a Longitude minute, and 60 seconds in a minute
}




