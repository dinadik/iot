#include "HX711.h"

#define DOUT  12
#define CLK  13
#define BUFFER_SIZE 3  // Number of indexes before overwriting

HX711 scale;

float calibration_factor = 1; //Change this for calibration your load cell

int buffer[BUFFER_SIZE];  // Array to store values
int pointer = 0;          // Pointer to track the current index
bool bufferFull = false; 


void addValue(int value) {
    buffer[pointer] = value;   // Store value at current pointer position
    pointer = (pointer + 1) % BUFFER_SIZE; // Move pointer and wrap around if needed

    if (pointer == 0) {
        bufferFull = true;
    }
}

void printBuffer() {
    Serial.println("Buffer Contents:");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        Serial.print(buffer[i]);
        Serial.print(" ");
      
    }
    Serial.println();
}

float calculateAverage() {
    int sum = 0;
    int count = bufferFull ? BUFFER_SIZE : pointer; // Use full buffer size if filled

    for (int i = 0; i < count; i++) {
        sum += buffer[i];
    }

    return (count > 0) ? (float)sum / count : 0; // Avoid division by zero
}

void setup() {
  Serial.begin(115200);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  
  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);

  // Initialize buffer with -1 to indicate empty slots
  for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = -1;
    }
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  //Serial.print("Reading: ");
  //Serial.print(scale.get_units(), 4);
  //Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  //Serial.print(" calibration_factor: ");
  //Serial.print(calibration_factor);
  

 // static int counter = 0;

  addValue(scale.get_units());  // Add a new value to the buffer

  float avg = calculateAverage(); // Calculate the average
    //Serial.print("Average: ");
    Serial.println(avg);

    delay(1000); // Wait before adding the next value
  }  





