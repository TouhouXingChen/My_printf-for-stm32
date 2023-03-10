#ifndef __PRINT_H
#define __PRINT_H

#include "usart.h"

#define u8 uint8_t

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
void Float_to_Char(float data, int keep, char* dst);//将浮点数转换成字符串
void Int_to_Char(int data, char* dst);//将整数转换成字符串

#endif
