#include <SoftwareSerial.h>
#include <Servo.h>

// VCC, GND, SET  pin of HC11 RF
int HC11_VCC = 3;
int HC11_GND = 4;
//int HC11_SET = 3;

 // TX Pin of RF, RX pin of RF
SoftwareSerial ArduinoReceiveRF(6, 5);

// create A servo class with name as ESC Motor
Servo LeftMotor;
Servo RightMotor;

// degine PWM pins of LeftMotor signal and RightMotor signal
//int PWMpin_LeftMotor = 11;
//int PWMpin_RightMotor = 10;

// variable receive from remote controller joystick
int PWM_LeftMotor;
int PWM_RightMotor;

void setup() {
  // sets the digital pin as output
  pinMode(HC11_VCC, OUTPUT);
  pinMode(HC11_GND, OUTPUT);
  //pinMode(HC11_SET, OUTPUT);

  // set VCC, GND always produce voltage
  digitalWrite(HC11_VCC, HIGH);
  digitalWrite(HC11_GND, LOW);
  //digitalWrite(HC11_SET, LOW);
  
  // attach pins of ESC Signal to receive PWM 
  LeftMotor.attach(11);
  RightMotor.attach(10);

  // produce PWM to ESC Motor
  LeftMotor.writeMicroseconds(1000);
  RightMotor.writeMicroseconds(1000);

  // open UART, let Arduino receive data from RF
  ArduinoReceiveRF.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // X-axis for LeftMotor
  PWM_LeftMotor = ArduinoReceiveRF.parseInt();
  LeftMotor.writeMicroseconds(PWM_LeftMotor);
  Serial.print("LeftMotor: ");
  Serial.println(PWM_LeftMotor);
  Serial.println();

  // Y-axis for RightMotor
  PWM_RightMotor = ArduinoReceiveRF.parseInt();
  RightMotor.writeMicroseconds(PWM_RightMotor);
  Serial.print("RightMotor: ");
  Serial.println(PWM_RightMotor);
  Serial.println();

  // delay should be <5
  delay(5);
}
