void setup() {
  Serial.begin(9600);  
  Serial.println("HC-05 Bluetooth module readyy");
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();
    Serial.write(data);
}
