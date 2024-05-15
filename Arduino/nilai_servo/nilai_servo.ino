//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
char buf[32];

//DRIVER SERVO
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  100 // minimum pulse length count (out of 4096)
#define SERVOMAX  600 // maximum pulse length count (out of 4096)
#define SERVO_FREQ 50 // PWM frequency for the servo driver
#define SERVO_CHANNEL 0 // PWM channel on the PCA9685

//HOME SERVO
int home_servo_bawah = 500;
int home_servo_depan = 160;
int home_servo_belakang = 550;

#define servo_bawah 8
#define servo_depan 15
#define servo_belakang 4

//BUTTON
int potPin1 = A11; // analog pin for potentiometer input
int potPin2 = A12; // analog pin for potentiometer input
int potPin3 = A13; // analog pin for potentiometer input
int val_1, val_2, val_3; // variable to store the potentiometer value
const int buttonPin = 5; //PIN PUSHBUTTON
bool state;     // variabel untuk menyimpan status tombol
bool button, buttonOld; //variabel pembacaan tombol
unsigned long prevMillis = 0;

//MOTOR VAKUM
const int   M1_A = 50 ;
const int   M1_B = 48 ;
const int ledpin = 13;

void setup() {
  Serial.begin(9600);
//  lcd.begin();
  lcd.init();
  lcd.backlight();

  //motor
  pinMode(buttonPin, INPUT_PULLUP); // konfigurasi pin tombol sebagai input dengan pull-up resistor
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(13, OUTPUT);

  //SERVO
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  pwm.setPWM(servo_depan, 0, home_servo_depan);
  pwm.setPWM(servo_belakang, 0, home_servo_belakang);
  pwm.setPWM(servo_bawah, 0, home_servo_bawah);
}

void loop() {
  //BUTTON
  unsigned long currMillis = millis();
  if (currMillis - prevMillis >= 50) {
    prevMillis = currMillis;
    button = !digitalRead(buttonPin);// membaca status tombol

    if (button && !buttonOld) {
      state = !state;
    }
    buttonOld = button;
  }
  Serial.println(state);          // menampilkan status tombol ke Serial Monitor
  Serial.println(button);
  Serial.println(buttonOld);

  if (state) {
    digitalWrite(M1_A, LOW);
    digitalWrite(M1_B, HIGH);
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(M1_A, HIGH);
    digitalWrite(M1_B, HIGH);
    digitalWrite(13, LOW);
  }

  //POTENSIO 1 SERVO BAWAH
  val_1 = analogRead(potPin1); // read the potentiometer value (0 to 1023) //300/500
  int pulse1 = map(val_1, 0, 1023, 100, 600); // map the potentiometer value to servo pulse range 150, 400
  pwm.setPWM(15, 0, pulse1); // set the servo pulse width
  Serial.print("Potentiometer Value: ");
  Serial.print(val_1);

  Serial.print("  Servo Pulse: ");
  Serial.println(pulse1);

  //delay(5); // small delay to prevent jitter

  //POTENSIO 2 SERVO DEPAN
  val_2 = analogRead(potPin2); // read the potentiometer value (0 to 1023)
  int pulse2 = map(val_2, 0, 1023, 100, 600); // map the potentiometer value to servo pulse range 300, 400
  pwm.setPWM(8, 0, pulse2); // set the servo pulse width
  Serial.print("Potentiometer Value: ");
  Serial.print(val_2);
  Serial.print("  Servo Pulse2: ");
  Serial.println(pulse2);

  //POTENSIO 3 SERVO BELAKANG
  val_3 = analogRead(potPin3); // read the potentiometer value (0 to 1023)
  int pulse3 = map(val_3, 0, 1023, 100, 600); // map the potentiometer value to servo pulse range 300, 400
  pwm.setPWM(4, 0, pulse3); // set the servo pulse width
  Serial.print("Potentiometer Value: ");
  Serial.print(val_3);
  Serial.print("  Servo Pulse3: ");
  Serial.println(pulse3);

  sprintf(buf, "1 PUL: %.3d POT1: %.3d",pulse1, val_1);
  lcd.setCursor(0, 0);
  lcd.print(buf);
  sprintf(buf, "2 PUL: %.3d POT2: %.3d",pulse2, val_2);
  lcd.setCursor(0, 1);
  lcd.print(buf);
  sprintf(buf, "3 PUL: %.3d POT3: %.3d",pulse3, val_3);
  lcd.setCursor(0, 2);
  lcd.print(buf);
  delay(5);
}
