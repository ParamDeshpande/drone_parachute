# taxir 
This is the repository for the problem statement 
```
Develop a mechanism (can be software/ hardware/ both ) to deploy a parachute installed on the UAV in case of an emergency landing or power outage. The parachute is placed inside a compartment.
The expected output "Can be in the form of validated electronic circuit design, parachute deployment mechanism, CAD design, code, hardware"
(The code can be written in any programming language of your choice)
```
## Code
There are few versions of the code, please find the latest one in arduino_version. STM_32 mbed version is deprecated has memory overflow issues. 
find the cpp files in /main headers in /include.
 
## Setup

### Mainframe SETUP 

Please do install PlatformIO extension in VSCODE or the arduino IDE, in your pc/laptop depending on which architecture and which is being used or any other if you know what you are doing .... . and do install any HC-05 bluetooth serial terminal. Like [this one](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en). Or any other as per your preference.

### The system SETUP

Connect the backup battery and main battery in any order whatsover, the system should give an error and should fire the parachute initially cause one of the battery was missing. (new feature or setup init needs to be added here). That way even the end user is assured of the system working.
**HIT THE RESET BUTTON**
Connect your device to get debug via bluetooth, as to what is happening, if everything works out good, you will get debug message on bt stating all's good, else you might find the buzzer still irritating you. And there you go The system is up and ready.


## Conditions 
To eject the parachute, we apply the condition that it must reach a certain speed (1.5 m/s) or more within a specified time interval (0.25 s)
ie an acceleration of about 6m/secsq
. Otherwise, the parachute will not be ejected. Under such conditions, the drone is not allowed to reach a dangerous fall speed.

## Effects ( aka what all is done )
Once the parachute deploys, the system stops the spinning rotors to avoid entanglement with the parachute cords and reduces the risk of laceration injuries to people on the ground.
If battery dies out
relays releases spring support for the chute lid , 
Manual 
Release the flow for the chute aka stop powering the relay to hold the lid
Automatic 
FAILSAFE MECHANISM : The above mentioned in code. 

EITHER WAY OPENS under the given or desired conditions.

## PROTOTYPE GPB VERSION.

SEE  drone_parachute_pcb folder for board schematic.

![GPB_image_isometric](https://user-images.githubusercontent.com/37805111/72545254-c17ed080-38ae-11ea-9e65-7e24cecc2b3a.jpg)

