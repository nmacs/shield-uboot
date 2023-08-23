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

#include "gpio_config_2_2.h"

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

int board_mmc_init(struct bd_info *bis)
{
	int ret;

	usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);
	usdhc_cfg[0].max_bus_width = 4;

	ret = fsl_esdhc_initialize(bis, &usdhc_cfg[0]);
	if (ret) {
		printf("Warning: failed to initialize mmc dev 0\n");
		return ret;
	}

	return 0;
}

#ifdef CONFIG_USB_EHCI_MX6
#ifndef CONFIG_DM_USB

#define USB_OTHERREGS_OFFSET	0x800
#define UCTRL_PWR_POL		(1 << 9)

static iomux_v3_cfg_t const usb_poweron_pads[] = {
	MX6_PAD_GPIO1_IO01__GPIO1_IO01 | MUX_PAD_CTRL(USB_POWERON_PAD_CTRL),
	MX6_PAD_GPIO1_IO02__GPIO1_IO02 | MUX_PAD_CTRL(USB_POWERON_PAD_CTRL),
};

/* At default the 3v3 enables the MIC2026 for VBUS power */
static void setup_usb(void)
{
	imx_iomux_v3_setup_multiple_pads(usb_poweron_pads,
					 ARRAY_SIZE(usb_poweron_pads));

#define USB1_POWERON_GPIO IMX_GPIO_NR(1, 1)
#define USB2_POWERON_GPIO IMX_GPIO_NR(1, 2)

	gpio_direction_output(USB1_POWERON_GPIO, 1);
	gpio_direction_output(USB2_POWERON_GPIO, 1);
}

int board_usb_phy_mode(int port)
{
	return USB_INIT_HOST;
}

int board_ehci_hcd_init(int port)
{
	if (port > 1)
		return -EINVAL;

	return 0;
}
#endif
#endif

int board_early_init_f(void)
{
	setup_iomux();
	return 0;
}

int board_init(void)
{
	/* Address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_USB_EHCI_MX6
#ifndef CONFIG_DM_USB
	setup_usb();
#endif
#endif

	return 0;
}

int board_late_init(void)
{
	return 0;
}

int checkboard(void)
{
	printf("ZixLink Shield V2.2\n");
	return 0;
}
