#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
from std_msgs.msg import Int32MultiArray

a = Int32MultiArray()

def callback(data):
    speed=pid(50 ,data.range)
    print('distance:',data.range,'speed:',speed)

    if data.range < 10.0 : halt()
    else: forward(speed)

def forward(speed):                         #function to move motors in forward direction
    a.data = [1,speed]
    pub.publish(a)

def halt():                                 #function to halt motor
    a.data = [0,0]
    pub.publish(a)

def left():                                 #function to move only right motor
    a.data = [2,255]
    pub.publish(a)

def pid(starting_distance,error):           #function to implement PID control
    if error > starting_distance : speed=255
    else:
        kp = 255 / starting_distance
        speed= kp*(error-10)                # speed = (error-10) x kp
    return speed


if __name__ == '__main__':
    try:
        rospy.init_node('motor_controller', anonymous=True)
        pub = rospy.Publisher('imput', Int32MultiArray, queue_size=10) # motor command publisher
        rospy.Subscriber("ultrasound", Range, callback)                # ultrasonic subscriber
        rospy.spin()
    except rospy.ROSInterruptException:
        halt()
        pass
