/*
 * fifo.h
 *
 *  Created on: Aug 13, 2025
 *      Author: Admin
 */


#ifndef FIFO_H
#define FIFO_H

#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//! FIFO counter/index
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
// following Fifo struct *are* correctly aligned for "atomic" access.
// In practice, most C compilers should provide such natural alignment
// (by inserting some padding into the ::Fifo struct, if necessary).
//

//! FIFO element type
//
// @details
// The FIFO supports generic elements of any size, specified at
// initialization. The element size is stored in the FIFO structure and used
// for accessing the buffer. The elements do not need to be "atomic". The
// larger the element size, the more RAM and CPU cycles are needed for copying
// elements into and out of the buffer memory.
//

//! FIFO struct
typedef struct {
    void *p_vBuf;           //!< pointer to the start of the FIFO buffer
    uint32_t ui32End;       //!< number of elements in the FIFO buffer
    uint32_t ui32Head;      //!< atomic index to where next element will be inserted
    uint32_t ui32Tail;      //!< atomic index to where next element will be removed
    size_t uiElementSize;   //!< size of each element in bytes
} Fifo_t;

void fifo_init(Fifo_t * const me, void *p_vSto, uint32_t ui32StoLen, size_t uiElementSize);
uint32_t fifo_num_free(Fifo_t * const me);
uint32_t fifo_put(Fifo_t * const me, const void *p_vElement);
uint32_t fifo_get(Fifo_t * const me, void *p_vElement);

//! FIFO callback function for fifo_process_all()
//
// @details
// The callback processes one element and runs in the context of
// fifo_process_all(). The element is passed as a void pointer to support
// generic element types.
//
typedef void (*FifoHandler)(const void *p_vElement);

void fifo_process_all(Fifo_t * const me, FifoHandler handler);

#endif // FIFO_H


