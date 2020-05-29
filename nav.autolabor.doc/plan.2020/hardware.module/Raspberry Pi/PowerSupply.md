# Power Supply

## 电源供电

The power supply requirements differ by Raspberry Pi model. All models require a 5.1V supply, but the current supplied generally increases according to model. All models up to the Raspberry Pi 3 require a microUSB power connector, whilst the Raspberry Pi 4 uses a USB-C connector.

Exactly how much current (mA) the Raspberry Pi requires is dependent on what you connect to it. The following table gives various current requirements.

| Raspberry Pi | 电压（V） | 电流(mA)  | 功率(W) | 保险丝 |
| ------------ | --------- | --------- | ------- | ------ |
|              |           |           |         |        |
| 4B           | 5.1       | 400~500mA | 2.5     | 750mA  |
|              |           |           |         |        |

## 电源推荐

| **Product**            | **Recommended PSU current capacity**（电流容量） | **Maximum total USB peripheral current draw** （USB总功率） | **Typical bare-board active current consumption** 裸板耗电量 |
| ---------------------- | ------------------------------------------------ | ----------------------------------------------------------- | ------------------------------------------------------------ |
| Raspberry Pi 2 Model B | 1.8A                                             | 600mA                                                       | 350mA                                                        |
| Raspberry Pi 4 Model B | 3.0A                                             | 1.2A                                                        | 600mA                                                        |
|                        |                                                  |                                                             |                                                              |



## 供电方式

| Raspberry Pi 2 Mode B | 电源   |      |
| --------------------- | ------ | ---- |
| Micro USB             | 5V /2A |      |
|                       |        |      |
|                       |        |      |

| Raspberry Pi 4 |       |      |
| -------------- | ----- | ---- |
| USB-C          | 5V/3A |      |
|                |       |      |
|                |       |      |

## 引脚供电

| PIN(Raspberry Pi 2) | 额定电流(A) | 实际测试电流（A) |
| ------------------- | ----------- | ---------------- |
| 3.3V                | 1.0A        | 0.8              |
| 5V                  |             |                  |
| GPIO                |             |                  |

| PIN(Raspberry Pi 4) | 额定电流(A) | 实际测试电流（A) |
| ------------------- | ----------- | ---------------- |
| 3.3V                | 1.5A        | 0.8              |
| 5V                  |             |                  |
| GPIO                |             |                  |