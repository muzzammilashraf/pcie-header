#ifndef HDR_H
#define HDR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <assert.h>

// Reg - hdr::common::dw0
#define HDR__COMMON__DW0__VENDOR_ID_bm 0xffff
#define HDR__COMMON__DW0__VENDOR_ID_bp 0
#define HDR__COMMON__DW0__VENDOR_ID_bw 16
#define HDR__COMMON__DW0__DEVICE_ID_bm 0xffff0000
#define HDR__COMMON__DW0__DEVICE_ID_bp 16
#define HDR__COMMON__DW0__DEVICE_ID_bw 16

// Reg - hdr::common::dw1
#define HDR__COMMON__DW1__COMMAND_bm 0xffff
#define HDR__COMMON__DW1__COMMAND_bp 0
#define HDR__COMMON__DW1__COMMAND_bw 16
#define HDR__COMMON__DW1__STATUS_bm 0xffff0000
#define HDR__COMMON__DW1__STATUS_bp 16
#define HDR__COMMON__DW1__STATUS_bw 16

// Reg - hdr::common::dw2
#define HDR__COMMON__DW2__REV_ID_bm 0xff
#define HDR__COMMON__DW2__REV_ID_bp 0
#define HDR__COMMON__DW2__REV_ID_bw 8
#define HDR__COMMON__DW2__CLASS_CODE_bm 0xffffff00
#define HDR__COMMON__DW2__CLASS_CODE_bp 8
#define HDR__COMMON__DW2__CLASS_CODE_bw 24

// Reg - hdr::common::dw3
#define HDR__COMMON__DW3__CACHE_LINE_SIZE_bm 0xff
#define HDR__COMMON__DW3__CACHE_LINE_SIZE_bp 0
#define HDR__COMMON__DW3__CACHE_LINE_SIZE_bw 8
#define HDR__COMMON__DW3__LATENCY_TIMER_bm 0xff00
#define HDR__COMMON__DW3__LATENCY_TIMER_bp 8
#define HDR__COMMON__DW3__LATENCY_TIMER_bw 8
#define HDR__COMMON__DW3__HEADER_TYPE_bm 0xff0000
#define HDR__COMMON__DW3__HEADER_TYPE_bp 16
#define HDR__COMMON__DW3__HEADER_TYPE_bw 8
#define HDR__COMMON__DW3__BIST_bm 0xff000000
#define HDR__COMMON__DW3__BIST_bp 24
#define HDR__COMMON__DW3__BIST_bw 8

// Reg - hdr::common::dw4
#define HDR__COMMON__DW4__BAR0_bm 0xffffffff
#define HDR__COMMON__DW4__BAR0_bp 0
#define HDR__COMMON__DW4__BAR0_bw 32

// Reg - hdr::common::dw5
#define HDR__COMMON__DW5__BAR1_bm 0xffffffff
#define HDR__COMMON__DW5__BAR1_bp 0
#define HDR__COMMON__DW5__BAR1_bw 32

// Regfile - hdr::common
typedef struct __attribute__ ((__packed__)) {
    uint32_t dw0;
    uint32_t dw1;
    uint32_t dw2;
    uint32_t dw3;
    uint32_t dw4;
    uint32_t dw5;
} hdr__common_t;

// Reg - hdr::type_0::dw6
#define HDR__TYPE_0__DW6__BAR2_bm 0xffffffff
#define HDR__TYPE_0__DW6__BAR2_bp 0
#define HDR__TYPE_0__DW6__BAR2_bw 32

// Reg - hdr::type_0::dw7
#define HDR__TYPE_0__DW7__BAR3_bm 0xffffffff
#define HDR__TYPE_0__DW7__BAR3_bp 0
#define HDR__TYPE_0__DW7__BAR3_bw 32

// Reg - hdr::type_0::dw8
#define HDR__TYPE_0__DW8__BAR4_bm 0xffffffff
#define HDR__TYPE_0__DW8__BAR4_bp 0
#define HDR__TYPE_0__DW8__BAR4_bw 32

// Reg - hdr::type_0::dw9
#define HDR__TYPE_0__DW9__BAR5_bm 0xffffffff
#define HDR__TYPE_0__DW9__BAR5_bp 0
#define HDR__TYPE_0__DW9__BAR5_bw 32

// Reg - hdr::type_0::dw10
#define HDR__TYPE_0__DW10__CARDBUS_CIS_POINTER_bm 0xffffffff
#define HDR__TYPE_0__DW10__CARDBUS_CIS_POINTER_bp 0
#define HDR__TYPE_0__DW10__CARDBUS_CIS_POINTER_bw 32

