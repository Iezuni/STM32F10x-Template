
#include "delay.h"
#include "usart.h"
#include "sys.h"

void LED_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOE, ENABLE); //使能PB,PE端口时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;         //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);            //根据设定参数初始化GPIOB.5
  GPIO_SetBits(GPIOB, GPIO_Pin_5);                  //PB.5 输出高

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //LED1-->PE.5 端口配置, 推挽输出
  GPIO_Init(GPIOE, &GPIO_InitStructure);    //推挽输出 ，IO口速度为50MHz
  GPIO_SetBits(GPIOE, GPIO_Pin_5);          //PE.5 输出高
}

void KEY_Init(void) //IO初始化
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE); //使能PORTA,PORTE时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3; //KEY0-KEY1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //设置成上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);                 //初始化GPIOE4,3

  //初始化 WK_UP-->GPIOA.0	  下拉输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);        //初始化GPIOA.0
}

int main(void)
{
  vu8 key = 0;
  delay_init();                      //延时函数初始化
  LED_Init();                        //初始化与LED连接的硬件接口
  KEY_Init();                        //初始化与按键连接的硬件接口
  GPIO_ResetBits(GPIOB, GPIO_Pin_5); //先点亮红灯
 // USART_SendData();
  while (1)
  {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
    {
      GPIO_SetBits(GPIOB, GPIO_Pin_5);
      GPIO_SetBits(GPIOE, GPIO_Pin_5);
    }
    else
    {
      GPIO_ResetBits(GPIOB, GPIO_Pin_5);
      GPIO_ResetBits(GPIOE, GPIO_Pin_5);
    }
    delay_ms(10);
  }
}
