# AtemTally_ESP8266EX_Arduino

This code was in reference to the https://github.com/kasperskaarhoj/SKAARHOJ-Open-Engineering/tree/master/ArduinoLibs

## Configration

D16: Red Tally (LED)
D5: Green Tally (LED)

D14: Cam No (LSB)
D12: Cam No
D13: Cam No (MSB)

    // IP address of the ATEM Switcher
    IPAddress switcherIp(192, 168, 10, 240);
    // My Router SSID
    const char* ssid = "MY SSID";
    // My Router passwod
    const char* password = "xxxxxxx";
