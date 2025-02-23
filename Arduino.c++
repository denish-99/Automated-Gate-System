#include <NewPing.h>
#include <Servo.h> // Include the Servo library

// Define ultrasonic sensor pins
#define TRIG_PIN 12
#define ECHO_PIN 13
#define BUZZER_PIN 8
#define MAX_DISTANCE 200 // Maximum range (in cm)
#define SERVO_PIN 9

// Create a NewPing object to interact with the ultrasonic sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Create a Servo object to control the servo motor
Servo myServo;

void setup()
{
    // Initialize serial communication at 9600 baud rate
    Serial.begin(9600);

    // Give some time to initialize the serial monitor
    delay(200);

    // Set the buzzer pin as output
    pinMode(BUZZER_PIN, OUTPUT);

    // Attach the servo to the defined pin (Servo control)
    myServo.attach(SERVO_PIN);
    myServo.write(60);

    // Print a startup message
    Serial.println("Sensor started and active");
}

void loop()
{
    // Measure the distance from the ultrasonic sensor
    int distance = sonar.ping_cm();

    // Check if the sensor has detected an object within 40 cm
    if (distance > 0 && distance < 40)
    {
        // Object detected, open the gate (move servo to 90 degrees)
        Serial.println("Object detected: opening gate");
        digitalWrite(BUZZER_PIN, HIGH);
        delay(1000); // Turn on the buzzer
        digitalWrite(BUZZER_PIN, LOW);
        myServo.write(180); // Move servo to 90 degrees (open position)
        delay(5000);        // Give time for servo to reach position
        myServo.write(60);  // Move servo to 90 degrees (open position)
        Serial.println("Gate closed");
    }
    else
    {
        // No object detected, keep the gate closed
        Serial.println("No object detected: clear");
        digitalWrite(BUZZER_PIN, LOW); // Turn off the buzzer
        myServo.write(60);             // Move servo to 0 degrees (closed position)
    }

    // Add a small delay to avoid overloading the sensor with readings
    delay(500);
}