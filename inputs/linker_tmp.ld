/**
 ******************************************************************************
 * @file    linker.ld
 *
 * @brief   Linker script template.
 *
 * @author  inz. Radoslaw Dembek
 * @date    4 June 2018
 ******************************************************************************
 */

#define __MEM_REG(name,attr,adr,size)               name  (attr)    : org = adr, len = size

#define __MEM_REG__(x)                              __MEM_REG(x)

#define __REG_NAME(name,attr,adr,size)              name
#define __REG_START(name,attr,adr,size)             __##name##_start
#define __REG_SIZE(name,attr,adr,size)              __##name##_size
#define __REG_END(name,attr,adr,size)               __##name##_end

#define __REG_NAME__(x)                             __REG_NAME(x)
#define __REG_START__(x)                            __REG_START(x)
#define __REG_SIZE__(x)                             __REG_SIZE(x)
#define __REG_END__(x)                              __REG_END(x)

#define __MEM_REG_DEF__(x)                          __MEM_REG_DEF(x)

#define __SECT_NAME(name,lma,vma,type,keep,load)    name
#define __SECT_START(name,lma,vma,type,keep,load)   __##name##_start
#define __SECT_END(name,lma,vma,type,keep,load)     __##name##_end
#define __SECT_VMA(name,lma,vma,type,keep,load)     vma
#define __SECT_LMA(name,lma,vma,type,keep,load)     lma
#define __SECT_TYPE(name,lma,vma,type,keep,load)    _XX_##type
#define __SECT_KEEP(name,lma,vma,type,keep,load)    _XX_##keep
#define __SECT_LOAD(name,lma,vma,type,keep,load)    _XX_##load

#define __SECT_NAME__(x)                           __SECT_NAME(x)
#define __SECT_START__(x)                          __SECT_START(x)
#define __SECT_END__(x)                            __SECT_END(x)
#define __SECT_VMA__(x)                            __SECT_VMA(x)
#define __SECT_LMA__(x)                            __SECT_LMA(x)
#define __SECT_TYPE__(x)                           __SECT_TYPE(x)
#define __SECT_KEEP__(x)                           __SECT_KEEP(x)
#define __SECT_LOAD__(x)                           __SECT_LOAD(x)

#define _XX_                                       0
#define _XX_BSS                                    1
#define _XX_NOINIT                                 2
#define _XX_DATA                                   3
#define _XX_KEEP                                   5
#define _XX_NOLOAD                                 6

SEARCH_DIR(.);
ENTRY(Reset_Handler);

/******************************************************************************
 * format configurations
 *****************************************************************************/

OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm");
OUTPUT_ARCH(arm);

/******************************************************************************
 * stacks sizes
 *****************************************************************************/

/* Handler mode (core exceptions / interrupts) can use only main stack */
/* Thread mode can use main stack (default) or process stack - selected in CONTROL special register */

PROVIDE(__main_stack_size       = MAIN_STACK_SIZE);
PROVIDE(__process_stack_size    = PROCESS_STACK_SIZE);

/******************************************************************************
 * available memories definitions
 *****************************************************************************/

MEMORY
{
#ifdef REGION_0
    __MEM_REG__(REGION_0)
#endif
#ifdef REGION_1
    __MEM_REG__(REGION_1)
#endif
#ifdef REGION_2
    __MEM_REG__(REGION_2)
#endif
#ifdef REGION_3
    __MEM_REG__(REGION_3)
#endif
#ifdef REGION_4
    __MEM_REG__(REGION_4)
#endif
#ifdef REGION_5
    __MEM_REG__(REGION_5)
#endif
#ifdef REGION_6
    __MEM_REG__(REGION_6)
#endif
#ifdef REGION_7
    __MEM_REG__(REGION_7)
#endif
#ifdef REGION_8
    __MEM_REG__(REGION_8)
#endif
#ifdef REGION_9
    __MEM_REG__(REGION_9)
#endif
#ifdef REGION_10
    __MEM_REG__(REGION_10)
#endif
#ifdef REGION_11
    __MEM_REG__(REGION_11)
#endif
#ifdef REGION_12
    __MEM_REG__(REGION_12)
#endif
#ifdef REGION_13
    __MEM_REG__(REGION_13)
#endif
#ifdef REGION_14
    __MEM_REG__(REGION_14)
#endif
#ifdef REGION_15
    __MEM_REG__(REGION_15)
#endif
#ifdef REGION_16
    __MEM_REG__(REGION_16)
#endif
#ifdef REGION_17
    __MEM_REG__(REGION_17)
#endif
#ifdef REGION_18
    __MEM_REG__(REGION_18)
#endif
#ifdef REGION_19
    __MEM_REG__(REGION_19)
#endif
}

