/* B&N OMAP EMIF init board file.
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <asm/system_info.h>
#include <linux/platform_device.h>

#include "common-board-devices.h"
#include "common.h"

#include "board-hummingbird.h"
#include "board-ovation.h"

void __init bn_emif_init(void)
{
	bool supported = 0;

	switch(omap_sdram_vendor()) {
		case SAMSUNG_SDRAM:
			printk(KERN_INFO "Samsung DDR Memory\n");
			switch(system_rev) {
#ifdef CONFIG_MACH_OMAP_OVATION
				case OVATION_EVT1A:
					omap_emif_set_device_details(1, &lpddr2_samsung_4G_S4_info,
							lpddr2_samsung_4G_S4_timings,
							ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
							&lpddr2_samsung_S4_min_tck, NULL);
					omap_emif_set_device_details(2, &lpddr2_samsung_4G_S4_info,
							lpddr2_samsung_4G_S4_timings,
							ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
							&lpddr2_samsung_S4_min_tck, NULL);
					supported = 1;
					break;
				case OVATION_EVT1B:
				case OVATION_EVT2:
					switch (omap_total_ram_size()) {
						case SZ_1G:
							pr_info("\twith size: 1GB\n");
							omap_emif_set_device_details(1, &lpddr2_samsung_4G_S4_info,
									lpddr2_samsung_4G_S4_timings,
									ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
									&lpddr2_samsung_S4_min_tck, NULL);
							omap_emif_set_device_details(2, &lpddr2_samsung_4G_S4_info,
									lpddr2_samsung_4G_S4_timings,
									ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
									&lpddr2_samsung_S4_min_tck, NULL);
							supported = 1;
							break;
						case SZ_2G - SZ_4K:
						case SZ_2G:
							pr_info("\twith size: 2GB\n");
						default:
							omap_emif_set_device_details(1, &lpddr2_samsung_4G_S4_x2_info,
									lpddr2_samsung_4G_S4_timings,
									ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
									&lpddr2_samsung_S4_min_tck, NULL);
							omap_emif_set_device_details(2, &lpddr2_samsung_4G_S4_x2_info,
									lpddr2_samsung_4G_S4_timings,
									ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
									&lpddr2_samsung_S4_min_tck, NULL);

							supported = 1;
					}
					break;
#endif
				default:
					omap_emif_set_device_details(1, &lpddr2_samsung_4G_S4_info,
							lpddr2_samsung_4G_S4_timings,
							ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
							&lpddr2_samsung_S4_min_tck, NULL);
					omap_emif_set_device_details(2, &lpddr2_samsung_4G_S4_info,
							lpddr2_samsung_4G_S4_timings,
							ARRAY_SIZE(lpddr2_samsung_4G_S4_timings),
							&lpddr2_samsung_S4_min_tck, NULL);
					supported = 1;
			}
			break;
		case ELPIDA_SDRAM:
			printk(KERN_INFO "Elpida DDR Memory\n");
			switch(system_rev) {
#ifdef CONFIG_MACH_OMAP_OVATION
				case OVATION_EVT0:
				case OVATION_EVT0B:
					omap_emif_set_device_details(1, &lpddr2_elpida_2G_S4_x2_info,
							lpddr2_elpida_2G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_2G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					omap_emif_set_device_details(2, &lpddr2_elpida_2G_S4_x2_info,
							lpddr2_elpida_2G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_2G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					supported = 1;
					break;
				case OVATION_EVT0C:
				case OVATION_EVT1A:
					omap_emif_set_device_details(1, &lpddr2_elpida_4G_S4_info,
							lpddr2_elpida_4G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					omap_emif_set_device_details(2, &lpddr2_elpida_4G_S4_info,
							lpddr2_elpida_4G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					supported = 1;
					break;
				case OVATION_EVT1B:
				case OVATION_EVT2:
					switch (omap_total_ram_size()) {
						case SZ_1G:
							pr_info("\twith size 1G\n");
							omap_emif_set_device_details(1, &lpddr2_elpida_4G_S4_info,
									lpddr2_elpida_4G_S4_timings,
									ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
									&lpddr2_elpida_S4_min_tck, NULL);
							omap_emif_set_device_details(2, &lpddr2_elpida_4G_S4_info,
									lpddr2_elpida_4G_S4_timings,
									ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
									&lpddr2_elpida_S4_min_tck, NULL);
							supported = 1;
							break;
						case SZ_2G - SZ_4K:
						case SZ_2G:
							pr_info("\twith size 2G\n");
						default:
							omap_emif_set_device_details(1, &lpddr2_elpida_4G_S4_x2_info,
									lpddr2_elpida_4G_S4_timings,
									ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
									&lpddr2_elpida_S4_min_tck, NULL);
							omap_emif_set_device_details(2, &lpddr2_elpida_4G_S4_x2_info,
									lpddr2_elpida_4G_S4_timings,
									ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
									&lpddr2_elpida_S4_min_tck, NULL);
							supported = 1;
					}
					break;
#endif
				default:
					omap_emif_set_device_details(1, &lpddr2_elpida_4G_S4_info,
							lpddr2_elpida_4G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					omap_emif_set_device_details(2, &lpddr2_elpida_4G_S4_info,
							lpddr2_elpida_4G_S4_timings,
							ARRAY_SIZE(lpddr2_elpida_4G_S4_timings),
							&lpddr2_elpida_S4_min_tck, NULL);
					supported = 1;
			}
			break;
		case HYNIX_SDRAM:
			printk(KERN_INFO "Hynix DDR Memory\n");
#ifdef CONFIG_MACH_OMAP_OVATION
			if (system_rev < OVATION_EVT1A)
				break;
#endif
			omap_emif_set_device_details(1, &lpddr2_hynix_4G_S4_info,
					lpddr2_hynix_4G_S4_timings,
					ARRAY_SIZE(lpddr2_hynix_4G_S4_timings),
					&lpddr2_hynix_S4_min_tck, NULL);
			omap_emif_set_device_details(2, &lpddr2_hynix_4G_S4_info,
					lpddr2_hynix_4G_S4_timings,
					ARRAY_SIZE(lpddr2_hynix_4G_S4_timings),
					&lpddr2_hynix_S4_min_tck, NULL);
			supported = 1;
			break;
		default:
			 pr_err("Memory type does not exist\n");
	}

	if (!supported)
		pr_err("Memory type not supported [VID: 0x%X, SYSTEM_REV: 0x%X]\n", omap_sdram_vendor(), system_rev);
}
