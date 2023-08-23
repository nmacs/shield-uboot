#define UART_PAD_CTRL         ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_MED  | PAD_CTL_DSE_40ohm                     | PAD_CTL_HYS               )
#define I2C_PAD_CTRL          ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_MED  | PAD_CTL_DSE_40ohm                     | PAD_CTL_HYS | PAD_CTL_ODE )
#define SPI_PAD_CTRL          ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )
#define SPI_CS_PAD_CTRL       ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )
#define SPI_AFE_PAD_CTRL      ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )
#define SPI_AFE_CS_PAD_CTRL   ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )

#define ENET_PAD_CTRL         ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_48ohm | PAD_CTL_SRE_FAST                              )
#define MDIO_PAD_CTRL         ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_MED  | PAD_CTL_DSE_48ohm | PAD_CTL_SRE_FAST                | PAD_CTL_ODE )
#define MDC_PAD_CTRL          ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_MED  | PAD_CTL_DSE_48ohm | PAD_CTL_SRE_FAST                              )
#define ENET_CLK_PAD_CTRL     ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP   | PAD_CTL_SPEED_LOW  | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )
#define ENET_RST_PAD_CTRL     ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_LOW  | PAD_CTL_DSE_40ohm                                                 )

#define AFE_IRQ_PAD_CTRL      ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN                                                              | PAD_CTL_HYS               )
#define GPIO_IRQ_PAD_CTRL     ( PAD_CTL_PUE | PAD_CTL_PUS_100K_UP                                                                | PAD_CTL_HYS               )

#define GPIO_OUT_PAD_CTRL     ( PAD_CTL_PUE                         | PAD_CTL_SPEED_LOW  | PAD_CTL_DSE_40ohm                                                 )
#define GPIO_IN_PAD_CTRL      (                                       PAD_CTL_SPEED_LOW  | PAD_CTL_DSE_40ohm                     | PAD_CTL_HYS               )
#define GPIO_IO_PAD_CTRL      ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_MED  | PAD_CTL_DSE_40ohm                     | PAD_CTL_HYS               )

#define SD_PAD_CTRL           ( PAD_CTL_PUE | PAD_CTL_PUS_22K_UP    | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )
#define SD_CLK_PAD_CTRL       ( PAD_CTL_PUE | PAD_CTL_PUS_22K_UP    | PAD_CTL_SPEED_HIGH | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST                              )

#define USB_POWERON_PAD_CTRL  ( PAD_CTL_PUE | PAD_CTL_PUS_100K_DOWN | PAD_CTL_SPEED_LOW  | PAD_CTL_DSE_40ohm                                                 )

static iomux_v3_cfg_t const peripheral_pads[] = {
	// UART2
	//
	MX6_PAD_UART2_RX_DATA__UART2_DCE_RX	| MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_UART2_TX_DATA__UART2_DCE_TX	| MUX_PAD_CTRL(UART_PAD_CTRL),

	// eMMC
	//
	MX6_PAD_SD1_CLK__USDHC1_CLK		| MUX_PAD_CTRL(SD_CLK_PAD_CTRL),
	MX6_PAD_SD1_CMD__USDHC1_CMD		| MUX_PAD_CTRL(SD_PAD_CTRL),
	MX6_PAD_SD1_DATA0__USDHC1_DATA0		| MUX_PAD_CTRL(SD_PAD_CTRL),
	MX6_PAD_SD1_DATA1__USDHC1_DATA1		| MUX_PAD_CTRL(SD_PAD_CTRL),
	MX6_PAD_SD1_DATA2__USDHC1_DATA2		| MUX_PAD_CTRL(SD_PAD_CTRL),
	MX6_PAD_SD1_DATA3__USDHC1_DATA3		| MUX_PAD_CTRL(SD_PAD_CTRL),
};
