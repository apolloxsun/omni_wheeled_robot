const int joysX = A2;

int sendData;

void setup(){
  Serial1.begin(57600);
  //Serial.begin(9600);
  analogReadResolution(10);
}

void loop(){
  sendData = analogRead(joysX);
  Serial1.print(sendData);
  //Serial.println(sendData);
  delay(5);
  Serial1.flush();
}