#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
from std_msgs.msg import Int32

def callback(data):
    print(data.range)
    if data.range > 10.0 : forward()
    else if data.range < 10.0 : halt()
    # else if data.range < 15.0 and data.range > 10.0 : left()
    # else if data.range < 20.0 and data.range > 15.0 : right()

def forward():
    pub.publish(1)

def halt():
    pub.publish(0)

def left():
    pub.publish(2)

def right():
    pub.publish(3)

if __name__ == '__main__':
    try:
        rospy.init_node('motor_controller', anonymous=True)
        pub = rospy.Publisher('imput', Int32, queue_size=10)
        rospy.Subscriber("ultrasound", Range, callback)
        rospy.spin()
    except rospy.ROSInterruptException:
        halt()
        pass    
