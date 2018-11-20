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

#ifndef MEMORY_CFG_H_
#define MEMORY_CFG_H_

; tego typu luźno wiszące stałe będą podmieniane jak w zwykłym preprocesorze
; tego może być więcej typów?
#define MAIN_STACK_SIZE                     1024
#define PROCESS_STACK_SIZE                  1024

#define STACK_REGION                        CCM_RAM
#define HEAP_REGION                         RAM

#define VECTORS_VMA_REGION                  ROM
#define VECTORS_LMA_REGION                  ROM

#define AFTERVECTORS_VMA_REGION             ROM
#define AFTERVECTORS_LMA_REGION             ROM

#define RODATA_VMA_REGION                   ROM
#define RODATA_LMA_REGION                   ROM

#define TEXT_VMA_REGION                     ROM
#define TEXT_LMA_REGION                     ROM

#define DATA_VMA_REGION                     RAM
#define DATA_LMA_REGION                     ROM

#define BSS_VMA_REGION                      RAM
#define BSS_LMA_REGION                      RAM

/**********************************************************************************************************
 * MEMORY REGIONS DEFINITION
 *
 * Max number of regions 20 <0..19>
 *
 **********************************************************************************************************/
; tu jakiś dodatkowy znacznik
#define REGION_0            ROM          , RX        , 0x08000000    , 2M
#define REGION_1            RAM          , RWX       , 0x20000000    , 112k
#define REGION_2            RAM1         , RWX       , 0x2001C000    , 16k
#define REGION_3            RAM2         , RWX       , 0x20020000    , 64k
#define REGION_4            CCM_RAM      , RWX       , 0x10000000    , 64k
#define REGION_5            BKP_RAM      , RW        , 0x40024000    , 4k
#define REGION_6            SRAM         , RWX       , 0x68000000    , 256k
#define REGION_7            NOR          , RWX       , 0x64000000    , 16M

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
; tu jakiś dodatkowy znacznik
#define SECTION_0           FUNC_RAM      , ROM         , RAM           , DATA      ,       ,
#define SECTION_1           SRAM          , SRAM        , SRAM          , NOINIT    ,       , NOLOAD

#endif /* MEMORY_CFG_H_ */
