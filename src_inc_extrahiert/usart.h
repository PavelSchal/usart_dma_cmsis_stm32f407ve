/*!
 * \file usart.h
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei usart.h v_1.0 wurde noch nicht getestet.
 * \brief usart Modul in DMA Modus.
 *
 * Diese Datei beinhaltet die usart Einstellungen des Mikrokontrollers.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#ifndef USART_H_
#define USART_H_
/**/
#define USART_DMA_ARR_SIZE 128		               /* rx tx Array Datenlaenge. Als Initialisation max.128 Elementen */
/**/
extern uint8_t UsartRxBuff[ USART_DMA_ARR_SIZE ] ; /* Usart receive Variable */
extern uint8_t UsartTxBuff[ USART_DMA_ARR_SIZE ] ; /* Usart transmit Variable */
extern uint8_t fl_rx, fl_tx ;
/**/
void UsartInit( void ) ;
void UsartDmaRx ( uint8_t* dt, uint16_t sz ) ;
void UsartDmaTx ( uint8_t* dt, uint16_t sz ) ;
/**/
#endif /* USART_H_ */
