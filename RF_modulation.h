#ifndef RF_MODULATION_H_INCLUDED
#define RF_MODULATION_H_INCLUDED

/* signal frame format:
CODE BREAK CODE BREAK ... for about ~2 seconds
the code + break happens about 100 times

values in milliseconds:
*/
#define SIGNAL_DURATION 2000
#define CODE_DURATION 20
#define REPEATS (SIGNAL_DURATION / CODE_DURATION)


// waveform values (microseconds)
#define SYMBOL_PERIOD 610
#define BIG_PULSE 450
#define SMALL_PULSE 160

// the gap between consecutive codes (~4200 us)
#define BREAK_BETWEEN 4190


/* The Symbols
Doesn't really matter which is which as long as the signal can match the original

LOW = 160us ON, 450 us OFF (small on, big off)
HIGH = 450us ON, 160 us OFF (big on, small off)


length of each code + break = 19.8ms

signals weakens after 1.79sec


The code:

LOW,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW,LOW,LOW,HIGH,LOW,HIGH,LOW,LOW,LOW,LOW,LOW,LOW,LOW,HIGH,LOW,LOW,LOW

25 Bits
*/

// Number of bits per frame
#define BIT_COUNT 25

// the code sent by the doorbell button
#define CODE 0x002028FE


// Port connected to the radio
#define RF_PIN  (GPIO_Pin_3 | GPIO_Pin_8)
#define RF_PORT GPIOA



#endif // RF_MODULATION_H_INCLUDED
