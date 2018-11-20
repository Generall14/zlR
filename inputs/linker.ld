/**
 ******************************************************************************
 * @file    memory_cfg.h
 *
 * @brief   Memory configuration.
 *
 * Memory configuration
 *
 * @author  inz. Radoslaw Dembek
 * @date    4 June 2018
 ******************************************************************************
 */
/**********************************************************************************************************
 * MEMORY REGIONS DEFINITION
 *
 * Max number of regions 20 <0..19>
 *
 **********************************************************************************************************/
/**********************************************************************************************************
 * USER SECTIONS DEFINITION
 *
 * Max number of sections 20 <0...19>
 *
 *
 * Possible parameters:
 * NAME         - unique name of section
 * LMA_ADDR     - defined region name
 * VMA_ADDR     - defined region name
 * TYPE         - DATA, BSS, NOINIT
 *                DATA - like data section, BSS - like bss section, NOINIT - not initialized data
 * KEEP         - KEEP or empty
 * NOLOAD       - NOLOAD or empty
 *
 *                          NAME            LMA_ADDR    VMA_ADDR        TYPE        KEEP    NOLOAD
 **********************************************************************************************************/
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
PROVIDE(__main_stack_size = 1024);
PROVIDE(__process_stack_size = 1024);
/******************************************************************************
 * available memories definitions
 *****************************************************************************/
MEMORY
{
    ROM (RX) : org = 0x08000000, len = 2M
    RAM (RWX) : org = 0x20000000, len = 112k
    RAM1 (RWX) : org = 0x2001C000, len = 16k
    RAM2 (RWX) : org = 0x20020000, len = 64k
    CCM_RAM (RWX) : org = 0x10000000, len = 64k
    BKP_RAM (RW) : org = 0x40024000, len = 4k
    SRAM (RWX) : org = 0x68000000, len = 256k
    NOR (RWX) : org = 0x64000000, len = 16M
}
__ROM_start = ORIGIN(ROM);
__ROM_size = LENGTH(ROM);
__ROM_end = __ROM_start + __ROM_size;
__RAM_start = ORIGIN(RAM);
__RAM_size = LENGTH(RAM);
__RAM_end = __RAM_start + __RAM_size;
__RAM1_start = ORIGIN(RAM1);
__RAM1_size = LENGTH(RAM1);
__RAM1_end = __RAM1_start + __RAM1_size;
__RAM2_start = ORIGIN(RAM2);
__RAM2_size = LENGTH(RAM2);
__RAM2_end = __RAM2_start + __RAM2_size;
__CCM_RAM_start = ORIGIN(CCM_RAM);
__CCM_RAM_size = LENGTH(CCM_RAM);
__CCM_RAM_end = __CCM_RAM_start + __CCM_RAM_size;
__BKP_RAM_start = ORIGIN(BKP_RAM);
__BKP_RAM_size = LENGTH(BKP_RAM);
__BKP_RAM_end = __BKP_RAM_start + __BKP_RAM_size;
__SRAM_start = ORIGIN(SRAM);
__SRAM_size = LENGTH(SRAM);
__SRAM_end = __SRAM_start + __SRAM_size;
__NOR_start = ORIGIN(NOR);
__NOR_size = LENGTH(NOR);
__NOR_end = __NOR_start + __NOR_size;
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
    } > ROM AT > ROM
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
    } > ROM AT > ROM
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
    } > ROM AT > ROM
/******************************************************************************
 *  TEXT SECTION
 *****************************************************************************/
    .text :
    {
        . = ALIGN(4);
        PROVIDE(__text_start = .);
        *(.text .text.* .gnu.linkonce.t.*);
        *(.glue_7t .glue_7);
        *(.ARM.extab* .gnu.linkonce.armextab.*); /* exception unwinding information */
        *(.gcc_except_table); /* information used for stack unwinding during exception */
        *(.eh_frame_hdr); /* additional information about .ex_frame section */
        *(.eh_frame); /* information used for stack unwinding during exception */
/******************************************************************************
 *  DATA INITIALIZER BEGIN.
 *****************************************************************************/
        . = ALIGN(4);
        PROVIDE(__data_array_start = .);
    LONG(LOADADDR(.data)); LONG(ADDR(.data)); LONG(ADDR(.data) + SIZEOF(.data));
    LONG(LOADADDR(.FUNC_RAM)); LONG(ADDR(.FUNC_RAM)); LONG(ADDR(.FUNC_RAM) + SIZEOF(.FUNC_RAM));
        . = ALIGN(4);
        PROVIDE(__data_array_end = .);
/******************************************************************************
 *  DATA INITIALIZER END.
 *****************************************************************************/
/******************************************************************************
 *  BSS INITIALIZER BEGIN.
 *****************************************************************************/
        PROVIDE(__bss_array_start = .);
    LONG(ADDR(.bss)); LONG(ADDR(.bss) + SIZEOF(.bss));
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
    } > ROM AT > ROM
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
    } > RAM AT > ROM
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
    } > RAM AT > RAM
