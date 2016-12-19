#!/usr/bin/env python
import rospy
from std_msgs.msg import String

if __name__ == '__main__':
    rospy.init_node('lcd_screen')

    environment_id = rospy.get_param("~environment_id")
    pub_name = '/actuators/lcd_screen/cmd'
    pub = rospy.Publisher(pub_name, String, queue_size=10)

    def air_temp_callback(temp):
        pub.publish('Air Temp: {}'.format(temp))
        #level = "normal" if (ph>6.0 and ph<7.5) else "abnormal"
        #pub.publiser("pH: {}".format(ph), "level: {}".format(level))
        
    sub_name = "/{}/measured/air_temperature".format(environment_id)
    sub = rospy.Subscriber(sub_name, Float64, air_temp_callback)

    rospy.spin()
