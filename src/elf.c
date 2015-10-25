/*
 ============================================================================
    Name        : elf.c
    Description : ELF-format-analyzation
 ============================================================================
*/

#include "defines.h"
#include "elf.h"
#include "lib.h"

/*** ELF header ***/
struct elf_header {
    /* 16-byte identification data */
    struct {
        unsigned char magic[4];     /* magic number */
        unsigned char class;        /* 32/64bit */
        unsigned char format;       /* endian */
        unsigned char version;      /* ELF format version */
        unsigned char abi;          /* OS type */
        unsigned char abi_version;  /* OS version */
        unsigned char reserve[7];   /* reserved */
    } id;
    short type;                 /* file type */
    short arch;                 /* CPU type */
    long version;               /* ELF format version */
    long entry_point;           /* address of entry point */
    long program_header_offset; /* address of program-header-table */
    long section_header_offset; /* address of section-header-table */
    long flags;                 /* flags */
    short header_size;          /* size of ELF header */
    short program_header_size;  /* size of program-header */
    short program_header_num;   /* number of program-header */
    short section_header_size;  /* size of section-header */
    short section_header_num;   /* number of section-header */
    short section_name_index;   /* section with section-name */
};

/*** program header ***/
struct elf_program_header {
    long type;          /* segment type */
    long offset;        /* pointer in file */
    long virtual_addr;  /* VA */
    long physical_addr; /* PA */
    long file_size;     /* size if file */
    long memory_size;   /* size of memory */
    long flags;         /* flags */
    long align;         /* alignment */
};

/*** check ELF header ***/
static int elf_check(struct elf_header *header)
{
    /* check magic number */
    if (memcmp(header->id.magic, "\x7f" "ELF", 4)) {
        return -1;
    }
    /* check each of parameters */
    if (header->id.class != 1) { /* ELF32 */
        return -1;
    }
    if (header->id.format != 2) { /* big endian */
        return -1;
    }
    if (header->id.version != 1) { /* version 1 */
        return -1;
    }
    if (header->type != 2) { /* executable file */
        return -1;
    }
    if (header->version != 1) { /* version 1 */
        return -1;
    }

    /* Hitachi H8/300 or H8/300H */
    if ((header->arch != 46) && (header->arch != 47)) {
        return -1;
    }

    return 0;
}

/*** load segments */
static int elf_load_program(struct elf_header *header)
{
    int i;
    struct elf_program_header *phdr;

    for (i = 0; i < header->program_header_num; i++) {
        phdr = (struct elf_program_header *)(
                    (char *)header
                    + header->program_header_offset
                    + header->program_header_size * i
                );
        /* is a segment enable to load */
        if (phdr->type != 1) {
            continue;
        }

        /* display some segment infomation */
        putxval(phdr->offset,        6); puts(" ");
        putxval(phdr->virtual_addr,  8); puts(" ");
        putxval(phdr->physical_addr, 8); puts(" ");
        putxval(phdr->file_size,     5); puts(" ");
        putxval(phdr->memory_size,   5); puts(" ");
        putxval(phdr->flags,         2); puts(" ");
        putxval(phdr->align,         2); puts("\n");
    }

    return 0;
}

/*** analyze ELF-format ***/
int elf_load(char *buf)
{
    struct elf_header *header = (struct elf_header *)buf;

    /* check ELF header */
    if (elf_check(header) < 0) {
        return -1;
    }

    /* load segments */
    if (elf_load_program(header) < 0) {
        return -1;
    }

    return 0;
}

