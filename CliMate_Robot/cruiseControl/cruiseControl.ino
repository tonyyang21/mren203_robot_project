
// #include <Arduino_LSM6DS3.h>;

//------------------------------------------------Initializing Pins----------------------------------------------//
// Motor driver PWM pin
const byte pwmLeftPin = 3;  // Left
const byte pwmRightPin = 11; // Right

// Motor driver direction pin
const byte wheelDirecPinLeftF = 4;  // Set this pin to high to go forward
const byte wheelDirecPinLeftB = 5;  // Set this pin to high to go backwards
const byte wheelDirecPinRightF = 8;  // Set this pin to high to go forward
const byte wheelDirecPinRightB = 9;  // Set this pin to high to go backwards

// Left wheel encoder digital pins
const byte encoderSigALeft = 13;
const byte encoderSigBLeft = 12;

// Right wheel encoder digital pins
const byte encoderSigARight = 6;
const byte encoderSigBRight = 7;

// Motor PWM command variable [0-255]
byte u = 0;

//---------------------------------------------Initializing Constants--------------------------------------------//
// Radius of wheel
const float wheelRad = 0.0625;

// Encoder ticks per (motor) revolution (TPR)
const int TPR = 3000;

// Length from centre of left wheel to centre of right wheel
const double trackWidth = 0.2775; 

// Sampling interval for measurements in milliseconds
const int T = 1000;

//--------------------------------------------- Global Variables--------------------------------------------//
// Counters for milliseconds during interval
long t_now = 0;
long t_last = 0;

// Counter to keep track of encoder ticks [integer]
volatile long encoder_ticksL = 0;
volatile long encoder_ticksR = 0;

// Hold the integral error for PI controller.
double errorInt = 0;

//--------------------------------------------- Functions --------------------------------------------//
// Used to count the wheel ticks, called when SIGNAL_A goes HIGH
void decodeEncoderTicksL()
{
    if (digitalRead(encoderSigBLeft) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        encoder_ticksL--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        encoder_ticksL++;
    }
}
void decodeEncoderTicksR()
{
    if (digitalRead(encoderSigBRight) == LOW)
    {
        // SIGNAL_A leads SIGNAL_B, so count one way
        encoder_ticksR--;
    }
    else
    {
        // SIGNAL_B leads SIGNAL_A, so count the other way
        encoder_ticksR++;
    }
}
// Compute vehicle speed [m/s]
double compute_vehicle_speed(double v_L, double v_R)
{
      double v;
      v = 0.5 * (v_L + v_R);
      return v;
}

// Compute vehicle turning rate [rad/s]
double compute_vehicle_rate(double v_L, double v_R)
{
    double omega;
    omega = 1.0 / trackWidth * (v_R - v_L);
    return omega;
}

// Wheel speed PI controller function
short getu(double enow, double eint, double kP, double kI)
{
    short u;
    u = (short)(kP * enow + kI * eint);
    if (u > 255)
        u = 255;
    else if (u < -255)
        u = -255;
    return u;
}

short piAlgorithm(float vdesired, float vcurr)
{
    double errorCurr = vdesired - vcurr;
    errorInt += errorCurr;
    return getu(errorCurr, errorInt, 200.0, 100.0);
}

void cruiseControl(float velL, float velR, float vd, float wd)
{
    // compute the speeds for the left and right wheels
    float vdLeft = vd - trackWidth * wd / 2;
    float vdRight = vd + trackWidth * wd / 2;

    short pwmLeft = piAlgorithm(vdLeft, velL);
    short pwmRight = piAlgorithm(vdRight, velR);

    digitalWrite(wheelDirecPinLeftF, HIGH);
    digitalWrite(wheelDirecPinLeftB, LOW);

    digitalWrite(wheelDirecPinRightF, HIGH);
    digitalWrite(wheelDirecPinRightB, LOW);

    analogWrite(pwmLeftPin, pwmLeft);
    analogWrite(pwmRightPin, pwmRight);
}


void setup()
{
    // Open the serial port at 9600 bps
    Serial.begin(9600);
    
    // Set the pin modes for PWM
    pinMode(pwmLeftPin, OUTPUT);
    pinMode(pwmRightPin, OUTPUT);

    // Set the pin modes for the motor driver
    pinMode(wheelDirecPinLeftF, OUTPUT);
    pinMode(wheelDirecPinLeftB, OUTPUT);
    pinMode(wheelDirecPinRightF, OUTPUT);
    pinMode(wheelDirecPinRightB, OUTPUT);

    // Set the pin modes for the encoders
    pinMode(encoderSigALeft, INPUT);
    pinMode(encoderSigBLeft, INPUT);
    pinMode(encoderSigARight, INPUT);
    pinMode(encoderSigBRight, INPUT);
    
    // Print a message
    Serial.print("Program initialized.");
    Serial.print("\n");

    // Every time encoder pin goes high (pulse), call decodeEncoder to count ticks
    attachInterrupt(digitalPinToInterrupt(encoderSigALeft), decodeEncoderTicksL, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderSigARight), decodeEncoderTicksR, RISING);
}

void loop()
{
    // Get the elapsed time [ms]
    t_now = millis();

    if (t_now - t_last >= T)
    {
        // Estimate the velocity speeds
        float measuredVelocityL = wheelRad * 2.0 * PI * ((double)encoder_ticksL / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        float measuredVelocityR = wheelRad * 2.0 * PI * ((double)encoder_ticksR / (double)TPR) * 1000.0 / (double)(t_now - t_last);
        // Reset the encoder ticks counters
        encoder_ticksL = 0;
        encoder_ticksR = 0;

        // Cruise Control, set your dersired velocity [m/s] and angular velocity [rad/s]
        float velocityDesired = 0.5;
        float angVelocityDesired = 0.0;
        cruiseControl(measuredVelocityL, measuredVelocityR, velocityDesired, angVelocityDesired);

        // Record the current time [ms]
        t_last = t_now;       

    }
}
