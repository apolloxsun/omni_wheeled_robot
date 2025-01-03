#include <math.h>

#define md1_EN 26

#define motor1_IN1 2
#define motor1_IN2 3
#define motor1_D1 22
#define motor1_D2 24

#define motor2_IN1 5
#define motor2_IN2 4
#define motor2_D1 28
#define motor2_D2 30

#define md2_EN 27

#define motor3_IN1 9
#define motor3_IN2 8
#define motor3_D1 25
#define motor3_D2 23

#define motor4_IN1 7
#define motor4_IN2 6
#define motor4_D1 31
#define motor4_D2 29

float normaliseAngle();
float degreesToRadians();
float reduceToNinety();

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data

float angle = 0.0;
float length = 0.0;
float rot_angle = 0.0;
float rot_length = 0.0;

boolean newData = false;

int speedVal = 0;
float readVal;

float givenAng = 0;
float givenRotAng = 0;
float radians;
float radiansX;
float radiansY;
float normalAng;
float speedX;
float speedY;
float length3 = 0;

float motor1_val = 0.0;
float motor2_val = 0.0;
float motor3_val = 0.0;
float motor4_val = 0.0;

void setup() {
  //setting pinmodes
  pinMode(md1_EN, OUTPUT); pinMode(md2_EN, OUTPUT);//enable pins
  pinMode(motor1_IN2, OUTPUT); pinMode(motor1_IN1, OUTPUT); pinMode(motor1_D2, OUTPUT); pinMode(motor1_D1, OUTPUT); //motor1
  pinMode(motor2_IN2, OUTPUT); pinMode(motor2_IN1, OUTPUT); pinMode(motor2_D2, OUTPUT); pinMode(motor2_D1, OUTPUT); //motor 2
  pinMode(motor3_IN2, OUTPUT); pinMode(motor3_IN1, OUTPUT); pinMode(motor3_D2, OUTPUT); pinMode(motor3_D1, OUTPUT); //motor 3
  pinMode(motor4_IN2, OUTPUT); pinMode(motor4_IN1, OUTPUT); pinMode(motor4_D2, OUTPUT); pinMode(motor4_D1, OUTPUT); //motor 4

  //setting pin status
  digitalWrite(md1_EN, HIGH); digitalWrite(md2_EN, HIGH);//enable pins
  digitalWrite(motor1_D1, LOW); digitalWrite(motor1_D2, HIGH); digitalWrite(motor1_IN1, LOW); digitalWrite(motor1_IN2, LOW); //motor1
  digitalWrite(motor2_D1, LOW); digitalWrite(motor2_D2, HIGH); digitalWrite(motor2_IN1, LOW); digitalWrite(motor2_IN2, LOW);//motor2
  digitalWrite(motor3_D1, LOW); digitalWrite(motor3_D2, HIGH); digitalWrite(motor3_IN1, LOW); digitalWrite(motor3_IN2, LOW);//motor3
  digitalWrite(motor4_D1, LOW); digitalWrite(motor4_D2, HIGH); digitalWrite(motor4_IN1, LOW); digitalWrite(motor4_IN2, LOW);//motor4

  //analogWrite(motor1_IN1, 50);  analogWrite(motor2_IN1, 50);  analogWrite(motor3_IN2, 50);  analogWrite(motor4_IN2, 50);

  Serial.begin(9600);
  Serial.println("Starting...");

}


