import sys
sys.path.append('/home/hiep/linuxcnc-dev/lib/python')

import linuxcnc

while(1):
    try:
        s = linuxcnc.stat() # create a connection to the status channel
        s.poll() # get current values
        x = 'joint_position'
        print x
        print getattr(s,x)

        #print s.axis[0]
    except linuxcnc.error, detail:
        print "error", detail
        sys.exit(1)

#python /home/hiep/Desktop/gazebo_plugin/rrbot/linuxcnc_test.py
