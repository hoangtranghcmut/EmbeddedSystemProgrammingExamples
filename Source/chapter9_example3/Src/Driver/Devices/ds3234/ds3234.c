/*
 * ds3234.c
 *
 *  Created on: Aug 6, 2025
 *      Author: Admin
 */


#include "ds3234.h"
#include "stddef.h"
#include "error_codes.h"

/**
 * @brief Khởi tạo DS3234 với các thông số được cung cấp
 * @param me Con trỏ tới cấu trúc DS3234_Dev_t
 * @param init Con trỏ tới cấu trúc DS3234_Init_t chứa thông tin khởi tạo
 */
uint32_t DS3234_Init(DS3234_Dev_t* me, const DS3234_Init_t* const init)
{
    if (me == NULL || init == NULL || init->spiBus == NULL || init->csPin == NULL) {

        return ERROR_INVALID_PARAM;
    }

    // Sao chép các thông số khởi tạo
    me->spiBus = init->spiBus;
    me->csPin = init->csPin;
    me->hourMode = init->hourMode;
    me->ui8OutputMode = init->ui8OutputMode;
    me->ui8SqwFreq = init->ui8SqwFreq & 0x03; // Giới hạn tần số sóng vuông (0-3)
    me->initialized = 1;

    // Cấu hình chế độ giờ
    DS3234_SetHourMode(me, me->hourMode);

    // Cấu hình chế độ ngõ ra và tần số sóng vuông
    DS3234_SetOutputMode(me, me->ui8OutputMode, me->ui8SqwFreq);
    return ERROR_OK;
}

uint32_t DS3234_write_register(DS3234_Dev_t* me, uint8_t ui8Reg, uint8_t ui8Value)
{
	uint32_t ret;
	uint8_t buffer[2];

    if (spi_io_is_busy(me->spiBus))	return ERROR_BUSY;
    do_reset(me->csPin);
    buffer[0] =  0x80 | ui8Reg;
    buffer[1] = ui8Value;
    ret = spi_io_write_sync(me->spiBus, buffer, 2);
    do_set(me->csPin);
    return ret;
}

uint32_t DS3234_read_register(DS3234_Dev_t* me, uint8_t ui8Reg, uint8_t * ui8Value)
{
	uint32_t ret;
	uint8_t ui8TxBuffer[2];
	uint8_t ui8RxBuffer[2];

    if (spi_io_is_busy(me->spiBus))	return ERROR_BUSY;
    do_reset(me->csPin);
    ui8TxBuffer[0] =   ui8Reg;
    ui8TxBuffer[1] = 0;
    ret = spi_io_transfer_sync(me->spiBus, ui8TxBuffer, ui8RxBuffer, 2);
    do_set(me->csPin);
    *ui8Value = ui8RxBuffer[1];
    return ret;
}

/**
 * @brief Thiết lập thời gian cho DS3234
 * @param me Con trỏ tới cấu trúc DS3234_Dev_t
 * @param time Con trỏ tới cấu trúc DS3234_Time_t chứa thông tin thời gian
 */
void DS3234_SetTime(DS3234_Dev_t* me, DS3234_Time_t* time)
{


    // Chuyển đổi từ thập phân sang BCD
    uint8_t seconds = DS3234_DecToBCD(time->seconds);
    uint8_t minutes = DS3234_DecToBCD(time->minutes);
    uint8_t hours = DS3234_DecToBCD(time->hours);
    uint8_t day = DS3234_DecToBCD(time->day);
    uint8_t date = DS3234_DecToBCD(time->date);
    uint8_t month = DS3234_DecToBCD(time->month);
    uint8_t year = DS3234_DecToBCD(time->year & 0xFF); // Lấy 2 chữ số cuối của năm

    // Xử lý chế độ 12/24 giờ
    if (me->hourMode == 1) { // 12 giờ
        hours |= (1 << 6); // Đặt bit 6 cho chế độ 12 giờ
        if (time->is_pm) hours |= (1 << 5); // Đặt bit AM/PM
    }

    // Ghi vào các thanh ghi
    DS3234_write_register(me, DS3234_REG_SECONDS, seconds);
    DS3234_write_register(me, DS3234_REG_MINUTES, minutes);
    DS3234_write_register(me, DS3234_REG_HOURS, hours);
    DS3234_write_register(me, DS3234_REG_DAY, day);
    DS3234_write_register(me, DS3234_REG_DATE, date);
    DS3234_write_register(me, DS3234_REG_MONTH, month);
    DS3234_write_register(me, DS3234_REG_YEAR, year);
}

