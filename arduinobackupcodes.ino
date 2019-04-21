/* Li industrial technologies. Last save 4/20/19
 *  
 *  
 */

#include <Servo.h>
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

#define windmillpin  9
#define servo2pin 10
#define servo3pin 11

// variables
int windmilldelay = 250;
int frequency = 0;
int sensordelay = 10;
int greenval = 0;
int redval = 0;
int blueval = 0;
int avred = 0;
int avgreen = 0;
int avblue = 0;

//add servos
Servo Windmill;
Servo Servo2;
Servo Servo3;

void setup() {
  // attach color sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //attach servos 
  Windmill.attach(windmillpin);
  Servo2.attach(servo2pin);
  Servo3.attach(servo3pin);

  //resets servos
  Windmill.write(0);
  Servo2.write(180);
  Servo3.write(180);
  
  // Color sensor Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
}
void loop() {
  
  // Setting red filtered photodiodes to be read

  avred = 0;
  avgreen = 0;
  avblue = 0;
 for(int count = 0; count < 11; count++) {
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    redval = pulseIn(sensorOut, LOW);
    //Remaping the value of the frequency to the RGB Model of 0 to 255
   // frequency = abs(frequency);
    // Printing the value on the serial monitor
    //Serial.print("R= ");//printing name
    //Serial.print(redval);//printing RED color frequency
    //Serial.print("  ");
    delay(sensordelay);
    avred = redval + avred; 
    
    // Setting Green filtered photodiodes to be read
    
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    // Reading the output frequency
    greenval = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
    //Serial.print("G= ");//printing name
   // Serial.print(greenval);//printing RED color frequency
    //Serial.print("  ");
    delay(sensordelay);
    avgreen = greenval + avgreen;
    
    // Setting Blue filtered photodiodes to be read
    
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    // Reading the output frequency
    blueval = pulseIn(sensorOut, LOW);
    //Serial.print("B= ");//printing name
    //Serial.print(blueval);//printing RED color frequency
    //Serial.println("  ");
    delay(sensordelay);
    avblue = blueval + avblue;
 }
 avred = avred/10;
 avgreen = avgreen/10;
 avblue = avblue/10;
 Serial.print(avred);
 Serial.print(" ");
 Serial.print(avgreen);
 Serial.print(" ");
 Serial.println(avblue);
 
  // beginning filtration sequence
  int delaytime = 500;
  
  if(avred > avgreen && avred > avblue && avred <= 45 && avgreen <= 45 && avblue <= 45) { //detect white
    Windmill.write(90);
    Servo2.write(180);
    Servo3.write(90);
    delay(windmilldelay);
    Windmill.write(0);
    delay(delaytime);
    Servo2.write(180);
    Servo3.write(180);
    Serial.println("Detected WHITE");
  }
  else if(avred >= 90 && avgreen <= 60 && avblue >= 85 && avred > avgreen && avgreen < avblue && avred > avblue) {  //detect red
    Windmill.write(90);
    Servo2.write(180);
    Servo3.write(90);
    delay(windmilldelay);
    Windmill.write(0);
    delay(delaytime);
    Servo2.write(180);
    Servo3.write(180);
    Serial.println("Detected RED");
  }
  else if(avred >= 60 && avgreen >= 60 && avblue >= 70 && avgreen < avblue && avred < avblue) {  //detect green
    Windmill.write(90);
    Servo2.write(180);
    Servo3.write(90);
    delay(windmilldelay);
    Windmill.write(0);
    delay(delaytime);
    Servo2.write(180);
    Servo3.write(180);
    Serial.println("Detected GREEN");
  }
  else if(avred >= 90 && avgreen >= 80 && avblue >= 50 && avred > avgreen && avgreen > avblue && avred > avblue) {  //detect blue
    Windmill.write(90);
    Servo2.write(180);
    Servo3.write(90);
    delay(windmilldelay);
    Windmill.write(0);
    delay(delaytime);
    Servo2.write(180);
    Servo3.write(180);
    Serial.println("Detected BLUE");
  }
  else { //finds nothing
    Windmill.write(0);
    Servo2.write(180);
    Servo3.write(180);
    Serial.println("Detected NOTHING");
  }
}