// Reg - hdr::type_0::dw11
#define HDR__TYPE_0__DW11__SUBSYSTEM_VENDOR_ID_bm 0xffff
#define HDR__TYPE_0__DW11__SUBSYSTEM_VENDOR_ID_bp 0
#define HDR__TYPE_0__DW11__SUBSYSTEM_VENDOR_ID_bw 16
#define HDR__TYPE_0__DW11__SUBSYSTEM_ID_bm 0xffff0000
#define HDR__TYPE_0__DW11__SUBSYSTEM_ID_bp 16
#define HDR__TYPE_0__DW11__SUBSYSTEM_ID_bw 16

// Reg - hdr::type_0::dw12
#define HDR__TYPE_0__DW12__EXPANSION_ROM_BASE_ADDRESS_bm 0xffffffff
#define HDR__TYPE_0__DW12__EXPANSION_ROM_BASE_ADDRESS_bp 0
#define HDR__TYPE_0__DW12__EXPANSION_ROM_BASE_ADDRESS_bw 32

// Reg - hdr::type_0::dw13
#define HDR__TYPE_0__DW13__CAPABILITIES_POINTER_bm 0xff
#define HDR__TYPE_0__DW13__CAPABILITIES_POINTER_bp 0
#define HDR__TYPE_0__DW13__CAPABILITIES_POINTER_bw 8
#define HDR__TYPE_0__DW13__RSVD_bm 0xffffff00
#define HDR__TYPE_0__DW13__RSVD_bp 8
#define HDR__TYPE_0__DW13__RSVD_bw 24

// Reg - hdr::type_0::dw14
#define HDR__TYPE_0__DW14__RSVD_bm 0xffffffff
#define HDR__TYPE_0__DW14__RSVD_bp 0
#define HDR__TYPE_0__DW14__RSVD_bw 32

// Reg - hdr::type_0::dw15
#define HDR__TYPE_0__DW15__INTERRUPT_LINE_bm 0xff
#define HDR__TYPE_0__DW15__INTERRUPT_LINE_bp 0
#define HDR__TYPE_0__DW15__INTERRUPT_LINE_bw 8
#define HDR__TYPE_0__DW15__INTERRUPT_PIN_bm 0xff00
#define HDR__TYPE_0__DW15__INTERRUPT_PIN_bp 8
#define HDR__TYPE_0__DW15__INTERRUPT_PIN_bw 8
#define HDR__TYPE_0__DW15__MIN_GNT_bm 0xff0000
#define HDR__TYPE_0__DW15__MIN_GNT_bp 16
#define HDR__TYPE_0__DW15__MIN_GNT_bw 8
#define HDR__TYPE_0__DW15__MAX_LAT_bm 0xff000000
#define HDR__TYPE_0__DW15__MAX_LAT_bp 24
#define HDR__TYPE_0__DW15__MAX_LAT_bw 8

// Regfile - hdr::type_0
typedef struct __attribute__ ((__packed__)) {
    uint32_t dw6;
    uint32_t dw7;
    uint32_t dw8;
    uint32_t dw9;
    uint32_t dw10;
    uint32_t dw11;
    uint32_t dw12;
    uint32_t dw13;
    uint32_t dw14;
    uint32_t dw15;
} hdr__type_0_t;

// Reg - hdr::type_1::dw6
#define HDR__TYPE_1__DW6__PRIMARY_BUS_NUMBER_bm 0xff
#define HDR__TYPE_1__DW6__PRIMARY_BUS_NUMBER_bp 0
#define HDR__TYPE_1__DW6__PRIMARY_BUS_NUMBER_bw 8
#define HDR__TYPE_1__DW6__SECONDARY_BUS_NUMBER_bm 0xff00
#define HDR__TYPE_1__DW6__SECONDARY_BUS_NUMBER_bp 8
#define HDR__TYPE_1__DW6__SECONDARY_BUS_NUMBER_bw 8
#define HDR__TYPE_1__DW6__SUBORDINATE_BUS_NUMBER_bm 0xff0000
#define HDR__TYPE_1__DW6__SUBORDINATE_BUS_NUMBER_bp 16
#define HDR__TYPE_1__DW6__SUBORDINATE_BUS_NUMBER_bw 8
#define HDR__TYPE_1__DW6__SECONDARY_LATENCY_TIMER_bm 0xff000000
#define HDR__TYPE_1__DW6__SECONDARY_LATENCY_TIMER_bp 24
#define HDR__TYPE_1__DW6__SECONDARY_LATENCY_TIMER_bw 8

// Reg - hdr::type_1::dw7
#define HDR__TYPE_1__DW7__IO_BASE_bm 0xff
#define HDR__TYPE_1__DW7__IO_BASE_bp 0
#define HDR__TYPE_1__DW7__IO_BASE_bw 8
#define HDR__TYPE_1__DW7__IO_LIMIT_bm 0xff00
#define HDR__TYPE_1__DW7__IO_LIMIT_bp 8
#define HDR__TYPE_1__DW7__IO_LIMIT_bw 8
#define HDR__TYPE_1__DW7__SECONDARY_STATUS_bm 0xffff0000
#define HDR__TYPE_1__DW7__SECONDARY_STATUS_bp 16
#define HDR__TYPE_1__DW7__SECONDARY_STATUS_bw 16

