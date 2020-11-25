/*!
 * \file dma.c
 * \author Pavel Schal
 * \version 1.0
 * \date 17.11.2020
 * \warning Die Datei dma.c v_1.0 wurde noch nicht getestet.
 * \brief Initialisation von dma.
 *
 * Diese Datei beinhaltet die dma Einstellungen des Mikrokontrollers.
 *
 * \attention Das .h/.c Modul kann frei und ohne Lizenz verwendet werden. Nur der erste Doxigen-Block in
 * 			  jeder Datei soll bleiben.
*/
/**/
#include "main.h"
/**/
//uint32_t UsartRxDmaCount = USART_DMA_ARR_SIZE ;						   	   /* Anzahl der empfangenen Bytes als Initialisationsparameter */
//uint32_t UsartTxDmaCount = USART_DMA_ARR_SIZE ;  						       /* Anzahl der gesendeten Bytes als Initialisationsparameter*/
/**/
/*!
 * Die Funktion DmaInit( ) stellt den dma2 Modul ein.
 * \param [ out ] void
 * \param [ in ]  void
*/
void DmaInit( void ) {
	SET_BIT( RCC -> AHB1ENR, RCC_AHB1ENR_DMA2EN ) ;					/* dma2 clock enable */
	tmpreg = READ_BIT( RCC -> AHB1ENR, RCC_AHB1ENR_DMA2EN ) ;		/* delay */
	/**/
	/*! dma2, channel 4, stream 2, USART1_RX */
	CLEAR_REG( DMA2_Stream2 -> CR ) ;								                                                /* CR Register reset */
	MODIFY_REG( DMA2_Stream2 -> CR, DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2,	DMA_SxCR_CHSEL_2 ) ;	/* 100: channel 4 selected */
	/**/
	WRITE_REG( DMA2_Stream2 -> PAR, ( uint32_t ) &( USART1 -> DR) ) ;	/* Pheripheral Registeradresse */
	WRITE_REG( DMA2_Stream2 -> M0AR, ( uint32_t ) &UsartRxBuff[ 0 ] ) ; /* Zeiger auf InputBuffer */
	WRITE_REG( DMA2_Stream2 -> NDTR, USART_DMA_ARR_SIZE ) ;				/* Anzahl der gesendetet Daten per usart_dma*/
	SET_BIT( DMA2_Stream2 -> CR, DMA_SxCR_MINC ) ;					/* memory increment */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_PINC ) ;			    /* peripherie no increment */
    /**/
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_MSIZE_0 ) ;		    	/* memory byte (8-bit) */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_MSIZE_1 ) ;		        /* memory byte (8-bit) */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_PSIZE_0 ) ;		    	/* peripherie byte (8-bit) */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_PSIZE_1 ) ;		   		/* peripherie byte (8-bit) */
	/**/
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_CIRC ) ;		   		/* circular mode disable */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_DIR_0 ) ;		   		/* p2m Direction */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_DIR_1 ) ;		   		/* p2m Direction */
	CLEAR_BIT( DMA2_Stream2 -> CR, DMA_SxCR_PL ) ;		   			/* Priority level: lown */
	SET_BIT( DMA2_Stream2 -> CR, DMA_SxCR_TCIE ) ;					/* Transfer complete interrupt enable */
	SET_BIT( DMA2_Stream2 -> FCR, DMA_SxFCR_FTH_0 ) ;				/* FIFO threshold full */
	SET_BIT( DMA2_Stream2 -> FCR, DMA_SxFCR_FTH_1 ) ;				/* FIFO threshold full */
	SET_BIT( DMA2_Stream2 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream2 enable */
	/**/
	/*! dma2, channel 4, stream 7, USART1_TX */
	CLEAR_REG( DMA2_Stream7 -> CR ) ;								                                                /* CR Register reset */
	MODIFY_REG( DMA2_Stream7 -> CR, DMA_SxCR_CHSEL_0 | DMA_SxCR_CHSEL_1 | DMA_SxCR_CHSEL_2,	DMA_SxCR_CHSEL_2 ) ;	/* 100: channel 4 selected */
	/**/
	WRITE_REG( DMA2_Stream7 -> PAR, ( uint32_t ) &( USART1 -> DR ) ) ;	/* Pheripheral Registeradresse */
	WRITE_REG( DMA2_Stream7 -> M0AR, ( uint32_t ) &UsartTxBuff[ 0 ] ) ;	/* Zeiger auf InputBuffer */
	WRITE_REG( DMA2_Stream7 -> NDTR, USART_DMA_ARR_SIZE ) ;				/* Anzahl der gesendetet Daten per spi_dma*/
	SET_BIT( DMA2_Stream7 -> CR, DMA_SxCR_MINC ) ;					/* memory increment */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_PINC ) ;			    /* peripherie no increment */
	/**/
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_MSIZE_0 ) ;		    	/* memory byte (8-bit) */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_MSIZE_1 ) ;		        /* memory byte (8-bit) */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_PSIZE_0 ) ;		    	/* peripherie byte (8-bit) */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_PSIZE_1 ) ;		   		/* peripherie byte (8-bit) */
	/**/
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_CIRC ) ;		   		/* circular mode disable */
	SET_BIT( DMA2_Stream7 -> CR, DMA_SxCR_DIR_0 ) ;		   			/* m2p Direction */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_DIR_1 ) ;		   		/* m2p Direction */
	CLEAR_BIT( DMA2_Stream7 -> CR, DMA_SxCR_PL ) ;		   			/* Priority level: lown */
	SET_BIT( DMA2_Stream7 -> CR, DMA_SxCR_TCIE ) ;					/* Transfer complete interrupt enable */
	SET_BIT( DMA2_Stream7 -> FCR, DMA_SxFCR_FTH_0 ) ;				/* FIFO threshold full */
	SET_BIT( DMA2_Stream7 -> FCR, DMA_SxFCR_FTH_1 ) ;				/* FIFO threshold full */
	SET_BIT( DMA2_Stream7 -> CR, DMA_SxCR_EN ) ;					/* DMA2 Stream7 enable */
	/**/
	NVIC_EnableIRQ( DMA2_Stream2_IRQn ) ;		/*  NVIC fuer DMA2 SPI1_RX */
	NVIC_SetPriority( DMA2_Stream2_IRQn, 5 ) ;	/*  Request Prioritaet 5 */
	/**/
	NVIC_EnableIRQ( DMA2_Stream7_IRQn ) ;		/* NVIC fuer DMA2 SPI1_TX */
	NVIC_SetPriority( DMA2_Stream7_IRQn, 4 ) ;	/* Request Prioritaet 4 */
}
