# [ENGLISH](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/master/README_EN.md)
# AutoPilotPi-Hardware

AutoPilotPi 是一个以运行PX4等自动驾驶固件的SBC（single board computer）。对于其他的通用SBC（如树莓派等），由于其硬件上缺少相关的传感器（IMU、磁罗盘、气压计等），因此需要使用
额外的接线来连接SBC和传感器们，这对于微型飞行器和电路洁癖患者来说很不友好。

## 为什么要在linux上跑自动驾驶的固件？

如果你经历过过去两三年的芯片短缺，可能也会有将过去运行在某些MCU（如Stm32F4/F7）系列上的开源项目移植到新平台上的想法。
然而，将项目在MCUs之间移植比将项目在可以跑linux的SOCs之间移植难得多也琐碎得多。当然，你可能会有一些实时性方面的顾虑，
仅就我目前测试而言，开启了软实时后的kernel基本可以满足PX4的实时性要求。


## why V3s? 
- 封装对手焊友好.(EQFP-128)
- 内置dram.
- 较为便宜

当然，V3s也有一些缺点，如只有两路PWM输出，因此我还在AutopilotPi上增加一片FPGA用于拓展PWM通告（使用I2C协议）

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
- wiki: https://github.com/Ncerzzk/AutoPilotPi-Hardware/wiki
