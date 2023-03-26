# [ENGLISH](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/master/README_EN.md)
# AutoPilotPi-Hardware

AutoPilotPi 是一个能够运行 PX4 等自动驾驶固件的单板计算机(SBC)。与通用的 SBC（如树莓派）不同，AutoPilotPi 集成了多种传感器（IMU、磁罗盘、气压计等），因此无需额外的接线即可使用，对于微型飞行器和电路洁癖患者来说非常友好。

AutoPilotPi 使用 V3s 处理器，虽然 V3s 不是性能强大的处理器，但如果能够证明 PX4 能在这些性能较弱的 Linux 处理器上运行，则对于性能更强的处理器来说更加不在话下了。

与传统基于 MCU 的自动驾驶固件不同，使用 Linux 系统的优势在于支持更多的开发语言和工具链，可以更方便地进行二次开发和调试。同时，开启了软实时后的内核基本可以满足 PX4 的实时性要求。

## 接口与传感器

- ICM20600：六轴惯性测量单元
- QMC5883L：三轴磁罗盘
- SPL06：气压高度传感器
- 3 个串口(U0、U1、U2，其中 U0 用于 Linux 调试)
- 1 个 I2C 接口
- 1 个 SPI 接口
- 最多 9 个 PWM 通道

## 特点

- 封装对手焊友好 (EQFP-128)
- 内置 DRAM
- 价格较为便宜

## 相关项目

- V3s 的 Linux 内核：https://github.com/Ncerzzk/linux
- 使用该项目的四旋翼飞行器 (WIP)：https://github.com/Ncerzzk/V3s_Quadrotor
- 该项目的 PX4 分支（部分提交尚未被官方 PX4 接受）：https://github.com/Ncerzzk/PX4-Autopilot
- FPGA 的 HDL 代码：https://github.com/Ncerzzk/I2C_PWM
- Wiki：https://github.com/Ncerzzk/AutoPilotPi-Hardware/wiki


## Images
![image1](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/master/images/AutoPilotPi.jpg?raw=true)
![image2](https://github.com/Ncerzzk/AutoPilotPi-Hardware/blob/master/images/AutoPilotPi-2.jpg?raw=true)

