#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
//#include "adc.h"
#include "button_handle.h"
#include "timers.h"
#include "uart.h"
#include "dwt_stm32_delay.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"

extern UART_HandleTypeDef huart1; /*declared in main.c*/
//extern ADC_HandleTypeDef hadc1; /*declared in main.c*/
extern TIM_HandleTypeDef htim9;



static void main_Init(void);
static void main_heartbeat(void);
static void main_draw(void);
static void main_buttons(void);


void main_usercode(void)
{

  uint8_t loc_buff[20];
  unsigned int loc_time;
  unsigned int loc_time_ms = 0;
  unsigned int loc_time_sec = 0;
  static unsigned int loc_prev_time_ms=0;
  static unsigned int loc_prev_time_sec=0;
  uint8_t loc_srbyte = 1;

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

  //loc_adc_val = adc_GetValue(&hadc1);


  loc_prev_time_sec = loc_time_sec;
  loc_prev_time_ms = loc_time_ms;
  
  return;
}



void main_Init(void)
{
  static uint8_t loc_B_IsFirstTime = 0;

  if(loc_B_IsFirstTime == 0)
  {
    /*BUTTON init*/
    button_SetActiveButtons('C',13);
    button_SetActiveButtons('B',6);

    /*TIM init*/
    tim_InitTimer(&htim9);

    /*DWT init*/
    DWT_Delay_Init();
    
    /*UART init*/
    uart_Init(&huart1);
    uart_PrintfBuildVersion(&huart1);
    
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
  loc_time = tim_GetTimeFromStartSEC();
  snprintf(loc_buff,sizeof(loc_buff),"%04d",(int)loc_time);

  ssd1306_SetCursor(2, 0);
  ssd1306_WriteString("HELLO WORLD!", Font_11x18, White);
  ssd1306_SetCursor(2, 26);
  ssd1306_WriteString(loc_buff, Font_11x18, White);
  ssd1306_Line(0, 0, 100, 100, White);
  ssd1306_UpdateScreen();

  return;
}

void main_buttons()
{
  unsigned char loc_B_button_state = 0;
  
  button_Processing();
  loc_B_button_state = button_GetButtonState('B',6);
  if(loc_B_button_state != 0)
  {
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
  }
  
  return;
}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
