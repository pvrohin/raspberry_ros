#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#include <std_msgs/Int32.h>
#include <beginner_tutorials/motor.h>

ros::NodeHandle  nh;


#define echoPin 10 // Echo Pin
#define trigPin 11 // Trigger Pin

byte l1 = 2;  //left motor control pin 1
byte l2 = 3;  //left motor control pin 2
byte lpwm = 4; //left motor pwm pin


byte r1 = 7;  //right motor control pin 1
byte r2 = 8;  //right motor control pin 2
byte rpwm = 9; //right motor pwm pin

void forward()     //function defintion to run both the motors in forward direction
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(lpwm,255);

  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  digitalWrite(rpwm,255);

  }

void halt()        //function defintion to stop both the motors
{
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);
  digitalWrite(rpwm,HIGH);


  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);
  digitalWrite(lpwm,HIGH);


  }

void left()
{

  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(lpwm,0);

  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  digitalWrite(rpwm,255);

}

void right()
{
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);
  digitalWrite(lpwm,255);

  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
  digitalWrite(rpwm,0);




}
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration;
int distance; // Duration used to calculate distance
long range_time;
int value;

void messageCb( const std_msgs::Int32& motor_msg){
  value=motor_msg.data;
  if(value==1)
  {forward();}            //FORWARD

  if(value==0)
  {halt();}              // STOP

  if(value==2)
 {left();}           //LEFT

  if(value==3)
 {right();}	//RIGHT

}

ros::Subscriber<std_msgs::Int32> sub("/imput", messageCb );


sensor_msgs::Range range_msg;
ros::Publisher pub_range( "/ultrasound", &range_msg);


char frameid[] = "/ultrasound";


void setup() {

pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(13, OUTPUT);
  nh.initNode();


  nh.initNode();
  nh.advertise(pub_range);
  nh.subscribe(sub);

  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;


  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 60;



 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

}

float getRange_Ultrasound(){

  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;

 return distance ;
}


void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */



   if ( millis() >= range_time ){
    int r =0;


  range_msg.range = getRange_Ultrasound();
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    range_time =  millis() + 50;
  }


  nh.spinOnce();


delay(50);}
