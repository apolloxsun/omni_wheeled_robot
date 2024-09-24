#define md1_EN 26

#define motor1_IN1 2
#define motor1_IN2 3
#define motor1_D1 22
#define motor1_D2 24

int recievedData = 0;
int mappedData = 0;

void setup(){
  pinMode(md1_EN, OUTPUT);//enable pins
  pinMode(motor1_IN2, OUTPUT); pinMode(motor1_IN1, OUTPUT); pinMode(motor1_D2, OUTPUT); pinMode(motor1_D1, OUTPUT);
  digitalWrite(md1_EN, HIGH); //enable pins
  digitalWrite(motor1_D1, LOW); digitalWrite(motor1_D2, HIGH); digitalWrite(motor1_IN1, LOW); //digitalWrite(motor1_IN2, HIGH); //motor1
  Serial1.begin(57600);
}

void loop(){
  while(Serial1.available() > 0){
  recievedData = Serial1.read();

  mappedData = map(recievedData, 4, 1023, 0, 255);
  
  analogWrite(motor1_IN2, recievedData);
  }

  // Serial1.print(recievedData);

  Serial1.flush();
  delay(5);

}