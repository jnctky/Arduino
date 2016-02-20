#include <PT_timer.h>
#include <pt.h>   // include protothread library
static struct pt pt1, pt2, pt3, pt4; // each protothread needs one of these
static PT_timer servoTimer;
static PT_timer carTimer;
static PT_timer mouseTimer;
static PT_timer naviTimer;

#include <PS2Mouse.h>
#define MOUSE_DATA 2//5
#define MOUSE_CLOCK 3//6
static PS2Mouse mouse(MOUSE_CLOCK, MOUSE_DATA, REMOTE/*STREAM*/);

#include "CJUltrasonicSensor.h"
static CJUltrasonicSensor mDistanceSensorLeft, mDistanceSensorRight, mDistanceSensorMid;

#include <Servo.h>
static Servo myservo;

static int angle[13] =
{ 0, 15, 30, 45, 60, 75, 90,
  105, 120, 135, 150, 165, 180
};
static int val[13];
static int valLeft, valRight, valMid;

#include "CJCar.h"
static CJCar mCar(11,12,13,9,8,10);
#define MIN_DISTANCE 50

#define LEDPIN 13  // LEDPIN is a constant 

static bool initFlag = false;
static bool resetFlag = true;

static float posX = 0;
static float posY = 0;
static int targetDirection=0;

void setup() {
  Serial.begin(38400); //仅能使用9、10号引脚

  PT_INIT(&pt1);  // initialise the two
  PT_INIT(&pt2);  // protothread variables
  PT_INIT(&pt3);  // protothread variables
  PT_INIT(&pt4);  // protothread variables

  /*
  myservo.attach(8); //8号引脚输出舵机控制信号
  myservo.write(90); //使舵机转到90度
  */

  //pinMode(LEDPIN, OUTPUT); // LED init
  
  mDistanceSensorRight.setMode(2, A0, A1);
  mDistanceSensorMid.setMode(2, A2, A3);
  mDistanceSensorLeft.setMode(2, A4, A5);

  //未连接鼠标时不能初始化鼠标,否则会导致PS2库程序阻塞卡死
  //mouse.initialize();
}

void toggleLED() {
  boolean ledstate = digitalRead(LEDPIN); // get LED state
  ledstate ^= 1;   // toggle LED state using xor
  digitalWrite(LEDPIN, ledstate); // write inversed state back
}

/* This function toggles the LED after 'interval' ms passed */
static int ultrasonic_thread(struct pt *pt) {
  static unsigned int interval = 50;
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
    Serial.println("PT1");
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
#if 0 
      //正常测距过程
      val[counter] = mDistanceSensorMid.GetDistance(); //将超声波读取的距离值赋值给val
      sprintf(s, "PT1 counter:%d - val[%d]:%d", counter, angle[counter], val[counter]);
      
     
      if (val[6] < 4000/*150*/ && initFlag) {
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
#else
    valMid = mDistanceSensorMid.GetDistance(); //将超声波读取的距离值赋值给val
    valLeft = mDistanceSensorLeft.GetDistance(); //将超声波读取的距离值赋值给val
    valRight = mDistanceSensorRight.GetDistance(); //将超声波读取的距离值赋值给val
    sprintf(s, "PT1 - valMid:%d, valLeft:%d, valRight:%d", valMid, valLeft, valRight);
    initFlag = true;
#endif
    }
    
    //等待舵机旋转时间
    //iAngle = abs(angle[counter] - lastAngle);
    //interval = max(iAngle * 10 + 5, 160);
    //lastAngle = angle[counter];
    //sprintf(s, "%s / interval:%d / iAngle:%d,", s, interval, iAngle);
    
    Serial.println(s);
    //servoTimer.setTimer(10);
    servoTimer.setTimer(interval);
    PT_WAIT_UNTIL(pt, servoTimer.Expired());
  }

  PT_END(pt);
}

