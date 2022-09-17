# AutoPilotPi-Hardware

Hi, this project aims to run autopilot firmware on linux. While if we directly use the SBC(single board computer, such as raspberrypi, orangepi and so on), 
it seems a bit overkill, because the large part of peripherals on the SBC is not necessary for flight controller, and these aslo bring weight for our planes. 
And also, the SBCs lack the sensors used by PX4, we need to connect them by wires, which is very very ugly.

So in this project, I design a special SBC, which is just for autopilot firmwares to run on linux. For now, allwinner V3s is choosed as 
the soc to do this.

## why to run autopilot firmware on linux?

As you can see the chip shortage recent years because of COVID-19. Comparing the MCU(like stm32F4XX) and linux SOCs, porting the software between 
linux SOCs is much easier obviously. Though for now, running PX4 on linux is not widely adopted and there are still a few problems, 
I think it's worth to do so.

## why V3s? 
- package is easy for hand soldering.(EQFP-128)
- internal dram, easy for layout.
- cheap

of course, there are also some disadvantages of v3s, like the only 2 pwm channels, because which I add a FPGA to extend the pwm channels using I2C.

## Interface and Sensors
- ICM20600
- QMC5883L
- SPL06
- 3 uarts(U0 U1 U2, U0 is for linux debug)
- 1 I2C
- 1 SPI
- 9 PWM channels maximum

## Images
![image1](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/mini/images/AutoPilotPi.jpg?raw=true)
![image2](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/mini/images/AutoPilotPi-2.jpg?raw=true)

## Related Projces
- kernel for v3s:https://github.com/Ncerzzk/linux
- a quadrotors using this core(WIP):https://github.com/Ncerzzk/V3s_Quadrotor
- PX4 fork for this project(some commits are not accepted by official PX4 yet):https://github.com/Ncerzzk/PX4-Autopilot
- HDL of the on board fpga:https://github.com/Ncerzzk/I2C_PWM
