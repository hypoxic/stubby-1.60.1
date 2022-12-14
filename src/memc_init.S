/*
 * u-boot/arch/arm/cpu/armv7/mb8ac0300/memc_init.S
 *
 * Copyright (C) 2011-2012 FUJITSU SEMICONDUCTOR LIMITED
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
                                                                                
/*
 * init_memc : Initialization of the Registers of MEMC
 */
.globl init_memc
init_memc:

	/*
	 * SPI boot force region size
	 */

	ldr	r0, =CONFIG_HSSPI_PHYS
	ldr	r1, [r0]
	orr	r1, r1, #0xb0000 /* 16MByte */
	str	r1, [r0]


	/*
	 * Mode Register0-7
	 */
	@ Bit1-0 WDT(Data Width)
	@	0:8bits(initial value)
	@	1:16bits
	@	2:32bits
	@	3:Reserved
	@ Bit2 RBMON(Read Byte Mask ON)
	@	0:Disabled(initial value)
	@	1:Enabled
	@ Bit3 WEOFF(WEX OFF) Write Enable OFF
	@	0:Disabled(initial value)
	@	1:Enabled
	@ Bit4 NAND(NAND flash mode)
	@	0:NAND flash mode OFF(initial value)
	@	1:NAND flash mode ON
	@ Bit5 PAGE(PAGE access mode) NOR flash page access mode
	@	0:NOR flash page access OFF(initial value)
	@	1:NOR flash page access ON
	@ Bit6 RDY(READY MODE)
	@	0:READY mode OFF(initial value)
	@	1:READY mode ON

	ldr	r0, =0xfff64000		@ MODE0 address
	ldr	r1, = 0x00000020	@ x8 NOR flash, pagemode
	str	r1, [r0]

	add	r0, r0, #4		@ MODE1 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ MODE2 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ MODE3 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ MODE4 address
	ldr	r1, = 0x00000022	@ x32 NOR Flash, pagemode
	str	r1, [r0]

	add     r0, r0, #4		@ MODE5 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ MODE6 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ MODE7 address
	ldr	r1, = 0x00000000	@ N.C
	str	r1, [r0]

	/*
	 * Timing Register0-7
	 */
	@ Bit3-0 RACC (Read Access Cycle)
	@	0:1cycle
	@	1:2cycles
	@	   ...
	@	15:16cycle(initial value)
	@ Bit7-4 RADC (Read Address Setup Cycle)
	@	0:1cycle
	@	1:2cycles
	@	   ...
	@	15:16cycle(initial value)
	@ Bit11-8 FRADC (First Read Address Cycle)
	@	0:1cycle(initial value)
	@	1:2cycles
	@	   ...
	@	15:16cycles
	@ Bit15-12 RIDLC (Read Idle Cycle)
	@	0:1cycle
	@	1:2cycles
	@	   ...
	@	15:16cycles(initial value)
	@ Bit19-16 WACC (Write Access Cycle)
	@	0:Reserved
	@	1:Reserved
	@	2:3cycles
	@	3:4cycles
	@	   ...
	@	15:16cycles(initial value)
	@ Bit23-20 WADC (Write Address Setup cycle)
	@	0:1cycle
	@	   ...
	@	5:6cycles(initial value)
	@	   ...
	@	14:15cycles
	@	15:Reserved
	@ Bit27-24 WWEC (Write Enable Cycle)
	@	0:1cycle
	@	   ...
	@	5:6cycles(initial value)
	@	   ...
	@	14:15cycles
	@	15:Reserved
	@ Bit31-28 WIDLC (Write Idle Cycle)
	@	0:1cycle
	@	1:2cycles
	@	   ...
	@	15:16cycles(initial value)

	ldr	r0, =0xfff64020		@ TIM0 address
	ldr	r1, =0x144c100a		@ x8 NOR flash
	str	r1, [r0]

	add     r0, r0, #4		@ TIM1 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ TIM2 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ TIM3 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ TIM4 address
	ldr	r1, =0x144c100a		@ x32 NOR Flash
	str	r1, [r0]

	add     r0, r0, #4		@ TIM5 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ TIM6 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ TIM7 address
	ldr	r1, =0x055ff00f		@ N.C
	str	r1, [r0]

	/*
	 * Area Register
	 */
	@ Bit7-0 ADDR (Address)
	@	These bits specify addresses
	@	to set the corresponding MCSX region.
	@ Bit23-16 MASK (address mask)
	@	These bits set the mask value of the value set in ADDR.

	ldr	r0, =0xfff64040		@ AREA0 address

/* XCS0 boot */
	ldr     r1, = 0x001f0000        @ x32 NOR Flash 32MByte 0x04000000

	str	r1, [r0]

	add     r0, r0, #4		@ AREA1 address
	ldr	r1, = 0x000f0090	@ N.C  16M +0x09000000
	str	r1, [r0]

	add     r0, r0, #4		@ AREA2 address
	ldr	r1, = 0x000f0020	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ AREA3 address
	ldr	r1, = 0x000f0030	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ AREA4 address

/* XCS0 boot */
	ldr     r1, = 0x001f0040        @ x8 NOR flash 16MByte   0x11000000

	str	r1, [r0]

	add     r0, r0, #4		@ AREA5 address
	ldr	r1, = 0x000f0080	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ AREA6 address
	ldr	r1, = 0x000f0060	@ N.C
	str	r1, [r0]

	add     r0, r0, #4		@ AREA7 address
	ldr	r1, = 0x00000070	@ N.C
	str	r1, [r0]

	mov	pc, lr

