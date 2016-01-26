#include <PT_timer.h>
#include <pt.h>   // include protothread library
#include <Servo.h>

#define LEDPIN 13  // LEDPIN is a constant 

static struct pt pt1, pt2; // each protothread needs one of these

static Servo myservo;
static int inputPin = 12; //  定义超声波信号接收接口
static int outputPin = 13; //  定义超声波信号发出接口

static int angle[13] =
{ 0, 15, 30, 45, 60, 75, 90,
  105, 120, 135, 150, 165, 180
};
static int val[13];
static float gear = 1.0;
static PT_timer servoTimer;
static PT_timer carTimer;
static bool initFlag = false;
static bool resetFlag = true;

void setup() {
  myservo.attach(8); //8号引脚输出舵机控制信号
  Serial.begin(9600); //仅能使用9、10号引脚
  pinMode(9, OUTPUT); //定义I3接口
  pinMode(10, OUTPUT); //定义I4接口
  pinMode(11, OUTPUT); //定义EB(PWM调速)接口
  pinMode(5, OUTPUT); //定义EA(PWM调速)接口
  pinMode(6, OUTPUT); //定义I2接口
  pinMode(7, OUTPUT); //定义I1接口
  myservo.write(90); //使舵机转到90度
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);

  pinMode(LEDPIN, OUTPUT); // LED init
  PT_INIT(&pt1);  // initialise the two
  PT_INIT(&pt2);  // protothread variables
}

void toggleLED() {
  boolean ledstate = digitalRead(LEDPIN); // get LED state
  ledstate ^= 1;   // toggle LED state using xor
  digitalWrite(LEDPIN, ledstate); // write inversed state back
}

/* This function toggles the LED after 'interval' ms passed */
static int ultrasonic_thread(struct pt *pt) {
  static unsigned int interval = 150;
  static unsigned long timestamp = 0;
  static unsigned int counter = 6; //90 degree
  static int lastAngle = 90;
  static bool bFlag = true;
  static bool bRightFlag = false;
  static bool bLeftFlag = false;
  
  char s[100];
  int iAngle = 0;
  PT_BEGIN(pt);
  while (1) { // never stop
    //Serial.println("PT1");
    /* each time the function is called the second boolean
       argument "millis() - timestamp > interval" is re-evaluated
       and if false the function exits after that. */
    //PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    //timestamp = millis(); // take a new timestamp
    //toggleLED();

    if (resetFlag) {
      //变向后首次测距前清楚旧数据
      counter = 6;
      initFlag = false;
      resetFlag = false;
      bRightFlag = false;
      bLeftFlag = false;
      for(int i = 0; i<13; i++) {
        val[i]=0;
      }
      myservo.write(angle[counter]);
      
    } else {
      //正常测距过程
      val[counter] = Ultrasonic(); //将超声波读取的距离值赋值给val
      sprintf(s, "PT1 counter:%d - val[%d]:%d", counter, angle[counter], val[counter]);
      
      if (val[6] < 150 && initFlag) {
        //90正前方1.5米内有障碍时,减速并持续监测正前方
        counter = 6;
      } else {
        //前方还有空间时,设为正常速度并持续监测左右
        if (bFlag) {
          //0-180度转向
          if (counter < 12) {
            counter++;
          } else {
            bFlag = false;
            counter = 11;
            bLeftFlag = true;
          }
        } else {
          //180-0度反转向
          if (counter > 0 ) {
            counter--;
          } else {
            bFlag = true;
            counter = 1;
            bRightFlag = true;
          }
        }

        if (bLeftFlag && bRightFlag) {
          initFlag = true;
        }
      }
      myservo.write(angle[counter]);
    }
    
    //等待舵机旋转时间
    iAngle = abs(angle[counter] - lastAngle);
    interval = max(iAngle * 10 + 5, 160);
    lastAngle = angle[counter];

    sprintf(s, "%s / interval:%d / iAngle:%d,", s, interval, iAngle);
    Serial.println(s);
    servoTimer.setTimer(interval);
    PT_WAIT_UNTIL(pt, servoTimer.Expired());
  }

  PT_END(pt);
}

