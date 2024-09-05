#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>


Adafruit_MPU6050 mpu;
BleMouse bleMouse("ESP32 Mouse");


const int button1Pin = 15;
const int button2Pin = 14;


int lastButton1State = HIGH;
int lastButton2State = HIGH;

void setup() {
  
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  Wire.begin(13, 12);

 
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  bleMouse.begin();
  Serial.println("Bluetooth cihazı başladı: ESP32 Mouse");
}

void loop() {
  static unsigned long lastUpdate = 0;
  unsigned long currentMillis = millis();

  if (bleMouse.isConnected()) {
    if (currentMillis - lastUpdate >= 20) { 
      lastUpdate = currentMillis;

      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      int deltaX = a.acceleration.y * 10;
      int deltaY = a.acceleration.x * 10;

      int button1State = digitalRead(button1Pin);
      int button2State = digitalRead(button2Pin);

      if (button1State != lastButton1State) {
        if (button1State == LOW) {
          bleMouse.press(MOUSE_LEFT);
        } else {
          bleMouse.release(MOUSE_LEFT);
        }
        lastButton1State = button1State;
      }

      if (button2State != lastButton2State) {
        if (button2State == LOW) {
          bleMouse.press(MOUSE_RIGHT);
        } else {
          bleMouse.release(MOUSE_RIGHT);
        }
        lastButton2State = button2State;
      }

      bleMouse.move(deltaX, deltaY);

      Serial.print("X: ");
      Serial.print(deltaX);
      Serial.print(" Y: ");
      Serial.println(deltaY);
    }
  } else {
    Serial.println("Mouse not connected!");
  }
}