#ifdef REGION_0
__REG_START__(REGION_0)   = ORIGIN(__REG_NAME__(REGION_0));
__REG_SIZE__(REGION_0)    = LENGTH(__REG_NAME__(REGION_0));
__REG_END__(REGION_0)     = __REG_START__(REGION_0) + __REG_SIZE__(REGION_0);
#endif
#ifdef REGION_1
__REG_START__(REGION_1)   = ORIGIN(__REG_NAME__(REGION_1));
__REG_SIZE__(REGION_1)    = LENGTH(__REG_NAME__(REGION_1));
__REG_END__(REGION_1)     = __REG_START__(REGION_1) + __REG_SIZE__(REGION_1);
#endif
#ifdef REGION_2
__REG_START__(REGION_2)   = ORIGIN(__REG_NAME__(REGION_2));
__REG_SIZE__(REGION_2)    = LENGTH(__REG_NAME__(REGION_2));
__REG_END__(REGION_2)     = __REG_START__(REGION_2) + __REG_SIZE__(REGION_2);
#endif
#ifdef REGION_3
__REG_START__(REGION_3)   = ORIGIN(__REG_NAME__(REGION_3));
__REG_SIZE__(REGION_3)    = LENGTH(__REG_NAME__(REGION_3));
__REG_END__(REGION_3)     = __REG_START__(REGION_3) + __REG_SIZE__(REGION_3);
#endif
#ifdef REGION_4
__REG_START__(REGION_4)   = ORIGIN(__REG_NAME__(REGION_4));
__REG_SIZE__(REGION_4)    = LENGTH(__REG_NAME__(REGION_4));
__REG_END__(REGION_4)     = __REG_START__(REGION_4) + __REG_SIZE__(REGION_4);
#endif
#ifdef REGION_5
__REG_START__(REGION_5)   = ORIGIN(__REG_NAME__(REGION_5));
__REG_SIZE__(REGION_5)    = LENGTH(__REG_NAME__(REGION_5));
__REG_END__(REGION_5)     = __REG_START__(REGION_5) + __REG_SIZE__(REGION_5);
#endif
#ifdef REGION_6
__REG_START__(REGION_6)   = ORIGIN(__REG_NAME__(REGION_6));
__REG_SIZE__(REGION_6)    = LENGTH(__REG_NAME__(REGION_6));
__REG_END__(REGION_6)     = __REG_START__(REGION_6) + __REG_SIZE__(REGION_6);
#endif
#ifdef REGION_7
__REG_START__(REGION_7)   = ORIGIN(__REG_NAME__(REGION_7));
__REG_SIZE__(REGION_7)    = LENGTH(__REG_NAME__(REGION_7));
__REG_END__(REGION_7)     = __REG_START__(REGION_7) + __REG_SIZE__(REGION_7);
#endif
#ifdef REGION_8
__REG_START__(REGION_8)   = ORIGIN(__REG_NAME__(REGION_8));
__REG_SIZE__(REGION_8)    = LENGTH(__REG_NAME__(REGION_8));
__REG_END__(REGION_8)     = __REG_START__(REGION_8) + __REG_SIZE__(REGION_8);
#endif
#ifdef REGION_9
__REG_START__(REGION_9)   = ORIGIN(__REG_NAME__(REGION_9));
__REG_SIZE__(REGION_9)    = LENGTH(__REG_NAME__(REGION_9));
__REG_END__(REGION_9)     = __REG_START__(REGION_9) + __REG_SIZE__(REGION_9);
#endif
#ifdef REGION_10
__REG_START__(REGION_10)   = ORIGIN(__REG_NAME__(REGION_10));
__REG_SIZE__(REGION_10)    = LENGTH(__REG_NAME__(REGION_10));
__REG_END__(REGION_10)     = __REG_START__(REGION_10) + __REG_SIZE__(REGION_10);
#endif
#ifdef REGION_11
__REG_START__(REGION_11)   = ORIGIN(__REG_NAME__(REGION_11));
__REG_SIZE__(REGION_11)    = LENGTH(__REG_NAME__(REGION_11));
__REG_END__(REGION_11)     = __REG_START__(REGION_11) + __REG_SIZE__(REGION_11);
#endif
#ifdef REGION_12
__REG_START__(REGION_12)   = ORIGIN(__REG_NAME__(REGION_12));
__REG_SIZE__(REGION_12)    = LENGTH(__REG_NAME__(REGION_12));
__REG_END__(REGION_12)     = __REG_START__(REGION_12) + __REG_SIZE__(REGION_12);
#endif
#ifdef REGION_13
__REG_START__(REGION_13)   = ORIGIN(__REG_NAME__(REGION_13));
__REG_SIZE__(REGION_13)    = LENGTH(__REG_NAME__(REGION_13));
__REG_END__(REGION_13)     = __REG_START__(REGION_13) + __REG_SIZE__(REGION_13);
#endif
#ifdef REGION_14
__REG_START__(REGION_14)   = ORIGIN(__REG_NAME__(REGION_14));
__REG_SIZE__(REGION_14)    = LENGTH(__REG_NAME__(REGION_14));
__REG_END__(REGION_14)     = __REG_START__(REGION_14) + __REG_SIZE__(REGION_14);
#endif
#ifdef REGION_15
__REG_START__(REGION_15)   = ORIGIN(__REG_NAME__(REGION_15));
__REG_SIZE__(REGION_15)    = LENGTH(__REG_NAME__(REGION_15));
__REG_END__(REGION_15)     = __REG_START__(REGION_15) + __REG_SIZE__(REGION_15);
#endif
#ifdef REGION_16
__REG_START__(REGION_16)   = ORIGIN(__REG_NAME__(REGION_16));
__REG_SIZE__(REGION_16)    = LENGTH(__REG_NAME__(REGION_16));
__REG_END__(REGION_16)     = __REG_START__(REGION_16) + __REG_SIZE__(REGION_16);
#endif
#ifdef REGION_17
__REG_START__(REGION_17)   = ORIGIN(__REG_NAME__(REGION_17));
__REG_SIZE__(REGION_17)    = LENGTH(__REG_NAME__(REGION_17));
__REG_END__(REGION_17)     = __REG_START__(REGION_17) + __REG_SIZE__(REGION_17);
#endif
#ifdef REGION_18
__REG_START__(REGION_18)   = ORIGIN(__REG_NAME__(REGION_18));
__REG_SIZE__(REGION_18)    = LENGTH(__REG_NAME__(REGION_18));
__REG_END__(REGION_18)     = __REG_START__(REGION_18) + __REG_SIZE__(REGION_18);
#endif
#ifdef REGION_19
__REG_START__(REGION_19)   = ORIGIN(__REG_NAME__(REGION_19));
__REG_SIZE__(REGION_19)    = LENGTH(__REG_NAME__(REGION_19));
__REG_END__(REGION_19)     = __REG_START__(REGION_19) + __REG_SIZE__(REGION_19);
#endif

