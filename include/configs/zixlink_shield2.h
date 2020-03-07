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

/* SPL options */
#include "imx6_spl.h"

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

//#define CONFIG_IMX_WATCHDOG
//#define CONFIG_HW_WATCHDOG
//#define CONFIG_WATCHDOG_TIMEOUT_MSECS 30000

//#define CONFIG_SPI_FLASH_MTD

/*#define SPINOR_UBOOT*/


/* Kernel command line: */
#define CONFIG_USE_BOOTARGS
#define CONFIG_BOOTARGS             ""


/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN       (16 * SZ_1M)

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE        UART2_BASE


#ifdef CONFIG_FSL_USDHC
#  define CONFIG_SYS_FSL_ESDHC_ADDR   USDHC1_BASE_ADDR
#endif

#if 1
#define CONFIG_BOOTCOMMAND "mmc rescan;" \
                           "load mmc 0:1 ${loadaddr} /kernel;" \
                           "bootm;"
#else
#define CONFIG_BOOTCOMMAND "bootm;" 
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
