//*****************************************************************************
//
// scheduler.h - Tiêu đề công khai cho mô-đun lập lịch chức năng định thời đơn giản.
//
// Bản quyền (c) 2010-2014 Texas Instruments Incorporated. Tất cả quyền được bảo lưu.
// Thỏa thuận cấp phép phần mềm
//
// Texas Instruments (TI) cung cấp phần mềm này để sử dụng duy nhất và
// độc quyền trên các sản phẩm vi điều khiển của TI. Phần mềm này thuộc sở hữu
// của TI và/hoặc các nhà cung cấp của TI, và được bảo vệ theo các luật bản quyền
// hiện hành. Bạn không được kết hợp phần mềm này với phần mềm mã nguồn mở
// "lan truyền" để tạo thành một chương trình lớn hơn.
//
// PHẦN MỀM NÀY ĐƯỢC CUNG CẤP "NGUYÊN TRẠNG" VÀ VỚI TẤT CẢ CÁC LỖI.
// KHÔNG CÓ BẢO HÀNH, DÙ RÕ RÀNG, NGỤ Ý HAY THEO LUẬT ĐỊNH, BAO GỒM NHƯNG
// KHÔNG GIỚI HẠN Ở BẢO HÀNH VỀ TÍNH THƯƠNG MẠI VÀ SỰ PHÙ HỢP CHO MỤC ĐÍCH
// CỤ THỂ ÁP DỤNG CHO PHẦN MỀM NÀY. TI SẼ KHÔNG CHỊU TRÁCH NHIỆM DƯỚI BẤT KỲ
// HOÀN CẢNH NÀO ĐỐI VỚI CÁC THIỆT HẠI ĐẶC BIỆT, NGẪU NHIÊN HOẶC HẬU QUẢ,
// VÌ BẤT KỲ LÝ DO NÀO.
//
// Đây là một phần của phiên bản 2.1.0.12573 của Thư viện Tiện ích Tiva.
//
//*****************************************************************************
#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include <stdbool.h>
#include <stdint.h>
//*****************************************************************************
//
// Nếu biên dịch với trình biên dịch C++, đảm bảo tất cả các định nghĩa trong tiêu đề
// này có liên kết kiểu C.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup scheduler_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Nguyên mẫu của một hàm mà bộ lập lịch có thể gọi định kỳ.
//
//*****************************************************************************
typedef void (*tSchedulerFunction)(void);

//*****************************************************************************
//
//! Cấu trúc định nghĩa một hàm mà bộ lập lịch sẽ gọi định kỳ.
//
//*****************************************************************************
typedef struct
{
    //
    //! Con trỏ đến hàm sẽ được gọi định kỳ bởi bộ lập lịch.
    //
    void (*pfnFunction)();

    //
    //! Tần suất gọi hàm, được biểu diễn bằng số tick hệ thống.
    //! Nếu giá trị này là 0, hàm sẽ được gọi trong mỗi lần gọi scheduler_run.
    //
    uint32_t ui32FrequencyTicks;

    //
    //! Thời điểm tick khi hàm này được gọi lần cuối. Trường này được cập nhật
    //! bởi bộ lập lịch.
    //
    uint32_t ui32LastCall;

    //
    //! Cờ chỉ định liệu tác vụ này có đang hoạt động hay không. Nếu true, hàm
    //! sẽ được gọi định kỳ. Nếu false, hàm bị vô hiệu hóa và sẽ không được gọi.
    //
    bool bActive;
}
tSchedulerTask;

//*****************************************************************************
//
//! Bảng toàn cục này phải được điền bởi client và chứa thông tin về
//! mỗi hàm mà bộ lập lịch sẽ gọi.
//
//*****************************************************************************
extern tSchedulerTask g_pTaskTable[];

//*****************************************************************************
//
//! Biến toàn cục này phải được xuất bởi client. Nó chứa số lượng mục
//! trong mảng g_pTaskTable.
//
//*****************************************************************************
extern uint32_t g_ui32SchedulerNumTasks;

//*****************************************************************************
//
// Đóng nhóm Doxygen.
//! @}
//
//*****************************************************************************

//*****************************************************************************
//
// Các nguyên mẫu hàm công khai
//
//*****************************************************************************
extern void scheduler_systick_int_handler(void);
extern void scheduler_init(uint32_t ui32TicksPerSecond);
extern void scheduler_run(void);
extern void scheduler_task_enable(uint32_t ui32Index, bool bRunNow);
extern void scheduler_task_disable(uint32_t ui32Index);
extern uint32_t scheduler_tick_count_get(void);
extern uint32_t scheduler_elapsed_ticks_get(uint32_t ui32TickCount);
extern uint32_t scheduler_elapsed_ticks_calc(uint32_t ui32TickStart,
                                               uint32_t ui32TickEnd);
extern uint32_t scheduler_get_tick();

//*****************************************************************************
//
// Đánh dấu phần kết thúc của liên kết C cho các trình biên dịch C++.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __ SCHEDULER_H_
