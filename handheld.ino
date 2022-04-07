// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 2 //attach pin D3 Arduino to pin Trig of HC-SR04
#define vibe 7
#define buzz 9

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int samples[5];
int ct = 0;


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(vibe, OUTPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  samples[0] = -1;
  samples[1] = -1;
  samples[2] = -1;
  samples[3] = -1;
  samples[4] = -1;
}
void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(ct > 4){
    ct = 0;
  }
  samples[ct] = distance;
  ct += 1;

  int a = avg(samples);
  
  Serial.print(a);
  Serial.print("###");

  if (a < 300){
    int lightyear = map(a, 0, 300, 0, 750);
  
    digitalWrite(vibe, HIGH);
    delay(250);
    digitalWrite(vibe, LOW);
    delay(lightyear);
  }
  



  
}

int avg(int samples[]){
  
  int total = 0;
  if(samples[4] >= 0){
    //Serial.print("Samples:\n");
    for (int i = 0; i < 5; i++){
      total += samples[i];
      //Serial.print(samples[i]);
      //Serial.print("\n");
    }
    //Serial.print("end samples\n");
    
    //
    //
    //Serial.print(i);
    //Serial.print("+++++\n");
  }
  return total/5;
}
