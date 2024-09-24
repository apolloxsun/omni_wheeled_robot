#define PPM_PIN 2     // Pin where the CPPM signal is connected
#define NUM_CHANNELS 8 // Adjust this depending on how many channels you are using
#define SYNC_GAP 3000  // Time in microseconds to detect the sync pulse

unsigned long channelValues[NUM_CHANNELS];  // Array to store channel values

void setup() {
  Serial.begin(115200);
  pinMode(PPM_PIN, INPUT);  // Set PPM pin as input
}

void loop() {
  static unsigned long lastTime = 0;
  static int currentChannel = 0;
  
  // Measure the length of the pulse
  unsigned long pulseLength = pulseIn(PPM_PIN, HIGH);

  // Check for sync pulse (longer gap means a new frame starts)
  if (pulseLength > SYNC_GAP) {
    currentChannel = 0;  // Reset the channel counter
  } 
  else if (currentChannel < NUM_CHANNELS) {
    // Store the pulse length as channel value
    channelValues[currentChannel] = pulseLength;
    currentChannel++;  // Move to the next channel
  }
  
  // Once all channels are read, print them out
  if (currentChannel == NUM_CHANNELS) {
    Serial.println("CPPM Channel Values:");
    for (int i = 0; i < NUM_CHANNELS; i++) {
      Serial.print("Channel ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(channelValues[i]);
    }
    Serial.println();
    delay(100);  // Delay to avoid overwhelming the serial monitor
  }
}
