#ifndef __OMAP_PMIC_COMMON__
#define __OMAP_PMIC_COMMON__

#include <linux/mfd/palmas.h>

#include <linux/i2c.h>
#include <plat/irqs.h>
#include "voltage.h"

#define TWL_COMMON_PDATA_USB		(1 << 0)
#define TWL_COMMON_PDATA_BCI		(1 << 1)
#define TWL_COMMON_PDATA_MADC		(1 << 2)
#define TWL_COMMON_PDATA_AUDIO		(1 << 3)
#define TWL_COMMON_PDATA_THERMAL	(1 << 4)

/* Common LDO regulators for TWL4030/TWL6030/TWL6032 */
/* LDOLN for TWL6032 */
#define TWL_COMMON_REGULATOR_VDAC	(1 << 0)
/* LDO2 for TWL6032 */
#define TWL_COMMON_REGULATOR_VAUX1	(1 << 1)
/* LDO4 for TWL6032 */
#define TWL_COMMON_REGULATOR_VAUX2	(1 << 2)
/* LDO3 for TWL6032 */
#define TWL_COMMON_REGULATOR_VAUX3	(1 << 3)

/* Common regulators for TWL6030/TWL6032 */
/* LDO5 for TWL6032 */
#define TWL_COMMON_REGULATOR_VMMC	(1 << 4)
/* LDO1 for TWL6032 */
#define TWL_COMMON_REGULATOR_VPP	(1 << 5)
/* LDO7 for TWL6032 */
#define TWL_COMMON_REGULATOR_VUSIM	(1 << 6)
#define TWL_COMMON_REGULATOR_VANA	(1 << 7)
/* LDO6 for TWL6032 */
#define TWL_COMMON_REGULATOR_VCXIO	(1 << 8)
/* LDOUSB for TWL6032 */
#define TWL_COMMON_REGULATOR_VUSB	(1 << 9)
#define TWL_COMMON_REGULATOR_CLK32KG	(1 << 10)
/* SMPS4 for TWL6032 */
#define TWL_COMMON_REGULATOR_V1V8	(1 << 11)
#define TWL_COMMON_REGULATOR_V2V1	(1 << 12)
#define TWL_COMMON_REGULATOR_SYSEN	(1 << 13)
#define TWL_COMMON_REGULATOR_CLK32KAUDIO	(1 << 14)
#define TWL_COMMON_REGULATOR_REGEN1	(1 << 15)

/* TWL4030 LDO regulators */
#define TWL_COMMON_REGULATOR_VPLL1	(1 << 4)
#define TWL_COMMON_REGULATOR_VPLL2	(1 << 5)


struct twl4030_platform_data;
struct twl6040_platform_data;

void omap_pmic_init(int bus, u32 clkrate, const char *pmic_type, int pmic_irq,
		    struct twl4030_platform_data *pmic_data);
void omap_pmic_late_init(void);

static inline void omap2_pmic_init(const char *pmic_type,
				   struct twl4030_platform_data *pmic_data)
{
	omap_pmic_init(2, 2600, pmic_type, INT_24XX_SYS_NIRQ, pmic_data);
}

static inline void omap3_pmic_init(const char *pmic_type,
				   struct twl4030_platform_data *pmic_data)
{
	omap_pmic_init(1, 2600, pmic_type, INT_34XX_SYS_NIRQ, pmic_data);
}

void omap4_pmic_init(const char *pmic_type,
		    struct twl4030_platform_data *pmic_data,
		    struct twl6040_platform_data *audio_data, int twl6040_irq);

void omap3_pmic_get_config(struct twl4030_platform_data *pmic_data,
			   u32 pdata_flags, u32 regulators_flags);

void omap4_pmic_get_config(struct twl4030_platform_data *pmic_data,
			   u32 pdata_flags, u32 regulators_flags);
void omap5_pmic_init(int bus_id, const char *pmic_type, int pmic_irq,
		     struct palmas_platform_data *pmic_data,
		     const char *audio_type, int audio_irq,
		     struct twl6040_platform_data *audio_data);

/**
 * struct omap_pmic_map - Describe the OMAP PMIC data for OMAP
 * @name:		name of the voltage domain
 * @pmic_data:		pmic data associated with it
 * @cpu:		CPUs this PMIC data is valid for
 * @special_action:	callback for any specific action to take for that map
 *
 * Since we support multiple PMICs each potentially functioning on multiple
 * OMAP devices, we describe the parameters in a map allowing us to reuse the
 * data as necessary.
 */
struct omap_pmic_map {
	char			*name;
	struct omap_voltdm_pmic	*pmic_data;
	u32			cpu;
	int			(*special_action)(struct voltagedomain *);
};

#define PMIC_CPU_OMAP3		(1 << 0)
#define PMIC_CPU_OMAP4430	(1 << 1)
#define PMIC_CPU_OMAP4460	(1 << 2)
#define PMIC_CPU_OMAP4470	(1 << 4)
#define PMIC_CPU_OMAP44XX	(PMIC_CPU_OMAP4430 | PMIC_CPU_OMAP4460 | \
		PMIC_CPU_OMAP4470)
#define PMIC_CPU_OMAP54XX	(1 << 3)

extern int omap_pmic_register_data(struct omap_pmic_map *map);
extern void omap_pmic_data_init(void);

#ifdef CONFIG_OMAP_TPS6236X
extern int omap_tps6236x_board_setup(bool use_62361, int gpio_vsel0,
			int gpio_vsel1, int pull0, int pull1);
extern int omap_tps6236x_init(void);
extern void omap_tps6236x_gpio_no_reset_wa(int gpio_vsel0,
		int gpio_vsel1, int gpio_bank_width);
#else
static inline int omap_tps6236x_board_setup(bool use_62361, int gpio_vsel0,
			int gpio_vsel1, int pull0, int pull1)
{
	return -EINVAL;
}
static inline int omap_tps6236x_init(void)
{
	return -EINVAL;
}
static inline void omap_tps6236x_gpio_no_reset_wa(int gpio_vsel0, int gpio_vsel1,
		int gpio_bank_width)
{}
#endif

#ifdef CONFIG_MFD_PALMAS
extern int omap_palmas_init(void);
#else
static inline int omap_palmas_init(void)
{
	return -EINVAL;
}
#endif
#endif /* __OMAP_PMIC_COMMON__ */
