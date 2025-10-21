#include <Arduino.h>
#include <Stepper.h>
#include <math.h>

// define Input pins of the Motor
#define OUTPUT1 5 // Connected to the Blue coloured wire
#define OUTPUT2 4 // Connected to the Pink coloured wire
#define OUTPUT3 3 // Connected to the Yellow coloured wire
#define OUTPUT4 2 // Connected to the Orange coloured wire

// Define the number of steps per rotation
const int stepsPerRotation = 2048; // 28BYJ-48 has 2048 steps per rotation in full step mode as given in data sheet

// Initialize the stepper motor with the sequence of control pins OUTPUT1, OUTPUT3, OUTPUT2, IN4
// OUTPUT1 and OUTPUT3 are connected to one coil and OUTPUT2 and OUTPUT4 are connected to one Coil
Stepper myStepper(stepsPerRotation, OUTPUT1, OUTPUT3, OUTPUT2, OUTPUT4);

const int minSpeedRPM = 1;
const int maxSpeedRPM = 19;
const float speedWaveFrequencyHz = 0.05f; // One full sinusoid every 20 seconds
int speedRPM = (minSpeedRPM + maxSpeedRPM) / 2; // Start near the midpoint

void setup()
{
  // Set the speed of the motor in RPM (adjust as needed)
  myStepper.setSpeed(speedRPM); // 15 RPM
}

void loop()
{
  unsigned long now = millis();
  float phase = (now / 1000.0f) * TWO_PI * speedWaveFrequencyHz;
  float normalized = (sin(phase) + 1.0f) * 0.5f; // Map sine from [-1, 1] to [0, 1]
  int newSpeedRPM = minSpeedRPM +
                    (int)(((maxSpeedRPM - minSpeedRPM) * normalized) + 0.5f);

  if (newSpeedRPM != speedRPM)
  {
    speedRPM = newSpeedRPM;
    myStepper.setSpeed(speedRPM);
  }

  myStepper.step(1);

  // Rotate in One Direction and complete one complete rotation i.e 2048 steps
  // myStepper.step(stepsPerRotation);
  // delay(1000);  // Delay between rotations
  // For Rotation in opposite direction provide the variable to the parameter with negative Sign
  // myStepper.step(-stepsPerRotation);
  // delay(1000);  // Delay between rotations
}