/******************************************************************************
 *  put data in sections
 *****************************************************************************/

SECTIONS
{
/******************************************************************************
 *  VECTORS SECTION
 *****************************************************************************/

    .vectors :
    {
        PROVIDE(__vectors_start = .);
        KEEP(*(.vectors));
        PROVIDE(__vectors_end = .);
    } > VECTORS_VMA_REGION AT > VECTORS_LMA_REGION

/******************************************************************************
 *  AFTER VECTORS SECTION
 *****************************************************************************/

    .after_vectors :
    {
        . = ALIGN(4);
        PROVIDE(__after_vectors_start = .);
        KEEP(*(.after_vectors));
        . = ALIGN(4);
        PROVIDE(__after_vectors_end = .);
    } > AFTERVECTORS_VMA_REGION AT > AFTERVECTORS_LMA_REGION

/******************************************************************************
 *  READONLY DATA SECTION
 *****************************************************************************/

    .rodata :
    {
        . = ALIGN(4);
        PROVIDE(__rodata_start = .);
        *(.rodata .rodata.* .gnu.linkonce.r.*);
        . = ALIGN(4);
        PROVIDE(__rodata_end = .);
    } > RODATA_VMA_REGION AT > RODATA_LMA_REGION

/******************************************************************************
 *  TEXT SECTION
 *****************************************************************************/

    .text :
    {
        . = ALIGN(4); 
        PROVIDE(__text_start = .);
        *(.text .text.* .gnu.linkonce.t.*);
        *(.glue_7t .glue_7);

        *(.ARM.extab* .gnu.linkonce.armextab.*);            /* exception unwinding information */
        *(.gcc_except_table);                               /* information used for stack unwinding during exception */
        *(.eh_frame_hdr);                                   /* additional information about .ex_frame section */
        *(.eh_frame);                                       /* information used for stack unwinding during exception */

/******************************************************************************
 *  DATA INITIALIZER BEGIN.
 *****************************************************************************/
        . = ALIGN(4);
        PROVIDE(__data_array_start = .);

#if VECTORS_VMA_REGION != VECTORS_LMA_REGION
    LONG(LOADADDR(.vectors));    LONG(ADDR(.vectors));    LONG(ADDR(.vectors)    + SIZEOF(.vectors));
#endif
    LONG(LOADADDR(.data));       LONG(ADDR(.data));       LONG(ADDR(.data)       + SIZEOF(.data));
#ifdef SECTION_0
#if __SECT_TYPE__(SECTION_0) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_0))); LONG(ADDR(.__SECT_NAME__(SECTION_0))); LONG(ADDR(.__SECT_NAME__(SECTION_0)) + SIZEOF(.__SECT_NAME__(SECTION_0)));
#endif
#endif
#ifdef SECTION_1
#if __SECT_TYPE__(SECTION_1) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_1))); LONG(ADDR(.__SECT_NAME__(SECTION_1))); LONG(ADDR(.__SECT_NAME__(SECTION_1)) + SIZEOF(.__SECT_NAME__(SECTION_1)));
#endif
#endif
#ifdef SECTION_2
#if __SECT_TYPE__(SECTION_2) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_2))); LONG(ADDR(.__SECT_NAME__(SECTION_2))); LONG(ADDR(.__SECT_NAME__(SECTION_2)) + SIZEOF(.__SECT_NAME__(SECTION_2)));
#endif
#endif
#ifdef SECTION_3
#if __SECT_TYPE__(SECTION_3) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_3))); LONG(ADDR(.__SECT_NAME__(SECTION_3))); LONG(ADDR(.__SECT_NAME__(SECTION_3)) + SIZEOF(.__SECT_NAME__(SECTION_3)));
#endif
#endif
#ifdef SECTION_4
#if __SECT_TYPE__(SECTION_4) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_4))); LONG(ADDR(.__SECT_NAME__(SECTION_4))); LONG(ADDR(.__SECT_NAME__(SECTION_4)) + SIZEOF(.__SECT_NAME__(SECTION_4)));
#endif
#endif
#ifdef SECTION_5
#if __SECT_TYPE__(SECTION_5) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_5))); LONG(ADDR(.__SECT_NAME__(SECTION_5))); LONG(ADDR(.__SECT_NAME__(SECTION_5)) + SIZEOF(.__SECT_NAME__(SECTION_5)));
#endif
#endif
#ifdef SECTION_6
#if __SECT_TYPE__(SECTION_6) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_6))); LONG(ADDR(.__SECT_NAME__(SECTION_6))); LONG(ADDR(.__SECT_NAME__(SECTION_6)) + SIZEOF(.__SECT_NAME__(SECTION_6)));
#endif
#endif
#ifdef SECTION_7
#if __SECT_TYPE__(SECTION_7) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_7))); LONG(ADDR(.__SECT_NAME__(SECTION_7))); LONG(ADDR(.__SECT_NAME__(SECTION_7)) + SIZEOF(.__SECT_NAME__(SECTION_7)));
#endif
#endif
#ifdef SECTION_8
#if __SECT_TYPE__(SECTION_8) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_8))); LONG(ADDR(.__SECT_NAME__(SECTION_8))); LONG(ADDR(.__SECT_NAME__(SECTION_8)) + SIZEOF(.__SECT_NAME__(SECTION_8)));
#endif
#endif
#ifdef SECTION_9
#if __SECT_TYPE__(SECTION_9) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_9))); LONG(ADDR(.__SECT_NAME__(SECTION_9))); LONG(ADDR(.__SECT_NAME__(SECTION_9)) + SIZEOF(.__SECT_NAME__(SECTION_9)));
#endif
#endif
#ifdef SECTION_10
#if __SECT_TYPE__(SECTION_10) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_10))); LONG(ADDR(.__SECT_NAME__(SECTION_10))); LONG(ADDR(.__SECT_NAME__(SECTION_10)) + SIZEOF(.__SECT_NAME__(SECTION_10)));
#endif
#endif
#ifdef SECTION_11
#if __SECT_TYPE__(SECTION_11) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_11))); LONG(ADDR(.__SECT_NAME__(SECTION_11))); LONG(ADDR(.__SECT_NAME__(SECTION_11)) + SIZEOF(.__SECT_NAME__(SECTION_11)));
#endif
#endif
#ifdef SECTION_12
#if __SECT_TYPE__(SECTION_12) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_12))); LONG(ADDR(.__SECT_NAME__(SECTION_12))); LONG(ADDR(.__SECT_NAME__(SECTION_12)) + SIZEOF(.__SECT_NAME__(SECTION_12)));
#endif
#endif
#ifdef SECTION_13
#if __SECT_TYPE__(SECTION_13) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_13))); LONG(ADDR(.__SECT_NAME__(SECTION_13))); LONG(ADDR(.__SECT_NAME__(SECTION_13)) + SIZEOF(.__SECT_NAME__(SECTION_13)));
#endif
#endif
#ifdef SECTION_14
#if __SECT_TYPE__(SECTION_14) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_14))); LONG(ADDR(.__SECT_NAME__(SECTION_14))); LONG(ADDR(.__SECT_NAME__(SECTION_14)) + SIZEOF(.__SECT_NAME__(SECTION_14)));
#endif
#endif
#ifdef SECTION_15
#if __SECT_TYPE__(SECTION_15) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_15))); LONG(ADDR(.__SECT_NAME__(SECTION_15))); LONG(ADDR(.__SECT_NAME__(SECTION_15)) + SIZEOF(.__SECT_NAME__(SECTION_15)));
#endif
#endif
#ifdef SECTION_16
#if __SECT_TYPE__(SECTION_16) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_16))); LONG(ADDR(.__SECT_NAME__(SECTION_16))); LONG(ADDR(.__SECT_NAME__(SECTION_16)) + SIZEOF(.__SECT_NAME__(SECTION_16)));
#endif
#endif
#ifdef SECTION_17
#if __SECT_TYPE__(SECTION_17) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_17))); LONG(ADDR(.__SECT_NAME__(SECTION_17))); LONG(ADDR(.__SECT_NAME__(SECTION_17)) + SIZEOF(.__SECT_NAME__(SECTION_17)));
#endif
#endif
#ifdef SECTION_18
#if __SECT_TYPE__(SECTION_18) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_18))); LONG(ADDR(.__SECT_NAME__(SECTION_18))); LONG(ADDR(.__SECT_NAME__(SECTION_18)) + SIZEOF(.__SECT_NAME__(SECTION_18)));
#endif
#endif
#ifdef SECTION_19
#if __SECT_TYPE__(SECTION_19) == _XX_DATA
    LONG(LOADADDR(.__SECT_NAME__(SECTION_19))); LONG(ADDR(.__SECT_NAME__(SECTION_19))); LONG(ADDR(.__SECT_NAME__(SECTION_19)) + SIZEOF(.__SECT_NAME__(SECTION_19)));
#endif
#endif
        . = ALIGN(4);
        PROVIDE(__data_array_end = .);
/******************************************************************************
 *  DATA INITIALIZER END.
 *****************************************************************************/
/******************************************************************************
 *  BSS INITIALIZER BEGIN.
 *****************************************************************************/
        PROVIDE(__bss_array_start = .);

    LONG(ADDR(.bss));       LONG(ADDR(.bss)       + SIZEOF(.bss));
#ifdef SECTION_0
#if __SECT_TYPE__(SECTION_0) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_0))); LONG(ADDR(.__SECT_NAME__(SECTION_0)) + SIZEOF(.__SECT_NAME__(SECTION_0)));
#endif
#endif
#ifdef SECTION_1
#if __SECT_TYPE__(SECTION_1) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_1))); LONG(ADDR(.__SECT_NAME__(SECTION_1)) + SIZEOF(.__SECT_NAME__(SECTION_1)));
#endif
#endif
#ifdef SECTION_2
#if __SECT_TYPE__(SECTION_2) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_2))); LONG(ADDR(.__SECT_NAME__(SECTION_2)) + SIZEOF(.__SECT_NAME__(SECTION_2)));
#endif
#endif
#ifdef SECTION_3
#if __SECT_TYPE__(SECTION_3) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_3))); LONG(ADDR(.__SECT_NAME__(SECTION_3)) + SIZEOF(.__SECT_NAME__(SECTION_3)));
#endif
#endif
#ifdef SECTION_4
#if __SECT_TYPE__(SECTION_4) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_4))); LONG(ADDR(.__SECT_NAME__(SECTION_4)) + SIZEOF(.__SECT_NAME__(SECTION_4)));
#endif
#endif
#ifdef SECTION_5
#if __SECT_TYPE__(SECTION_5) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_5))); LONG(ADDR(.__SECT_NAME__(SECTION_5)) + SIZEOF(.__SECT_NAME__(SECTION_5)));
#endif
#endif
#ifdef SECTION_6
#if __SECT_TYPE__(SECTION_6) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_6))); LONG(ADDR(.__SECT_NAME__(SECTION_6)) + SIZEOF(.__SECT_NAME__(SECTION_6)));
#endif
#endif
#ifdef SECTION_7
#if __SECT_TYPE__(SECTION_7) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_7))); LONG(ADDR(.__SECT_NAME__(SECTION_7)) + SIZEOF(.__SECT_NAME__(SECTION_7)));
#endif
#endif
#ifdef SECTION_8
#if __SECT_TYPE__(SECTION_8) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_8))); LONG(ADDR(.__SECT_NAME__(SECTION_8)) + SIZEOF(.__SECT_NAME__(SECTION_8)));
#endif
#endif
#ifdef SECTION_9
#if __SECT_TYPE__(SECTION_9) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_9))); LONG(ADDR(.__SECT_NAME__(SECTION_9)) + SIZEOF(.__SECT_NAME__(SECTION_9)));
#endif
#endif
#ifdef SECTION_10
#if __SECT_TYPE__(SECTION_10) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_10))); LONG(ADDR(.__SECT_NAME__(SECTION_10)) + SIZEOF(.__SECT_NAME__(SECTION_10)));
#endif
#endif
#ifdef SECTION_11
#if __SECT_TYPE__(SECTION_11) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_11))); LONG(ADDR(.__SECT_NAME__(SECTION_11)) + SIZEOF(.__SECT_NAME__(SECTION_11)));
#endif
#endif
#ifdef SECTION_12
#if __SECT_TYPE__(SECTION_12) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_12))); LONG(ADDR(.__SECT_NAME__(SECTION_12)) + SIZEOF(.__SECT_NAME__(SECTION_12)));
#endif
#endif
#ifdef SECTION_13
#if __SECT_TYPE__(SECTION_13) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_13))); LONG(ADDR(.__SECT_NAME__(SECTION_13)) + SIZEOF(.__SECT_NAME__(SECTION_13)));
#endif
#endif
#ifdef SECTION_14
#if __SECT_TYPE__(SECTION_14) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_14))); LONG(ADDR(.__SECT_NAME__(SECTION_14)) + SIZEOF(.__SECT_NAME__(SECTION_14)));
#endif
#endif
#ifdef SECTION_15
#if __SECT_TYPE__(SECTION_15) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_15))); LONG(ADDR(.__SECT_NAME__(SECTION_15)) + SIZEOF(.__SECT_NAME__(SECTION_15)));
#endif
#endif
#ifdef SECTION_16
#if __SECT_TYPE__(SECTION_16) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_16))); LONG(ADDR(.__SECT_NAME__(SECTION_16)) + SIZEOF(.__SECT_NAME__(SECTION_16)));
#endif
#endif
#ifdef SECTION_17
#if __SECT_TYPE__(SECTION_17) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_17))); LONG(ADDR(.__SECT_NAME__(SECTION_17)) + SIZEOF(.__SECT_NAME__(SECTION_17)));
#endif
#endif
#ifdef SECTION_18
#if __SECT_TYPE__(SECTION_18) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_18))); LONG(ADDR(.__SECT_NAME__(SECTION_18)) + SIZEOF(.__SECT_NAME__(SECTION_18)));
#endif
#endif
#ifdef SECTION_19
#if __SECT_TYPE__(SECTION_19) == _XX_BSS
    LONG(ADDR(.__SECT_NAME__(SECTION_19))); LONG(ADDR(.__SECT_NAME__(SECTION_19)) + SIZEOF(.__SECT_NAME__(SECTION_19)));
#endif
#endif
        . = ALIGN(4);
        PROVIDE(__bss_array_end = .);

/******************************************************************************
 *  BSS INITIALIZER END.
 *****************************************************************************/

        . = ALIGN(4);
        KEEP(*(.init));
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP(*(.preinit_array));
        . = ALIGN(4);
        __preinit_array_end = .;
        __init_array_start = .;
        KEEP(*(SORT(.init_array.*)));
        . = ALIGN(4);
        KEEP(*(.init_array));
        . = ALIGN(4);
        __init_array_end = .;
        KEEP(*(.fini));
        . = ALIGN(4);
        __fini_array_start = .;
        KEEP(*(.fini_array));
        . = ALIGN(4);
        KEEP(*(SORT(.fini_array.*)));
        . = ALIGN(4);
        __fini_array_end = .;

        . = ALIGN(4);
        PROVIDE(__text_end = .);
    } > TEXT_VMA_REGION AT > TEXT_LMA_REGION

/******************************************************************************
 *  DATA SECTION
 *****************************************************************************/

    .data :
    {
        . = ALIGN(4);
        PROVIDE(__data_start = .);
        *(.data .data.* .gnu.linkonce.d.*)
        . = ALIGN(4);
        PROVIDE(__data_end = .);
    } > DATA_VMA_REGION AT > DATA_LMA_REGION

/******************************************************************************
 *  BSS SECTION
 *****************************************************************************/

    .bss :
    {
        . = ALIGN(4);
        PROVIDE(__bss_start = .);
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON);
        . = ALIGN(4);
        PROVIDE(__bss_end = .);
    } > BSS_VMA_REGION AT > BSS_LMA_REGION

