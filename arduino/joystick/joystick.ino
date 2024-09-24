// Analog input pin numbers for X and Y axes
const int xAxisPin = A3;
const int yAxisPin = A2;

class joystickData {
  public:
    int centerX;
    int centerY;
};

int mappedX;
int mappedY;

void setup() {
  Serial.begin(9800);
  analogReadResolution(12);
  }

void loop() { 
  // Read the analog values from X and Y axes
  joystickData joys1;
  joys1.centerX = 2788;
  joys1.centerY = 2818;

  int xAxisValue = analogRead(xAxisPin);
  xAxisValue = analogRead(xAxisPin);
  int yAxisValue = analogRead(yAxisPin);
  yAxisValue = analogRead(yAxisPin);

  // Map the analog values to a range of -100 to 100 (optional)
  if(xAxisValue>=joys1.centerX){
    mappedX = map(xAxisValue, joys1.centerX, 4095, 0, 1000);
  }
  else {
    mappedX = map(xAxisValue, 0, joys1.centerX, -1000,0);
  }
  int mappedYValue = map(yAxisValue, 0, 1023, -100, 0);

  // Display the mapped values in the Serial Monitor
  Serial.print("X-axis: ");
  Serial.print(xAxisValue);
  Serial.print("\tmapped x : ");
  Serial.print(mappedX);
  Serial.print("\tY-axis: ");
  Serial.println(yAxisValue);

  // Add a small delay for smooth readings
  delay(100);
}