#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <Adafruit_NeoPixel.h>

const int PulseWire=0;
int pin=4;
int ledes=20;
int Signal;
int Threshold=520;
int buzzer=8;
int bpm;

PulseSensorPlayground pulseSensor;
Adafruit_NeoPixel faixa(ledes, pin , NEO_GRB + NEO_KHZ800);


void setup(){
  faixa.begin();
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  pulseSensor.begin();
  pinMode(buzzer,OUTPUT);
}


void loop(){
  bpm = pulseSensor.getBeatsPerMinute();
  if(pulseSensor.sawStartOfBeat()){
    faixaLiga();
    faixaDesliga();
  }
  if(bpm<20){morreu();}
  delay(10);
}


void faixaLiga(){
  tone(buzzer,256, 100);
  for (int i = 0; i < ledes; i++){
    faixa.setPixelColor(i, faixa.Color(255, 0, 0));
    faixa.show();
    delay(1500 / bpm);
  }
  noTone(buzzer);
}
void faixaDesliga(){
  for (int i = ledes; i > 0; i--){
    faixa.setPixelColor(i, faixa.Color(255, 255, 255));
    faixa.show();
    delay(1500 / bpm);
  }
}
void morreu(){
  tone(buzzer,256);
  faixa.setPixelColor(0, faixa.Color(255, 0, 0));
  faixa.show();
  for (int i = 0; i < 256; i++){
    faixa.setPixelColor(0, faixa.Color(255, i, i));
    faixa.show();
    delay(5);
  }
  faixa.clear();
  noTone(buzzer);
}