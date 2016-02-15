const int TrigPin = A2; //13;//A2; 
const int EchoPin = A3; //12;//A3; 
float cm; 
void setup() 
{ 
Serial.begin(9600); 
pinMode(TrigPin, OUTPUT); 
pinMode(EchoPin, INPUT); 
} 
void loop() 
{ 
digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
delayMicroseconds(2); 
digitalWrite(TrigPin, HIGH); 
//delayMicroseconds(100000); 
delay(100); 
digitalWrite(TrigPin, LOW); 

delayMicroseconds(5); 
cm = pulseIn(EchoPin, !(LOW)) / 58.0; //将回波时间换算成cm 
cm = (int(cm * 100.0)) / 100.0; //保留两位小数 
Serial.print(cm); 
Serial.print("cm"); 
Serial.println(); 
delay(100); 
} 
