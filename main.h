#ifndef __MAIN_H_

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */



void delay(uint32_t milliseconds);

#ifdef USE_UART
void print(char * message);
#endif // USE_UART

#endif // __MAIN_H_
