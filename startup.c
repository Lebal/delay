/*
 * 	startup.c
 *
 */
 
#define	STK_CTRL	((volatile unsigned int *) (0xE000E010))
#define	STK_LOAD	((volatile unsigned int *) (0xE000E014))
#define	STK_VAL		((volatile unsigned int *) (0xE000E018))


#define GPIO_D 0x40020C00
#define GPIO_MODER  ((volatile unsigned int *) (GPIO_D))  
#define GPIO_OTYPER  ((volatile unsigned short *) (GPIO_D+0x4))  
#define GPIO_PUPDR ((volatile unsigned int *) (GPIO_D+0xC))  
#define GPIO_IDR_LOW ((volatile unsigned char *) (GPIO_D+0x10))  
#define GPIO_IDR_HIGH  ((volatile unsigned char *) (GPIO_D+0x11))  
#define GPIO_ODR_LOW ((volatile unsigned char *) (GPIO_D+0x14))  
#define GPIO_ODR_HIGH ((volatile unsigned char *) (GPIO_D+0x15))  
 
 #define SIMULATOR
 void delay_250ns(){
	 /*SystemCoreClock = 168000000*/
	 *STK_CTRL =  0;
	 *STK_LOAD = ((168/4) -1);
	 *STK_VAL = 0;
	 *STK_CTRL = 5;
	 while((*STK_CTRL & 0x10000) ==0){
		 }
	 
	 *STK_CTRL = 0;
	 
	 
 }
	 
void delay_milli(unsigned int ms){
	int i;

#ifdef SIMULATOR
	//ms = ms/100;
	ms = 5;
	ms++;
#endif
	while (ms--){
#ifdef SIMULATOR
		for(i = 0; i<5; i++)
#else	
		for(i =0; i<1000;i++)
#endif
			{
			delay_250ns();
			delay_250ns();
			delay_250ns();
			delay_250ns();
			
			}
	}
}
	
void delay_mikro(unsigned int us){
	while(us--){
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		}
	
	
	}
 
 
 
 
 
 
 
void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );


void app_Init(){
	*GPIO_MODER = 0x5555;
	
	}
void startup ( void )
{
asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	".L1: B .L1\n"				/* never return */
	) ;
}










void main(void)
{
	
	app_Init();
	
	while(1){
		*GPIO_ODR_LOW = 0xFF;
		delay_milli(500);
		*GPIO_ODR_LOW = 0;
		delay_milli(500);
		
		}
}

