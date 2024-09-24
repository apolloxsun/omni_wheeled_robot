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

float readVal;
float givenAng;

void setup() {
  //setting pinmodes
  pinMode(md1_EN, OUTPUT); pinMode(md2_EN, OUTPUT);//enable pins
  pinMode(motor1_IN2, OUTPUT); pinMode(motor1_IN1, OUTPUT); pinMode(motor1_D2, OUTPUT); pinMode(motor1_D1, OUTPUT); //motor1
  pinMode(motor2_IN2, OUTPUT); pinMode(motor2_IN1, OUTPUT); pinMode(motor2_D2, OUTPUT); pinMode(motor2_D1, OUTPUT); //motor 2
  pinMode(motor3_IN2, OUTPUT); pinMode(motor3_IN1, OUTPUT); pinMode(motor3_D2, OUTPUT); pinMode(motor3_D1, OUTPUT); //motor 3
  pinMode(motor4_IN2, OUTPUT); pinMode(motor4_IN1, OUTPUT); pinMode(motor4_D2, OUTPUT); pinMode(motor4_D1, OUTPUT); //motor 4


  //setting pin status
  digitalWrite(md1_EN, HIGH); digitalWrite(md2_EN, HIGH);//enable pins
  digitalWrite(motor1_D1, LOW); digitalWrite(motor1_D2, HIGH); digitalWrite(motor1_IN1, HIGH); //motor1
  digitalWrite(motor2_D1, LOW); digitalWrite(motor2_D2, HIGH); digitalWrite(motor2_IN1, HIGH); //motor2
  digitalWrite(motor3_D1, LOW); digitalWrite(motor3_D2, HIGH); digitalWrite(motor3_IN1, HIGH); //motor3
  digitalWrite(motor4_D1, LOW); digitalWrite(motor4_D2, HIGH); digitalWrite(motor4_IN1, HIGH); //motor4

  analogWrite(motor1_IN1, 30);   analogWrite(motor2_IN1, 30);   analogWrite(motor3_IN1, 30);   analogWrite(motor4_IN1, 30); 

  Serial.begin(9600);
  Serial.println("Starting...");

}

void loop(){
  /*  if(Serial.available() > 0){
  readVal = Serial.parseFloat();
  givenAng = readVal;

  }
  Serial.println(givenAng);
  digitalWrite(motor1_IN1, LOW);
  analogWrite(motor1_IN2, givenAng);*/
}