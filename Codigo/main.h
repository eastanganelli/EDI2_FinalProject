#include <16F877.h>
#device ADC=10
#use delay(crystal=4000000)
#use rs232(baud=9600, xmit=PIN_C6,rcv=PIN_C7, bits=8, parity=N)
