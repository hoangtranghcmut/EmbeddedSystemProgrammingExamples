/*
 * atomic.h
 *
 *  Created on: Jul 1, 2025
 *      Author: Admin
 */

#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#ifndef ATOMIC_H
#define ATOMIC_H

#include <stdint.h>
#include "stdbool.h"
#include "stm32f4xx.h"

typedef volatile uint8_t spinLock_t;

// Define BASEPRI priority level (0-15, lower number = higher priority)
#define BASE_PRI 2

// Macro để vào critical section
#define ENTER_CRITICAL() do { \
    __set_BASEPRI(BASE_PRI << (8 - __NVIC_PRIO_BITS)); \
} while (0)

// Macro để thoát critical section
#define EXIT_CRITICAL() do { \
    __set_BASEPRI(0); \
} while (0)

// Macro để thực hiện thao tác atomic đơn giản (đọc/ghi)
#define ATOMIC_READ(var) ({ \
    uint32_t val; \
    ENTER_CRITICAL(); \
    val = (var); \
    EXIT_CRITICAL(); \
    val; \
})

#define ATOMIC_WRITE(var, val) do { \
    ENTER_CRITICAL(); \
    (var) = (val); \
    EXIT_CRITICAL(); \
} while (0)

static inline bool _io_try_lock(volatile uint8_t *pLock)
{
    uint8_t val = __LDREXB(pLock);     // đọc giá trị hiện tại
    if (val != 0) return false;        // nếu đang lock → thất bại
    return (__STREXB(1, pLock) == 0);  // nếu store thành công → lock thành công
}
static inline void _io_unlock(volatile uint8_t *pLock)
{
    __DMB();           // hàng rào bộ nhớ, đảm bảo thứ tự truy cập
    *pLock = 0;
}
// Hàm atomic để tăng/giảm giá trị
uint32_t atomic_inc(volatile uint32_t *var);
uint32_t atomic_dec(volatile uint32_t *var);

// Hàm atomic để thiết lập và lấy giá trị cũ
uint32_t atomic_set_and_get_old(volatile uint32_t *var, uint32_t new_val);

// Hàm atomic để so sánh và hoán đổi (compare-and-swap)
uint32_t atomic_compare_and_swap(volatile uint32_t *var, uint32_t old_val, uint32_t new_val);

#endif

#endif /* MIDDLEWARE_UTILS_PORTS_STM32F7XX_ATOMIC_H_ */
