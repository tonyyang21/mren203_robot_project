/**
* Code used for operating robot
*/
#include "pinAssignments.h"
#include "lights.h"
// #include "speaker.h"

#include <ros.h>
#include <geometry_msgs/Twist.h>

#define EN_L 3
#define IN1_L 4
#define IN2_L 5

#define EN_R 9
#define IN1_R 10
#define IN2_R 8

double speed_ang, speed_lin;
double speed_r, speed_l;
double pwm_r, pwm_l;
double wheel_rad = 0.0625, wheel_sep = 0.2775;
int count = 0;
float distanceFromObj;
float sharpF_val;

ros::NodeHandle nh;

void messageCb( const geometry_msgs::Twist& msg){
    speed_lin = msg.linear.x;
    speed_ang = msg.angular.z * 10;
    
    speed_r = speed_lin + wheel_sep / 2.0 * speed_ang;
    speed_l = speed_lin - wheel_sep / 2.0 * speed_ang;

    pwm_r = speed_r * 300;
    pwm_l = speed_l * 300;
}
    
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );

void Motors_init(){
    pinMode(EN_L, OUTPUT);
    pinMode(EN_R, OUTPUT);
    pinMode(IN1_L, OUTPUT);
    pinMode(IN2_L, OUTPUT);
    pinMode(IN1_R, OUTPUT);
    pinMode(IN2_R, OUTPUT);
    
    digitalWrite(EN_L, LOW);
    digitalWrite(EN_R, LOW);
    digitalWrite(IN1_L, LOW);
    digitalWrite(IN2_L, LOW);
    digitalWrite(IN1_R, LOW);
    digitalWrite(IN2_R, LOW);
}

void MotorL(int pwm){
    if (pwm > 0){
        digitalWrite(IN1_L, HIGH);
        digitalWrite(IN2_L, LOW);
        analogWrite(EN_L, pwm);
    }
    else {
        pwm=abs(pwm);
        digitalWrite(IN1_L, LOW);
        digitalWrite(IN2_L, HIGH);
        analogWrite(EN_L, pwm);
    }
}

void MotorR(int pwm){
    if (pwm > 0){
        digitalWrite(IN1_R, LOW);
        digitalWrite(IN2_R, HIGH);
        analogWrite(EN_R, pwm);
    }
    else {
        pwm=abs(pwm);
        digitalWrite(IN1_R, HIGH);
        digitalWrite(IN2_R, LOW);
        analogWrite(EN_R, pwm);
    }
}

int collision_warning()
{
    int flag = 0;
    // Read the sensor output (0-1023, which is 10 bits and fits inside an Arduino int-type)
    sharpF_val = analogRead(FRONT_SHARP_PIN);

    // If object is too close sound alarm
    float reading = convertDistance(sharpF_val);

    if (reading < 15.0)
    {
      flag = 1;
    }    
    return flag;
}

float convertDistance (float sharpVal){
    // 112.12*e^(-0.005*sharpVal)
    distanceFromObj = (112.12 * exp((-0.005*sharpVal)));
    return distanceFromObj;
}

void setup(){
    Serial.begin(9600);
    Motors_init();
    nh.initNode();
    nh.subscribe(sub);

    pinMode(buzzer, OUTPUT);
    lights_setup();
    yel_LED();
    delay(3000);
}

void loop(){
    green_LED();
    
    if(collision_warning() == 1 && speed_lin > 0){
        MotorL(0);
        MotorR(0);
        tone(buzzer, 800);
        Motors_init();
        red_LED();
        delay(100);
        count = 0; 
    } 
        nh.spinOnce();
        noTone(buzzer);
        Motors_init();
        MotorL(pwm_l);
        MotorR(pwm_r);
}
