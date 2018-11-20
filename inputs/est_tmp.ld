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

PROVIDE(__main_stack_size       = MAIN_STACK_SIZE);
PROVIDE(__process_stack_size    = PROCESS_STACK_SIZE);

/******************************************************************************
 * available memories definitions
 *****************************************************************************/


/*================================================================================================================================================*/
MEMORY
{
##MEM_REG(JAKAS_NAZWA_REGIONU_0)
##MEM_REG(JAKAS_NAZWA_REGIONU_0)
...
/
##MEM_REG_ALL ???????????????
}

/
a może:
##MAKE_MEMORY{lista / all} - tworzy blok memory oraz stałe _start, _size, _end
/*================================================================================================================================================*/


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

/*================================================================================================================================================*/
; to zastąpić pojedynczym wpisem?
#if VECTORS_VMA_REGION != VECTORS_LMA_REGION
    LONG(LOADADDR(.vectors));    LONG(ADDR(.vectors));    LONG(ADDR(.vectors)    + SIZEOF(.vectors));
#endif
    LONG(LOADADDR(.data));       LONG(ADDR(.data));       LONG(ADDR(.data)       + SIZEOF(.data));

/*================================================================================================================================================*/
##PUT_INIT_SECTIONS{TYPE} ; tu wpakuje wszystkie sekcje z typem TYPE // DATA

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
/*================================================================================================================================================*/
##PUT_INIT_SECTIONS{TYPE} ; tu wpakuje wszystkie sekcje z typem TYPE // BSS
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
/*================================================================================================================================================*/
; Czy to nizej można zastąpić jedną instrukcją? Czy przewiduje się głębsze modyfikacje tego?
; np:
##PUT_USER_SECTIONS
...
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
