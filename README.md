# ESP-GPIO
The two files are for ESP8266 board
The LED code file is to enable the GPIO pin 4 to go high or low when a payload message of on or off is received on the topic "lounge"
The switch code publishes to the topic "lounge" with a payload of on or off depending on wether there is a high or low input on GPIO pin 14 (although the code say's it's pin 5, I don't know why this is)
If you find any issues with this code or my git hub then please let me know, I am a newbie to this.
