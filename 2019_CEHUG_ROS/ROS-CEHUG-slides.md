---
author: Marek Gawryszewski
title: ROS, czyli o robotach słów kilka
date: 26-06-2019
---

#  The problem

## Robot software construction

* buildsystem
* algorithm(s) implementation
* logging (online/offline)
* teleoperation
* simulation (optional?)
* interfacing with hardware
* ...?

## Robot software construction

Business problem here is only one:

_algorithm(s) implementation_

The rest is infrastructure.

# ROS: what and why

## What ROS provides

* Communication infrastructure
* Message passing
* RPC
* Robot specific features (i.e. pose estimation, mapping, localization)

## expectations vs ROS

:::::::::::::: {.columns}
::: {.column width="50%"}
* buildsystem
* algorithm(s) implementation
* logging (online/offline)
* teleoperation
* simulation (optional?)
* interfacing with hardware
* ...?

:::
::: {.column width="50%"}
* catkin
* existing algorithms
* rosbag
* gazebo, v-rep, webots
* existing drivers
:::
::::::::::::::

## Definitions

<small>
_Nodes_: A node is an executable that uses ROS to communicate with other nodes.

_Messages_: ROS data type used when subscribing or publishing to a topic.

_Topics_: Nodes can publish messages to a topic as well as subscribe to a topic to receive messages.

_Master_: Name service for ROS (i.e. helps nodes find each other)

_roscore_: Master + rosout + parameter server 

[source](http://wiki.ros.org/ROS/Tutorials/UnderstandingNodes#Quick_Overview_of_Graph_Concepts)
</small>

# Demo 1

##

Turtlesim - LOGO in ROS.

## roscore

```bash
roscore
```

```bash
rosrun turtlesim turtlesim_node
```

## node

```bash
rosnode list

rosnode info /turtlesim
```

## service

```bash
rosservice list
```

## topic

```bash
rostopic list
rostopic list -v
rostopic info /turtle1/cmd_vel
rostopic type /turtle1/cmd_vel
rostopic echo /turtle1/pose
```

## type

```bash
rosmsg show geometry_msgs/Twist
```

## more

```bash
rostopic type /turtle1/cmd_vel | rosmsg show
```
## let's move our turtle

```bash
rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'
```

## Where is the turtle?

```bash
rostopic echo /turtle1/pose
```

## reset turtle position

```bash
rosservice call /reset
```

##

Turtle require message stream with 1Hz.

```bash
rostopic pub -r 0.5 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'
rostopic pub -r 10 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'
```

## rqt

```bash
rqt
```

## Keyboard control

Another node to control turtle

```bash
rosrun turtlesim turtle_teleop_key
```

## see what happened!

```bash
rosnode list
rosnode info /turtlesim_node
```

## Let's add some logic!

```bash
#workspace
mkdir demo
cd demo
mkdir src
catkin_make
## package demo
cd src
catkin_create_pkg demo roscpp rospy turtlesim
```

## Adjustments

* CMakeLists.txt
* package.xml

## code

```
src/demo_node.cpp
```
## run

```bash
rosrun demo demo_node
```

##

```bash
source demo/devel/setup.zsh
catkin_make
```

# Demo 2

## Arduino

Arduino is controlled with ROS node.

## Installation

* get Arduino IDE from arduino.cc
* install rosserial

```bash
sudo apt install ros-melodic-rosserial_arduino
```

```bash
rosrun rosserial_arduino make_libraries.py .
```

##

```bash
sudo chmod a+rw /dev/ttyUSB0
rosrun rosserial_python serial_node.py /dev/ttyUSB0
rostopic list
rostopic pub message std_msgs/String "Kolejny tekst" --once

rostopic echo /message_size
```

[rosserial](http://wiki.ros.org/rosserial_python)

# Demo 3

## Turtlebot

![](./images/png/turtlebot3_series.png)

Turtlebot is simulated in Gazebo controled with ROS node

[Turtlebot3](https://robots.ros.org/turtlebot3/)

## Turtlebot

Teleoparation in default world

```bash
 export TURTLEBOT3_MODEL=waffle_pi
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch

 export TURTLEBOT3_MODEL=waffle_pi
roslaunch turtlebot3_gazebo turtlebot3_world.launch
```
## Turtlebot

* [More tutorials](http://emanual.robotis.com/docs/en/platform/turtlebot3/overview/)
* [Simulation](http://emanual.robotis.com/docs/en/platform/turtlebot3/simulation/#turtlebot3-simulation-using-fake-node)
* [Teleoperation](http://emanual.robotis.com/docs/en/platform/turtlebot3/simulation/#turtlebot3-simulation-using-fake-node)