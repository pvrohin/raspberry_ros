# Raspberry_ros
 Motor control with arduino and raspberry pi from Ultrasonic range data

![alt text](https://github.com/pvrohin/raspberry_ros/blob/master/images/raspberry_ros.jpg)
## Open arduino IDE
Open a new terminal in Arduino folder and run the following command in the terminal
```python
sudo ./arduino
```
Upload the code **speed_control.ino** to the board

### How to use

In one terminal ,run roscore
```python
roscore
```
### Port Configuration
Setup the port configuration by running following commands,
```python
sudo chmod a+rw /dev/ttyACM0

rosrun rosserial_python serial_node.py /dev/ttyACM0
```
### Run the Python file
#### If Control 
In the python file directory,open a terminal and run the following command
```python 
rosrun beginner_tutorials if_control.py
```

Link to video: "https://www.youtube.com/embed/dbZTTAcDrP0" 

#### Proportional Control
In the python file directory,open a terminal and run the following command
```python
rosrun beginner_tutorials p_control.py
```
