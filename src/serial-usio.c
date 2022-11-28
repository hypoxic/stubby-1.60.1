#include "asm/utils.h"
#include "io.h"
#include "serial.h"

#if defined(CONFIG_UARTOFF)

void uart_init(void)
{
}

void _putc(char c)
{
}

int _getc(void)
{
	return -1;
}

#else // CONFIG_UARTOFF

void uart_init(void)
{
#ifdef CONFIG_MLB01
	switch(CONFIG_SYS_USIO_CH) {
	case 0://UART ch 0
		writel(0x00000008|readl(IO_EPCR_PE), IO_EPCR_PE);//PE2,3
		break;
	case 1://UART ch 1
	    writel(0x00000020|readl(IO_EPCR_PE), IO_EPCR_PE);//PE4,5
		break;
	case 2://UART ch 2
	    writel(0x00000002|readl(IO_EPCR_PE), IO_EPCR_PE);//PE0,PE1
		break;
	case 3://UART ch 3
		writel(0x00000800|readl(IO_PERSEL3), IO_PERSEL3);//PERSEL3 - PRT1SOU3
		writel(0x00000002|readl(IO_EPCR_PY), IO_EPCR_PY);//PY1,PY2
		break;
	}
#endif
    writew(0x363, CONFIG_SYS_USIO + 0x06);//BGR 115200
    writew(0, CONFIG_SYS_USIO + 0x0C);//FCR
    writeb(0, CONFIG_SYS_USIO + 0x00);//SMR
    writeb(0, CONFIG_SYS_USIO + 0x02);//ESCR
    writeb(0x80, CONFIG_SYS_USIO + 0x03);//SSR
    writeb(3, CONFIG_SYS_USIO + 0x01);//SCR
    writeb(1, CONFIG_SYS_USIO + 0x00);//SMR:SOE->1 mean set SOUT
}

void _putc(char c)
{
        while (!(readb(CONFIG_SYS_USIO + 3) & 2))
                ;
        writew(c & 0xff, CONFIG_SYS_USIO + 4);
}

int _getc(void)
{
	if (readb(CONFIG_SYS_USIO + 3) & 0x4)
		return readb(CONFIG_SYS_USIO + 4);

	return -1;
}

#endif // CONFIG_UARTOFF
