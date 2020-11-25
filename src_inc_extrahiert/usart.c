/*!
 * \file usart.c
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei usart.c v_1.0 wurde noch nicht getestet.
 * \brief Usart Modul in DMA Modus.
 *
 * Diese Datei beinhaltet die usart Einstellungen des Mikrokontrollers.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#include "main.h"
/**/
uint8_t UsartRxBuff[ USART_DMA_ARR_SIZE ] = { 0x00 } ;  /* Usart receive Variable */
uint8_t UsartTxBuff[ USART_DMA_ARR_SIZE ] = { 0x00 } ;  /* Usart transmit Variable */
uint8_t fl_rx = 0x00 , fl_tx = 0x00 ;			        /* Flagvariablen */
/**/
/*!
 * Die Funktion UsartInit( ) stellt den usart Modul ein
 * \param [ out ] void
 * \param [ in ]  void
*/
void UsartInit( void ) {
	SET_BIT( RCC -> APB2ENR, RCC_APB2ENR_USART1EN ) ;                                       /* usart1 clock enable */
	tmpreg = READ_BIT( RCC -> APB2ENR, RCC_APB2ENR_USART1EN ) ;		                        /* delay */
	/**/
	CLEAR_BIT( USART1 -> CR1, USART_CR1_UE ) ;												/* USART1 disable */
	MODIFY_REG( USART1 -> CR1, USART_CR1_M | USART_CR1_PCE, USART_CR1_TE | USART_CR1_RE ) ;	/* 1 Start bit, 8 Data bits, n Stop bit; Parity control disabled; Transmitter enable; Receiver enable */
	CLEAR_BIT( USART1 -> CR2, ( USART_CR2_LINEN | USART_CR2_CLKEN ) ) ;						/* Asynchron Modus: LIN mode disabled, CK pin disabled */
	CLEAR_BIT( USART1 -> CR3, ( USART_CR3_SCEN | USART_CR3_IREN | USART_CR3_HDSEL ) ) ;		/* Smartcard Mode disabled, IrDA disabled, Half duplex mode is not selected,  */
	WRITE_REG(USART1 -> BRR, ( ( 0x27 ) << 4 ) | 0x01 ) ;	                                /* Baundrate: 115200; Referenzmanual Table 192 */
	SET_BIT( USART1 -> CR3, USART_CR3_DMAR )	;	                                        /* Rx Buffer DMA Enable */
	SET_BIT( USART1 -> CR3, USART_CR3_DMAT )	;	                                        /* Tx Buffer DMA Enable */
	/**/
	SET_BIT( USART1 -> CR1, USART_CR1_UE ) ;                                                /* usart1 enable */
}
/**/
/*!
 * Die Funktion UsartDmaRx( ) empfaengt die 8 Bit array Daten.
 * \param [ out ] void
 * \param [ in ]  *dt 8 Bit Adresse auf ersten Element des empangegen arrays.
 * \param [ in ]  sz Elementen-Laenge des arrays
 * \warning
*/
void UsartDmaRx( uint8_t* dt, uint16_t sz ) {
	/**/
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream2 disable */
	MODIFY_REG( DMA2_Stream2 -> NDTR, DMA_SxNDT, sz ) ;				/* Anzahl der enpfangeneg Daten per usart_dma*/
	SET_BIT( DMA2_Stream2 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream2 enable */
	while( !fl_rx ) asm( "NOP\n\t" ) ;								/* abwarten bis Daten empfangt werden */
	fl_rx = 0x00 ;													/* fl_rx reseten */
	/**/
	for( uint16_t n = 0x00 ; n < sz ; n ++  ) {	                    /* Kopieren der rx Variable in UsartRxBuff[ ] Variable */
		*( dt + n ) = *( UsartRxBuff + n ) ;
	}
}
/**/
/*!
 * Die Funktion UsartDmaTx( ) sendet die 8 Bit array Daten.
 * \param [ out ] void
 * \param [ in ]  *dt 8 Bit Adresse auf ersten Element des gesendeten arrays.
 * \param [ in ]  sz Elementen-Laenge des arrays
*/
void UsartDmaTx ( uint8_t* dt, uint16_t sz ) {
	for( uint16_t n = 0x00 ; n < sz ; n ++  ) {	                    /* Kopieren der tx Variable in UsartTxBuff[ ] Variable */
		*( UsartTxBuff + n ) = *( dt + n ) ;
	}
	/**/
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream7 disable */
	MODIFY_REG( DMA2_Stream7 -> NDTR, DMA_SxNDT ,sz ) ;				/* Anzahl der gesendeten Daten per usart_dma*/
	SET_BIT( DMA2_Stream7 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream7 enable */
	while( !fl_tx ) asm( "NOP\n\t" ) ;								/* abwarten bis Daten gesendet werden */
	fl_tx = 0x00 ;													/* fl_tx reseten */
}
