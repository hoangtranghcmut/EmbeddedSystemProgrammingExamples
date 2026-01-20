#ifndef RING_BUF_H
#define RING_BUF_H

#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>

//! Ring buffer counter/index
//
// @attention
// The following uint32_t type is assumed to be "atomic" in a target CPU,
// meaning that the CPU needs to write the whole uint32_t in one machine
// instruction. An example of violating this assumption would be an 8-bit
// CPU, which writes uint32_t (4-bytes) in multiple machine instructions. For
// such 8-bit CPU, the maximum size of uint32_t would need adjustment.
//
// Another case of violating the "atomic" writes to uint32_t type would
// be misalignment of a uint32_t variable in memory, which could cause
// the compiler to generate multiple instructions to write a uint32_t value.
// Therefore, it is further assumed that all uint32_t variables in the
// following RingBuf struct *are* correctly aligned for "atomic" access.
// In practice, most C compilers should provide such natural alignment
// (by inserting some padding into the ::RingBuf struct, if necessary).
//

//! Ring buffer element type
//
// @details
// The type of the ring buffer elements is not critical for the lock-free
// operation and does not need to be "atomic". For example, it can be
// an integer type (uint16_t, uint32_t, uint64_t), a pointer type,
// or even a struct type. However, the bigger the type the more RAM is
// needed for the ring buffer and more CPU cycles are needed to copy it
// into and out of the buffer memory.
//

//! Ring buffer struct
typedef struct {
    uint8_t *p_ui8Buf;      //!< pointer to the start of the ring buffer
    uint32_t ui32End;       //!< index of the end of the ring buffer


    //! atomic index to where next element will be inserted
    uint32_t ui32Head;

    //! atomic index to where next element will be removed
    uint32_t ui32Tail;
} RingBuf_t;

void ring_buf_init(RingBuf_t * const me,
                   uint8_t p_ui8Sto[], uint32_t ui32StoLen);
uint32_t ring_buf_num_free(RingBuf_t * const me);
uint32_t ring_buf_put(RingBuf_t * const me, uint8_t const ui8Element) ;
uint32_t ring_buf_get(RingBuf_t * const me, uint8_t *pui8Element) ;

//! Ring buffer callback function for ring_buf_process_all()
//
// @details
// The callback processes one element and runs in the context of
// ring_buf_process_all().
//
typedef void (*RingBufHandler)(uint8_t const ui8Element);

void ring_buf_process_all(RingBuf_t * const me, RingBufHandler handler);

#endif // RING_BUF_H
