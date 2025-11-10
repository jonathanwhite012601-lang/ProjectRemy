//pin 9 and 10 are disabled
#include <Servo.h>
#include <math.h>
//ADXL345 pin layout
const int groundpin = 18;             // analog input pin 4 -- ground

const int powerpin = 19;              // analog input pin 5 -- voltage

const int xpin = A3;                  // x-axis of the accelerometer

const int ypin = A2;                  // y-axis

const int zpin = A1; 


void stopMotor(){
  digitalWrite(motor1p1,   LOW);
  digitalWrite(motor1p2, LOW);

 digitalWrite(motor2p1, LOW);
  digitalWrite(motor2p2, LOW);

 digitalWrite(motor3p1, LOW);
  digitalWrite(motor3p2, LOW); 

 digitalWrite(motor4p1, LOW);
   digitalWrite(motor4p2, LOW);

}

void Move(){
 digitalWrite(motor1p1,   HIGH);
  digitalWrite(motor1p2, LOW);

 digitalWrite(motor2p1, HIGH);
  digitalWrite(motor2p2, LOW);

 digitalWrite(motor3p1, HIGH);
  digitalWrite(motor3p2, LOW); 

 digitalWrite(motor4p1, HIGH);
   digitalWrite(motor4p2, LOW);

} 
void Grasp(){
  for(pos=45;pos>=0;pos--)
  {
    HND.write(pos);
  }
}

void deGrasp(){
  for(pos=0;pos <=45;pos++)
  {
    HND.write(pos);
  }
}

Servo SHO;
Servo WRST;
Servo HND;


 unsigned long previousMillis = 0; // Stores the last time the action was performed
 const long interval = 1000;       // Interval at which to perform the action (e.g., 1 second)
 bool timerActive;          // Flag to control if the timer is active
//Runtime time elapsed while moving
void runTime(){
  a = 
  
  if(a > 0 || a < 0){
    timerActive = true;
    currentTime = millis()*1000; //runs time and turns milliseconds to seconds
   }
  else{timerActive = false;}
}
//distance travelled
void Distance(){
  pinMode(groundPin, output);
  pinMode(powerPin, output);
  digitalWrite(groundpin,LOW);
  digitalWrite(powerpin, HIGH);
  if(analogRead(A2) != 0){
    float d_t = analogRead(A2) * pow(Runtime(),2);
  }
  else {
    d_t = 0
  }
  
}


//set the target distance to 7ft
const float target = 7;

void setup() {
  serial.begin(9600);
  pinMode(groundPin, output);
  pinMode(powerPin, output);
  digitalWrite(groundpin,LOW);
  deigitalWrite(powerpin, HIGH);
 SHO.attach();
 WRST.attach();
 HND.attach();
 
 pinMode(Motor1p1, OUTPUT);
 pinMode(Motor1p2, OUTPUT);

 pinMode(Motor2p1, OUTPUT);
 pinMode(Motor2p2, OUTPUT);

 pinMode(Motor3p1, OUTPUT);
 pinMode(Motor3p2, OUTPUT);

 pinMode(Motor4p1, OUTPUT);
 pinMode(Motor4p2, OUTPUT);
 
}

void loop() {
 unsigned long Runtime = millis();
  analogWrite( -6,100);
  analogWrite( -5, 100);
  
  //robot drives for 1ft then will stop
 do{ 
   Move();

   }
 while(target-Distance() >= 6); 
  stopMotor();
  Grasp();
  delay(10)
  do{
    Move();
  } 
  while(target-Distance() == 0);

  deGrasp();
 delayMicroseconds(10);

  
}

