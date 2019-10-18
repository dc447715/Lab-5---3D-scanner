/* ME 4550 - Lab 5
 *  Objective 1
 *  10/16/2019 
 */

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

/* Connect NEMA 17 stepper motor with 200 steps per revolution (1.8 degree)
 * Controls the height of the 3D scanner
 * to motor port #2 (M3 and M4)
 */
Adafruit_StepperMotor *sensor_Stepper = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *rot_Stepper = AFMS.getStepper(200, 1);

void motorStep(){
  sensor_Stepper->step(10,FORWARD,MICROSTEP);
}

#define limitSwitch 8 // initialize limit switch to pin 8
static int switchState=0; // set initial state of NC limit switch to 0
static int rot_Stepper_State = 0; // set inital state of stepper motor

void setup() {
  Serial.begin(9600);                 // initialize serial monitor
  pinMode(limitSwitch, INPUT_PULLUP); // sets limit switch using built in Arduino resistor
  AFMS.begin();                       // create with the default frequency 1.6KHz
  
  sensor_Stepper->setSpeed(1000);       // 20 rpm   

  // homing
  switchState = digitalRead(limitSwitch);
  while(switchState == 0){
    Serial.print("This shit homin' homie, limit switch state = \t"); // degubber to check switch
    switchState = digitalRead(limitSwitch);
    delay(10);
    sensor_Stepper->step(1, FORWARD, MICROSTEP);
    Serial.println(switchState);
    
  }
  if(switchState == 1){
    sensor_Stepper->step(5, BACKWARD, MICROSTEP);
    Serial.println("Homing complete"); 
    }
}
void loop(){
}
