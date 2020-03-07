/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6UL 14x14 EVK board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __ZIXLINK_ROUTER_CONFIG_H
#define __ZIXLINK_ROUTER_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/mach-imx/gpio.h>

#define CONFIG_SERVERIP 	192.168.0.2
#define CONFIG_IPADDR 	 	192.168.0.1
#define CONFIG_ETHADDR  	00:11:22:33:44:55

/* SPL options */
#include "imx6_spl.h"

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

#define CONFIG_IMX_WATCHDOG
#define CONFIG_HW_WATCHDOG
#define CONFIG_WATCHDOG_TIMEOUT_MSECS 10000

#define CONFIG_SPI_FLASH_MTD

#define MTDPARTS_DEFAULT 		"mtdparts="			\
								"gpmi-nand:"		\
									"5m(uboot),"	\
									"27m(fit),"		\
									"35m(root_ro),"	\
									"-(root_data);"	\
								"nor1:"			\
									"5m(uboot_X0),"	\
									"11m(fit_X0)"



/*#define SPINOR_UBOOT*/

#ifdef SPINOR_UBOOT
#define UBOOT_FLAG	"UBOOT_SPI"
#else
#define UBOOT_FLAG	"UBOOT_NAND"
#endif


/* For uboot - nor1, for Linux spi0.0  AAAAAAaaaaAAAaaaa!!!! */
#define MTDIDS_SPINOR		"nor1=nor1"
#define MTDPARTS_SPINOR 	"mtdparts=nor1:5m(uboot_X0),11m(fit_X0)"
#define MTDIDS_NAND			"nand0=gpmi-nand"
#define MTDPARTS_NAND 		"mtdparts="			\
							"gpmi-nand:"		\
								"5m(uboot),"	\
								"27m(fit),"		\
								"35m(root_ro),"	\
								"-(root_data)"

/* Kernel command line: */
#define CONFIG_USE_BOOTARGS
#define CONFIG_BOOTARGS		"console=ttymxc3,115200 ubi.mtd=root_ro ubi.mtd=root_data mtdparts=" \
							"gpmi-nand:5m(uboot),27m(fit),35m(root_ro),-(root_data);" \
							"spi0.0:5m(uboot_X0),11m(fit_X0)" \
							" "UBOOT_FLAG


/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART1_BASE


#ifdef CONFIG_FSL_USDHC


#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR

#define CONFIG_MXC_SPI
//#define CONFIG_CMD_SF

#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED		20000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#define CONFIG_SPI_FLASH_BAR

#define CONFIG_SYS_MAX_FLASH_BANKS	1

#ifdef CONFIG_NAND_MXS
# define CONFIG_SYS_MAX_NAND_DEVICE	1
# define CONFIG_SYS_NAND_BASE		0x40000000
# define CONFIG_SYS_NAND_5_ADDR_CYCLE
# define CONFIG_SYS_NAND_ONFI_DETECTION
# define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE
# define CONFIG_SYS_NAND_U_BOOT_OFFS	0x200000
#endif


#endif
			

#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ret=ok\0" 						\
	"console=ttymxc3\0" 			\
	"fit_name=fitImage\0" 			\
	"mtdparts="MTDPARTS_DEFAULT"\0"	\
	"hostname=RTU325R\0"						\
	"tftp_start="							\
		"tftpboot ${loadaddr} ${fit_name};"	\
		"bootm;\0"
	

/*Need to be defined during u-boot building - So we have 2 different bootloaders for SPI boot and NAND boot*/
#ifdef SPINOR_UBOOT 

/* If we are booting from SPI it means NAND is not OK => We need to avoid UBOOT errors caused by NAND inaccessibility */
/* SPI NOR ONLY - anyway */
#define CONFIG_BOOTCOMMAND									\
		"if sf probe; then "								\
			"echo SPI BOOT;"								\
			"setenv mtdids "MTDIDS_SPINOR";"				\
			"setenv mtdparts "MTDPARTS_SPINOR";"			\
			"setenv bootargs \""CONFIG_BOOTARGS" FIT_SPI\";"\
			"ubi part fit_X0;"								\
			"ubifsmount ubi0;"								\
			"ubifsload ${loadaddr} ${fit_name};"			\
			"bootm;"										\
		"else "												\
			"echo SPI NOR PROBE FAILED;"					\
			"sleep 5;"										\
			"reset;"										\
		"fi"

#else
/* We need to probe the NOR to avoid UBOOT errors caused by SPI NOR inaccessibility */
/* If SPI NOT is unvailable UBOOT must forget it (NAND ONLY) */		
#define CONFIG_BOOTCOMMAND							\
		"if sf probe; then "						\
			"echo SPI PROBED;"						\
			"echo NAND BOOT ATTEMPT;"				\
			"ubi part fit;"							\
			"ubifsmount ubi0;"						\
			"if ubifsload ${loadaddr} ${fit_name}; then "	\
				"echo UBIFS OK;"					\
			"else "									\
				"setenv ret error;"					\
			"fi;"									\
			"setenv bootargs \""CONFIG_BOOTARGS" FIT_NAND\";"	\
			"if test ${ret} = ok; then "			\
				"if bootm; then "					\
					"echo NAND BOOT OK;"			\
				"else "								\
					"setenv ret error;"				\
				"fi;"								\
			"fi;"									\
			"if test ${ret} = error; then "			\
				"echo NAND BOOT FAILED;"			\
				"echo SPI BOOT;"					\
				"setenv mtdids "MTDIDS_SPINOR";"	\
				"setenv mtdparts "MTDPARTS_SPINOR";"\
				"setenv bootargs \""CONFIG_BOOTARGS" FIT_SPI\";"	\
				"ubi part fit_X0;"					\
				"ubifsmount ubi0;"					\
				"ubifsload ${loadaddr} ${fit_name};"\
				"bootm;"							\
			"fi;"									\
		"else "										\
			"echo SPI NOR PROBE FAILED ;"			\
			"setenv mtdids "MTDIDS_NAND";"			\
			"setenv mtdparts "MTDPARTS_NAND";"		\
			"setenv bootargs \""CONFIG_BOOTARGS" FIT_NAND\";"	\
			"echo NAND BOOT ATTEMPT;"				\
			"ubi part fit;"							\
			"ubifsmount ubi0;"						\
			"ubifsload ${loadaddr} ${fit_name};"	\
			"bootm;"								\
		"fi"
		

#endif

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ				1000

/* Physical Memory Map */
#define PHYS_SDRAM					MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR 	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */

#define CONFIG_ENV_SIZE				SZ_8K
#define CONFIG_ENV_OFFSET			(8 * SZ_64K)

#ifndef CONFIG_SYS_DCACHE_OFF
#endif

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#endif


#ifdef CONFIG_CMD_NET

#define CONFIG_FEC_MXC
#define CONFIG_MII
#define CONFIG_FEC_ENET_DEV		0
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR	0x1
#define CONFIG_FEC_XCV_TYPE		RMII
#define CONFIG_ETHPRIME			"FEC"

#endif


#endif /* __ZIXLINK_ROUTER_CONFIG_H */
