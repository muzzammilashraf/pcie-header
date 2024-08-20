#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pci.h>
#include "hdr.h"

#define GET_VALUE(TYPE, DW, FIELD) \
    (config[DW] & HDR__##TYPE##__DW##DW##__##FIELD##_bm) >> HDR__##TYPE##__DW##DW##__##FIELD##_bp

static struct pci_dev * search_device(struct pci_access *pacc, uint8_t bus,
                                      uint8_t slot, uint8_t func) {
    struct pci_dev *dev;
    for(dev = pacc->devices; dev != NULL; dev = dev->next){
        if((dev-> bus == bus) && (dev->dev == slot) && (dev->func == func)){
            return dev;
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    struct pci_access *pacc;
    struct pci_dev    *pci_dev;
    uint32_t config[16] = {0};

    pacc = pci_alloc();
    pci_init(pacc);
    pci_scan_bus(pacc);

    if(argc < 4) {
        printf("Error: device bus:device:function (bdf) number missing\n");
        return -1;
    }

    pci_dev = search_device(pacc, strtol(argv[1], NULL, 16),
                            strtol(argv[2], NULL, 16),
                            strtol(argv[3], NULL, 16));
    if(pci_dev == NULL) {
        printf("Error: could not find device with the id: %s:%s.%s\n", argv[1],
                argv[2], argv[3]);
        return -1;
    }

    pci_read_block(pci_dev, 0, (uint8_t *) config, 64);

    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|    Byte 3    |   Byte 2     |    Byte 1    |    Byte 0    | DoubleWord\n");
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|           Device ID         |           Vendor ID         |    0x00\n");
    printf("\t|             %04x            |             %04x            |\n",
        GET_VALUE(COMMON, 0, DEVICE_ID), GET_VALUE(COMMON, 0, VENDOR_ID));
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|            Status           |            Command          |    0x04\n");
    printf("\t|             %04x            |             %04x            |\n",
        GET_VALUE(COMMON, 1, STATUS), GET_VALUE(COMMON, 1, COMMAND));
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                  Class Code                | Revision ID  |    0x08\n");
    printf("\t|                    %06x                  |      %02x      |\n",
        GET_VALUE(COMMON, 2, CLASS_CODE), GET_VALUE(COMMON, 2, REV_ID));
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|     BIST     | Header Type  | latency timer| CachLineSize |    0x0c\n");
    printf("\t|      %02x      |      %02x      |      %02x      |      %02x      |\n",
        GET_VALUE(COMMON, 3, BIST),
        GET_VALUE(COMMON, 3, HEADER_TYPE),
        GET_VALUE(COMMON, 3, LATENCY_TIMER),
        GET_VALUE(COMMON, 3, CACHE_LINE_SIZE));
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                Base Address 0 = %08x                  |    0x10\n",
        GET_VALUE(COMMON, 4, BAR0));
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                Base Address 1 = %08x                  |    0x14\n",
        GET_VALUE(COMMON, 5, BAR1));
    printf("\t|-----------------------------------------------------------|\n");

    if(GET_VALUE(COMMON, 3, HEADER_TYPE)) {
        printf("\t| Sec Latency  | Subordinate  |   Secondary  |    Primary   |    0x18\n");
        printf("\t|    Timer     | Bus  Number  |  Bus  Number |  Bus Number  |\n");
        printf("\t|     %02x       |      %02x      |      %02x      |      %02x      |\n",
            GET_VALUE(TYPE_1, 6, SECONDARY_LATENCY_TIMER),
            GET_VALUE(TYPE_1, 6, SUBORDINATE_BUS_NUMBER),
            GET_VALUE(TYPE_1, 6, SECONDARY_BUS_NUMBER),
            GET_VALUE(TYPE_1, 6, PRIMARY_BUS_NUMBER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|        Secondary Status     |   I/O Limit  |   I/O Base   |    0x1c\n");
        printf("\t|              %04x           |      %02x      |      %02x      |\n",
            GET_VALUE(TYPE_1, 7, SECONDARY_STATUS),
            GET_VALUE(TYPE_1, 7, IO_LIMIT),
            GET_VALUE(TYPE_1, 7, IO_BASE));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|          Memory Limit       |          Memory Base        |    0x20\n");
        printf("\t|              %04x           |             %04x            |\n",
            GET_VALUE(TYPE_1, 8, MEMORY_LIMIT),
            GET_VALUE(TYPE_1, 8, MEMORY_BASE));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|   Prefetchable Memory Limit |  Prefetchable Memory Base   |    0x24\n");
        printf("\t|              %04x           |             %04x            |\n",
            GET_VALUE(TYPE_1, 9, PREFETCHABLE_MEMORY_LIMIT),
            GET_VALUE(TYPE_1, 9, PREFETCHABLE_MEMORY_BASE));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|             Prefetchable Base - Upper 32-bits             |    0x28\n");
        printf("\t|                         %08x                          |\n",
            GET_VALUE(TYPE_1, 10, PREFETCHABLE_MEMORY_BASE_UPPER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|             Prefetchable Limit - Upper 32-bits            |    0x2c\n");
        printf("\t|                         %08x                          |\n",
            GET_VALUE(TYPE_1, 11, PREFETCHABLE_MEMORY_LIMIT_UPPER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|    I/O Limit Upper 16-bits  |   I/O Base Upper 16-bits    |    0x30\n");
        printf("\t|              %04x           |           %04x              |\n",
            GET_VALUE(TYPE_1, 12, IO_BASE_LIMIT),
            GET_VALUE(TYPE_1, 12, IO_BASE_UPPER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                  Reserved                  | Cap Pointer  |    0x34\n");
        printf("\t|                   %06x                   |     %02x       |\n",
            GET_VALUE(TYPE_1, 13, RSVD),
            GET_VALUE(TYPE_1, 13, CAPABILITIES_POINTER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|          Expansion ROM Base Address =  %08x           |    0x38\n",
            GET_VALUE(TYPE_1, 14, EXPANSION_ROM_BASE_ADDRESS));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|        Bridge Control       |   Intr Pin   |  Intr Line   |    0x3c\n");
        printf("\t|              %02x             |      %02x      |      %02x      |\n",
            GET_VALUE(TYPE_1, 15, BRIDGE_CONTROL),
            GET_VALUE(TYPE_1, 15, INTERRUPT_PIN),
            GET_VALUE(TYPE_1, 15, INTERRUPT_LINE));
        printf("\t|-----------------------------------------------------------|\n");
    } else {
        printf("\t|                Base Address 2 = %08x                  |    0x18\n",
            GET_VALUE(TYPE_0, 6, BAR2));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                Base Address 3 = %08x                  |    0x1c\n",
            GET_VALUE(TYPE_0, 7, BAR3));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                Base Address 4 = %08x                  |    0x20\n",
            GET_VALUE(TYPE_0, 8, BAR4));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                Base Address 5 = %08x                  |    0x24\n",
            GET_VALUE(TYPE_0, 9, BAR5));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|             CardBus CIS Pointer = %08x                |    0x28\n",
            GET_VALUE(TYPE_0, 10, CARDBUS_CIS_POINTER));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|          Subsystem ID         |    Subsystem Vendor ID    |    0x2c\n");
        printf("\t|              %04x             |            %04x           |\n",
            GET_VALUE(TYPE_0, 11, SUBSYSTEM_ID),
            GET_VALUE(TYPE_0, 11, SUBSYSTEM_VENDOR_ID));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|          Expansion ROM Base Address =  %08x           |    0x30\n",
            GET_VALUE(TYPE_0, 12, EXPANSION_ROM_BASE_ADDRESS));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                  Reserved                |   Cap Pointer  |    0x34\n");
        printf("\t|                   %06x                 |       %02x       |\n",
            GET_VALUE(TYPE_0, 13, CAPABILITIES_POINTER),
            GET_VALUE(TYPE_0, 13, RSVD));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|                   Reserved = %08x                     |    0x38\n",
            GET_VALUE(TYPE_0, 14, RSVD));
        printf("\t|-----------------------------------------------------------|\n");
        printf("\t|    Max_lat   |    Min_Gnt   |   Intr Pin   |  Intr Line   |    0x3c\n");
        printf("\t|      %02x      |      %02x      |      %02x      |      %02x      |\n",
            GET_VALUE(TYPE_0, 15, INTERRUPT_LINE),
            GET_VALUE(TYPE_0, 15, INTERRUPT_PIN),
            GET_VALUE(TYPE_0, 15, MIN_GNT),
            GET_VALUE(TYPE_0, 15, MAX_LAT));
        printf("\t|-----------------------------------------------------------|\n");
    }

    pci_cleanup(pacc);
    return 0;
}
