#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pci.h>

typedef struct __attribute__((packed)) {
	uint32_t vendor_id:16,
			 device_id:16;
	uint32_t command:16,
			 status:16;
	uint32_t rev_id:8,
			 class_code:24;
	uint32_t cache_line_size:8,
	 		 latency_timer:8,
	 		 header_type:8,
	 		 bist:8;
	uint32_t bar_0;
	uint32_t bar_1;
	union {
		struct __attribute__((packed)) {
			uint8_t pri_bus_num;
			uint8_t sec_bus_num;
			uint8_t sub_bus_num;
			uint8_t sec_latency_timer;
			uint8_t io_base;
			uint8_t io_limit;
			uint16_t sec_status;
			uint16_t mem_base;
			uint16_t mem_limit;
			uint16_t prefetch_mem_base;
			uint16_t prefetch_mem_limit;
			uint32_t prefetch_base;
			uint32_t prefetch_limit;
			uint16_t io_base_upper;
			uint16_t io_limit_upper;
			uint8_t cap_ptr;
			uint32_t rsvd:24;
			uint32_t exp_rom_base_addr;
			uint8_t intr_line;
			uint8_t intr_pin;
			uint16_t bridge_ctrl;
		} one;
		struct __attribute__((packed)) {
			uint32_t bar_2;
			uint32_t bar_3;
			uint32_t bar_4;
			uint32_t bar_5;
			uint32_t cardbus_cis_ptr;
			uint16_t subsystem_vendor_id;
			uint16_t subsystem_id;
			uint32_t exp_rom_base_addr;
			uint8_t cap_ptr;
			uint32_t rsvd:24;
			uint32_t rsvd_1;
			uint8_t intr_line;
			uint8_t intr_pin;
			uint8_t min_gnt;
			uint8_t max_lat;
		} zero;
	} type;
} hdr_t;

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
	char config[64] = {0};

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

	pci_read_block(pci_dev, 0, config, 64);
	hdr_t *hdr = (hdr_t *) config;
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|    Byte 3    |   Byte 2     |    Byte 1    |    Byte 0    | DoubleWord\n");
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|           Device ID         |           Vendor ID         |    0x00\n");
    printf("\t|             %04x            |             %04x            |\n", hdr->device_id, hdr->vendor_id);
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|            Status           |            Command          |    0x04\n");
    printf("\t|             %04x            |             %04x            |\n", hdr->status, hdr->command);
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                  Class Code                | Revision ID  |    0x08\n");
    printf("\t|                    %06x                  |      %02x      |\n", hdr->class_code, hdr->rev_id);
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|     BIST     | Header Type  | latency timer| CachLineSize |    0x0c\n");
    printf("\t|      %02x      |      %02x      |      %02x      |      %02x      |\n", hdr->bist, hdr->header_type, hdr->latency_timer, hdr->cache_line_size);
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                Base Address 0 = %08x                  |    0x10\n", hdr->bar_0);
    printf("\t|-----------------------------------------------------------|\n");
    printf("\t|                Base Address 1 = %08x                  |    0x14\n", hdr->bar_1);
    printf("\t|-----------------------------------------------------------|\n");
	
	if(hdr->header_type) {
    	printf("\t| Sec Latency  | Subordinate  |   Secondary  |    Primary   |    0x18\n");
    	printf("\t|    Timer     | Bus  Number  |  Bus  Number |  Bus Number  |\n");
    	printf("\t|     %02x       |      %02x      |      %02x      |      %02x      |\n", hdr->type.one.sec_latency_timer, hdr->type.one.sub_bus_num, hdr->type.one.sec_bus_num, hdr->type.one.pri_bus_num);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|        Secondary Status     |   I/O Limit  |   I/O Base   |    0x1c\n");
    	printf("\t|              %04x           |      %02x      |      %02x      |\n", hdr->type.one.sec_status, hdr->type.one.io_limit, hdr->type.one.io_base);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|          Memory Limit       |          Memory Base        |    0x20\n");
    	printf("\t|              %04x           |             %04x            |\n", hdr->type.one.mem_limit, hdr->type.one.mem_base);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|   Prefetchable Memory Limit |  Prefetchable Memory Base   |    0x24\n");
    	printf("\t|              %04x           |             %04x            |\n", hdr->type.one.prefetch_mem_limit, hdr->type.one.prefetch_mem_base);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|             Prefetchable Base - Upper 32-bits             |    0x28\n");
    	printf("\t|                         %08x                          |\n", hdr->type.one.prefetch_base);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|             Prefetchable Limit - Upper 32-bits            |    0x2c\n");
    	printf("\t|                         %08x                          |\n", hdr->type.one.prefetch_limit);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|    I/O Limit Upper 16-bits  |   I/O Base Upper 16-bits    |    0x30\n");
    	printf("\t|              %04x           |           %04x              |\n", hdr->type.one.io_limit_upper, hdr->type.one.io_base_upper);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                  Reserved                  | Cap Pointer  |    0x34\n");
    	printf("\t|                   %06x                   |     %02x       |\n", hdr->type.one.rsvd, hdr->type.one.cap_ptr);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|          Expansion ROM Base Address =  %08x           |    0x38\n", hdr->type.one.exp_rom_base_addr);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|        Bridge Control       |   Intr Pin   |  Intr Line   |    0x3c\n");
    	printf("\t|              %02x             |      %02x      |      %02x      |\n", hdr->type.one.bridge_ctrl, hdr->type.one.intr_pin, hdr->type.one.intr_line);
    	printf("\t|-----------------------------------------------------------|\n");
	} else {
    	printf("\t|                Base Address 2 = %08x                  |    0x18\n", hdr->type.zero.bar_2);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                Base Address 3 = %08x                  |    0x1c\n", hdr->type.zero.bar_3);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                Base Address 4 = %08x                  |    0x20\n", hdr->type.zero.bar_4);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                Base Address 5 = %08x                  |    0x24\n", hdr->type.zero.bar_5);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|             CardBus CIS Pointer = %08x                |    0x28\n", hdr->type.zero.cardbus_cis_ptr);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|          Subsystem ID         |    Subsystem Vendor ID    |    0x2c\n");
    	printf("\t|              %04x             |            %04x           |\n", hdr->type.zero.subsystem_id, hdr->type.zero.subsystem_vendor_id);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|          Expansion ROM Base Address =  %08x           |    0x30\n", hdr->type.zero.exp_rom_base_addr);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                  Reserved                |   Cap Pointer  |    0x34\n");
    	printf("\t|                   %06x                 |       %02x       |\n", hdr->type.zero.rsvd, hdr->type.zero.cap_ptr);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|                   Reserved = %08x                     |    0x38\n", hdr->type.zero.rsvd);
    	printf("\t|-----------------------------------------------------------|\n");
    	printf("\t|    Max_lat   |    Min_Gnt   |   Intr Pin   |  Intr Line   |    0x3c\n");
    	printf("\t|      %02x      |      %02x      |      %02x      |      %02x      |\n", hdr->type.zero.max_lat, hdr->type.zero.min_gnt, hdr->type.zero.intr_pin, hdr->type.zero.intr_line);
    	printf("\t|-----------------------------------------------------------|\n");
	}		

	pci_cleanup(pacc);
	return 0;
}