/******************************************************************************
 *  ARM.exidx SECTION
 *****************************************************************************/

    . = ALIGN(4);
    PROVIDE(__exidx_start = .);

    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*);
    } > TEXT_VMA_REGION AT > TEXT_LMA_REGION                             /* index entries for section unwinding */

    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
    
/******************************************************************************
 *
 *  USER SECTION BEGIN.
 *
 *****************************************************************************/

#ifdef SECTION_0
/******************************************************************************
 *  __SECT_NAME__(SECTION_0) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_0) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_0) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_0) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_0) = .);
#if __SECT_KEEP__(SECTION_0) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_0) .__SECT_NAME__(SECTION_0).*));
#else
        *(.__SECT_NAME__(SECTION_0) .__SECT_NAME__(SECTION_0).*);
#endif
        PROVIDE(__SECT_END__(SECTION_0) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_0) AT > __SECT_LMA__(SECTION_0)
#endif
#ifdef SECTION_1
/******************************************************************************
 *  __SECT_NAME__(SECTION_1) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_1) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_1) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_1) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_1) = .);
#if __SECT_KEEP__(SECTION_1) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_1) .__SECT_NAME__(SECTION_1).*));
#else
        *(.__SECT_NAME__(SECTION_1) .__SECT_NAME__(SECTION_1).*);
#endif
        PROVIDE(__SECT_END__(SECTION_1) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_1) AT > __SECT_LMA__(SECTION_1)
#endif
#ifdef SECTION_2
/******************************************************************************
 *  __SECT_NAME__(SECTION_2) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_2) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_2) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_2) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_2) = .);
#if __SECT_KEEP__(SECTION_2) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_2) .__SECT_NAME__(SECTION_2).*));
#else
        *(.__SECT_NAME__(SECTION_2) .__SECT_NAME__(SECTION_2).*);
#endif
        PROVIDE(__SECT_END__(SECTION_2) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_2) AT > __SECT_LMA__(SECTION_2)
#endif
#ifdef SECTION_3
/******************************************************************************
 *  __SECT_NAME__(SECTION_3) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_3) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_3) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_3) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_3) = .);
#if __SECT_KEEP__(SECTION_3) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_3) .__SECT_NAME__(SECTION_3).*));
#else
        *(.__SECT_NAME__(SECTION_3) .__SECT_NAME__(SECTION_3).*);
#endif
        PROVIDE(__SECT_END__(SECTION_3) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_3) AT > __SECT_LMA__(SECTION_3)
#endif
#ifdef SECTION_4
/******************************************************************************
 *  __SECT_NAME__(SECTION_4) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_4) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_4) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_4) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_4) = .);
#if __SECT_KEEP__(SECTION_4) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_4) .__SECT_NAME__(SECTION_4).*));
#else
        *(.__SECT_NAME__(SECTION_4) .__SECT_NAME__(SECTION_4).*);
#endif
        PROVIDE(__SECT_END__(SECTION_4) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_4) AT > __SECT_LMA__(SECTION_4)
#endif
#ifdef SECTION_5
/******************************************************************************
 *  __SECT_NAME__(SECTION_5) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_5) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_5) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_5) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_5) = .);
#if __SECT_KEEP__(SECTION_5) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_5) .__SECT_NAME__(SECTION_5).*));
#else
        *(.__SECT_NAME__(SECTION_5) .__SECT_NAME__(SECTION_5).*);
#endif
        PROVIDE(__SECT_END__(SECTION_5) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_5) AT > __SECT_LMA__(SECTION_5)
#endif
#ifdef SECTION_6
/******************************************************************************
 *  __SECT_NAME__(SECTION_6) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_6) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_6) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_6) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_6) = .);
#if __SECT_KEEP__(SECTION_6) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_6) .__SECT_NAME__(SECTION_6).*));
#else
        *(.__SECT_NAME__(SECTION_6) .__SECT_NAME__(SECTION_6).*);
#endif
        PROVIDE(__SECT_END__(SECTION_6) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_6) AT > __SECT_LMA__(SECTION_6)
#endif
#ifdef SECTION_7
/******************************************************************************
 *  __SECT_NAME__(SECTION_7) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_7) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_7) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_7) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_7) = .);
#if __SECT_KEEP__(SECTION_7) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_7) .__SECT_NAME__(SECTION_7).*));
#else
        *(.__SECT_NAME__(SECTION_7) .__SECT_NAME__(SECTION_7).*);
#endif
        PROVIDE(__SECT_END__(SECTION_7) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_7) AT > __SECT_LMA__(SECTION_7)
#endif
#ifdef SECTION_8
/******************************************************************************
 *  __SECT_NAME__(SECTION_8) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_8) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_8) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_8) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_8) = .);
#if __SECT_KEEP__(SECTION_8) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_8) .__SECT_NAME__(SECTION_8).*));
#else
        *(.__SECT_NAME__(SECTION_8) .__SECT_NAME__(SECTION_8).*);
#endif
        PROVIDE(__SECT_END__(SECTION_8) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_8) AT > __SECT_LMA__(SECTION_8)
#endif
#ifdef SECTION_9
/******************************************************************************
 *  __SECT_NAME__(SECTION_9) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_9) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_9) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_9) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_9) = .);
#if __SECT_KEEP__(SECTION_9) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_9) .__SECT_NAME__(SECTION_9).*));
#else
        *(.__SECT_NAME__(SECTION_9) .__SECT_NAME__(SECTION_9).*);
#endif
        PROVIDE(__SECT_END__(SECTION_9) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_9) AT > __SECT_LMA__(SECTION_9)
#endif
#ifdef SECTION_10
/******************************************************************************
 *  __SECT_NAME__(SECTION_10) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_10) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_10) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_10) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_10) = .);
#if __SECT_KEEP__(SECTION_10) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_10) .__SECT_NAME__(SECTION_10).*));
#else
        *(.__SECT_NAME__(SECTION_10) .__SECT_NAME__(SECTION_10).*);
#endif
        PROVIDE(__SECT_END__(SECTION_10) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_10) AT > __SECT_LMA__(SECTION_10)
#endif
#ifdef SECTION_11
/******************************************************************************
 *  __SECT_NAME__(SECTION_11) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_11) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_11) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_11) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_11) = .);
#if __SECT_KEEP__(SECTION_11) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_11) .__SECT_NAME__(SECTION_11).*));
#else
        *(.__SECT_NAME__(SECTION_11) .__SECT_NAME__(SECTION_11).*);
#endif
        PROVIDE(__SECT_END__(SECTION_11) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_11) AT > __SECT_LMA__(SECTION_11)
#endif
#ifdef SECTION_12
/******************************************************************************
 *  __SECT_NAME__(SECTION_12) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_12) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_12) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_12) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_12) = .);
#if __SECT_KEEP__(SECTION_12) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_12) .__SECT_NAME__(SECTION_12).*));
#else
        *(.__SECT_NAME__(SECTION_12) .__SECT_NAME__(SECTION_12).*);
#endif
        PROVIDE(__SECT_END__(SECTION_12) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_12) AT > __SECT_LMA__(SECTION_12)
#endif
#ifdef SECTION_13
/******************************************************************************
 *  __SECT_NAME__(SECTION_13) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_13) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_13) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_13) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_13) = .);
#if __SECT_KEEP__(SECTION_13) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_13) .__SECT_NAME__(SECTION_13).*));
#else
        *(.__SECT_NAME__(SECTION_13) .__SECT_NAME__(SECTION_13).*);
#endif
        PROVIDE(__SECT_END__(SECTION_13) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_13) AT > __SECT_LMA__(SECTION_13)
#endif
#ifdef SECTION_14
/******************************************************************************
 *  __SECT_NAME__(SECTION_14) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_14) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_14) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_14) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_14) = .);
#if __SECT_KEEP__(SECTION_14) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_14) .__SECT_NAME__(SECTION_14).*));
#else
        *(.__SECT_NAME__(SECTION_14) .__SECT_NAME__(SECTION_14).*);
#endif
        PROVIDE(__SECT_END__(SECTION_14) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_14) AT > __SECT_LMA__(SECTION_14)
#endif
#ifdef SECTION_15
/******************************************************************************
 *  __SECT_NAME__(SECTION_15) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_15) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_15) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_15) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_15) = .);
#if __SECT_KEEP__(SECTION_15) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_15) .__SECT_NAME__(SECTION_15).*));
#else
        *(.__SECT_NAME__(SECTION_15) .__SECT_NAME__(SECTION_15).*);
#endif
        PROVIDE(__SECT_END__(SECTION_15) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_15) AT > __SECT_LMA__(SECTION_15)
#endif
#ifdef SECTION_16
/******************************************************************************
 *  __SECT_NAME__(SECTION_16) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_16) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_16) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_16) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_16) = .);
#if __SECT_KEEP__(SECTION_16) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_16) .__SECT_NAME__(SECTION_16).*));
#else
        *(.__SECT_NAME__(SECTION_16) .__SECT_NAME__(SECTION_16).*);
#endif
        PROVIDE(__SECT_END__(SECTION_16) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_16) AT > __SECT_LMA__(SECTION_16)
#endif
#ifdef SECTION_17
/******************************************************************************
 *  __SECT_NAME__(SECTION_17) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_17) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_17) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_17) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_17) = .);
#if __SECT_KEEP__(SECTION_17) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_17) .__SECT_NAME__(SECTION_17).*));
#else
        *(.__SECT_NAME__(SECTION_17) .__SECT_NAME__(SECTION_17).*);
#endif
        PROVIDE(__SECT_END__(SECTION_17) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_17) AT > __SECT_LMA__(SECTION_17)
#endif
#ifdef SECTION_18
/******************************************************************************
 *  __SECT_NAME__(SECTION_18) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_18) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_18) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_18) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_18) = .);
#if __SECT_KEEP__(SECTION_18) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_18) .__SECT_NAME__(SECTION_18).*));
#else
        *(.__SECT_NAME__(SECTION_18) .__SECT_NAME__(SECTION_18).*);
#endif
        PROVIDE(__SECT_END__(SECTION_18) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_18) AT > __SECT_LMA__(SECTION_18)
#endif
#ifdef SECTION_19
/******************************************************************************
 *  __SECT_NAME__(SECTION_19) definition.
 *****************************************************************************/
