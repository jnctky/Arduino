#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
// - AT Mode缺省速率为38400，需要先按住HC05的Reset同时启动Arduino，使HC05进入AT模式，已进行速率设置，AT+UART=38400,0,0
// - 正常Mode缺省速率为9600，需要改为38400
 
char c = ' ';
 
void setup() 
{
    Serial.begin(38400);
    Serial.println("Arduino is ready");
    Serial.println("Remember to select Both NL & CR in the serial monitor");
 
    // HC-05 default serial speed for AT mode is 38400
    BTserial.begin(38400);  
}
 
void loop()
{

#if 1
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
        BTserial.write(c);  
    }
#else    

    Serial.println("serial");
    BTserial.println("BTserial");
#endif
}
