# simple_bot
Simple 2 wheel Differential Drive robot.


## Initial Setup
Follow the given instructions in sequence:


Clone the Project
```bash
git clone https://github.com/Pratham-Pandey/simple_bot.git
```

Change Directory
```
cd simple_bot/
cd pratham_pandey_ws/
```

Build Project
```bash
  colcon build --symlink-install
```

Source Project
```bash
  source install/setup.bash 
```

Now follow the commands below to run each package.


## Question 1: Package -> bot_description

Visualize robot in Rviz.
```bash
  ros2 launch bot_description rviz.launch
```

> [!NOTE]
> The robot's wheels won't appear yet, as joint states aren't published. Launch the Gazebo simulation (next step) to start the joint_state_publisher.

Visualize robot in Gazebo.
```bash
  ros2 launch bot_description spawn.launch
```
> [!NOTE]
> Check RViz now—wheels should be visible, and the camera view should be active.

Launch Differential Drive Controller
```bash
  ros2 launch bot_description control.launch
```

Now set fixed frame in rviz to "odom".

Launch Teleop Twist Keyboard
```bash
  ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diff_drive_controller/cmd_vel -p stamped:=true
```

Now we can drive the robot using the instructions printed on the terminal. 

> [!IMPORTANT]
> Make sure the teleop_twist_keyboard terminal is activae window when driving the robot otherwise the robot won't move..



## Question 2: Package -> bot_world

To spawn the robot in a world with obstacles:
```bash
  ros2 launch bot_world spawn.launch
```
To Drive the robot, run the following commands in scequence:

```bash
  ros2 launch bot_description control.launch
  ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diff_drive_controller/cmd_vel -p stamped:=true
```

> [!TIP]
> Don't forget to set "odom" as fixed frame in rviz.
> The robot may move slowly or respond with a delay due to the added computational load from textured maps.


## Question 3: Package -> bot_control

To spawn the robot in a world with obstacles:
```bash
  ros2 launch bot_world spawn.launch
```

To Run Lidar Data Filtering script and launch rviz:
```bash
ros2 launch bot_control rviz.launch
```

To Drive the robot, run the following commands in sequence:

```bash
  ros2 launch bot_description control.launch
  ros2 run teleop_twist_keyboard teleop_twist_keyboard --ros-args -r /cmd_vel:=/diff_drive_controller/cmd_vel -p stamped:=true
```

> [!TIP]
> Don't forget to set "odom" as fixed frame in rviz.