/******************************************************************************
 *  ARM.exidx SECTION
 *****************************************************************************/
    . = ALIGN(4);
    PROVIDE(__exidx_start = .);
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*);
    } > ROM AT > ROM /* index entries for section unwinding */
    . = ALIGN(4);
    PROVIDE(__exidx_end = .);
/******************************************************************************
 *
 *  USER SECTION BEGIN.
 *
 *****************************************************************************/
/******************************************************************************
 *  __SECT_NAME__(SECTION_0) definition.
 *****************************************************************************/
    .FUNC_RAM :
    {
        . = ALIGN(4);
        PROVIDE(__FUNC_RAM_start = .);
        *(.FUNC_RAM .FUNC_RAM.*);
        PROVIDE(__FUNC_RAM_end = .);
        . = ALIGN(4);
    } > RAM AT > ROM
/******************************************************************************
 *  __SECT_NAME__(SECTION_1) definition.
 *****************************************************************************/
    .SRAM (NOLOAD) :
    {
        . = ALIGN(4);
        PROVIDE(__SRAM_start = .);
        *(.SRAM .SRAM.*);
        PROVIDE(__SRAM_end = .);
        . = ALIGN(4);
    } > SRAM AT > SRAM
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
        PROVIDE(__main_stack_end = .);
        PROVIDE(__process_stack_start = .);
        . += __process_stack_size;
        . = ALIGN(8);
        PROVIDE(__process_stack_end = .);
        PROVIDE(__stack_end = .);
    } > CCM_RAM AT > CCM_RAM
/******************************************************************************
 *  HEAP
 *****************************************************************************/
    .heap :
    {
        . = ALIGN(4);
        PROVIDE(__heap_start = .);
        . = ALIGN(4);
        __heap_end = ORIGIN(RAM) + LENGTH(RAM);
        PROVIDE(__heap_end = __heap_end);
    } > RAM AT > RAM
/******************************************************************************
 *
 *****************************************************************************/
    .stab 0 (NOLOAD) : { *(.stab) }
    .stabstr 0 (NOLOAD) : { *(.stabstr) }
    /* DWARF debug sections.
    * Symbols in the DWARF debugging sections are relative to the beginning
    * of the section so we begin them at 0. */
    /* DWARF 1 */
    .debug 0 : { *(.debug) }
    .line 0 : { *(.line) }
    /* GNU DWARF 1 extensions */
    .debug_srcinfo 0 : { *(.debug_srcinfo) }
    .debug_sfnames 0 : { *(.debug_sfnames) }
    /* DWARF 1.1 and DWARF 2 */
    .debug_aranges 0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    /* DWARF 2 */
    .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
    .debug_abbrev 0 : { *(.debug_abbrev) }
    .debug_line 0 : { *(.debug_line) }
    .debug_frame 0 : { *(.debug_frame) }
    .debug_str 0 : { *(.debug_str) }
    .debug_loc 0 : { *(.debug_loc) }
    .debug_macinfo 0 : { *(.debug_macinfo) }
    /* SGI/MIPS DWARF 2 extensions */
    .debug_weaknames 0 : { *(.debug_weaknames) }
    .debug_funcnames 0 : { *(.debug_funcnames) }
    .debug_typenames 0 : { *(.debug_typenames) }
    .debug_varnames 0 : { *(.debug_varnames) }
    .note.gnu.arm.ident 0 : { KEEP(*(.note.gnu.arm.ident)) }
    .ARM.attributes 0 : { KEEP(*(.ARM.attributes)) }
    /DISCARD/ : { *(.note.GNU-stack) }
}
