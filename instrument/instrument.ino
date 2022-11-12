const int trigPin = 9;
const int echoPin = 10;

long currentTime = 0;

int distanceOffset = 0;

int pPin = 8;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, INPUT); //button
  pinMode(A0, INPUT); //potentiometer
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  if (millis() - currentTime > 200 || currentTime == 0) {
    if (digitalRead(11) == 1) {
      distanceOffset = findDistance();
      Serial.print("new offset: ");
      Serial.println(distanceOffset);
      currentTime = millis();
    }
  }

  int distance = findDistance() - distanceOffset;
  //Serial.println(distance);
  int pitch = intoNotes(map(distance, 0, 20, 1, 7));
  //int vib = map(analogRead(A0), 1023, 0, 0, 100);

  if(distance <= 20){
    tone(pPin, pitch);
    Serial.println("sound");
  }else{
    noTone(pPin);
  }

  delay(10);
}

int findDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

float intoNotes(int x){
  switch(x){
    case 1:
      return 261.63;
    case 2:
      return 293.66;
    case 3:
      return 329.63;
    case 4:
      return 349.23;
    case 5:
      return 392.00;
    case 6:
      return 440.00;
    case 7:
      return 493.88;
    default:
      return 0;
  }
}
