// Include the Stepper library:
#include <Stepper.h>
// Define number of steps per revolution:
const int stepsPerRevolution = 200;
// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13
#define PUSH_SW  2

int pressed = false; 
// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);
void setup() {
  // Set the PWM and brake pins so that the direction pins can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
   pinMode(PUSH_SW, INPUT);
  // Set the motor speed (RPMs):
  myStepper.setSpeed(0);
}

void stepmotor_open(){
  myStepper.setSpeed(10);
  myStepper.step(stepsPerRevolution);
}

void stepmotor_close(){
  myStepper.setSpeed(10);
  myStepper.step(-stepsPerRevolution);
}
void loop() {

    /* Read button */
  if (digitalRead(PUSH_SW) == false) // push : 0, NOP : 1
  {
    pressed = !pressed;
  }
  while (digitalRead(PUSH_SW) == false);
  delay(20); //ms

  
  // 트렁크 열림 신호
  if(pressed == TRUE)
  {
    stepmotor_open();
  }
  if(pressed == FALSE)
  {
    stepmotor_close();
  }
}
