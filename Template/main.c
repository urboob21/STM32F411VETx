#include "stm32f4xx.h"
#define PLL_M 8		// /8
#define PLL_N 200  //*200
#define PLL_P 0 // /2
uint16_t count=0;
void SysClockConfig(void);
void initGPIO(void);
void delay(uint32_t t);
void init_exti(void);
int main(void)
{
	SysClockConfig();
	initGPIO();
	init_exti();
	while(1)
	{
		GPIOD->BSRR|=(1<<12);
		delay(2000000);
		GPIOD->BSRR|=((1<<12)<<16);
		delay(2000000);
	}
}
void delay(uint32_t t)
{
	while(t--);
}

void initGPIO(void)
{
		//PD12, no pullup/pulldown , pushpull,lowspeed
	
	RCC->AHB1ENR|=(1<<3); //clock for port
	GPIOD->MODER|=(1<<24); //select mode pin port
	GPIOD->OTYPER=0; //pullup/pulldow
	GPIOD->OSPEEDR=0; //speed
	GPIOD->PUPDR&=~(3<<24);  //GPIOA->PUPDR &= ~((1<<10) | (1<<11));
	GPIOD->BSRR|=((1<<12)<<16); //low state

		//PA0 , pull up
	RCC->AHB1ENR|=(1<<0);
	GPIOA->MODER&=~(3<<1);
	GPIOA->PUPDR|=(1<<1); //pull dowwn
	//GPIOA->PUPDR&=~(1<<1);
}
//config exti 
void init_exti(void)
{ //mode pullup co nghia mac dinh la keo len => gia tri =1
	//doc gia tri tuy vao button
		RCC->APB2ENR|=(1<<14); //enable config clock
		SYSCFG->EXTICR[0]&=~(0xF<<0);  //1111 ~ 0000 & => ful bit 1 =0 slect pin for line
		EXTI->IMR|=(1<<0);  //disable mask
		EXTI->RTSR|=(1<<0); //enable risng
		EXTI->FTSR&=~(1<<0); //disable falling
		NVIC_SetPriority(EXTI0_IRQn,0);
		NVIC_EnableIRQ(EXTI0_IRQn);
}

//handler  ext
void EXTI0_IRQHandler(void)
{
	if((EXTI->PR)&(1<<0))
	{
		EXTI->PR|=(1<<0);
		count++;
		GPIOD->BSRR|=(1<<12);
		delay(2000000);
		GPIOD->BSRR|=((1<<12)<<16);
	}
}
	
//
void config_timit(void)
{
	
}

void SysClockConfig(void)
{
	//1. Enable HSE and wait HSE ready
	RCC->CR|=1<<16; 
	while(!(RCC->CR)&(1<<17));
	//2. Set power and voltage
	RCC->APB1ENR|=1<<28;
	PWR->CR|=3<<14;
	//3.Flash config
	FLASH->ACR|=(1<<11)|(1<<10)|(1<<8)|(3<<0);
	//4.Config prescaler 
	RCC->CFGR&=~(1<<7); //bit CFGR[7:3]=0xxx
	RCC->CFGR|=(4<<12); 
	RCC->CFGR&=~(1<<15);
	//5.Config MAIN PLL
	RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (1<<22);
//so bit dich = bit dich cao nhat can toi - bit phai dich cao nhat\
	//6.Enable PLL and wait PLL ready
	RCC->CR|=(1<<24);
	while(!((RCC->CR)&(1<<25))); //w
	//7.Set PLL for SYSCLK
	RCC->CFGR|=(2<<0);
	while(!((RCC->CFGR)&(2<<2))); //2 thuoc bit[1:0] dich 2 thi toi [3:2]
		//=> settup will allow STM32F11 to run at 100Mhz 
}