/* exactly the same as the protothread1 function */
static int car_thread(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  unsigned int DistanceLeft = 0;
  unsigned int DistanceRight = 0;
  unsigned int i;

  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    //timestamp = millis();

    Serial.println("PT2");
    //至少等待至前方180度都扫描完毕
    PT_WAIT_UNTIL(pt, initFlag );
      
    if (val[6] < 50 || val[5] < 50 || val[7] < 50) {
      //前方(为避免正前方声波无法反射,监测左右15度范围内障碍)有障碍,重新寻路
      Stop();


      DistanceRight = 0;
      for (i = 0; i <= 5; i++) DistanceRight += val[i];
      DistanceLeft = 0;
      for (i = 7; i <= 12; i++) DistanceLeft += val[i];

      if (DistanceRight < DistanceLeft) {
        TurnLeft();
        resetFlag = true;
      } else {
        TurnRight();
        resetFlag = true;
      }
      
      carTimer.setTimer(600);
      PT_WAIT_UNTIL(pt, carTimer.Expired());
      Stop();
    } else if (val[6] < 150) {
      //90正前方1.5米内有障碍时,减速并持续监测正前方
      gear = 0.75f;
      Serial.println("SpeedDown");
      MoveForward();
    } else {
      //前方还有空间时,设为正常速度并持续监测左右
      gear = 1.25f;
      Serial.println("SpeedUP");
      MoveForward();
    }

    carTimer.setTimer(200);
    PT_WAIT_UNTIL(pt, carTimer.Expired());
  }
  PT_END(pt);
}

void loop() {
  ultrasonic_thread(&pt1); // schedule the two protothreads
  car_thread(&pt2, 200); // by calling them infinitely
}

int Ultrasonic()
{
  //Mode2
  digitalWrite(outputPin, LOW); //使发出发出超声波信号接口低电平2 μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH); //使发出发出超声波信号接口高电平10μs ，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);     // 保持发出超声波信号接口低电平
  int distance = pulseIn(inputPin, HIGH);  //  读出脉冲时间
  distance = distance / 58; // 将脉冲时间转化为距离（单位：厘米）

  return distance;
}

void MoveForward()//前进
{
  analogWrite(5, int(165 * gear)); //输入模拟值进行设定速度
  digitalWrite(7, LOW); //使直流电机（右）顺时针转
  digitalWrite(6, HIGH);
  analogWrite(11, int(160 * gear)); //输入模拟值进行设定速度
  digitalWrite(9, HIGH); //使直流电机（左）逆时针转
  digitalWrite(10, LOW);

  Serial.println("MoveForward");
}
void MoveBackward()//前进
{
  analogWrite(5, int(165 * gear)); //输入模拟值进行设定速度
  digitalWrite(6, LOW); //使直流电机（右）顺时针转
  digitalWrite(7, HIGH);
  analogWrite(11, int(160 * gear)); //输入模拟值进行设定速度
  digitalWrite(10, HIGH); //使直流电机（左）逆时针转
  digitalWrite(9, LOW);

  Serial.println("MoveBackward");
}
void Stop()//停止
{
  digitalWrite(6, HIGH); //使直流电机（右）制动
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH); //使直流电机（左）制动
  digitalWrite(10, HIGH);

  Serial.println("Stop");
}
void TurnRight()//右转
{
  analogWrite(5, int(170 * gear)); //输入模拟值进行设定速度
  digitalWrite(6, LOW); //使直流电机（右）顺时针转
  digitalWrite(7, HIGH);
  analogWrite(11, int(150 * gear)); //输入模拟值进行设定速度
  digitalWrite(9, HIGH); //使直流电机（左）逆时针转
  digitalWrite(10, LOW);

  Serial.println("TurnRight");
}
void TurnLeft()//左转
{
  analogWrite(5, int(150 * gear)); //输入模拟值进行设定速度
  digitalWrite(7, LOW); //使直流电机（右）顺时针转
  digitalWrite(6, HIGH);
  analogWrite(11, int(170 * gear)); //输入模拟值进行设定速度
  digitalWrite(10, HIGH); //使直流电机（左）逆时针转
  digitalWrite(9, LOW);

  Serial.println("TurnLeft");
}
