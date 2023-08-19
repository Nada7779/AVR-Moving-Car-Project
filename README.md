# AVR Moving Car Project
## Project Description:
this is a project for the Embedded Systems L1 module in Sprints Automotive Bootcamp.<br />
This Delivery takes 3 working days.<br />
## Project Details:
The aim of this project is to design a system for a four-driving wheel robot that moves in a rectangular shape. The system consists of several modules, including Interrupt, timers, motor, LED indicators, and button drivers. The robot is equipped with four motors, two buttons (one for start and one for stop), and four LEDs to indicate the state of movement.<br />
The Microcontroller used is atmega32.
## Project sequence :
1. The car starts initially from 0 speed.
2. When PB1 is pressed, the car will move forward after 1 second.
3. The car will move forward to create the longest side of the rectangle for 3 seconds with 50% of its maximum speed.<br />
4. After finishing the first longest side the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 second.<br />
5. The car will move to create the short side of the rectangle at 30% of its speed for 2 seconds.<br />
6. After finishing the shortest side, the car will stop for 0.5 seconds, rotate 90 degrees to the right, and stop for 0.5 second.<br />
7. Steps 3 to 6 will be repeated infinitely until you press the stop button (PB2).<br />
8. PB2 acts as a sudden break, and it has the highest priority.<br />

