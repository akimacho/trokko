/*
 ============================================================================
    Name        : serial.c
    Description : serial device driver
 ============================================================================
*/

#include "defines.h"
#include "serial.h"

/* number of serial communication interface */
#define SERIAL_SCI_NUM 3

/* serial communication interface */
#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

/* registers of SCI */
struct h8_3069f_sci {
    volatile uint8 smr;     /* serial mode register to setup mode of serial communication*/
    volatile uint8 brr;     /* bit rate register to setup baudrate*/ 
    volatile uint8 scr;     /* serial control register: whether the transmission and reception are enabled */
    volatile uint8 tdr;     /* transmit data register to write a single character */
    volatile uint8 ssr;     /* serial status register : reception completion and transmission completion */
    volatile uint8 rdr;     /* receive data register to receive a single character*/
    volatile uint8 scmr;    /* smart card mode register */
};

/*** each bit of SMR:Serial Mode Register ***/
/*
 * setting of serial-communication-format and boud-rate-generater's clock-source 
 */
#define H8_3069F_SCI_SMR_CKS_PER1   (0 << 0) /* x[clock] */
#define H8_3069F_SCI_SMR_CKS_PER4   (1 << 0) /* x[clock] / 4 */
#define H8_3069F_SCI_SMR_CKS_PER16  (2 << 0) /* x[clock] / 16 */
#define H8_3069F_SCI_SMR_CKS_PER64  (3 << 0) /* x[clock] / 64 */
#define H8_3069F_SCI_SMR_MP         (1 << 2) /* Multi Processor */
#define H8_3069F_SCI_SMR_STOP       (1 << 3) /* STOP bit length */
#define H8_3069F_SCI_SMR_OE         (1 << 4) /* parity mode */
#define H8_3069F_SCI_SMR_PE         (1 << 5) /* Parity Enable */
#define H8_3069F_SCI_SMR_CHR        (1 << 6) /* CHaracteR length */
#define H8_3069F_SCI_SMR_CA         (1 << 7) /* Communication mode */

/*** each bit of SCR:Serial Mode Register ***/
/*
 * sending and receiving of SCI and serial-clock-output,
 * interruption request, sending/receiving-clock-source
 */
#define H8_3069F_SCI_SCR_CKE0       (1 << 0) /* ClocK Enable 0 */
#define H8_3069F_SCI_SCR_CKE1       (1 << 1) /* ClocK Enable 1 */
#define H8_3069F_SCI_SCR_TEIE       (1 << 2) /* Transmit End Interrupt Enable */
#define H8_3069F_SCI_SCR_MPIE       (1 << 3) /* Multi Processor Interrupt Enable */
#define H8_3069F_SCI_SCR_RE         (1 << 4) /* Receive Enable */
#define H8_3069F_SCI_SCR_TE         (1 << 5) /* Transmit Enable */
#define H8_3069F_SCI_SCR_RIE        (1 << 6) /* Receive Interrupt Enable */
#define H8_3069F_SCI_SCR_TIE        (1 << 7) /* Transmit Interactive Enable */

/*** each bit of SSR:Serial Status Register ***/
/*
 * status flag with the operation status of SCI and multi-processor-bit
 */
#define H8_3069F_SCI_SSR_MPBT       (1 << 0) /* Multi Proccesor Bit Transfer */
#define H8_3069F_SCI_SSR_MPB        (1 << 1) /* Multi Processor Bit */
#define H8_3069F_SCI_SSR_TEND       (1 << 2) /* Transmit END */
#define H8_3069F_SCI_SSR_PER        (1 << 3) /* Pariy ErroR */
#define H8_3069F_SCI_SSR_FERERS     (1 << 4) /* Framing ErroR/ErroR signals Status */
#define H8_3069F_SCI_SSR_ORER       (1 << 5) /* Over Run ErroR */
#define H8_3069F_SCI_SSR_RDRF       (1 << 6) /* Receive Data Register Full */
#define H8_3069F_SCI_SSR_TDRE       (1 << 7) /* Transmitt Data Register Empty */

/* SCI table */
static struct {
    volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
    { H8_3069F_SCI0 },
    { H8_3069F_SCI1 }, /* for serial communication */
    { H8_3069F_SCI2 }, 
};

/* init serial device */
int serial_init(int index)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    sci->scr = 0; /* invalidate the serial control register */
    /*
     * baud rate             : 9600bps
     * data length           : 8bit
     * stop bit length       : 1bit
     * non-parity
     * hardware flow control : off
     * software flow control : off
     */
    sci->smr = 0;
    sci->brr = 64;  /* generate a 9600bps from 20MHz clock */
    sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE; /* ready to send and receive */
    sci->ssr = 0;

    return 0;
}

/* check whether it is possible to send a message */
int serial_is_send_enable(int index)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    /* examine whether it is possible to write data */
    return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

/* send single character */
int serial_send_byte(int index, unsigned char c)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    /* wait until serial device can send */
    while (!serial_is_send_enable(index)) {
        ;
    }

    sci->tdr = c; /* write a single charactor */
    sci->ssr = sci->ssr & ~H8_3069F_SCI_SSR_TDRE; /* transmission start */

    return 0;
}

/* check whether it is possible to receive a message */
int serial_is_recv_enable(int index)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    /* examines whether there is data received by serial communication */
    return (sci->ssr & H8_3069F_SCI_SSR_RDRF);
}

/* receive a single character */
unsigned char serial_recv_byte(int index)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    unsigned char c;

    /* wait until a character is transmitted */
    while (!serial_is_recv_enable(index)) {
        ;
    }
    c = sci->rdr;
    sci->ssr = sci->ssr & ~H8_3069F_SCI_SSR_RDRF; /* reception complete */

    return c;
}

