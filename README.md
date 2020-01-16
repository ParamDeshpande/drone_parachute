# taxir 
This is the repository for the problem statement 
```
Develop a mechanism (can be software/ hardware/ both ) to deploy a parachute installed on the UAV in case of an emergency landing or power outage. The parachute is placed inside a compartment.
The expected output "Can be in the form of validated electronic circuit design, parachute deployment mechanism, CAD design, code, hardware"
(The code can be written in any programming language of your choice)
```
## Code
find the cpp files in /src headers in /include.

## Conditions 
To eject the parachute emission, we apply the condition that it must reach a certain speed (1.5 m/s) or more within a specified time interval (0.25 s)
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
![GPB_image_isometric](https://user-images.githubusercontent.com/37805111/72545254-c17ed080-38ae-11ea-9e65-7e24cecc2b3a.jpg)
