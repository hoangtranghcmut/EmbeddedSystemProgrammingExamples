#ifndef DS3234_H
#define DS3234_H

#include "do.h"
#include <spi_io.h>

// Định nghĩa các thanh ghi của DS3234
#define DS3234_REG_SECONDS      0x00
#define DS3234_REG_MINUTES      0x01
#define DS3234_REG_HOURS        0x02
#define DS3234_REG_DAY          0x03
#define DS3234_REG_DATE         0x04
#define DS3234_REG_MONTH        0x05
#define DS3234_REG_YEAR         0x06
#define DS3234_REG_CONTROL      0x0E
#define DS3234_REG_STATUS       0x0F

// Định nghĩa các chế độ cho DS3234
#define DS3234_HOUR_MODE_24H    0  // Chế độ 24 giờ
#define DS3234_HOUR_MODE_12H    1  // Chế độ 12 giờ
#define DS3234_OUTPUT_MODE_SQW  0  // Chế độ sóng vuông
#define DS3234_OUTPUT_MODE_INT  1  // Chế độ ngắt báo thức
#define DS3234_SQW_FREQ_1HZ     0  // Tần số sóng vuông 1 Hz
#define DS3234_SQW_FREQ_1024HZ  1  // Tần số sóng vuông 1.024 kHz
#define DS3234_SQW_FREQ_4096HZ  2  // Tần số sóng vuông 4.096 kHz
#define DS3234_SQW_FREQ_8192HZ  3  // Tần số sóng vuông 8.192 kHz

// Cấu trúc thời gian
typedef struct {
    uint8_t seconds;    // 0-59
    uint8_t minutes;    // 0-59
    uint8_t hours;      // 0-23 (24h) hoặc 1-12 (12h)
    uint8_t day;        // 1-7 (Sunday = 1)
    uint8_t date;       // 1-31
    uint8_t month;      // 1-12
    uint16_t year;      // e.g., 2025
    uint8_t is_pm;      // 0: AM, 1: PM (chỉ dùng trong chế độ 12h)
} DS3234_Time_t;

// Cấu trúc khởi tạo cho DS3234
typedef struct {
    SPI_Io_t *	spiBus;
    do_t	 *	csPin;
    uint8_t 	hourMode;          // DS3234_HOUR_MODE_24H hoặc DS3234_HOUR_MODE_12H
    uint8_t     ui8OutputMode;     // DS3234_OUTPUT_MODE_SQW hoặc DS3234_OUTPUT_MODE_INT
    uint8_t 	ui8SqwFreq;       // DS3234_SQW_FREQ_1HZ, DS3234_SQW_FREQ_1024HZ, DS3234_SQW_FREQ_4096HZ, hoặc DS3234_SQW_FREQ_8192HZ
} DS3234_Init_t;

// Instance structure cho DS3234
typedef struct {
    SPI_Io_t *	spiBus;
    do_t	*	csPin;
    uint8_t 	hourMode;          // DS3234_HOUR_MODE_24H hoặc DS3234_HOUR_MODE_12H
    uint8_t 	ui8OutputMode;     // DS3234_OUTPUT_MODE_SQW hoặc DS3234_OUTPUT_MODE_INT
    uint8_t 	ui8SqwFreq;       // DS3234_SQW_FREQ_1HZ, DS3234_SQW_FREQ_1024HZ, DS3234_SQW_FREQ_4096HZ, hoặc DS3234_SQW_FREQ_8192HZ
    uint8_t 	initialized;   // 0: chưa khởi tạo, 1: đã khởi tạo
} DS3234_Dev_t;

// Nguyên mẫu hàm
uint32_t DS3234_Init(DS3234_Dev_t* me, const DS3234_Init_t* const init);
void DS3234_WriteRegister(DS3234_Dev_t* dev, uint8_t reg, uint8_t value);
uint8_t DS3234_ReadRegister(DS3234_Dev_t* dev, uint8_t reg);
void DS3234_SetTime(DS3234_Dev_t* dev, DS3234_Time_t* time);
void DS3234_GetTime(DS3234_Dev_t* dev, DS3234_Time_t* time);
void DS3234_SetHourMode(DS3234_Dev_t* dev, uint8_t mode); // Chuyển đổi 12/24 giờ
void DS3234_SetOutputMode(DS3234_Dev_t* dev, uint8_t mode, uint8_t sqw_freq); // Cấu hình ngõ ra và tần số sóng vuông
uint8_t DS3234_DecToBCD(uint8_t dec);
uint8_t DS3234_BCDToDec(uint8_t bcd);

#endif // DS3234_H
