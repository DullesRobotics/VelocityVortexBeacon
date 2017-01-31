# VelocityVortexBeacon
Make your own FTC 2016-2017 Season Velocity Vortex Beacon with an arduino

##Power
The beacon can be powered from USB power or any 6-20V source using a barrel connector. The only component requiring a direct source of power is the arduino. 

##Installation
LED's can be directly conected to the Arduino's pins when used with a suitable resistor.
(Resistance will vary with LED forward voltage drop and forward current rating)
Ex.) Arduino Pin --> LED --> Resistor --> Arduino Ground

###Pins
Pin numbers may be changed but the default values are as follows
Without modifications to the code, LED's should be connected to the following pins.

####Left
Red - pin 3  
Blue - pin 4  
Button - 8  

####Right
Red - 5  
Blue - 6  
Button - 9  
