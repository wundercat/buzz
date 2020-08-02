# buzz

## A somewhat overbuilt continuity tester

I use a continuity tester to verify my wiring when I build an electronic prototype.  It beeps or lights up when the test leads are connected to each other.  You can buy a "buzz light" at a car parts store.   You can use the beep function in a multimeter.   But I wanted features:
- Tester should not mistake a diode for a wired connection.
- Light and sound indications.
- Earbud output so I don't bug my roommate with beeping
- Low test current doesn't damage delecate connections
- small size
- rechargeable battery
Additional constraints:
- Use parts already on hand only, no parts shopping for this project
- Firmware can be updated easily

## Theory of Operations
Three resistors in series  form a voltage divider.   It draws about 1 ma from the 5V supply.   The middle ("sense") resistor is chosen to drop about 150 millivolts (mV) and its pins are brought out to test leads.   The analog to digital converter in the Arduino resolves voltage in 5 mV increments.  The Arduino firmware periodically (a few KHz) measures the drop on the sense resistor.  If the semse resistor is shorted, the 1 ma flows through the short instead of the sense resistor.   A connection is indicated if the difference between the test leads falls to less than 20 mV.

## other stuff
### power supply
 The regulator on the Arduino Nano steps the battery voltage down to regulated 5V.  A blue LED indicates the system is powered up, so you don't forget and run down the battery.  
 
## safety
 - A P-channel MOSFET protects the system if the battery is reversed.
 - A pair of fast PN diodes protect the Arduino analog inputs from ESD and accidently measuring a charged capacitor.
 
## Earbud jack
Software detects a plug present in the jack, by reading the switch contact in the jack.   If it's the same as the tip signal, there's no plug.



