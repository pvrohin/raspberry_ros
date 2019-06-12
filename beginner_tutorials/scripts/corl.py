#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Range
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32MultiArray

def differential(v, w, L=0.017 , R=0.07):

    vr = (2*v + w*L) / (2*R)
    vl = (2*v - w*L) / (2*R)
    return vr,vl

def callback(vel_msg):
    print('start')
    vr , vl  = differential(vel_msg.linear.x, vel_msg.angular.z, L=0.017 , R=0.07)
    pub.publish([vr,vl])
    print('v:',vel_msg.linear.x,'w:',vel_msg.angular.z, 'v_r:',vr*9.5493 ,'v_l:',vl*9.5493)


if __name__ == '__main__':
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("cmd_vel", Twist, callback)
    pub = rospy.Publisher('wheel_velocities', Float32MultiArray, queue_size=10) # motor command publisher
    # rospy.Subscriber("ultrasound", Range, callback)                # ultrasonic subscriber

    rospy.spin()
