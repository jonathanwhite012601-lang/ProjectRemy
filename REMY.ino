#include <Servo.h>

// ----- Motor pins (L298N) -----
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 12;
const int IN4 = 13;
const int ENA = 5;
const int ENB = 11;

// ----- Servo pins -----
const int LIFT_SERVO_PIN = 9;  // arm up/down
const int CLAW_SERVO_PIN = 3;  // grab/release

// ----- Distance timing (YOU MUST TUNE THESE) -----
const unsigned long TIME_1FT = 2000;   // ms to move 1 ft (adjust after testing)
const unsigned long TIME_6FT = 7000;   // ms to move 6 ft (adjust after testing)

// ----- Motor speed -----
const int DRIVE_SPEED = 200;   // 0–255

// ----- Servo objects -----
Servo liftServo;
Servo clawServo;

// ----- Servo angles (tune to match your arm) -----
const int LIFT_DOWN_ANGLE  = 20;   // arm lowest position
const int LIFT_UP_ANGLE    = 100;  // carry position
const int LIFT_DUMP_ANGLE  = 140;  // dump position (optional)

const int CLAW_OPEN_ANGLE   = 100; // open to pick/drop balls
const int CLAW_CLOSED_ANGLE = 40;  // closed to hold balls

// ---------- Motor helper functions ----------
void setMotors(int leftSpeed, int rightSpeed) {
  // leftSpeed, rightSpeed: -255..255 (negative = reverse)

  // Left motor (A): IN1, IN2, ENA
  if (leftSpeed > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (leftSpeed < 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    leftSpeed = -leftSpeed;
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  leftSpeed = constrain(leftSpeed, 0, 255);
  analogWrite(ENA, leftSpeed);

  // Right motor (B): IN3, IN4, ENB
  if (rightSpeed > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else if (rightSpeed < 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    rightSpeed = -rightSpeed;
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  rightSpeed = constrain(rightSpeed, 0, 255);
  analogWrite(ENB, rightSpeed);
}

void driveForward(int speed, unsigned long durationMs) {
  setMotors(speed, speed);
  delay(durationMs);
  setMotors(0, 0);
}

void stopMotors() {
  setMotors(0, 0);
}

// ---------- Setup ----------
void setup() {
  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Attach servos
  liftServo.attach(LIFT_SERVO_PIN);
  clawServo.attach(CLAW_SERVO_PIN);

  // Optional: Serial for debugging
  Serial.begin(9600);
  Serial.println("Robot ball-run starting...");

  // Initialize arm: arm down, claw open
  liftServo.write(LIFT_DOWN_ANGLE);
  clawServo.write(CLAW_OPEN_ANGLE);
  delay(1000);
}

// ---------- Main mission ----------
void loop() {
  // 1) Start with arm down & claw open (already done in setup, but repeat for safety)
  liftServo.write(LIFT_DOWN_ANGLE);
  clawServo.write(CLAW_OPEN_ANGLE);
  delay(1000);

  // 2) Drive 1 ft to reach balls
  driveForward(DRIVE_SPEED, TIME_1FT);

  // 3) Pick up balls: close claw
  clawServo.write(CLAW_CLOSED_ANGLE);
  delay(800);  // let claw close

  // 4) Lift arm up to carry position
  liftServo.write(LIFT_UP_ANGLE);
  delay(1000);

  // 5) Drive 6 ft to drop zone
  driveForward(DRIVE_SPEED, TIME_6FT);

  // 6) Drop balls: move arm to dump position & open claw
  liftServo.write(LIFT_DUMP_ANGLE);
  delay(700);
  clawServo.write(CLAW_OPEN_ANGLE);
  delay(1000);

  // 7) Stop forever (so it doesn't repeat)
  stopMotors();
  while (true) {
    // do nothing
  }
}
