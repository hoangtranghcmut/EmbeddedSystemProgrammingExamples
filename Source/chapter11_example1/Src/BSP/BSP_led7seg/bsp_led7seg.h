/*
 * bsp_led7seg.h
 *
 *  Created on: Aug 14, 2025
 *      Author: Admin
 */

#ifndef _BSP_LED7SEG_H_
#define _BSP_LED7SEG_H_

void bsp_led7seg_display(uint16_t ui16LedIdx, uint8_t ui8LedCode);
void bsp_led7seg_turn_off_single(uint16_t ui16LedIdx);
void bsp_led7seg_turn_off_all();
void bsp_led7seg_turn_on_single(uint16_t ui16LedIdx);


#endif /* BSP_BSP_LED7SEG_BSP_LED7SEG_H_ */
