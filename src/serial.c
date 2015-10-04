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
    volatile uint8 smr;     /* serial mode register */
    volatile uint8 brr;     /* bit rate register */ 
    volatile uint8 scr;     /* serial control register */
    volatile uint8 tdr;     /* transmit data register */
    volatile uint8 ssr;     /* serial status register */
    volatile uint8 rdr;     /* receive data register */
    volatile uint8 scmr;    /* smart card mode register */
};

/* each bit of SMR */
#define H8_3069F_SCI_SMR_CKS_PER1   (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4   (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16  (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64  (3 << 0)
#define H8_3069F_SCI_SMR_MP         (1 << 2)
#define H8_3069F_SCI_SMR_STOP       (1 << 3)
#define H8_3069F_SCI_SMR_OE         (1 << 4)
#define H8_3069F_SCI_SMR_PE         (1 << 5)
#define H8_3069F_SCI_SMR_CHR        (1 << 6)
#define H8_3069F_SCI_SMR_CA         (1 << 7)

/* each bit of SCR */
#define H8_3069F_SCI_SCR_CKE0       (1 << 0)
#define H8_3069F_SCI_SCR_CKE1       (1 << 1)
#define H8_3069F_SCI_SCR_TEIE       (1 << 2)
#define H8_3069F_SCI_SCR_MPIE       (1 << 3)
#define H8_3069F_SCI_SCR_RE         (1 << 4)
#define H8_3069F_SCI_SCR_TE         (1 << 5)
#define H8_3069F_SCI_SCR_RIE        (1 << 6)
#define H8_3069F_SCI_SCR_TIE        (1 << 7)

/* each bit of SSR */
#define H8_3069F_SCI_SSR_MPBT       (1 << 0)
#define H8_3069F_SCI_SSR_MPB        (1 << 1)
#define H8_3069F_SCI_SSR_TEND       (1 << 2)
#define H8_3069F_SCI_SSR_PER        (1 << 3)
#define H8_3069F_SCI_SSR_FERERS     (1 << 4)
#define H8_3069F_SCI_SSR_ORER       (1 << 5)
#define H8_3069F_SCI_SSR_RDRF       (1 << 6)
#define H8_3069F_SCI_SSR_TDRE       (1 << 7)

/* SCI table */
static struct {
    volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
    { H8_3069F_SCI0 }, 
    { H8_3069F_SCI1 }, 
    { H8_3069F_SCI2 }, 
};

/* init serial device */
int serial_init(int index)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    sci->scr = 0;
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
    return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

/* send single character */
int serial_send_byte(int index, unsigned char c)
{
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    /* wait until serial device can send */
    while (!serial_is_send_enable(index))
        ;
    sci->tdr = c;
    sci->ssr &= ~H8_3069F_SCI_SSR_TDRE; /* transmission start */

    return 0;
}

