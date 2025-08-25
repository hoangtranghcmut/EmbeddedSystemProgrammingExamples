/*
 * fifo.c
 *
 *  Created on: Aug 13, 2025
 *      Author: Admin
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "fifo.h"
#include "atomic.h"
#include "error_codes.h"

//............................................................................
void fifo_init(Fifo_t * const me, void *p_vSto, uint32_t ui32StoLen, size_t uiElementSize) {
    me->p_vBuf = p_vSto;
    me->ui32End = ui32StoLen;
    me->uiElementSize = uiElementSize;
    ENTER_CRITICAL();
    me->ui32Head = 0U;  // initialize head atomically
    me->ui32Tail = 0U;  // initialize tail atomically
    EXIT_CRITICAL();
}

//............................................................................
uint32_t fifo_put(Fifo_t * const me, const void *p_vElement) {
    uint32_t ui32RetVal;
    ENTER_CRITICAL();
    uint32_t ui32Head = me->ui32Head + 1U;
    if (ui32Head == me->ui32End) {
        ui32Head = 0U;
    }
    uint32_t ui32Tail = me->ui32Tail;
    if (ui32Head != ui32Tail) { // buffer NOT full?
        // Copy element to buffer at head position
        memcpy((uint8_t *)me->p_vBuf + (me->ui32Head * me->uiElementSize),
               p_vElement,
               me->uiElementSize);
        me->ui32Head = ui32Head;
        ui32RetVal = ERROR_OK;
    }
    else {
        ui32RetVal = ERROR_BUFFER_FULL; // buffer full
    }
    EXIT_CRITICAL();
    return ui32RetVal;
}

//............................................................................
uint32_t fifo_get(Fifo_t * const me, void *p_vElement) {
    uint32_t ui32RetVal;
    ENTER_CRITICAL();
    uint32_t ui32Tail = me->ui32Tail;
    uint32_t ui32Head = me->ui32Head;
    if (ui32Head != ui32Tail) { // buffer NOT empty?
        // Copy element from buffer at tail position
        memcpy(p_vElement,
               (uint8_t *)me->p_vBuf + (ui32Tail * me->uiElementSize),
               me->uiElementSize);
        ++ui32Tail;
        if (ui32Tail == me->ui32End) {
            ui32Tail = 0U;
        }
        me->ui32Tail = ui32Tail;
        ui32RetVal = ERROR_OK;
    }
    else {
        ui32RetVal = ERROR_BUFFER_EMPTY; // buffer empty
    }
    EXIT_CRITICAL();
    return ui32RetVal;
}

//............................................................................
uint32_t fifo_num_free(Fifo_t * const me) {
    ENTER_CRITICAL();
    uint32_t ui32Head = me->ui32Head;
    uint32_t ui32Tail = me->ui32Tail;
    EXIT_CRITICAL();
    if (ui32Head == ui32Tail) { // buffer empty?
        return (uint32_t)(me->ui32End - 1U);
    }
    else if (ui32Head < ui32Tail) {
        return (uint32_t)(ui32Tail - ui32Head - 1U);
    }
    else {
        return (uint32_t)(me->ui32End + ui32Tail - ui32Head - 1U);
    }
}

//............................................................................
void fifo_process_all(Fifo_t * const me, FifoHandler handler) {
    uint32_t ui32Tail = atomic_load_explicit(&me->ui32Tail, memory_order_relaxed);
    uint32_t ui32Head = atomic_load_explicit(&me->ui32Head, memory_order_acquire);
    while (ui32Head != ui32Tail) { // buffer NOT empty?
        // Pass element to handler
        (*handler)((uint8_t *)me->p_vBuf + (ui32Tail * me->uiElementSize));
        ++ui32Tail;
        if (ui32Tail == me->ui32End) {
            ui32Tail = 0U;
        }
        atomic_store_explicit(&me->ui32Tail, ui32Tail, memory_order_release);
    }
}
