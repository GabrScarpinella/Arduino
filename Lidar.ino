//Made for the OBR (Brazilian robotics olimpics)

#include <Servo.h>
#include <Wire.h>
#include <VL53L1X.h>
#include <Ultrasonic.h>

Servo servo;
VL53L1X sensor;
Ultrasonic ultrasonic(12, 13);

int ultrasonic;
int laser;
int pos=0;

void setup() {
    servo.attach(9);
    while (!Serial) {}
    Serial.begin(115200);          //Ultrasonic asks for Serial.begin(9600);, but I'll do nothing.
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
void posToSensors() {               //Prints the servo's angle and the correspondent laser and ultrasonic measurements.
    servo.write(pos);
    Serial.print(pos);              //Servo's angle
    Serial.print(":");
    Serial.print(laser);            //Laser's measurement (mm)
    Serial.print(",");
    Serial.println(ultrasonic*10);  //Ultrasonic's measurement (mm)
}

void loop() {
    ultrasonic=ultrasonic.read();
    laser=sensor.read();
    for (pos=0; pos<=180; pos+=1) {
        //posToSensors();
        if(laser<ultrasonic*10) {
        Serial.println("Object detected.");
        }
        delay(2);
    }
    for (pos=180; pos>=0; pos-=1) {
        //posToSensors();
        if(laser<ultrasonic*10) {
        Serial.println("Object detected.");
        }
        delay(2);
    }
}
