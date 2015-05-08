#define trigPin 13
#define echoPin 12
#define motorPinForward 2
#define motorPinReverse 3
#define motorPinPower 9
#define motorPinConstant 6

long duration, distance;
unsigned long counter;
unsigned long counter2;
unsigned long counter3;
unsigned long delay1;
unsigned long delay2;
unsigned long delay3;


void setup(){
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPinForward, OUTPUT);
  pinMode(motorPinReverse, OUTPUT);
  pinMode(motorPinPower, OUTPUT);
  digitalWrite(motorPinPower,HIGH);
  digitalWrite(motorPinForward, HIGH);
  digitalWrite(motorPinReverse,LOW);
  analogWrite(motorPinConstant,400);
}

void loop(){
  wallDetector();
  delay(100);
}

void wallDetector(){
  static int reader;
  static int forwardReader;
  static int reverseReader;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  reader = digitalRead(motorPinPower);
  forwardReader = digitalRead(motorPinForward);
  reverseReader = digitalRead(motorPinReverse);
  
  
  if(distance < 20){
    digitalWrite(motorPinPower,LOW);
    digitalWrite(motorPinConstant,LOW);
    counter = counter++;
  }
    if(counter == 20){
      delay1 = 20;
      counter = 0;
    }
    if(delay1 == 20){
      digitalWrite(motorPinPower,HIGH);
      digitalWrite(motorPinForward,LOW);
      digitalWrite(motorPinReverse,HIGH);
      counter2 = counter2++;
    }
    if(delay1 == 20 & counter2 == 10){
      delay2 = 20;
      counter2 = 0;
    }
    if(delay2 == 20){
      digitalWrite(motorPinPower,LOW);
      counter3 = counter3++;
    }
    if(counter3 == 20){
      delay3 = 20;
      counter3 = 0;
    }
    if(distance > 20 & delay3 == 20){
      analogWrite(motorPinConstant,400);
      digitalWrite(motorPinPower,HIGH);
      digitalWrite(motorPinForward,HIGH);
      digitalWrite(motorPinReverse,LOW);
      
    }
   if(delay1 == 20 && delay2 == 20 && delay3 == 20){
     counter = 0;
     counter2 = 0;
     counter3 = 0;
     delay1 = 0;
     delay2 = 0;
     delay3 = 0;
   }
  
  
  Serial.print(counter);
  Serial.print("  |  ");
  Serial.print(counter2);
  Serial.print("  |  ");
  Serial.print(counter3);
  Serial.print("  |  ");
  Serial.print(delay1);
  Serial.print("  |  ");
  Serial.print(delay2);
  Serial.print("  |  ");
  Serial.print(delay3);
  Serial.print("  |  ");
  Serial.print("cm: ");
  Serial.println(distance);
  
}
