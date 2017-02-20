/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "main.h"
#include "RF_modulation.h"

volatile unsigned long long TimingDelay = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured,
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */
    /* Add your application code here */
    // set up the systick every microsecond
    if (SysTick_Config(SystemCoreClock / 1000000))
    {
        /* Capture error */
        while(1);
    }


    //enable the clocks

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    #ifdef USE_UART
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    #endif

    // enable the pins
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Configure the pin in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = RF_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(RF_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    #ifdef USE_UART
    /* USART1 Tx (PA9) */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);


    //set up the UART (1 for comms to pc)
    USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate            = 115200  ;// baud rate
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;
	USART_InitStructure.USART_Parity              = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
    #endif

    /* Infinite loop */

    uint8_t bit = 0;

    while (1)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
        {
            continue;
        }

        // button pressed
        // send the frame
        for (int i = 0; i < (int)REPEATS; i++)
        {
            //i = repetition

            for (int j = 0; j < BIT_COUNT; j++)
            {
                // j = the bit we are up to

                bit = (uint8_t)(((uint32_t)CODE >> j) & 0x01);

                if (bit)
                {
                    //high bit
                    //set output high
                    GPIO_SetBits(RF_PORT,RF_PIN);
                    delay(BIG_PULSE);

                    //set output low
                    GPIO_ResetBits(RF_PORT,RF_PIN);
                    delay(SMALL_PULSE);
                }
                else
                {
                    // low bit
                    //set output high
                    GPIO_SetBits(RF_PORT,RF_PIN);
                    delay(SMALL_PULSE);

                    //set output low
                    GPIO_ResetBits(RF_PORT,RF_PIN);
                    delay(BIG_PULSE);
                }
            }

            // set pin low
            GPIO_ResetBits(RF_PORT,RF_PIN);
            delay(BREAK_BETWEEN);
        }

        GPIO_ResetBits(RF_PORT,RF_PIN);
        delay(10000000); // dont allow it to be pressed for the next 10 seconds
    }
}



#ifdef USE_UART
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {}
    return ch;
}

/* my version of printf
    their printf is fucked up and wont redirect to the PUTCHAR thing, so i had to rewrite it
   need to use windows line endings, \r\n */
void print(char * message)
{
    char* ch = message;
    while (*ch != 0)
    {
        __io_putchar((int)*(ch++));
    }
}
#endif

// delay in us
void delay(uint32_t microseconds)
{
    TimingDelay = microseconds;

    while(TimingDelay != 0);
}
