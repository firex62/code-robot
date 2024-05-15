//LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
char buf[32];

//DRIVER SERVO
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  100 // minimum pulse length count (out of 4096)
#define SERVOMAX  600 // maximum pulse length count (out of 4096)
#define SERVO_FREQ 50 // PWM frequency for the servo driver
#define SERVO_CHANNEL 0 // PWM channel on the PCA9685

//HOME SERVO
int home_servo_depan = 300;
int home_servo_belakang = 300;

#define servo_depan 5
#define servo_belakang 4

int x =digitalRead (servo_belakang);
int y = digitalRead (servo_depan);

//BUTTON
int potPin1 = A3; // analog pin for potentiometer input
int potPin2 = A2; // analog pin for potentiometer input
int val_1, val_2; // variable to store the potentiometer value
const int buttonPin = 5; //PIN PUSHBUTTON
bool state;     // variabel untuk menyimpan status tombol
bool button, buttonOld; //variabel pembacaan tombol
unsigned long prevMillis = 0;

//MOTOR VAKUM
const int   M1_A = 8 ;
const int   M1_B = 9 ;
const int ledpin = 13;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  //motor
  pinMode(buttonPin, INPUT_PULLUP); // konfigurasi pin tombol sebagai input dengan pull-up resistor
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(13, OUTPUT);

  //SERVO
  pwm.setPWM(5, 0, 180);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  pwm.setPWM(servo_depan, 0, home_servo_depan);
  pwm.setPWM(servo_belakang, 0, home_servo_belakang);


}

void loop() {
//Step 1
//  SERVO ATAS
      for (int i =300; i>=260 ; i--) {
    pwm.setPWM(15, 0, i--);
    delay(50);}
    
    
   //SERVO BAWAH
        for (int i =300; i>=241 ; i--) {
    pwm.setPWM(4, 0, i--);
    delay(50); }
    
//step 2
  //SERVO ATAS
        for (int i =260; i<=341 ; i++) {
    pwm.setPWM(15, 0, i++);
    delay(50);}

  //SERVO BAWAH
        for (int i =241; i<=378 ; i++) {
    pwm.setPWM(4, 0, i++);
    delay(50);} 

    //SERVO BAWAH
        for (int i =378; i>=120 ; i--) {
    pwm.setPWM(4, 0, i--);
    delay(50);}

         for (int i =341; i>=300 ; i--) {
    pwm.setPWM(15, 0, i--);
    delay(50);}

         for (int i =120; i<=300 ; i++) {
    pwm.setPWM(4, 0, i++);
    delay(50);}
    
    }
 
