/*
 * License:	GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/arch/iomux.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/boot_mode.h>
#include <asm/io.h>
#include <common.h>
#include <miiphy.h>
#include <linux/sizes.h>
#include <mmc.h>
#include <netdev.h>
#include <power/pmic.h>
#include <power/pfuze3000_pmic.h>
//#include "../common/pfuze.h"
#include <usb.h>
#include <usb/ehci-ci.h>
#include <fsl_esdhc_imx.h>

DECLARE_GLOBAL_DATA_PTR;

#include "gpio_config.h"

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();
	return 0;
}

static void setup_iomux(void)
{
	imx_iomux_v3_setup_multiple_pads(peripheral_pads, ARRAY_SIZE(peripheral_pads));
}

static struct fsl_esdhc_cfg usdhc_cfg[] = {
	{
		.esdhc_base = USDHC1_BASE_ADDR,
		.max_bus_width = 4,
	},
};

int board_mmc_getcd(struct mmc *mmc)
{
	return 1;
}

int board_mmc_init(bd_t *bis)
{
	int ret;

	usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);
	ret = fsl_esdhc_initialize(bis, &usdhc_cfg[0]);
	if (ret) {
		printf("Warning: failed to initialize mmc dev 0\n");
		return ret;
	}

	return 0;
}

int board_early_init_f(void)
{
	setup_iomux();
	return 0;
}

int board_init(void)
{
	/* Address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

	return 0;
}

int board_late_init(void)
{
	#define ENET2_RST_GPIO	IMX_GPIO_NR(2, 5)
	gpio_direction_output(ENET2_RST_GPIO, 1);
	
	return 0;
}

int checkboard(void)
{
	printf("ZixLink Shield2\n");
	return 0;
}
