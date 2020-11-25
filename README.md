# usart_dma_cmsis_stm32f407ve
Das Projekt "usart_dma_cmsis_stm32f407ve" bietet einen Beispielcode basierend auf "Blackboard STM32F407" in Eclipse IDE.
- jlink v 9
- eclipse c/c++
	
  Beispielkode aus main.c
  /**/
  while( 1 ) {
  	UsartDmaTx( testBuffTx, 10 ) ;						                /* 10 Bytes werden ueber usart dma gesendet */
	for( uint32_t i = 0x00 ; i < 100000 ; i ++ ) asm( "NOP\n\t" ) ;				/* delay */
	UsartDmaRx( testBuffRx, 10 ) ;						                /* 10 Bytes werden ueber usart dma empfangen */
	for( uint32_t i = 0x00 ; i < 100000 ; i ++ ) asm( "NOP\n\t" ) ; /* delay */
  }
  
  Hier ( PA8 -> USART1_CK, ) PA9 -> USART1_TX, PA10 -> USART1_RX
  
  Bei Fragen, fragen =)
  
  WhatsApp: +49 1577 6970034
