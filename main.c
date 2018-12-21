#include <stdint.h>
#include <stdio.h>
#include "deeplearning.h"

#define DELAYTIME 2000000

#define GPFSEL0 ((volatile uint32_t *)0x20200000)
#define GPFSEL1 (GPFSEL0 + 0x04)
#define GPFSEL2 (GPFSEL1 + 0x04)
#define GPFSEL3 (GPFSEL2 + 0x04)
#define GPFSEL4 (GPFSEL3 + 0x04)
#define GPFSEL5 (GPFSEL4 + 0x04)

#define UART_BASE ((volatile uint32_t *)0x20201000)
#define UART_DR UART_BASE
#define UART_FR (UART_BASE + 0x18)
#define UART_IBRD (UART_BASE + 0x24)
#define UART_FBRD (UART_BASE + 0x28)
#define UART_LCRH (UART_BASE + 0x2c)
#define UART_CR (UART_BASE + 0x30)

/*
uint32_t * GPIOPort(int port)
{
  uint32_t indeed = port%10;
  return (uint32_t)0x20200000 + indeed;
} */

void __errno();
caddr_t _sbrk _PARAMS((int));
int _write _PARAMS((int,char*,int));
int _close _PARAMS((int));
int _fstat _PARAMS((int));
int _isatty _PARAMS((int));
int _lseek _PARAMS((int , int , int));
int _read _PARAMS((int, char *, int));

void __errno(){
}

caddr_t _sbrk(int incr){
  static char* heap_end=NULL;
  volatile void* __bss_end;
  char* prev_heap_end;
  if(heap_end==NULL) heap_end= (char*)&__bss_end;
  prev_heap_end = heap_end;
  heap_end += incr;
  return (caddr_t) prev_heap_end;
}
int _write(int file, char* ptr, int len){
  for(volatile int i=0;i<len;i++){
    *UART_DR = *ptr;
    ptr++;
    for(volatile int j=0;j<DELAYTIME;j++);
  }
  return len;
}
int _close(int file){
  return 0;
}
int _fstat(int file){
  return 0;
}
int _isatty(int fd){
  return 0;
}
int _lseek(int file, int ptr, int dir){
	return 0;
}
int _read(int file, char* ptr, int len){
	return 0;
}

int main(void)
{
  // GPIO22
  *GPFSEL2 &= ~(uint32_t)(0x07 << (2*3));
  *GPFSEL2 |= (uint32_t)(0x03 << (2*3));

  // GPIO4
  *GPFSEL0 &= ~(uint32_t)(0x07 << (4*3));
  *GPFSEL0 |= (uint32_t)(0x02 << (4*3));

  // GPIO27
  *GPFSEL2 &= ~(uint32_t)(0x07 << (7*3));
  *GPFSEL2 |= (uint32_t)(0x03 << (7*3));

  // GPIO25
  *GPFSEL2 &= ~(uint32_t)(0x07 << (5*3));
  *GPFSEL2 |= (uint32_t)(0x03 << (5*3));

  // GPIO24
  *GPFSEL2 &= ~(uint32_t)(0x07 << (4*3));
  *GPFSEL2 |= (uint32_t)(0x03 << (4*3));

  *GPFSEL4 &= ~(uint32_t)(0x07 << (7*3));
  *GPFSEL4 |= (uint32_t)(0x01 << (7*3));

  *UART_CR = 0; // UARTの無効化
  // tx GPIO14
  *GPFSEL1 &= ~(uint32_t)(0x07 << (4*3));
  *GPFSEL1 |= (uint32_t)(0x04 << (4*3));
  // Rx GPIO15
  *GPFSEL1 &= ~(uint32_t)(0x07 << (5*3));
  *UART_IBRD = 1;
  *UART_FBRD = 40;
  *UART_LCRH = 0x03 << 5;
  *UART_CR = (1 << 8) | 1; // UARTの有効化

  //volatile char a = deeplearning();
  for(;;)
  {
    printf("fas");
    /*
    if(a == 0) *UART_DR = '0';
    if (a == 1) *UART_DR = '1';
    if (a == 2) *UART_DR = '2';
    if (a == 3) *UART_DR = '3';
    if (a == 4) *UART_DR = '4';
    if (a == 5) *UART_DR = '5';
    if (a == 6) *UART_DR = '6';
    if (a == 7) *UART_DR = '7';
    if (a == 8) *UART_DR = '8';
    if (a == 9) *UART_DR = '9';
    */
    *(volatile uint32_t *)0x2020002C = 1 << (47-32);
    for(volatile int i=0;i<DELAYTIME;i++);
    *(volatile uint32_t *)0x20200020 = 1 << (47-32);
    for(volatile int i=0;i<DELAYTIME;i++);
  }
  return 0;
}
