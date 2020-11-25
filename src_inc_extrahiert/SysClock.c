/*!
 * \file SysClock.c
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei SysClock.c v_1.0 wurde noch nicht getestet.
 * \brief RCC Modul.
 *
 * Diese Datei beinhaltet die RCC Einstellungen des Mikrokontrollers.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#include "main.h"
/**/
/*!
 * Die Funktion SysClockInit( ) stellt den rcc Modul ein
 * \param [ out ] void
 * \param [ in ]  void
*/
void SysClockInit( void ) {

	RCC->CR |= (RCC_CR_HSEON); 							    //Enable HSE

	while( !(RCC->CR & RCC_CR_HSERDY) ) asm( "NOP\n\t" ) ;  //ready to start HSE



	//FLASH

	FLASH->ACR |= FLASH_ACR_LATENCY 		                //clock  flash memory

			   | FLASH_ACR_PRFTEN

			   | FLASH_ACR_ICEN

			   | FLASH_ACR_DCEN;



	//PLL - HSE

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;     //set HSE as PLL source

	RCC->CR &= ~(RCC_CR_PLLON); 				//disable PLL before changes



	//PLL /M 4

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM); 		//clear all PLLM bits

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2; 		//set PLLM = 4 (100)



	//PLL /P 2

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP); 		//main PLL division PLLP = 2: 00



	//PLL *N 168

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN); 		//clear all PLLN bits with mask

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3; 		//set PLLN = 168 (1010 1000)

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_5; 		//for 8 or 16 MHz HSE

	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_7; 		//



	//PLL Q 7 (0111)

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQ);

	RCC->PLLCFGR |= (RCC_PLLCFGR_PLLQ_0

				 | RCC_PLLCFGR_PLLQ_1

				 | RCC_PLLCFGR_PLLQ_2);



	//AHB Prescaler 1

	RCC->CFGR &= ~(RCC_CFGR_HPRE); 					//Prescaler 1

	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; 				//AHB = SYSCLK/1



	//APB1 Prescaler 4

	RCC->CFGR &= ~(RCC_CFGR_PPRE1);

	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;



	//APB2 Prescaler 2

	RCC->CFGR &= ~(RCC_CFGR_PPRE2);

	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;



	//PLL enable

	RCC->CR |= RCC_CR_PLLON; 								    //enalbe PLL

	while((RCC->CR & RCC_CR_PLLRDY) == 0)	asm( "NOP\n\t" ) ;	//wait for PLL is ready



	//PLL System

	//RCC->CFGR &= ~RCC_CFGR_SW;

	RCC->CFGR |= RCC_CFGR_SW_PLL; 					            //PLL selected as system clock

	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)	asm( "NOP\n\t" ) ;	/* wait for PLL is used */

}
