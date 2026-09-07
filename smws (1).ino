#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>
#include <NewPing.h>

// ===================== WiFi & Blynk =====================
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

// ===================== Ultrasonic Sensors =====================
// Outside Sensor
NewPing outsideSensor(16, 17, 200);

// Inside Sensor
NewPing insideSensor(22, 34, 200);

// ===================== Servos =====================
Servo lidServo;
Servo dumpServo;

// ===================== LED & Buzzer =====================
const int ledPin = 2;
const int buzzerPin = 15;

// ===================== IR Sensors =====================
#define IR_SENSOR_RIGHT 23
#define IR_SENSOR_LEFT 35

// ===================== Motor Driver (L298N) =====================
const int enableLeftMotor = 14;
const int leftMotorPin1 = 27;
const int leftMotorPin2 = 26;

const int enableRightMotor = 32;
const int rightMotorPin1 = 25;
const int rightMotorPin2 = 33;

#define MOTOR_SPEED 80

bool startMoving = false;

// PWM Channels
const int leftChannel = 0;
const int rightChannel = 1;

void setup()
{
  Serial.begin(115200);

  // Connect to WiFi & Blynk
  Blynk.begin(auth, ssid, pass);

  Serial.println("Connected to WiFi and Blynk!");

  // Servos
  lidServo.attach(18);
  dumpServo.attach(19);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);

  ledcSetup(leftChannel, 1000, 8);
  ledcAttachPin(enableLeftMotor, leftChannel);

  ledcSetup(rightChannel, 1000, 8);
  ledcAttachPin(enableRightMotor, rightChannel);

  lidServo.write(0);
  dumpServo.write(0);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  rotateMotor(0, 0);
}
void loop()
{
  int outsideDistance = outsideSensor.ping_cm();

  if (outsideDistance > 0 && outsideDistance < 20)
  {
    lidServo.write(90);
    delay(3000);
    lidServo.write(0);
  }

  int insideDistance = insideSensor.ping_cm();

  if (insideDistance > 0 && insideDistance <= 8)
  {
    startMoving = true;
  }

  if (startMoving)
  {
    int rightIR = digitalRead(IR_SENSOR_RIGHT);
    int leftIR = digitalRead(IR_SENSOR_LEFT);

    if (rightIR == LOW && leftIR == LOW)
    {
      rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
    else if (rightIR == HIGH && leftIR == LOW)
    {
      rotateMotor(0, MOTOR_SPEED);
    }
    else if (rightIR == LOW && leftIR == HIGH)
    {
      rotateMotor(MOTOR_SPEED, 0);
    }
    else if (rightIR == HIGH && leftIR == HIGH)
    {
      rotateMotor(0, 0);

      digitalWrite(buzzerPin, HIGH);
      delay(30000);
      digitalWrite(buzzerPin, LOW);

      dumpServo.write(90);
      delay(4000);
      dumpServo.write(0);

      digitalWrite(ledPin, HIGH);
      delay(5000);
      digitalWrite(ledPin, LOW);

      startMoving = false;
    }
  }

  delay(100);
}

void rotateMotor(int leftSpeed, int rightSpeed)
{
  if (leftSpeed > 0)
  {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
    ledcWrite(leftChannel, leftSpeed);
  }
  else
  {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
    ledcWrite(leftChannel, 0);
  }

  if (rightSpeed > 0)
  {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
    ledcWrite(rightChannel, rightSpeed);
  }
  else
  {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
    ledcWrite(rightChannel, 0);
  }
}