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


///////////////////////////////////////////////
/*sensor0가 오픈하기 위한 거리 측정 센서,
sensor1가 클로즈하기 위한 거리 측정 센서
이에 따른 측정 거리는 각각 distance0, distance1임*/
#define trigPin0 48
#define echoPin0 49

#define trigPin1 50
#define echoPin1 51
////////////////////////////////////////////////

/*Ultrasonic Sensor (HC-SR04)*/
//ultrasonic speed : 340m/s
float duration0, distance0;
float duration1, distance1;
int pressed = false; 
int open_sig = false;

int cnt1 = 0;
int cnt2 = 0;
int Mode = 2;

void read_distance0(void);
void read_distance1(void);
void stepmotor_open(void);
void stepmotor_close(void);

// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

void setup() {

  // Stepper 모터 setup
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  myStepper.setSpeed(10); // Set the motor speed (RPMs):
  
  // swtich swtup
  pinMode(PUSH_SW, INPUT);

  
  // 초음파 센서 setup
  pinMode(trigPin0, OUTPUT);
  pinMode(echoPin0, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  SerialASC.begin(9600);
}


void loop() {
  ////////////////////////////////////////
  //  Mode
  //  1: Open  2: Close  3: Opening  4: Closing
  //////////////////////////////////////

  switch(Mode){
    case 1:
    read_switch();
    if (pressed == TRUE)
    {
      Mode = 4;
    }

    break;

    case 2:

      // 초음파 센서 거리 측정
      read_distance0();
      read_switch();
      if(((distance0 < 5) && (distance0>0)) || (pressed == TRUE))
      {
        Mode = 3;
      }
     
    break;

    case 3:
        stepmotor_open();
        Mode = 1;
    break;

    case 4:
       stepmotor_close();
       Mode = 2;
    break;
    
    default:
    break;
  }
  SerialASC.println(Mode);
}

void read_switch(void){
    /* Read button */
  if (digitalRead(PUSH_SW) == false) // push : 0, NOP : 1
  {
    pressed = !pressed;
  }
  while (digitalRead(PUSH_SW) == false);
  delay(20); //ms
}

void stepmotor_open(){
  myStepper.step(stepsPerRevolution);
}

void stepmotor_close(){
  myStepper.step(-stepsPerRevolution);
}


void read_distance0(void)
{
  digitalWrite(trigPin0, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin0, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin0, LOW); 
  // Echo 핀으로 들어온 펄스 시간 (us) 측정 
  //pulseIn(pin, value, timeout)
  //pin :  the number of the Arduino pin on which you want to read the pulse.
  //value: type of pulse to read: either HIGH or LOW
  //timeout (optional): the number of microseconds to wait for the pulse to start; 
  // --> default is one second, unsigned long
  duration0 = pulseIn(echoPin0, HIGH, 11000); //time[us]
  distance0 = ((float)(duration0)*0.34/10)/2; //time[us]*speed[cm/us]
   
   SerialASC.println("sensor0: ");
   SerialASC.println(distance0);

  delay(100);
}
void read_distance1(void)
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW); 
  // Echo 핀으로 들어온 펄스 시간 (us) 측정 
  //pulseIn(pin, value, timeout)
  //pin :  the number of the Arduino pin on which you want to read the pulse.
  //value: type of pulse to read: either HIGH or LOW
  //timeout (optional): the number of microseconds to wait for the pulse to start; 
  // --> default is one second, unsigned long
  duration1 = pulseIn(echoPin1, HIGH, 11000); //time[us]
  distance1 = ((float)(duration1)*0.34/10)/2; //time[us]*speed[cm/us]
  
  // printf("sensor1: ");
   //SerialASC.println("sensor1: ");
   //SerialASC.println(distance1);

  delay(100);
}
