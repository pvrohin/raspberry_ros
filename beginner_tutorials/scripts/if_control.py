#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
from std_msgs.msg import Int32MultiArray

a = Int32MultiArray()


def callback(data):
    print(data.range)
    if data.range > 10.0 : forward()
    else: halt()
    # else if data.range < 15.0 and data.range > 10.0 : left()
    # else if data.range < 20.0 and data.range > 15.0 : right()

def forward():
    a.data = [1,255]
    pub.publish(a)

def halt():
    a.data = [0,255]
    pub.publish(a)


def left():
    a.data = [2,255]
    pub.publish(a)
#
# def right():
#     pub.publish(3,255)

if __name__ == '__main__':
    try:
        rospy.init_node('motor_controller', anonymous=True)
        pub = rospy.Publisher('imput', Int32MultiArray, queue_size=10)
        rospy.Subscriber("ultrasound", Range, callback)
        rospy.spin()
    except rospy.ROSInterruptException:
        halt()
        pass
