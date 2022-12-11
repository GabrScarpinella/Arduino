#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>

Servo servo;
VL53L1X sensor;
int pos = 0;

void setup() {
  servo.attach(9);
  while (!Serial) {}
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  sensor.setDistanceMode(VL53L1X::Long);
  sensor.setMeasurementTimingBudget(50000);
  sensor.startContinuous(50);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    Serial.print(pos);
    Serial.print(":");
    Serial.println(sensor.read());
    delay(2);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    Serial.print(pos);
    Serial.print(":");
    Serial.println(sensor.read());
    delay(2);
  }
}
