#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle  nh;


#define echoPin 10 // Echo Pin
#define trigPin 11 // Trigger Pin

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration;
int distance; // Duration used to calculate distance




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
long range_time;

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 

 

   if ( millis() >= range_time ){
    int r =0;

  
  range_msg.range = getRange_Ultrasound();
    range_msg.header.stamp = nh.now();
    pub_range.publish(&range_msg);
    range_time =  millis() + 50;
  
  
  
  
  if(range_msg.range>10)
  {
    
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(8,HIGH);
  digitalWrite(9,255);
  //digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  //digitalWrite(9,25);
  digitalWrite(2,HIGH);
  digitalWrite(4,255);
  //digitalWrite(8,LOW);
  digitalWrite(3,LOW);
   
  
    }
    
  
  if(range_msg.range<10){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(8,HIGH);
  digitalWrite(9,0);
  //digitalWrite(8,LOW);
  digitalWrite(7,1);
  //digitalWrite(9,25);
  digitalWrite(2,HIGH);
  digitalWrite(4,0);
  //digitalWrite(8,LOW);
  digitalWrite(3,1);
   }


  /*if(range_msg.data == 2){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(8,HIGH);
  digitalWrite(9,255);
  //digitalWrite(8,LOW);
  digitalWrite(7,LOW);
  //digitalWrite(9,25);
  digitalWrite(2,HIGH);
  digitalWrite(4,0);
  //digitalWrite(8,LOW);
  digitalWrite(3,1);
   }

   if(range_msg.data == 3){
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led
  digitalWrite(8,HIGH);
  digitalWrite(9,0);
  //digitalWrite(8,LOW);
  digitalWrite(7,1);
  //digitalWrite(9,25);
  digitalWrite(2,HIGH);
  digitalWrite(4,255);
  //digitalWrite(8,LOW);
  digitalWrite(3,0);
   }*/
  }

  
  nh.spinOnce();
 

delay(50);}
