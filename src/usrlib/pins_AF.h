/**
 * Перечень альтернтивных функций каждого пина
 */
 #ifndef PINS_AF_HPP
 #define PINS_AF_HPP
 
 enum {
	AF0 = 0,
	AF1, AF2, AF3, AF4, AF5, AF6, AF7,
	AF8, AF9, AF10, AF11, AF12, AF13,
	AF14, AF15
};
typedef enum {
	TIM2_CH1_ETR	= AF1,
	TIM5_CH1		= AF2,
	TIM8_ETR		= AF3,
	USART2_CTS		= AF7,
	USART4_TX		= AF8,
	ETH_MII_CRS		= AF11
} PA0_AF_t;
typedef enum {
	TIM2_CH2		= AF1,
	TIM5_CH2		= AF2,
	USART2_RTS		= AF7,
	UART4_RX		= AF8,
	ETH_MII_RX_CLK	= AF11
} PA1_AF_t;
typedef enum {
	TIM2_CH3		= AF1,
	TIM5_CH3		= AF2,
	TIM9_CH1		= AF3,
	USART2_TX		= AF7,
	ETH_MDIO		= AF11
} PA2_AF_t;

#endif // PINS_AF_HPP