#if __SECT_LOAD__(SECTION_19) == _XX_NOLOAD
    .__SECT_NAME__(SECTION_19) (NOLOAD) :
#else
    .__SECT_NAME__(SECTION_19) :
#endif
    {
        . = ALIGN(4);
        PROVIDE(__SECT_START__(SECTION_19) = .);
#if __SECT_KEEP__(SECTION_19) == _XX_KEEP
        KEEP(*(.__SECT_NAME__(SECTION_19) .__SECT_NAME__(SECTION_19).*));
#else
        *(.__SECT_NAME__(SECTION_19) .__SECT_NAME__(SECTION_19).*);
#endif
        PROVIDE(__SECT_END__(SECTION_19) = .);
        . = ALIGN(4);
    } > __SECT_VMA__(SECTION_19) AT > __SECT_LMA__(SECTION_19)
#endif

/******************************************************************************
 *
 *  USER SECTION END.
 *
 *****************************************************************************/

/******************************************************************************
 *  STACK
 *****************************************************************************/

    .stack :
    {
        . = ALIGN(8);
        PROVIDE(__stack_start = .);
        PROVIDE(__main_stack_start = .);

        . += __main_stack_size;

        . = ALIGN(8);
        PROVIDE(__main_stack_end   = .);

        PROVIDE(__process_stack_start = .);

        . += __process_stack_size;

        . = ALIGN(8);
        PROVIDE(__process_stack_end = .);
        PROVIDE(__stack_end = .);
    } > STACK_REGION AT > STACK_REGION

