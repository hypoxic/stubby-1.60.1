#ifdef MB86S70_MHU_PHYS
#include "mhu.h"
#include "scb_mhu_api.h"

int fdt_set_memory_from_mhu(void *dtb);
void mhu_show_version(void);
#else
static inline int fdt_set_memory_from_mhu(void *dtb) { return 0; }
static inline void mhu_show_version(void) { }
#endif

int update_dtb(char *dtb, enum boot_source device, int partition,
	       enum filesystem_types rootfstype);
void *fdt_find_path(void *start, const char *path, int *len);
void fdt_set_prop_size(void *start, void *_prop, int new_size);

#if defined(CONFIG_FILEPATH_DTB_CONFIG)
void process_dtb_config(void *dtb, char *dtb_config, int dtb_config_len);
#else
static inline void process_dtb_config(void *dtb) { do { } while(0); }
#endif

#if defined(CONFIG_MB86S7X)
void mb86s7x_hsspi_init(void);
#else
static inline void mb86s7x_hsspi_init(void) { do { } while(0); }
#endif

extern int is_secondary_stubby;
extern int load_from_filesystem(enum boot_source device, int part, enum filesystem_types rootfstype);
