Door Alarm with ATtiny85 and Piezo Buzzer

This project uses the ATtiny85 to monitor two doors with magnetic switches. When a door is opened, the Piezo buzzer emits a sound. The code also implements a sleep mode to minimize power consumption when no doors are open.

Adjustable Variables (ms):
delayTime: The delay before the door alarm is triggered after a door is opened.
beepDuration1On: The duration of the beep when Door 1 is open.
beepDuration1Off: The pause after the beep for Door 1.
beepDuration2On: The duration of the beep when Door 2 is open.
beepDuration2Off: The pause after the beep for Door 2.

How it works:
The ATtiny85 monitors the doors (DOOR1_PIN and DOOR2_PIN) and activates the Piezo buzzer (PIEZO_PIN) when one or both doors are open.
The Piezo emits different tones for each door.
When no doors are open, the device enters sleep mode to save power.
Interrupts allow for quick response to door movements without the need for continuous polling of the state.

Hardware
ATtiny85 Microcontroller
2 x Magnetic Door Contacts (Switches, normaly open)
1 x Piezo Buzzer