void loop() {
  //getting angle value
    recvWithStartEndMarkers();
  if (newData == true) {
      strcpy(tempChars, receivedChars);
          // this temporary copy is necessary to protect the original data
          //   because strtok() used in parseData() replaces the commas with \0
      parseData();
      givenAng = angle - 45.0;
      givenRotAng = rot_angle;
      newData = false;
  }

  //processing angle data

  radiansX = degreesToRadians(normaliseAngle(givenAng));
  //radiansY = PI/2 - radiansX;
  Serial.print("radians : ");
  Serial.println(radiansX);


  if(givenRotAng >= -90 && givenRotAng < 90){
    length3 = rot_length;
  }
  else if(givenRotAng < -90 || givenRotAng >= 90){
    length3 = -(rot_length);
  }

  float length1 = (length*cos(radiansX));
  float length2 = (length*sin(radiansX));

  float motor1_length = length1 + length3;
  float motor2_length = length2 - length3;
  float motor3_length = length1 + length3;
  float motor4_length = length2 - length3;

  if(length != 0 && rot_length != 0){
  speedX = map(length1, 0, 10, 0, 100);
  speedY = map(length2, 0, 10, 0, 100); }
  else{
  digitalWrite(motor1_IN1, LOW); digitalWrite(motor1_IN2, LOW); //motor1
  digitalWrite(motor2_IN1, LOW); digitalWrite(motor2_IN2, LOW);//motor2
  digitalWrite(motor3_IN1, LOW); digitalWrite(motor3_IN2, LOW);//motor3
  digitalWrite(motor4_IN1, LOW); digitalWrite(motor4_IN2, LOW);//motor4
  }

  Serial.print("length : ");
  Serial.print(length1);
  Serial.print(" ");
  Serial.print(length2);
  Serial.print(" ");
  Serial.println(length3);  

  Serial.print("angle : ");
  Serial.println(normaliseAngle(givenAng));


  // //seperating to quadrants

  // if(givenAng>=0 && givenAng<90){ //forward
  //   digitalWrite(motor1_IN1, HIGH); digitalWrite(motor1_IN2, LOW);
  //   digitalWrite(motor2_IN1, HIGH); digitalWrite(motor2_IN2, LOW);
  //   digitalWrite(motor3_IN1, LOW); digitalWrite(motor3_IN2, HIGH);
  //   digitalWrite(motor4_IN1, LOW); digitalWrite(motor4_IN2, HIGH);
  //   analogWrite(motor1_IN1, speedX); analogWrite(motor2_IN1, speedY); analogWrite(motor3_IN2, speedX); analogWrite(motor4_IN2, speedY);

  // }
  // else if(givenAng>=90 && givenAng<180){ //left
  //   digitalWrite(motor1_IN1, LOW); digitalWrite(motor1_IN2, HIGH);
  //   digitalWrite(motor2_IN1, HIGH); digitalWrite(motor2_IN2, LOW);
  //   digitalWrite(motor3_IN1, HIGH); digitalWrite(motor3_IN2, LOW);
  //   digitalWrite(motor4_IN1, LOW); digitalWrite(motor4_IN2, HIGH);
  //   analogWrite(motor1_IN2, speedY); analogWrite(motor2_IN1, speedX); analogWrite(motor3_IN1, speedY); analogWrite(motor4_IN2, speedX);
  // }
  // else if(givenAng>=180 && givenAng<270){ //backward
  //   digitalWrite(motor1_IN1, LOW); digitalWrite(motor1_IN2, HIGH);
  //   digitalWrite(motor2_IN1, LOW); digitalWrite(motor2_IN2, HIGH);
  //   digitalWrite(motor3_IN1, HIGH); digitalWrite(motor3_IN2, LOW);
  //   digitalWrite(motor4_IN1, HIGH); digitalWrite(motor4_IN2, LOW);
  //   analogWrite(motor1_IN2, speedX); analogWrite(motor2_IN2, speedY); analogWrite(motor3_IN1, speedX); analogWrite(motor4_IN1, speedY);

  // }
  // else if(givenAng>=270 && givenAng<360){ //right
  //   digitalWrite(motor1_IN1, HIGH); digitalWrite(motor1_IN2, LOW);
  //   digitalWrite(motor2_IN1, LOW); digitalWrite(motor2_IN2, HIGH);
  //   digitalWrite(motor3_IN1, LOW); digitalWrite(motor3_IN2, HIGH);
  //   digitalWrite(motor4_IN1, HIGH); digitalWrite(motor4_IN2, LOW);
  //   analogWrite(motor1_IN1, speedY); analogWrite(motor2_IN2, speedX); analogWrite(motor3_IN2, speedY); analogWrite(motor4_IN1, speedX);
  // }

  delay(1000);
}


//functions

float degreesToRadians(float a){
  return (a/180) * PI;
  }

float normaliseAngle(float c){
  while(c<0){
    c += 360;
  }
  while(c>=360){
    c -= 360;
  }
  if(c>180){
    c = map(c, 180, 360, -180, 0);
  }
  return c;
}

float reduceToNinety(float d){
  while(d>90){
    d-=90;
  }
  return d;
}

//=================

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

float parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    angle = atof(strtokIndx);     // convert this part to a float

    strtokIndx = strtok(NULL, ",");
    length = atof(strtokIndx);     // convert this part to a float

    strtokIndx = strtok(NULL, ",");
    rot_angle = atof(strtokIndx);     // convert this part to a float

    strtokIndx = strtok(NULL, ",");
    rot_length = atof(strtokIndx);     // convert this part to a float

}
