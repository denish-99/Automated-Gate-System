#include <Servo.h> // Include the Servo library to control a servo motor

Servo myservo; // Create a servo object to control the servo motor

int pos = 0; // Variable to store the position of the servo motor (angle in degrees)
int cm = 0;  // Variable to store the distance measured by the ultrasonic sensor

// Function to read distance from the ultrasonic sensor
long readUltrasonicDistance(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT);    // Set the trigger pin as an output
    digitalWrite(triggerPin, LOW);  // Ensure trigger pin is low before sending a pulse
    delayMicroseconds(2);           // Wait for 2 microseconds
    digitalWrite(triggerPin, HIGH); // Send a 10 microsecond HIGH pulse to trigger the ultrasonic sensor
    delayMicroseconds(10);          // Wait for 10 microseconds
    digitalWrite(triggerPin, LOW);  // Set the trigger pin back to LOW after the pulse

    pinMode(echoPin, INPUT);       // Set the echo pin as an input to receive the pulse
    return pulseIn(echoPin, HIGH); // Measure the time it takes to receive the pulse back (echo time)
}

void setup()
{
    digitalWrite(12, LOW); // Set pin 12 to LOW (could be for some external device, though it's unused here)
    myservo.attach(9);     // Attach the servo motor to pin 9
    Serial.begin(9600);    // Start the serial communication at 9600 baud rate for debugging
}

void loop()
{
    // Calculate the distance in cm using the ultrasonic sensor by multiplying the echo time
    cm = 0.01723 * readUltrasonicDistance(6, 7); // Pins 6 and 7 are used for the trigger and echo of the ultrasonic sensor

    if (cm < 30)
    {                         // If the measured distance is less than 30 cm
        Serial.print(cm);     // Print the measured distance to the Serial Monitor
        Serial.println("cm"); // Print "cm" after the distance value for clarity

        // Rotate the servo from 0 degrees to 120 degrees in steps of 1 degree
        for (pos = 0; pos <= 120; pos += 1)
        {
            myservo.write(pos); // Set the servo motor to the current 'pos' value
            delay(15);          // Delay 15 milliseconds to control the speed of the servo movement
        }
        delay(500); // Wait for 500 milliseconds before moving the servo back

        // Rotate the servo back from 120 degrees to 0 degrees in steps of 1 degree
        for (pos = 120; pos >= 0; pos -= 1)
        {
            myservo.write(pos); // Set the servo motor to the current 'pos' value
            delay(15);          // Delay 15 milliseconds to control the speed of the servo movement
        }
        delay(5000); // Wait for 5000 milliseconds (5 seconds) before checking the distance again
    }
}