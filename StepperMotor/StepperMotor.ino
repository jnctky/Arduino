int dirPin1 = 2;
int stepperPin1 = 3; //pwm
int dirPin2 = 7;
int stepperPin2 = 6; //pwm
void setup() {
  pinMode(dirPin1, OUTPUT);
  pinMode(stepperPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepperPin2, OUTPUT);
}

void step(boolean dir,int steps){
  digitalWrite(dirPin1,dir);
  digitalWrite(dirPin2,dir);
  delay(100);
  for(int i=0;i<steps;i++){
    digitalWrite(stepperPin1, HIGH);
    digitalWrite(stepperPin2, HIGH);
    delayMicroseconds(70);
    digitalWrite(stepperPin1, LOW);
    digitalWrite(stepperPin2, LOW);
    delayMicroseconds(70);
  }
}

void pwm(boolean dir){
  digitalWrite(dirPin1,dir);
  digitalWrite(dirPin2,dir);
  delay(100);
  analogWrite(stepperPin1, 128);
  analogWrite(stepperPin2, 128);
}

void loop(){

#if 0
  step(true,1600);
  delay(500);
  step(false,1600);
  delay(500);
#else
  pwm(true);
  delay(2000);
  pwm(false);
  delay(2000);
#endif

}

