#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Range
from std_msgs.msg import Int32

def callback(data):
    print(data.range)
    if data.range > 10.0 : forward()
    else : stop()

def forward():
    pub.publish(1)   
   
def stop():
    pub.publish(0)   

if __name__ == '__main__':
    rospy.init_node('motor_controller', anonymous=True)

    pub = rospy.Publisher('imput', Int32, queue_size=10)
    rospy.Subscriber("ultrasound", Range, callback)
    rospy.spin()
