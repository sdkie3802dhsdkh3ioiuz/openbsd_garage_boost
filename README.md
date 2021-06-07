# openbsd_garage_boost
Briefly writes 1 to a Raspberry Pi digital pin to simulate pressing button on garage wall console

WARNING!!! I am NOT an electrician. I personally use a relay in this project to connect
to my garage wall console. Is this safe? I have ABSOLUTELY no idea. USE AT YOUR OWN RISK.

EXTRA WARNING!! All this does is simulate pressing your garage door's wall button by creating
a momentary short. This short will also happen if your Raspberry Pi or other device loses
power or reboots. I have found even a cheap UPS can prevent accidental reboots that
might otherwise occur due to power loss. Of course, this would not prevent a reboot
due to failing hardware or Soviet EMPs targeting your garage. All it takes to make
the garage door open is a momentary short, so preventing every single momentary short
except those for those induced programmatically might require a slightly different
setup. As long as the all the wires are plugged into the relay, the system will
be sensitive to momentay fluctuations, possibly opening the door at inopportune times.
The problem might be that we're not being sufficiently realistic in our simulation of
the button press -- maybe the program needs to look for a state change to the pin
that lasts a bit longer, and then move a robot arm to press the button . . . . 

In order to open a garage door, find the contacts on the back of your garage door wall console
that correspond to pushing the button. Solder a lead to each. Test them -- if you touch
the wires together very briefly, your garage door should open.

Now connect one lead to common (COM) on a relay (you can use a breadboard) and the other lead to
"normally closed" (NC). Connect a jumper wire from the Raspberry Pi's GPIO 23 (I call it DOOR_PIN)
to one side of the relay's coil, and the 5v Raspberry Pi pin to the other side of the coil.
(If nothing works, switch which pin goes to which side of the coil.)

The relay will be energized, so COM and NC will not be connected. But the momentary
change in power when we change state on the GPIO pin will short the two garage leads,
dropping the voltage to zero and trigggering the garage door controller to work its magic.

NOTE WELL: Please see the note above in the "EXTRA WARNNIG" section about accidental opening.

WARNING AGAIN: Did you see the part where I tell you I am not an electrician and have
no idea how safe this is? Talk to a qualified professional before you do this, because
you are not reading the words of one at this moment.
