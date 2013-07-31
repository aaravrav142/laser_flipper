laser_flipper
=============

A ROS node for reversing the order of a LaserScan message. Subscribes to base_scan and publishes to base_scan_flipped.
This is useful when you have a laser scanner mounted upside-down and you want to run slam with it
