#include <Servo.h> 
Servo myservo;
int duration; //定义变量duration用来存储脉冲 
int distance; //定义变量distance用来存储距离值 
int srfPin = 13; //15; //定义srfPin为数字口15 
int z; //定义变量Z int val; 
int val;//定义变量val 
int val1; //定义变量val1 
int val2; //定义变量val2 
void setup() 
{ 
  myservo.attach(8); //8号引脚输出舵机控制信号 
  Serial.begin(9600); //仅能使用9、10号引脚 
  pinMode(9,OUTPUT); //定义I3接口 
  pinMode(10,OUTPUT); //定义I4接口 
  pinMode(11,OUTPUT); //定义EB(PWM调速)接口 
  pinMode(5,OUTPUT); //定义EA(PWM调速)接口 
  pinMode(6,OUTPUT); //定义I2接口 
  pinMode(7,OUTPUT); //定义I1接口 
  myservo.write(90); //使舵机转到90度
}
void loop() 
{ 
  delay(100); //延时20毫秒 
  Goahead(); //调用前进子程序 
  val=Ultrasonic(z); //将超声波读取的距离值赋值给val 
  if(val<25) //判断如果val小于25则继续执行 
  { 
    Stop(); //调用停止子程序 
    myservo.write(0); //让舵机转0度 
    delay(1000); //延时1秒等待舵机到达指定位置
    val1=Ultrasonic(z); //将超声波读取的距离值赋值给
    delay(1000); //延时1秒等待舵机到达指定位置 
    myservo.write(179); //让舵机转180度 
    delay(1000); //延时1秒等待舵机到达指定位置 
    val2=Ultrasonic(z); //将超声波读取的距离值赋值给val2 
    delay(1000); //延时1秒等待舵机到达指定位置 
    myservo.write(83); //让舵机转90度 
    //delay(1000); //延时1秒 
    if(val1<val2) { 
      Turn_left(); //调用左转子程序 
      Serial.println("TurnLeft");
      delay(200); //延时200毫秒
    } else { 
      Serial.println("TurnRight");
      Turn_right(); //调用右转子程序 
      delay(200); //延时200毫秒 
    } 
    delay(500); //延时500毫秒
  }
  Serial.print("val=");
  Serial.print( val );
  Serial.print(" / val1=");
  Serial.print( val1 );
  Serial.print(" / val2=");
  Serial.print( val2 );
  Serial.println();
}
int Ultrasonic(int distance) 
{ 
  pinMode(srfPin,OUTPUT); //定义srfPin为输出接口 
  digitalWrite(srfPin, LOW); //高电平触发前发送2微秒的低电平 
  delayMicroseconds(2); 
  digitalWrite(srfPin, HIGH); //发送10微秒的高电平开始检测 
  delayMicroseconds(10); 
  digitalWrite(srfPin, LOW); //等待脉冲返回前发送一个低电平 
  pinMode(srfPin, INPUT); //定义srfPin为输入接口 
  duration = pulseIn(srfPin, HIGH); //从URF02读取脉冲 
  distance = duration/58; //除以58得到距离值 
  return distance; 
}
void Goahead()//前进 
{ 
  analogWrite(5,165); //输入模拟值进行设定速度 
  digitalWrite(7,LOW); //使直流电机（右）顺时针转 
  digitalWrite(6,HIGH); 
  analogWrite(11,160); //输入模拟值进行设定速度 
  digitalWrite(9,HIGH); //使直流电机（左）逆时针转 
  digitalWrite(10,LOW);
 } 
void Stop()//停止 
{ 
digitalWrite(6,HIGH); //使直流电机（右）制动 
digitalWrite(7,HIGH); 
digitalWrite(9,HIGH); //使直流电机（左）制动 
digitalWrite(10,HIGH); 
} 
void Turn_right()//右转 
{ 
  analogWrite(5,170); //输入模拟值进行设定速度 
  digitalWrite(6,LOW); //使直流电机（右）顺时针转 
  digitalWrite(7,HIGH); 
  analogWrite(11,150); //输入模拟值进行设定速度 
  digitalWrite(9,HIGH); //使直流电机（左）逆时针转 
  digitalWrite(10,LOW); 
} 
void Turn_left()//左转 
{ 
  analogWrite(5,150); //输入模拟值进行设定速度 
  digitalWrite(7,LOW); //使直流电机（右）顺时针转 
  digitalWrite(6,HIGH); 
  analogWrite(11,170); //输入模拟值进行设定速度 
  digitalWrite(10,HIGH); //使直流电机（左）逆时针转 
  digitalWrite(9,LOW); 
}
