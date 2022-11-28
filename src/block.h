
enum boot_source {
#if defined(CONFIG_F_SDH30_SDHCI)
	BS_SD,
#endif
#if defined(F_EMMC_BASE)
	BS_EMMC,
#endif
#if defined(CONFIG_ROMFS_POSSIBLE_ADDRESSES)
	BS_MEM,
#endif
	BS_COUNT
};

enum filesystem_types {
#if defined(CONFIG_FS_VFAT)
	FS_FAT,
#endif
#if defined(CONFIG_FS_EXT2)
	FS_EXT2,
#endif
#if defined(CONFIG_ROMFS_POSSIBLE_ADDRESSES)
	FS_ROMFS,
#endif
	FS_COUNT,
};

extern unsigned int partition_offset_blocks, partition_length_blocks;                  
extern unsigned long (*bread)(ulong start, unsigned int blkcnt, void *dst);
extern int (*filesystem_read)(const char *filename, void *buffer, unsigned long maxsize);
extern int parse_partition(int partition_index);
extern int romfs_mount(const void *_romfs);
extern int partition_read_table(void);
extern void *romfs_filesystem_get_ads(const char *filepath, int *len);

