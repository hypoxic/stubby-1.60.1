/*
 * u-boot/arch/arm/cpu/armv7/mb8ac0300/ddr3c_init.c
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
#include "ddr3c.h"

void wait(u32 count)
{
	u32 i;

	for(i=0; i<count; i++)
	{
		asm("nop");
	}
}

u32 init_ddr3c(void)
{
	unsigned long vSWLVL_OP_DONE = 0;
	unsigned long vINT_STATUS = 0;

	if ((DATABAHN->CTL000 & START1) == START1)
	{
		/* Finished DDRC initialize */
		return 0;
	}

/*
 * Initialization procedure
 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x41C) = 0x00FF0F01;
	*(volatile u32 *)((u32)DDR3C_BASE+0x420) = 0x01882222;

	wait(10);

	DATABAHN->CTL000 = DRAM_CLASS
			| START0;

	DATABAHN->CTL001 = MAX_CS_REG
			| MAX_COL_REG
			| MAX_ROW_REG;

	DATABAHN->CTL002 = TINIT;

	DATABAHN->CTL003 = TRST_PWRON;

	DATABAHN->CTL004 = CKE_INACTIVE;

	DATABAHN->CTL005 = TBST_INT_INTERVAL
			| WRLAT
			| CASLAT_LIN
			| INITAREF;

	DATABAHN->CTL006 = TRAS_MIN
			| TRC
			| TRRD
			| TCCD;

	DATABAHN->CTL007 = TMRD
			| TRTP
			| TRP
			| TWTR;

	DATABAHN->CTL008 = TRAS_MAX
			| TMOD;

	DATABAHN->CTL009 = AP
			| WRITEINTERP
			| TCKESR
			| TCKE;

	DATABAHN->CTL010 = TWR_INT
			| TRCD_INT
			| TRAS_LOCKOUT
			| CONCURRENTAP;

	DATABAHN->CTL011 = NO_CMD_INIT
			| TDLL
			| TDAL;

	DATABAHN->CTL012 = TCPD
			| TFAW
			| BSTLEN;

	DATABAHN->CTL013 = ADDRESS_MIRRORING
			| REG_DIMM_ENABLE
			| TRP_AB;

	DATABAHN->CTL014 = RDIMM_CTL_0_31_0;

	DATABAHN->CTL015 = RDIMM_CTL_0_63_32;

	DATABAHN->CTL016 = RDIMM_CW_HOLD_CKE_EN
			| RDIMM_CWW_REQ
			| RDIMM_CWW_MAP;

	DATABAHN->CTL017 = RDIMM_TSTAB
			| RDIMM_TMRD;

	DATABAHN->CTL018 = TREF_ENABLE
			| AUTO_REFRESH_MODE
			| AREFRESH
			| REG_DIMM_PARITY_ERROR;

	DATABAHN->CTL019 = TREF
			| TRFC;

	DATABAHN->CTL020 = POWER_DOWN
			| TREF_INTERVAL;

	DATABAHN->CTL021 = TXPDLL
			| TPDEX;

	DATABAHN->CTL022 = TXSNR
			| TXSR;

	DATABAHN->CTL023 = ENABLE_QUICK_SREFRESH
			| SREFRESH_EXIT_NO_REFRESH
			| PWRUP_SREFRESH_EXIT
			| SREFRESH;

	DATABAHN->CTL024 = PWRDN_SHIFT_DELAY
			| CKE_DELAY;

	DATABAHN->CTL025 = WRITE_MODEREG;

	DATABAHN->CTL026 = MR0_DATA_0
			| MRW_STATUS;

	DATABAHN->CTL027 = MR2_DATA_0
			| MR1_DATA_0;

	DATABAHN->CTL028 = MR3_DATA_0
			| MRSINGLE_DATA_0;

	DATABAHN->CTL029 = MR1_DATA_1
			| MR0_DATA_1;

	DATABAHN->CTL030 = MRSINGLE_DATA_1
			| MR2_DATA_1;

	DATABAHN->CTL031 = ZQINIT
			| MR3_DATA_1;

	DATABAHN->CTL032 = ZQCS
			| ZQCL;

	DATABAHN->CTL033 = ZQ_IN_PROGRESS
			| REFRESH_PER_ZQ
			| ZQ_ON_SREF_EXIT
			| ZQ_REQ;

	DATABAHN->CTL034 = COLUMN_SIZE
			| ADDR_PINS
			| EIGHT_BANK_MODE
			| ZQCS_ROTATE;

	DATABAHN->CTL035 = ADDR_CMP_EN
			| COMMAND_AGE_COUNT
			| AGE_COUNT
			| APREBIT;

	DATABAHN->CTL036 = RW_SAME_EN
			| PRIORITY_EN
			| PLACEMENT_EN
			| BANK_SPLIT_EN;

	DATABAHN->CTL037 = CS_MAP
			| INHIBIT_DRAM_CMD
			| SWAP_PORT_RW_SAME_EN
			| SWAP_EN;

	DATABAHN->CTL038 = Q_FULLENESS
			| FAST_WRITE
			| REDUCT
			| BURST_ON_FLY_BIT;

	DATABAHN->CTL039 = RESYNC_DLL_PER_AREF_EN
			| RESYNC_DLL
			| CONTROLLER_BUSY;

	DATABAHN->CTL040 = INT_STATUS;

	DATABAHN->CTL041 = INT_ACK;

	DATABAHN->CTL042 = INT_MASK;

	DATABAHN->CTL043 = OUT_OF_RANGE_ADDR;

	DATABAHN->CTL044 = OUT_OF_RANGE_TYPE
			| OUT_OF_RANGE_LENGTH
			| OUT_OF_RANGE_ADDR_33_32;

	DATABAHN->CTL045 = OUT_OF_RANGE_SOURCE_ID;

	DATABAHN->CTL046 = PORT_CMD_ERROR_ADDR;

	DATABAHN->CTL047 = PORT_CMD_ERROR_TYPE
			| PORT_CMD_ERROR_ID
			| PORT_CMD_ERROR_ADDR_33_32;

	DATABAHN->CTL048 = ODT_WR_MAP_CS0
			| ODT_RD_MAP_CS0
			| PORT_DATA_ERROR_ID;

	DATABAHN->CTL049 = ADD_ODT_CLK_W2R_SAMECS
			| ADD_ODT_CLK_R2W_SAMECS
			| OUT_WR_MAP_CS1
			| OUT_RD_MAP_CS1;

	DATABAHN->CTL050 = R2W_DIFFCS_DLY
			| R2R_DIFFCS_DLY
			| ADD_ODT_CLK_SAMETYPE_DIFFCS
			| ADD_ODT_CLK_DIFFTYPE_DIFFCS;

	DATABAHN->CTL051 = R2W_SAMECS_DLY
			| R2R_SAMECS_DLY
			| W2W_DIFFCS_DLY
			| W2R_DIFFCS_DLY;

	DATABAHN->CTL052 = OCD_ADJUST_PUP_CS_0
			| OCD_ADJUST_PDN_CS_0
			| W2W_SAMECS_DLY
			| W2R_SAMECS_DLY;

	DATABAHN->CTL053 = SWLVL_EXIT
			| SWLVL_START
			| SWLVL_LOAD
			| SWLVL_LEVELING_MODE;

	DATABAHN->CTL054 = SWLVL_RESP_1
			| SWLVL_RESP_0
			| LVL_STATUS
			| SWLVL_OP_DONE;

	DATABAHN->CTL055 = WRLVL_CS
			| WRLVL_REQ
			| SWLVL_RESP_3
			| SWLVL_RESP_2;

	DATABAHN->CTL056 = WRLVL_EN
			| WLMRD
			| WLDQSEN;

	DATABAHN->CTL057 = WRLVL_ERROR_STATUS
			| WRLVL_REFRESH_INTERVAL;

	DATABAHN->CTL058 = WRLVL_DELAY_0
			| WRLVL_REG_EN;

	DATABAHN->CTL059 = WRLVL_DELAY_2
			| WRLVL_DELAY_1;

	DATABAHN->CTL060 = RDLVL_GATE_REQ
			| RDLVL_REQ
			| WRLVL_DELAY_3;

	DATABAHN->CTL061 = RDLVL_REG_EN
			| RDLVL_BEGIN_DELAY_EN
			| RDLVL_EDGE
			| RDLVL_CS;

	DATABAHN->CTL062 = RDLVL_BEGIN_DELAY_0
			| RDLVL_GATE_REG_EN;

	DATABAHN->CTL063 = RDLVL_MIDPOINT_DELAY_0
			| RDLVL_END_DELAY_0;

	DATABAHN->CTL064 = RDLVL_OFFSET_DIR_0
			| RDLVL_OFFSET_DELAY_0;

	DATABAHN->CTL065 = RDLVL_GATE_DELAY_0
			| RDLVL_DELAY_0;

	DATABAHN->CTL066 = RDLVL_END_DELAY_1
			| RDLVL_BEGIN_DLEAY_1;

	DATABAHN->CTL067 = RDLVL_OFFSET_DELAY_1
			| RDLVL_MIDPOINT_DELAY_1;

	DATABAHN->CTL068 = RDLVL_DELAY_1
			| RDLVL_OFFSET_DIR_1;

	DATABAHN->CTL069 = RDLVL_BEGIN_DELAY_2
			| RDLVL_GATE_DELAY_1;

	DATABAHN->CTL070 = RDLVL_MIDPOINT_DELAY_2
			| RDLVL_END_DELAY_2;

	DATABAHN->CTL071 = RDLVL_OFFSET_DIR_2
			| RDLVL_OFFSET_DELAY_2;

	DATABAHN->CTL072 = RDLVL_GATE_DELAY_2
			| RDLVL_DELAY_2;

	DATABAHN->CTL073 = RDLVL_END_DELAY_3
			| RDLVL_BEGIN_DELAY_3;

	DATABAHN->CTL074 = RDLVL_OFFSET_DELAY_3
			| RDLVL_MIDPOINT_DELAY_3;

	DATABAHN->CTL075 = RDLVL_DELAY_3
			| RDLVL_OFFSET_DIR_3;

	DATABAHN->CTL076 = AXI0_EN_SIZE_LT_WIDTH_INSTR
			| RDLVL_GATE_DELAY_3;

	DATABAHN->CTL077 = AXI0_FIFO_TYPE_REG;

	DATABAHN->CTL078 = AXI1_EN_SIZE_LT_WIDTH_INSTR;

	DATABAHN->CTL079 = AXI2_EN_SIZE_LT_WIDTH_INSTR
			| AXI1_FIFO_TYPE_REG;

	DATABAHN->CTL080 = AXI3_EN_SIZE_LT_WIDTH_INSTR
			| AXI2_FIFO_TYPE_REG;

	DATABAHN->CTL081 = AXI3_FIFO_TYPE_REG;

	DATABAHN->CTL082 = AXI0_PRIORITY0_RELATIVE_PRIORITY
			| WRR_PARAM_VALUE_ERR
			| WEIGHTED_ROUND_ROBIN_WEIGHT_SHARING
			| WEIGHTED_ROUND_ROBIN_LATENCY_CONTROL;

	DATABAHN->CTL083 = AXI0_PORT_ORDERING
			| AXI0_PRIORITY3_RELATIVE_PRIORITY
			| AXI0_PRIORITY2_RELATIVE_PRIORITY
			| AXI0_PRIORITY1_RELATIVE_PRIORITY;

	DATABAHN->CTL084 = AXI1_PRIORITY1_RELATIVE_PRIORITY
			| AXI1_PRIORITY0_RELATIVE_PRIORITY
			| AXI0_PRIORITY_RELAX;

	DATABAHN->CTL085 = AXI1_PORT_ORDERING
			| AXI1_RPIORITY3_RELATIVE_PRIORITY
			| AXI1_RPIORITY2_RELATIVE_PRIORITY;

	DATABAHN->CTL086 = AXI2_PRIORITY1_RELATIVE_PRIORITY
			| AXI2_PRIORITY0_RELATIVE_PRIORITY
			| AXI1_PRIORITY_RELAX;

	DATABAHN->CTL087 = AXI2_PORT_ORDERING
			| AXI2_PRIORITY3_RELATIVE_PRIORITY
			| AXI2_PRIORITY2_RELATIVE_PRIORITY;

	DATABAHN->CTL088 = AXI3_PRIORITY1_RELATIVE_PRIORITY
			| AXI3_PRIORITY0_RELATIVE_PRIORITY
			| AXI2_PRIORITY_RELAX;

	DATABAHN->CTL089 = AXI3_PORT_ORDERING
			| AXI3_PRIORITY3_RELATIVE_PRIORITY
			| AXI3_PRIORITY2_RELATIVE_PRIORITY;

	DATABAHN->CTL090 = MEM_RST_VALID
			| CKE_STATUS
			| AXI3_PRIORITY_RELAX;

	DATABAHN->CTL091 = TDFI_PHY_WRLAT
			| DLL_RST_ADJ_DLY
			| DLL_RST_DELAY;

	DATABAHN->CTL092 = DRAM_CLK_DISABLE
			| TDFI_RDDATA_EN
			| TDFI_PHY_RDLAT
			| UPDATE_ERROR_STATUS;

	DATABAHN->CTL093 = TDFI_CTRLUPD_MAX
			| TDFI_CTRLUPD_MIN;

	DATABAHN->CTL094 = TDFI_PHYUPD_TYPE1
			| TDFI_PHYUPD_TYPE0;

	DATABAHN->CTL095 = TDFI_PHYUPD_TYPE3
			| TDFI_PHYUPD_TYPE2;

	DATABAHN->CTL096 = TDFI_PHYUPD_RESP;

	DATABAHN->CTL097 = TDFI_CTRLUPD_INTERVAL;

	DATABAHN->CTL098 = DFI_WRLVL_MAX_DELAY
			| WRLAT_ADJ
			| RDLAT_ADJ;

	DATABAHN->CTL099 = TDFI_WRLVL_RESPLAT
			| TDFI_WRLVL_LOAD
			| TDFI_WRLVL_DLL
			| TDFI_WRLVL_EN;

	DATABAHN->CTL100 = TDFI_WRLVL_WW;

	DATABAHN->CTL101 = TDFI_WRLVL_RESP;

	DATABAHN->CTL102 = TDFI_WRLVL_MAX;

	DATABAHN->CTL103 = RDLVL_GATE_MAX_DELAY
			| RDLVL_MAX_DELAY;

	DATABAHN->CTL104 = TDFI_RDLVL_RESPLAT
			| TDFI_RDLVL_LOAD
			| TDFI_RDLVL_DLL
			| TDFI_RDLVL_EN;

	DATABAHN->CTL105 = TDFI_RDLVL_RR;

	DATABAHN->CTL106 = TDFI_RDLVL_RESP;

	DATABAHN->CTL107 = RDLVL_RESP_MASK;

	DATABAHN->CTL108 = RDLVL_GATE_RESP_MASK;

	DATABAHN->CTL109 = RDLVL_GATE_PREAMBLE_CHECK_EN
			| RDLVL_GATE_EN
			| RDLVL_EN;

	DATABAHN->CTL110 = TDFI_RDLVL_MAX;

	DATABAHN->CTL111 = RDLVL_GATE_DQ_ZERO_COUNT
			| RDLVL_DQ_ZERO_COUNT;

	DATABAHN->CTL112 = RDLVL_ERROR_STATUS;
	DATABAHN->CTL113 = RDLVL_GATE_REFRESH_INTERVAL
			| RDLVL_REFRESH_INTERVAL;

	DATABAHN->CTL114 = ODT_ALT_EN;

	wait(10);

/*
 * Reset sequence
 */

	/* IRSTX 0->1 */
	*(volatile u32 *)((u32)DDR3C_BASE+0x408) = 0x0000000F;

	wait(1);

	/* IDLLRSTX,IPZQRSTX 0->1 */
	*(volatile u32 *)((u32)DDR3C_BASE+0x408) = 0x0003000F;

	wait(11000);   /* wait DLL Lock about 73us */

	/* ISOFTRSTX 0->1 */
	*(volatile u32 *)((u32)DDR3C_BASE+0x408) = 0x0007000F;

