/******Test by Athelloren******/
/*********2014.03.12***********/
/*ADNS-3080传感器测试程序(不写固件)
采用Arduino mega 2560测试
Arduino.2-A3080.CS
Arduino.50-A3080.MISO
Arduino.51-A3080.MOSI
Arduino.52-A3080.CLK
Arduino.5V-A3080.5V
Arduino.GND-A3080.GND
只接这几条线即可 A3080.3V.RST.NPD.LED这四个脚悬空即可
Arduino UNO不按此接线*/
/******Test by Athelloren******/
#include "SPI.h"
#include "ADNS3080.h"

char a1,a2,a3,a4;

void setup() 
{
  pinMode(2,OUTPUT);//将数字脚2设为输出模式
  SPI.begin();//启动SPI
  SPI.setBitOrder(MSBFIRST);//串行数据传输时先传输高位
  SPI.setDataMode(SPI_MODE3);//时钟极性和相位
  SPI.setClockDivider(SPI_CLOCK_DIV8);//传感器工作频率为时钟频率的1/8=2MHz 
  Serial.begin(115200);//串口波特率设为115200bps
  Serial.println("ADNS-3080 test by Athelloren\n");
  
  delay(1000);
}

void loop() 
{
    a1=read_register(0x00);
    a2=read_register(0x02);
    a3=read_register(0x03);
    a4=read_register(0x04);
    Serial.print("ID: ");
    Serial.print(a1,HEX);
    Serial.print("\tMotion: ");
    Serial.print(a2,BIN);
    Serial.println();
    Serial.print("dx: ");
    Serial.print(a3,DEC);
    Serial.print("\tdy: ");
    Serial.print(a4,DEC);
    Serial.println();
    delay(10);
}

byte read_register(byte address)//从A3080的寄存器中读数据
{
  byte result = 0, junk = 0;
  digitalWrite(2, LOW);//拉低从机CS
  junk = SPI.transfer(address);
  delayMicroseconds(50);
  result = SPI.transfer(0x00);
  digitalWrite(2, HIGH);//拉高从机CS
  return result;
}

void write_register(byte address, byte value)//写数据到A3080寄存器
{
  byte junk = 0;
  digitalWrite(2, LOW);
  junk = SPI.transfer(address | 0x80 );//写数据时最高位必需为1
  delayMicroseconds(50);
  junk = SPI.transfer(value);
  digitalWrite(2, HIGH);
}

/******Test by Athelloren******/
/*********2014.03.12***********/