/* exactly the same as the protothread1 function */
static int car_thread(struct pt *pt) {
  static unsigned long timestamp = 0;
  unsigned int DistanceLeft = 0;
  unsigned int DistanceRight = 0;
  unsigned int i;
  int x,y;
  char s[100];
  int interval;

  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    //timestamp = millis();

    Serial.println("PT2");
    //至少等待至前方180度都扫描完毕
    PT_WAIT_UNTIL(pt, !resetFlag && initFlag );
 
    if (valMid < MIN_DISTANCE || valLeft < MIN_DISTANCE/4 || valRight < MIN_DISTANCE/4 ) {
      Serial.println("***************PT2 debug 1");
      //前方(为避免正前方声波无法反射,监测左右15度范围内障碍)有障碍,重新寻路
      mCar.Stop();
      resetFlag = true;
      PT_WAIT_UNTIL(pt, !resetFlag && initFlag );

      //if (valRight < MIN_DISTANCE && valLeft < MIN_DISTANCE ) {
      //  mCar.MoveBackward();
      //} else {
        if (valRight < valLeft) {
          interval = mCar.TurnLeft(45);
          resetFlag = true;
        } else {
          interval = mCar.TurnRight(45);
          resetFlag = true;
        }
      //}
      interval = max(interval, 100);
      carTimer.setTimer(interval);
      PT_WAIT_UNTIL(pt, carTimer.Expired());

      mCar.Stop();
      interval = 300;
      carTimer.setTimer(interval);
      PT_WAIT_UNTIL(pt, carTimer.Expired());
    } else {
      Serial.println("***************PT2 debug 2");
      if (valMid < MIN_DISTANCE * 3 ) {
        //90正前方1.5米内有障碍时,减速并持续监测正前方
        mCar.ChangeGear( 0.75f );
        Serial.println("SpeedDown");
        mCar.MoveForward();
      } else {
        //前方还有空间时,设为正常速度并持续监测左右
        mCar.ChangeGear( 1.0f );
        Serial.println("SpeedUP");
        mCar.MoveForward();
      }

      carTimer.setTimer(50);
      PT_WAIT_UNTIL(pt, carTimer.Expired());
    }
    

  }
  PT_END(pt);
}

/* exactly the same as the protothread1 function */
static int mouse_thread(struct pt *pt) {
  static unsigned long timestamp = 0;
  unsigned int DistanceLeft = 0;
  unsigned int DistanceRight = 0;
  char s[100];

  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, millis() - timestamp > 10 );
    Serial.println("PT3");
    Serial.println(millis() - timestamp);
    timestamp = millis();

    int data[2];
    mouse.report(data);
    posX += data[1];
    posY += data[2];
    sprintf(s, " X:%d / Y:%d,", posX, posY);
    Serial.println(s);

    mouseTimer.setTimer(10);
    PT_WAIT_UNTIL(pt, mouseTimer.Expired());
  }
  PT_END(pt);
}

/* exactly the same as the protothread1 function */
static int navi_thread(struct pt *pt) {
  static unsigned long timestamp = 0;
  char s[100];

  PT_BEGIN(pt);
  while (1) {
    //PT_WAIT_UNTIL(pt, millis() - timestamp > 10 );
    Serial.println("PT4");
    //timestamp = millis();

//    mNavigater.setPosition(posX,posY);
//    targetDirection = mNavigater.getDirection();
    sprintf(s, " X:%d / Y:%d,", posX, posY);
    Serial.println(s);

    naviTimer.setTimer(200);
    PT_WAIT_UNTIL(pt, naviTimer.Expired());
  }
  PT_END(pt);
}

void loop() {
  ultrasonic_thread(&pt1); // schedule the two protothreads
  car_thread(&pt2); // by calling them infinitely
  //mouse_thread(&pt3);
  //navi_thread(&pt4);
  /*
  char s[100];
  sprintf(s, " X:%d / Y:%d,", posX, posY);
  Serial.println(s);
  */
}


