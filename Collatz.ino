#define ledOdd 4
#define ledEven 7
int x;

void setup(){
    Serial.begin(9600);
    pinMode(ledOdd,OUTPUT);
    pinMode(ledEven,OUTPUT);
}

void loop(){
    Serial.print("Write a number: ");
    if(Serial.available()>0){x=Serial.read();}
    while(x!=1){
        if(x%2==0){
            x/=2;
            digitalWrite(ledEven,HIGH);
            delay(10);
            digitalWrite(ledEven,LOW);
        }
        else
        {
            x*=3+1;
            digitalWrite(ledOdd,HIGH);
            delay(10);
            digitalWrite(ledOdd,LOW);
        }
    }
}