// Reg - hdr::type_1::dw8
#define HDR__TYPE_1__DW8__MEMORY_BASE_bm 0xffff
#define HDR__TYPE_1__DW8__MEMORY_BASE_bp 0
#define HDR__TYPE_1__DW8__MEMORY_BASE_bw 16
#define HDR__TYPE_1__DW8__MEMORY_LIMIT_bm 0xffff0000
#define HDR__TYPE_1__DW8__MEMORY_LIMIT_bp 16
#define HDR__TYPE_1__DW8__MEMORY_LIMIT_bw 16

// Reg - hdr::type_1::dw9
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_BASE_bm 0xffff
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_BASE_bp 0
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_BASE_bw 16
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_LIMIT_bm 0xffff0000
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_LIMIT_bp 16
#define HDR__TYPE_1__DW9__PREFETCHABLE_MEMORY_LIMIT_bw 16

// Reg - hdr::type_1::dw10
#define HDR__TYPE_1__DW10__PREFETCHABLE_MEMORY_BASE_UPPER_bm 0xffffffff
#define HDR__TYPE_1__DW10__PREFETCHABLE_MEMORY_BASE_UPPER_bp 0
#define HDR__TYPE_1__DW10__PREFETCHABLE_MEMORY_BASE_UPPER_bw 32

// Reg - hdr::type_1::dw11
#define HDR__TYPE_1__DW11__PREFETCHABLE_MEMORY_LIMIT_UPPER_bm 0xffffffff
#define HDR__TYPE_1__DW11__PREFETCHABLE_MEMORY_LIMIT_UPPER_bp 0
#define HDR__TYPE_1__DW11__PREFETCHABLE_MEMORY_LIMIT_UPPER_bw 32

// Reg - hdr::type_1::dw12
#define HDR__TYPE_1__DW12__IO_BASE_UPPER_bm 0xffff
#define HDR__TYPE_1__DW12__IO_BASE_UPPER_bp 0
#define HDR__TYPE_1__DW12__IO_BASE_UPPER_bw 16
#define HDR__TYPE_1__DW12__IO_BASE_LIMIT_bm 0xffff0000
#define HDR__TYPE_1__DW12__IO_BASE_LIMIT_bp 16
#define HDR__TYPE_1__DW12__IO_BASE_LIMIT_bw 16

// Reg - hdr::type_1::dw13
#define HDR__TYPE_1__DW13__CAPABILITIES_POINTER_bm 0xff
#define HDR__TYPE_1__DW13__CAPABILITIES_POINTER_bp 0
#define HDR__TYPE_1__DW13__CAPABILITIES_POINTER_bw 8
#define HDR__TYPE_1__DW13__RSVD_bm 0xffffff00
#define HDR__TYPE_1__DW13__RSVD_bp 8
#define HDR__TYPE_1__DW13__RSVD_bw 24

// Reg - hdr::type_1::dw14
#define HDR__TYPE_1__DW14__EXPANSION_ROM_BASE_ADDRESS_bm 0xffffffff
#define HDR__TYPE_1__DW14__EXPANSION_ROM_BASE_ADDRESS_bp 0
#define HDR__TYPE_1__DW14__EXPANSION_ROM_BASE_ADDRESS_bw 32

// Reg - hdr::type_1::dw15
#define HDR__TYPE_1__DW15__INTERRUPT_LINE_bm 0xff
#define HDR__TYPE_1__DW15__INTERRUPT_LINE_bp 0
#define HDR__TYPE_1__DW15__INTERRUPT_LINE_bw 8
#define HDR__TYPE_1__DW15__INTERRUPT_PIN_bm 0xff00
#define HDR__TYPE_1__DW15__INTERRUPT_PIN_bp 8
#define HDR__TYPE_1__DW15__INTERRUPT_PIN_bw 8
#define HDR__TYPE_1__DW15__BRIDGE_CONTROL_bm 0xffff0000
#define HDR__TYPE_1__DW15__BRIDGE_CONTROL_bp 16
#define HDR__TYPE_1__DW15__BRIDGE_CONTROL_bw 16

// Regfile - hdr::type_1
typedef struct __attribute__ ((__packed__)) {
    uint32_t dw6;
    uint32_t dw7;
    uint32_t dw8;
    uint32_t dw9;
    uint32_t dw10;
    uint32_t dw11;
    uint32_t dw12;
    uint32_t dw13;
    uint32_t dw14;
    uint32_t dw15;
} hdr__type_1_t;

#ifdef __cplusplus
}
#endif

#endif /* HDR_H */