/**
 * @brief Đọc thời gian từ DS3234
 * @param me Con trỏ tới cấu trúc DS3234_Dev_t
 * @param time Con trỏ tới cấu trúc DS3234_Time_t để lưu thời gian
 */
void DS3234_GetTime(DS3234_Dev_t* me, DS3234_Time_t* time)
{


    // Đọc các thanh ghi
    uint8_t hours ;
    uint8_t year;
	DS3234_read_register(me, DS3234_REG_HOURS, &hours);
    DS3234_read_register(me, DS3234_REG_SECONDS,&time->seconds);
    DS3234_read_register(me, DS3234_REG_MINUTES, &time->minutes);
    DS3234_read_register(me, DS3234_REG_DAY, &time->day);
    DS3234_read_register(me, DS3234_REG_DATE, &time->date);
    DS3234_read_register(me, DS3234_REG_MONTH, &time->month);
    DS3234_read_register(me, DS3234_REG_YEAR, &year) ; // Giả sử thế kỷ 21
    time->year = year + 2000;
    // Xử lý chế độ 12/24 giờ
    if (hours & (1 << 6)) { // Chế độ 12 giờ
        time->is_pm = (hours & (1 << 5)) ? 1 : 0; // Kiểm tra bit AM/PM
        time->hours = DS3234_BCDToDec(hours & 0x1F); // Lấy giá trị giờ
        me->hourMode = 1;
    } else { // Chế độ 24 giờ
        time->is_pm = 0;
        time->hours = DS3234_BCDToDec(hours & 0x3F);
        me->hourMode = 0;
    }
    time->seconds = DS3234_BCDToDec(time->seconds);
    time->minutes = DS3234_BCDToDec(time->minutes);
    time->day = DS3234_BCDToDec(time->day);
    time->date = DS3234_BCDToDec(time->date);
    time->month = DS3234_BCDToDec(time->month);
}

/**
 * @brief Chuyển đổi chế độ giờ (12/24 giờ) của DS3234
 * @param me Con trỏ tới cấu trúc DS3234_Dev_t
 * @param mode 0: 24 giờ, 1: 12 giờ
 */
void DS3234_SetHourMode(DS3234_Dev_t* me, uint8_t mode)
{


    uint8_t hour_reg ;
    DS3234_read_register(me, DS3234_REG_HOURS,&hour_reg);
    if (mode == 1) {
        hour_reg |= (1 << 6); // Đặt bit 6 cho chế độ 12 giờ
    } else {
        hour_reg &= ~(1 << 6); // Xóa bit 6 cho chế độ 24 giờ
    }
    DS3234_write_register(me, DS3234_REG_HOURS, hour_reg);
    me->hourMode = mode;
}

/**
 * @brief Cấu hình chế độ ngõ ra và tần số sóng vuông của DS3234
 * @param me Con trỏ tới cấu trúc DS3234_Dev_t
 * @param mode 0: sóng vuông, 1: ngắt báo thức
 * @param sqw_freq Tần số sóng vuông: 0 (1Hz), 1 (1.024kHz), 2 (4.096kHz), 3 (8.192kHz)
 */
void DS3234_SetOutputMode(DS3234_Dev_t* me, uint8_t mode, uint8_t sqw_freq)
{


    uint8_t control_reg ;
    DS3234_read_register(me, DS3234_REG_CONTROL,&control_reg);
    if (mode == 0) { // Sóng vuông
        control_reg &= ~(1 << 2); // Xóa bit INTCN
        control_reg &= ~(3 << 3); // Xóa bit RS2, RS1
        control_reg |= (sqw_freq & 0x03) << 3; // Đặt tần số
    } else { // Ngắt báo thức
        control_reg |= (1 << 2); // Đặt bit INTCN
    }
    DS3234_write_register(me, DS3234_REG_CONTROL, control_reg);
    me->ui8OutputMode = mode;
    me->ui8SqwFreq = sqw_freq & 0x03;
}

/**
 * @brief Chuyển đổi từ thập phân sang BCD
 * @param dec Giá trị thập phân (0-99)
 * @return Giá trị BCD
 */
uint8_t DS3234_DecToBCD(uint8_t dec)
{
    return ((dec / 10) << 4) | (dec % 10);
}

/**
 * @brief Chuyển đổi từ BCD sang thập phân
 * @param bcd Giá trị BCD
 * @return Giá trị thập phân
 */
uint8_t DS3234_BCDToDec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
