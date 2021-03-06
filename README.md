# Ping Pong Ball Launcher
https://youtu.be/X3PAqk20X44

## Introduction
The goal of this personal project was to create ping pong robot that I could use for exercise at the fraction of the cost of buying one off the shelf. The design itself is very modular. 

## Microcontroller
I am using the STM32G071RB microcontroller for this project. I've added the ability to send commands to the robot using the HC-05 Bluetooth module. This allows you to turn on/off the robot or adjust launching setting using your phone. I also used the Arduino Pro Micro to prototype the robot due to how convenient it was compared to the STM32. 

## Motors
My original plan was to use two brushed DC motors as my primary method of launching the balls. However, it was difficult to find brushed motors that had any documentation and they have a reputation of low durability due to wear on the brush contacts inside the motor. This is not ideal for my project because I intend to use it for long sessions and don't want it breaking down in months. I ended up researching brushless motors and decided that they were a better fit for my project. They provide more torque than brushed motors and have consistent speed. Brushless motors are commonly used in drone and quadcopter projects and the particular motor that I chose appears to be very popular and easily replaceable. 

![Motors](https://i.imgur.com/jhpEa0S.jpg)

I also wanted to mention that another reason I've decided to avoid brushed motors was due to a Kickstarter campaign called Trainerbot (another ping pong robot). According to their updates, they seem to have having trouble with failing gearboxes on their brushed motors. The product was supposed to ship in 2017 and it's currently 2021.

## ESC
You cannot drive a brushless motor by applying a voltage to the leads like you can with a brushed motor. An electronic speed controller (ESC) is required to drive a brushless motor. The electronic speed controller detects the position of the motor using the back-EMF generated by the motor spin and powers the three phases individually based on the detected position.

My initial plan was to build my own ESC. I could've easily bought a few because they are really cheap on AliExpress, but then I wouldn't learn as much. On top of that, I could've added my own features such as a current sensor to detect how much current my motors were actually using. Unfortunately due to the current semiconductor shortages, getting hold of the necessary parts (STM32, N-Channel MOSFETs, MOSFET drivers) to build my own has been difficult and expensive. I am still working on building my own ESC, but for now the cheap ESCs work perfectly.

## Power Supply
Brushless motors are known to consume a lot of power when running. The maximum current draw of my brushless motors were going to be ~20A each. I will not be running my motors anywhere near max speed, so the current draw should be much lower. Regardless, a 12V 5A wall plug will not be enough.

Designing and building my own power supply would be very dangerous due to my lack of knowledge and experience, so I used an off-the-shelf power supply. A cheap 12V 30A switching power supply from Amazon will likely be enough for this use cases of this project, but the power supply that I ended up using was 650W ATX power supply (typically used for gaming PCs). The power supply is likely overkill for my project, but I had an extra one lying around. I also bought an adapter for easy connection to my components.

![Adapter](https://i.imgur.com/2E70pyY.jpg)

## Feeding System
I needed a way to feed ping pong balls individually into the launching barrel that was both reliable and compact. The feeding system was modeled in Fusion 360 and 3D printed on the Ender 3 Pro. In the center of the feeding system is a rotating disk powered by a slow rotating stepper motor. The rotating disk would fit one ball and feed it into the barrel to be launched. 

![feeding system 1](https://i.imgur.com/62OQNeL.jpg)
![feeding system 2](https://i.imgur.com/W45Cp2A.jpg)
![feeding system 3](https://i.imgur.com/Q3kYxCx.jpg)


## Limitations & Weaknesses
I would say that the ping pong robot works really well, but there are still limitations on the project.

The stepper motor in my feeding system comes in many Arduino kits and is super cheap. Unfortunately, the motor is incredibly weak. I didn't think it possible that a stack of ping pong balls weighing almost nothing can cause the motor to stall, but it did. Fortunately this problem is extremely rare. I would've switched to a more powerful stepper motor, but that would mean I had to revise my feeding system design to accommodate the new motor. I would also need to reprint the part which would take several hours and use a lot of plastic filament.

Another limit is my robot's inability to rotate horizontally. The robot will only launch the balls in the direction that the barrel. Implementing a feature to rotate the barrel would require an additional motor and more 3D printed parts, so I've elected to manually adjust the robot direction for now. 

The barrel only has two launching wheels and is only capable of topspin or backspin in its default orientation. You can physically rotate the barrel 90 degrees to get sidespin. Commercial ping pong robots can have up to three wheels and is capable of many more types of spin without the need to physically modify the robot. Those robots can cost over $1000. I'm not a professional player (I'm not even particularly good at table tennis), I only need something that works well enough to use for exercise. With the BOM for this project being around $120, I am fine with this trade-off.


Despite all of the limitations of my robot, the design is very modular. This allows me the opportunity to improve or repair specific parts of project without affecting the rest of the system.

![complete robot](https://i.imgur.com/Mqq9rPa.jpg)
