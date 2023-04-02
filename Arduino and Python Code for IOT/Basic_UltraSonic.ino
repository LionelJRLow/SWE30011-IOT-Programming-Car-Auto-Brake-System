const int pingPin = 3; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor
const int yellow1= 6;
const int yellow2=7;
int motorPin = 4;
int buzzer=5;
long duration, inches, cm;
bool fan=true;

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(motorPin,OUTPUT);
   pinMode(buzzer,OUTPUT);
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
  pinMode(yellow1,OUTPUT);
   pinMode(yellow2, OUTPUT);
}

void loop() {

digitalWrite(yellow1,HIGH);
digitalWrite(yellow2,HIGH);
   
    char state = Serial.read();
if (state == 'a')
    {
      fan=true;
    }
if (state == 'b')
    {
      fan=false;
    }
if (fan==true){
  digitalWrite(motorPin, HIGH);
   noTone(buzzer);
      delay(1);
  }

  if(fan==false) {
    digitalWrite(motorPin, LOW);
   
    tone(buzzer,349);
      delay(1);
    }
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   Serial.println(cm);
   delay(250);


}



long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