/******************************************************************************
 *  HEAP
 *****************************************************************************/

    .heap :
    {
        . = ALIGN(4);
        PROVIDE(__heap_start = .);
        . = ALIGN(4);
        __heap_end = ORIGIN(HEAP_REGION) + LENGTH(HEAP_REGION);
        PROVIDE(__heap_end = __heap_end);
    } > HEAP_REGION AT > HEAP_REGION

/******************************************************************************
 *
 *****************************************************************************/

    .stab                       0 (NOLOAD) : { *(.stab) }
    .stabstr                    0 (NOLOAD) : { *(.stabstr) }
    /* DWARF debug sections.
    * Symbols in the DWARF debugging sections are relative to the beginning
    * of the section so we begin them at 0. */
    /* DWARF 1 */
    .debug                      0 : { *(.debug) }
    .line                       0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo              0 : { *(.debug_srcinfo) }
    .debug_sfnames              0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges              0 : { *(.debug_aranges) }
    .debug_pubnames             0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info                 0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev               0 : { *(.debug_abbrev) }
    .debug_line                 0 : { *(.debug_line) }
    .debug_frame                0 : { *(.debug_frame) }
    .debug_str                  0 : { *(.debug_str) }
    .debug_loc                  0 : { *(.debug_loc) }
    .debug_macinfo              0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames            0 : { *(.debug_weaknames) }
    .debug_funcnames            0 : { *(.debug_funcnames) }
    .debug_typenames            0 : { *(.debug_typenames) }
    .debug_varnames             0 : { *(.debug_varnames) }

    .note.gnu.arm.ident         0 : { KEEP(*(.note.gnu.arm.ident)) }
    .ARM.attributes             0 : { KEEP(*(.ARM.attributes)) }
    /DISCARD/                     : { *(.note.GNU-stack) }
}
