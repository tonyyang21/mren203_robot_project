# mren203_robot_project
Repository showcasing Tony, Leo, and Nathan's MREN 203 2nd year robotics project at Queen's University called CliMate.

### Problem Definition
The effects of poor air quality can be detrimental to an individual’s health over time or even with acute exposure. Indoor air quality (IAQ) is especially important to monitor as people spend a significant amount of time indoors where air tends to be more stagnant, allowing for toxins to accumulate even with a fully functioning HVAC system. Fueled by airborne virus transmission during the Covid-19 pandemic, IAQ has become a worriment for virtually all individuals who work, live, and breath in indoor environments. CliMate, a semi-autonomous indoor air quality surveillance mobile robot, is designed to solve the issue of contaminant exposure by periodically patrolling a building and recording contaminant levels and their location, then configuring them to inform building occupants. 

## The Setup
The setup of the CliMate robot is shown below. In green are the processing units. In red are the human interfacing components, and the blue blocks highlight the air quality sensors. The yellow shape outlines the LiDAR sensor and its accessories and in orange are the range sensors. Additional components such as the battery, motor, and motor controllers are beneath.
![image](https://github.com/tonyyang21/mren203_robot_project/assets/116667620/797dfea0-789f-46b3-b898-8beff35aded3)

## Algorithms
The following sections show flow diagrams of the pipeline of the algorithms developed for CliMate.

### Arduino Microcontroller
The Arduino controlled the actuation of the robot using PID controllers with incorporated object avoidance. The Arduino also controlled a buzzer and LED strips to communicate with building occupants.
![image](https://github.com/tonyyang21/mren203_robot_project/assets/116667620/f1d00362-f9e5-44a5-8592-fc76ea1a3157)

### Raspberry Pi Teleoperation
The Raspberry Pi received input from a remote controller and decoded it into actuation commands for the robot. These commands were then transmitted to the Arduino through the Robotics Operating System (ROS) framework.
![image](https://github.com/tonyyang21/mren203_robot_project/assets/116667620/8bafb8b0-b402-4ea1-beae-780026c65ae0)

### Raspberry Pi Heatmap
Using the LiDAR and the CO2 sensors, the quality of air was measured at various points in a room and a heatmap could be generated.
![image](https://github.com/tonyyang21/mren203_robot_project/assets/116667620/00d2cf3d-7b74-4766-be51-946e1c3666a2)

## Generated Maps
Using documentation from the RPLiDAR and packages from ROS, Hector SLAM (Simultaneous Localization and Mapping) was used to map out the room CliMate was monitoring.

<p align="center">
    <img width="500" src="https://github.com/tonyyang21/mren203_robot_project/assets/116667620/55dc6e89-222f-423d-80b7-35c34fe4a4f5">
</p>
<p align="center">
    *A map of the room CliMate was monitoring generated from a SLAM algorithm using a LiDAR*
</p>


<p align="center">
    <img width="900" src="https://github.com/tonyyang21/mren203_robot_project/assets/116667620/26713d58-4c96-45c8-b153-96b9b783e2b0">
</p>
<p align="center">
    _A heatmap generated from the CO2 sensors of CliMate._
</p>
