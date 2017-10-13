#include <SoftwareSerial.h>
/*
 * Code toggle nut nhan thi moi bat module RF
 * khai bao chan nut nhan cua joystick
 * analogRead trang thai joystick
 * toggle thi bat/tat chan RF
 * Good Morning ViệtNam.
Sau đây là bản chỉ dẫn từng bước thao tác để chỉnh ga đầu, ga cuối của điều tốc MGM, 1 điều đáng mừng cho những ai thích chơi hàng khủng là điều tốc của MGM mổi khi cắm pin vô chạy đều phải chỉnh ga đầu ga cuối, như vậy mới hiệu quả!
Bước thứ nhất: vặn Mote lên, kéo full ga.
Bước thứ hai: Vặn On đìều tốc, chờ nghe 3 tiếng (tít,tít,tít)
Bước thứ ba: buông ga Mote, chờ nghe 1 tiếng (tít)
bước thứ tư: kéo full ga và chờ nghe 3 tiếng (tít,tít,tít) sau đó buông ga.
chờ vài giây.........điều tốc đã sẳn sàn.......
chúc may mắn!
*/
int ledPin = 13;                 // LED connected to digital pin 13

// VCC, GND, SET  pin of HC11 RF
//int HC11_SET = 3;

// TX Pin of RF, RX pin of RF
SoftwareSerial ArduinoSendRF(6, 5); 

// define joystick pins Analog
int joyX_pin = A0;
int joyY_pin = A1;

// variable to read value from analog pins
int joyX_val;
int joyY_val;

// mapped values
int PWM_LeftMotor; // Y-axis
int PWM_RightMotor; // X-axis


void setup() {
  // sets the digital pin as output
  //pinMode(HC11_VCC, OUTPUT);
  //pinMode(HC11_GND, OUTPUT);
  //pinMode(HC11_SET, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // set VCC, GND always produce voltage
  //digitalWrite(HC11_VCC, HIGH);
  //digitalWrite(HC11_GND, LOW);
  //digitalWrite(HC11_SET, LOW);
  digitalWrite(ledPin, HIGH);   // sets the LED on
  
  // open UART, let Arduino send data to RF 
  ArduinoSendRF.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // read value of joystick X for Left Motor
  // map(value, fromLow, fromHigh, toLow, toHigh)
  joyX_val = analogRead(joyX_pin);
  // ESC PWM value between 500-1500
  PWM_LeftMotor = map(joyX_val, 0, 1023, 480, 1543);
  ArduinoSendRF.println(PWM_LeftMotor);
  Serial.print("PWM_LeftMotor: ");
  Serial.println(PWM_LeftMotor);
  Serial.println();

  
  // read value of joystick Y for Right Motor
  joyY_val = analogRead(joyY_pin);
  // ESC PWM value between 510-1533
  PWM_RightMotor = map(joyY_val, 0, 1023, 520, 1543);
  ArduinoSendRF.println(PWM_RightMotor);
  Serial.print("PWM_RightMotor: ");
  Serial.println(PWM_RightMotor);
  Serial.println();

  // delay should be <5
  //delay(5);
}
