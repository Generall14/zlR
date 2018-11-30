/**
 ******************************************************************************
 *
 * Memory configuration
 *
 * mgr inż. W. Kogut tu był!
 *
 ******************************************************************************
 */

#ifndef TST_H
#define TST_H


//##CONST
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


//##REGION
/**                         Nazwa           Prawa        Adres        Rozmiar   */
#define REGION_0            ROM           , RX         , 0x08000000 , 2M
#define REGION_1            RAM           , RWX        , 0x20000000 , 112k
#define REGION_2            RAM1          , RWX        , 0x2001C000 , 16k
#define REGION_3            RAM2          , RWX        , 0x20020000 , 64k
#define REGION_4            CCM_RAM       , RWX        , 0x10000000 , 64k
#define REGION_5            BKP_RAM       , RW         , 0x40024000 , 4k
#define REGION_6            SRAM          , RWX        , 0x68000000 , 256k
#define REGION_7            NOR           , RWX        , 0x64000000 , 16M


//##SECTION
/**                         Nazwa           LMA_ADDR     VMA_ADDR     TYPE         KEEP         NOLOAD   */
#define SECTION_0           FUNC_RAM      , ROM        , RAM        , DATA       ,            , 
#define SECTION_1           SRAM          , SRAM       , SRAM       , NOINIT     ,            , NOLOAD


#endif /* TST_H */
