#include "print.h"
#include "math.h"
#include "string.h"

static char num[100] = { 0 };//存放data，用于输出
static u8 uartSend[100] = { 0 };
static char send[10][100];

void My_printf(UART_HandleTypeDef* huart, const char* ch, float* data)
{
	int pos = 0, pos_char = 0;

	while (*ch != '\0')
	{
		if (*ch == '{')
		{
			ch++;
			send[pos_char][pos] = '\0';
			pos = 0;
			pos_char++;
			switch (*ch)
			{
			case '.'://浮点类型
				ch++;
				Float_to_Char(*(data++), (int)(*ch++) - 48, send[pos_char++]);
				break;
			case 'd'://整形
				Int_to_Char((int)(*(data++)), send[pos_char++]);
				ch++;
				break;
			case 'h'://hex
				send[pos_char][0] = (char)(*(data++));
				send[pos_char++][1] = '\0';
				ch++;
				break;
            case 'e'://发送串口屏的结束帧
				for (int i = 0; i < 3; i++)
				{
					send[pos_char][i] = 0xFF;
				}
				send[pos_char++][3] = '\0';
				ch++;
				break;
			default:
				break;
			}
			ch++;
		}
		else
		{
			send[pos_char][pos++] = *ch;
			ch++;
		}
	}
	send[pos_char++][pos] = '\0';
	

	if (pos_char != 0)
	{
		for (int i = 1; i < pos_char; i++)
		{
			strcat(send[0], send[i]);
		}
	}

	int len = (int)strlen(send[0]);
	strcpy((char*)uartSend, send[0]);

	HAL_UART_Transmit(huart, uartSend, len, 0xffffffff);
}

void Float_to_Char(float data, int keep, char* dst)
{
	int pos = 0;//记录num数组的位置
	int count = 0;//记录位数
	int tool = 0;

	if (data < 0)
	{
		data = -data;
		tool = 1;
	}
	int temp = (int)(data * pow(10, keep) + 0.5);//保留小数，四舍五入

	while (temp != 0)
	{
		if (pos == keep)
		{
			num[pos++] = '.';
			count++;
			continue;
		}
		num[pos++] = (char)(temp % 10 + 48);
		temp /= 10;
		count++;
	}

    if (data < 1)
	{
		num[pos++] = '.';
		num[pos++] = '0';
		count += 2;
	}
	
	for (int i = 0; i < count; i++)
	{
		dst[i] = num[count - i - 1];
	}
	if (tool)//data是负数
	{
		for (int i = count; i > 0; i--)
		{
			dst[i] = dst[i - 1];
		}
		dst[0] = '-';
		count++;
	}
	dst[count] = '\0';
}

void Int_to_Char(int data, char* dst)
{
	int pos = 0;
	int tool = 0;
	if (data < 0)
	{
		data = -data;
		tool = 1;
	}
	if (data == 0)
	{
		dst[0] = '0';
		dst[1] = '\0';
		return;
	}
	while (data != 0)
	{
		num[pos++] = (char)(data % 10 + 48);
		data /= 10;
	}

	for (int i = 0; i < pos; i++)
	{
		dst[i] = num[pos - i - 1];
	}
	if (tool)//data是负数
	{
		for (int i = pos; i > 0; i--)
		{
			dst[i] = dst[i - 1];
		}
		dst[0] = '-';
		pos++;
	}
	dst[pos] = '\0';
}