/*
 * PZQ initial calibration
 */
	wait(225000);   /* wait PZQ_INIT about 1500us */

	*(volatile u32 *)((u32)DDR3C_BASE+0x440) = 0x00000000;

	wait(10);

	/* dfi_init_complete 0->1 */
	*(volatile u32 *)((u32)DDR3C_BASE+0x404) = 0x00000001;

	wait(20);

	DATABAHN->CTL000 = DRAM_CLASS
			| START1;

	wait(20);

/*
 * Initial Setting End
 */

/* =================================================== */

/*
 * Write Leveling
 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x18C) = 0x141F0F10;
					/* TDFI_WRLVL_DLL = 0xF */
					/* TDFI_WRLVL_LOAD = 0x1F */
					/* TDFI_WRLVL_RESPLAT = 0x14 */
					/* TDFI_WRLVL_EN = 0x10 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x194) = 0x00000000;
					/* TDFI_WRLVL_RESP = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x190) = 0x0000001A;
					/* TDFI_WRLVL_WW = 0x1A */

	*(volatile u32 *)((u32)DDR3C_BASE+0x020) = 0x06DB000C;
						/* TMOD = 0xC */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0E0) = 0x00002819;
						/* WLDQSEN = 0x19 */
						/* WLMRD = 0x28 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0DC) = 0x00000000;
						/* WRLVL_CS = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00010001;
					/* SW_LEVELING_MODE = 0x1 */
					/* SWLVL_START = 0x1 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x06C) = 0x000010C0;
				/* CS0 MRS(DRAM write leveling entry) */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
					/* SWLVL_OP_DONE == 0x1 */
		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	*(volatile u32 *)((u32)DDR3C_BASE+0x0E8) = 0x00001E00;
					/* WRLVL_DELAY_0 = 0x1E */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0EC) = 0x001A001C;
					/* WRLVL_DELAY_1 = 0x1C */
					/* WRLVL_DELAY_2 = 0x1A */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0F0) = 0x00000017;
					/* WRLVL_DELAY_3 = 0x17 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x42C) = 0x000A3004;
					/* r_txdq_sft_0,r_rxdqs_sft_0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x430) = 0x000A2F04;
					/* r_txdq_sft_1,r_rxdqs_sft_1 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x434) = 0x000A2C04;
					/* r_txdq_sft_2,r_rxdqs_sft_2 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x438) = 0x000A2A04;
					/* r_txdq_sft_3,r_rxdqs_sft_3 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00000101;
						/* SWLVL_LOAD = 0x1 */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
					/* SWLVL_OP_DONE == 0x1 */
		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0D8) & 0x00FF0000;
						/* SWLVL_RESP_0 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0D8) & 0xFF000000;
						/* SWLVL_RESP_1 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0DC) & 0x0000FF00;
						/* SWLVL_RESP_2 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0DC) & 0x000000FF;
						/* SWLVL_RESP_3 check */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x01000001;
						/* SWLVL_EXIT = 0x1 */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
						/* SWLVL_OP_DONE == 0x1 */

		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	*(volatile u32 *)((u32)DDR3C_BASE+0x06C) = 0x00001040;
				/* CS0 MRS(DRAM write leveling exit) */

	*(volatile u32 *)((u32)DDR3C_BASE+0x18C) = 0x00000000;
					/* TDFI_WRLVL_DLL = 0x0 */
					/* TDFI_WRLVL_LOAD = 0x0 */
					/* TDFI_WRLVL_RESPLAT = 0x0 */
					/* TDFI_WRLVL_EN = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A4) = 0x00000000;
					/* TDFI_RDLVL_RR = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00000000;
					/* SW_LEVELING_MODE = 0x0 */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0A0);
