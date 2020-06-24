# 室内小车巡航算法B

## 一、接口与电气特性

| module      | power /data interface | voltage（V） | **current**（mA） | power(W) |
| ----------- | --------------------- | ------------ | ----------------- | -------- |
| TFminiPlus  | MX1.25 4P             | 5.0          | 110mA             | 0.55     |
| LinkTrack P | USB Type-C /GH1.25 4P | 5.0          | 270               | 1.35     |
|             |                       |              |                   |          |

## 二、接口/线缆/PCB 设计

| module      | power /data interface | 对接器件             | 对接PCB              | PCB interface    |
| ----------- | --------------------- | -------------------- | -------------------- | ---------------- |
| TFminiPlus  | MX1.25 4P （公）      | MX1.25 4P （母）     | GH1.25 4P （公）锁扣 | GH1.25 4P （母） |
| LinkTrack P | GH1.25 4P （母）      | GH1.25 4P （公）锁扣 | GH1.25 4P （公）锁扣 | GH1.25 4P （母） |
|             |                       |                      |                      |                  |

## 三、接口/线缆/测试 

| module     | power /data interface | 对接器件         | 对接PCB      | PCB interface |
| ---------- | --------------------- | ---------------- | ------------ | ------------- |
|            |                       |                  |              |               |
| TFminiPlus | MX1.25 4P （公）      | MX1.25 4P （母） | PH2.0 4P(孔) | PH2.0 4P(针)  |
|            |                       |                  |              |               |