#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
//#include "adc.h"
#include "timers.h"
#include "uart.h"
#include "dwt_stm32_delay.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

extern UART_HandleTypeDef huart1; /*declared in main.c*/
extern TIM_HandleTypeDef htim9;



static void main_Init(void);
static void main_heartbeat(void);
static void main_draw(void);
static void main_buttons(void);


void main_usercode(void)
{
  unsigned int loc_time;
  unsigned int loc_time_ms = 0;
  unsigned int loc_time_sec = 0;
  static unsigned int loc_prev_time_ms=0;
  static unsigned int loc_prev_time_sec=0;

  main_Init();

  tim_UpdatePeriod();
  loc_time = tim_GetPeriod();
  loc_time_sec = tim_GetTimeFromStartSEC();
  
  
  /*HeartBeat*/
  main_heartbeat();
  main_draw();
  /*Running LED*/
  if(loc_time_sec != loc_prev_time_sec)
  {

  }
  else
  {
    /*nothing to do*/
  }


  loc_prev_time_sec = loc_time_sec;
  loc_prev_time_ms = loc_time_ms;
  
  return;
}



void main_Init(void)
{
  static uint8_t loc_B_IsFirstTime = 0;

  if(loc_B_IsFirstTime == 0)
  {
    /*TIM init*/
    tim_InitTimer(&htim9);

    /*DWT init*/
    DWT_Delay_Init();
    
    /*UART init*/
    uart_Init(&huart1);
    uart_PrintfBuildVersion();
    
    /*OLED SSD1306 init*/
    ssd1306_Init();
    //ssd1306_TestAll();
 
    loc_B_IsFirstTime = 1;
  }
  else
  {
    /*nothing to do*/
  }


  return;
}


void main_heartbeat(void)
{
  uint32_t loc_time_sec;
  static uint32_t loc_prev_time_sec = 0;

  loc_time_sec = tim_GetTimeFromStartSEC();
  
  if(loc_prev_time_sec != loc_time_sec)
  {
    UART_PRINTFINTEGER(loc_time_sec,"DEC")


      
    /*
     * LED2 is occupied by SCI
    if((loc_time_sec % 2) == 0)
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    }
    */
    loc_prev_time_sec = loc_time_sec;
  }
  else
  {
    /*nothing to do*/
  }
  
  
  return;
}


void main_draw(void)
{
  uint32_t loc_time;
  char loc_buff[8];
  SSD1306_VERTEX loc_vertex[4] =
  {
      {0,0},
      {30,30},
      {30,10},
      {100,50}
  };

  loc_time = tim_GetTimeFromStartSEC();
  snprintf(loc_buff,sizeof(loc_buff),"%04d",(int)loc_time);
/*
  ssd1306_SetCursor(2, 0);
  ssd1306_WriteString("HELLO WORLD!", Font_11x18, White);
  ssd1306_SetCursor(2, 26);
  ssd1306_WriteString(loc_buff, Font_11x18, White);
  ssd1306_Line(30, 30, 100, 30, White);*/
 // ssd1306_DrawArc(30,30,20,30,360,White);
 // ssd1306_DrawCircle(60,30,20,White);

  ssd1306_Polyline(loc_vertex,sizeof(loc_vertex)/sizeof(loc_vertex[0]),White);
  ssd1306_UpdateScreen();

  return;
}

void main_buttons()
{

  
  return;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
