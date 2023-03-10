# STM32基于HAL库的串口输出自定义函数 V1.0

## 一、函数体
```c
/*自己定义的串口发送函数，模仿了printf
 *huart：串口号
 *ch：要发送的字符串
 *data：占位符中要发送的数据，从左到右，从0到最后依次发送
 *占位符格式：
 *{.n}：以浮点数形式打印，n表示保留小数点后几位，如{.2}表示保留小数点后2位
 *{d}：以整数形式打印，直接去掉小数部分，没有四舍五入
 *{h}：直接发送ACSII数据，比如"1"直接发送49
 *{e}: 发送串口屏结束帧 0xFF 0xFF 0xFF
 */
void My_printf(UART_HandleTypeDef* huart, const char* ch, float* data);
```

## 二、使用方法
### 1.定义一个float类型的数组用来存储要发的数据。
```c
float send[100] = { 0 };        //串口要发送的数据
```
### 2.占位符：

| 占位符 | 含义 |
| :-: | :-: |
| {.n} | 以浮点数形式打印，n表示保留小数点后几位，如{.2}表示保留小数点后2位 |
| {d} | 以整数形式打印，直接去掉小数部分，没有四舍五入 |
| {h} | 直接发送ACSII数据，比如"1"直接发送0x31，也可以用来发字符(类似C语言里的%c) |
| {e} | 发送串口屏结束帧 0xFF 0xFF 0xFF |

* 注：send数组中的数据个数要与占位符的个数相同。

### 3.例子
```c
float send[100] = { 0 };

send[0] = 1.14514;
send[1] = 2.7;
send[2] = 0x31;

My_printf(&huart1, "The first data: {.2}, the second: {d}, the third: {h}.{e}\n", send);

//串口打印:
//The first data: 1.15, the second: 2, the third: 1.(0xff)(0xff)(0xff)
//The first data: 1.15, the second: 2, the third: 1.���(这三个东西没有对应的ASCII码)

```
### 4.注意事项
* 基于stm32HAL库编写，要能支持HAL_UART_Transmit()函数。
* 关于本函数如有需要改进的地方，欢迎提出意见。
  