/*
 * (C) Copyright 2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "asm/armv7.h"
#include "asm/system.h"
#include "asm/utils.h"
#include "io.h"

void flush_dcache_all(void);

#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))

#if defined(CONFIG_SYS_ARM_CACHE_WRITETHROUGH)
#define CACHE_SETUP	0x1a
#else
#define CACHE_SETUP	0x1e
#endif

static void cp_delay (void)
{
	volatile int i;

	/* copro seems to need some delay between reading and writing */
	for (i = 0; i < 100; i++)
		nop();
	asm volatile("" : : : "memory");
}

static inline void dram_bank_mmu_setup(u32 size)
{
	u32 *page_table = (u32 *)(CONFIG_SYS_SDRAM_BASE + OFFSET_PAGETABLES);
	u32 i;

	for (i = CONFIG_SYS_SDRAM_BASE >> 20;
			     i < (CONFIG_SYS_SDRAM_BASE + size) >> 20; i++)
		page_table[i] = i << 20 | (3 << 10) | CACHE_SETUP;
}


/* to activate the MMU we need to set up virtual memory: use 1M areas */

extern unsigned int start_ads;

static inline void mmu_setup(void)
{
	u32 *page_table = (u32 *)(CONFIG_SYS_SDRAM_BASE + OFFSET_PAGETABLES);
	int i;
	u32 reg;

	/* clear start_ads for pic_dereference because now we are running before clear bss code */
	start_ads = 0;

	// print32(get_aux());
	// puts("\n");

	/* Set up an identity-mapping for all 4GB, rw for everyone */
	for (i = 0; i < 4096; i++)
		page_table[i] = i << 20 | (3 << 10) | 0x12;

	dram_bank_mmu_setup(0x7f000000);

	/* add page table entry for the memory region stubby running */
	i = (u32)pic_dereference(0) >> 20;
	page_table[i] = i << 20 | (3 << 10) | CACHE_SETUP;

#if defined(CONFIG_SPLASH) && defined(CONFIG_SPLASH_FB_PA)

	/* framebuffer exception: strongly-ordered */

	for (i = CONFIG_SPLASH_FB_PA >> 20; i < (CONFIG_SPLASH_FB_PA >> 20) + 4; i++)
		page_table[i] = i << 20 | (3 << 10) | 0x12;

#endif


	/* Copy the page table address to cp15 */
	asm volatile(
		"mcr p15, 0, %0, c2, c0, 0"  : : "r" (page_table) : "memory");

	/* Set the access control to all-supervisor */
	asm volatile("mcr p15, 0, %0, c3, c0, 0" : : "r" (~0));

	/* and enable the mmu */

	reg = get_cr();	/* get control reg. */
	cp_delay();
	set_cr(reg | CR_M);
}

static int mmu_enabled(void)
{
	return get_cr() & CR_M;
}

/* cache_bit must be either CR_I or CR_C */
static void cache_enable(uint32_t cache_bit)
{
	uint32_t reg;

	/* The data cache is not active unless the mmu is enabled too */

	if ((cache_bit == CR_C) && !mmu_enabled())
		mmu_setup();

	reg = get_cr();	/* get control reg. */
	cp_delay();
	set_cr(reg | cache_bit);
}

/* cache_bit must be either CR_I or CR_C */
static void cache_disable(uint32_t cache_bit)
{
	uint32_t reg;

	reg = get_cr();
	cp_delay();

	if (cache_bit == CR_C) {
		/* if cache isn;t enabled no need to disable */
		if ((reg & CR_C) != CR_C)
			return;
		/* if disabling data cache, disable mmu too */
		cache_bit |= CR_M;
		flush_dcache_all();
	}
	set_cr(reg & ~cache_bit);
}
#endif

#ifdef CONFIG_SYS_ICACHE_OFF
void icache_enable (void)
{
	return;
}

void icache_disable (void)
{
	return;
}

int icache_status (void)
{
	return 0;					/* always off */
}
#else
void icache_enable(void)
{
	cache_enable(CR_I);
}

void icache_disable(void)
{
	cache_disable(CR_I);
}

int icache_status(void)
{
	return (get_cr() & CR_I) != 0;
}
#endif

#ifdef CONFIG_SYS_DCACHE_OFF
void dcache_enable (void)
{
	return;
}

void dcache_disable (void)
{
	return;
}

int dcache_status (void)
{
	return 0;					/* always off */
}
#else
void dcache_enable(void)
{
	cache_enable(CR_C);
}

void dcache_disable(void)
{
	cache_disable(CR_C);
}

int dcache_status(void)
{
	return (get_cr() & CR_C) != 0;
}
#endif