//	vUPDATE_ERROR_STATUS = *((volatile unsigned long *)0xFFF4A170);
	*(volatile u32 *)((u32)DDR3C_BASE+0x0A4) = vINT_STATUS;


/* =================================================== */

/*
 * Gate Training
 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A0) = 0x0D0F0F0F;
					/* TDFI_RDLVL_DLL = 0xF */
					/* TDFI_RDLVL_LOAD = 0x0F */
					/* TDFI_RDLVL_RESPLAT = 0xD */
					/* TDFI_RDLVL_EN = 0xF */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A8) = 0x00000000;
					/* TDFI_RDLVL_RESP = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A4) = 0x0000001A;
					/* TDFI_RDLVL_RR = 0x1A */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0F4) = 0x00000000;
					/* RDLVL_CS = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00010003;
					/* SW_LEVELING_MODE = 0x3 */
					/* SWLVL_START = 0x1 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x070) = 0x00040000;
					/* CS0 MRS DRAM MPR entry) */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
					/* SWLVL_OP_DONE == 0x1 */

		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	*(volatile u32 *)((u32)DDR3C_BASE+0x0E8) = 0x00320000;
					/* RDLVL_GATE_DELAY_0 = 0x32 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x114) = 0x00000030;
					/* RDLVL_GATE_DELAY_1 = 0x30 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x120) = 0x002D0000;
					/* RDLVL_GATE_DELAY_2 = 0x2D */

	*(volatile u32 *)((u32)DDR3C_BASE+0x130) = 0x0000002B;
					/* RDLVL_GATE_DELAY_3 = 0x2B */

	*(volatile u32 *)((u32)DDR3C_BASE+0x42C) = 0x000A3004;
					/* r_txdq_sft_0,r_rxdqs_sft_0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x430) = 0x000A2F04;
					/* r_txdq_sft_1,r_rxdqs_sft_1 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x434) = 0x000A2C04;
					/* r_txdq_sft_2,r_rxdqs_sft_2 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x438) = 0x000A2A04;
					/* r_txdq_sft_3,r_rxdqs_sft_3 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00000103;
					/* SWLVL_LOAD = 0x1 */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
					/* SWLVL_OP_DONE == 0x1 */

		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0D8) & 0x00FF0000;
						/* SWLVL_RESP_0 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0D8) & 0xFF000000;
						/* SWLVL_RESP_1 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0DC) & 0x0000FF00;
						/* SWLVL_RESP_2 check */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0DC) & 0x000000FF;
						/* SWLVL_RESP_3 check */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x01000003;
						/* SWLVL_EXIT = 0x1 */

	while (1)
	{
		vSWLVL_OP_DONE = *((volatile unsigned long *)0xFFF4A0D8);
						/* SWLVL_OP_DONE == 0x1 */
		if((vSWLVL_OP_DONE & 0x00000001) == 0x00000001)
		{
			break;
		}
	}

	*(volatile u32 *)((u32)DDR3C_BASE+0x070) = 0x00000000;
					/* CS0 MRS DRAM MPR end) */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A0) = 0x00000000;
					/* TDFI_RDLVL_DLL = 0x0 */
					/* TDFI_RDLVL_LOAD = 0x0 */
					/* TDFI_RDLVL_RESPLAT = 0x0 */
					/* TDFI_RDLVL_EN = 0x0 */
	*(volatile u32 *)((u32)DDR3C_BASE+0x1A8) = 0x00000000;
					/* TDFI_RDLVL_RESP = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x1A4) = 0x00000000;
					/* TDFI_RDLVL_RR = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0F4) = 0x00000000;
					/* RDLVL_CS = 0x0 */

	*(volatile u32 *)((u32)DDR3C_BASE+0x0D4) = 0x00000000;
					/* SW_LEVELING_MODE = 0x0 */
					/* SWLVL_START = 0x0 */

	vINT_STATUS = *((volatile unsigned long *)0xFFF4A0A0);
//	vUPDATE_ERROR_STATUS = *((volatile unsigned long *)0xFFF4A170);
	*(volatile u32 *)((u32)DDR3C_BASE+0x0A4) = vINT_STATUS;

	return 0;

}

