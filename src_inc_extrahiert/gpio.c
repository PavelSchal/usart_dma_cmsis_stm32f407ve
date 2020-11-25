/*!
 * \file gpio.c
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei gpio.c v_1.0 wurde noch nicht getestet.
 * \brief Initialisation von GPIOs.
 *
 * Diese Datei beinhaltet die GPIO Einstellungen des Mikrokontrollers.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#include "main.h"
/**/
/*!
 * Die Funktion GpioInit( ) stellt den gpio Modul ein.
 * gpioa fuer usart1 Modul.
 * \param [ out ] void
 * \param [ in ]  void
*/
void GpioInit( void ) {
	SET_BIT( RCC -> AHB1ENR, RCC_AHB1ENR_GPIOAEN ) ;            /* porta clock enable */
	tmpreg = READ_BIT( RCC -> AHB1ENR, RCC_AHB1ENR_GPIOAEN ) ;  /* delay */
	/**/
	/*!
	 * gpioa fuer usart1
	 * AF7, PushPull, pullup ( PA8 -> USART1_CK, ) PA9 -> USART1_TX, PA10 -> USART1_RX
	*/
	MODIFY_REG( GPIOA -> MODER, /*GPIO_MODER_MODER8 |*/ GPIO_MODER_MODER9 | GPIO_MODER_MODER10,\
								/*GPIO_MODER_MODER8_1 |*/ GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1 ) ;		    /* MODER: 10 */
	CLEAR_REG( GPIOA -> OTYPER ) ;																			    	/* OTYPER: 0 */
	MODIFY_REG( GPIOA -> OSPEEDR, /*GPIO_OSPEEDR_OSPEED8 |*/ GPIO_OSPEEDR_OSPEED9 | GPIO_OSPEEDR_OSPEED10,\
								  /*GPIO_OSPEEDR_OSPEED8 |*/ GPIO_OSPEEDR_OSPEED9 | GPIO_OSPEEDR_OSPEED10 ) ;	    /* 11: Very high speed */
	//CLEAR_REG( GPIOA -> PUPDR ) ;		/*!< PUPDR: 00 */
	MODIFY_REG( GPIOA -> PUPDR, GPIO_PUPDR_PUPD9 | GPIO_PUPDR_PUPD10 , GPIO_PUPDR_PUPD9_0 | GPIO_PUPDR_PUPD10_0 ) ;	/* PP + PU : 01 */

	MODIFY_REG( GPIOA -> AFR[ 1 ], /*GPIO_AFRH_AFSEL8 | */GPIO_AFRH_AFSEL9 | GPIO_AFRH_AFSEL10,\
								   /*GPIO_AFRH_AFSEL8_0 | GPIO_AFRH_AFSEL8_1 | GPIO_AFRH_AFSEL8_2 |*/
								   GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2 |\
								   GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2 ) ;              /* PA8: 0111: AF7 *//* PA9: 0111: AF7 *//* PA10: 0111: AF7 */
}




