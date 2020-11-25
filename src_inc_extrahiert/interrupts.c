/*!
 * \file interrupts.c
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei interrupts.c v_1.0 wurde noch nicht getestet.
 * \brief Interrupts Funktionen.
 *
 * Diese Datei beinhaltet die Interrupts Funktionen.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#include "main.h"
/**/
/*!
 * Die ISR Funktion DMA2_Stream2_IRQHandler( ) ist zum USART_RX.
 * \param [ out ] void
 * \param [ in ]  void
*/
void DMA2_Stream2_IRQHandler( void ) {
	if( READ_BIT( DMA2 ->LISR, DMA_LISR_TCIF2 ) == ( DMA_LISR_TCIF2 ) ) {	/*  Wenn Receive komplett ist ... */
		WRITE_REG(	DMA2 ->	LIFCR, DMA_LIFCR_CTCIF2 ) ;	                    /* Clear stream 2 global interrupt flag */
		fl_rx = 0x01 ;	                                                    /* Daten wurden vollstaendig und ervollgreich empfangen */
    }
}
/**/
/*!
 * Die ISR Funktion DMA2_Stream7_IRQHandler( ) ist zum USART_TX.
 * \param [ out ] void
 * \param [ in ]  void
*/
void DMA2_Stream7_IRQHandler( void ) {
	if( READ_BIT( DMA2 -> HISR, DMA_HISR_TCIF7 ) == ( DMA_HISR_TCIF7 ) ) {  /* Wenn Transmit komplett ist ... */
		WRITE_REG(	DMA2 ->	HIFCR, DMA_HIFCR_CTCIF7 ) ;	                    /* Clear stream  global interrupt flag */
		fl_tx = 0x01 ;	                                                    /* Daten wurden vollstaendig und ervollgreich gesendet */
    }
}
