//*****************************************************************************
//
// scheduler.c - Một bộ lập lịch tác vụ đơn giản
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "scheduler.h"
//*****************************************************************************
//
//! \addtogroup scheduler_api
//! @{
//
//*****************************************************************************

static volatile uint32_t g_ui32SchedulerTickCount;
extern uint32_t SystemCoreClock;
static uint32_t SchedulerTickPerSecond = 1000;
//*****************************************************************************
//
//! Xử lý ngắt SysTick thay cho mô-đun lập lịch.
//!
//! Các ứng dụng sử dụng mô-đun lập lịch phải đảm bảo rằng hàm này được gắn
//! vào vector ngắt SysTick.
//!
//! \return Không có giá trị trả về.
//
//*****************************************************************************
void
scheduler_systick_int_handler(void)
{
    g_ui32SchedulerTickCount++;
}

//*****************************************************************************
//
//! Khởi tạo bộ lập lịch tác vụ.
//!
//! \param ui32TicksPerSecond thiết lập tần suất cơ bản của ngắt SysTick
//! được sử dụng bởi bộ lập lịch để xác định khi nào gọi các hàm tác vụ.
//!
//! Hàm này phải được gọi trong quá trình khởi động ứng dụng để cấu hình
//! bộ định thời SysTick. Bộ định thời này được mô-đun lập lịch sử dụng để
//! xác định khi nào gọi các hàm được cung cấp trong mảng g_pTaskTable.
//!
//! Người gọi chịu trách nhiệm đảm bảo rằng scheduler_systick_int_handler()
//! đã được cài đặt vào vector SYSTICK trong bảng vector và cũng phải đảm bảo
//! rằng các ngắt được bật ở cấp CPU.
//!
//! Lưu ý rằng hàm này không khởi động việc bộ lập lịch gọi các hàm đã cấu hình.
//! Tất cả các cuộc gọi hàm được thực hiện trong ngữ cảnh của các lần gọi sau
//! đến scheduler_run(). Hàm này chỉ cấu hình ngắt SysTick được sử dụng bởi
//! bộ lập lịch để xác định thời gian hệ thống hiện tại.
//!
//! \return Không có giá trị trả về.
//
//*****************************************************************************
void
scheduler_init(uint32_t TicksPerSecond)
{
  /* Cấu hình SysTick để có ngắt trong khoảng thời gian 1ms */
  SysTick->LOAD  = (uint32_t)((SystemCoreClock / TicksPerSecond) - 1UL);  /* thiết lập thanh ghi reload */
  SysTick->VAL   = 0UL;                                       /* Nạp giá trị bộ đếm SysTick */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk |
                   SysTick_CTRL_TICKINT_Msk;                   /* Bật ngắt bộ định thời SysTick */
  SchedulerTickPerSecond = TicksPerSecond;
}
//*****************************************************************************
//
//! Lấy số tick.
//!
//! \return Số tick mỗi giây.
//
//*****************************************************************************
uint32_t
scheduler_get_tick()
{
    return SchedulerTickPerSecond;
}
//*****************************************************************************
//
//! Yêu cầu bộ lập lịch cập nhật bảng tác vụ của nó và thực hiện các
//! cuộc gọi đến các hàm cần được gọi.
//!
//! Hàm này phải được gọi định kỳ bởi client để cho phép bộ lập lịch
//! thực hiện các cuộc gọi đến các hàm tác vụ đã cấu hình nếu đến thời điểm
//! của chúng. Cuộc gọi phải được thực hiện ít nhất với tần suất bằng với
//! tác vụ thường xuyên nhất được cấu hình trong mảng g_pTaskTable.
//!
//! Mặc dù bộ lập lịch sử dụng ngắt SysTick, tất cả các cuộc gọi đến các hàm
//! được cấu hình trong \e g_pTaskTable được thực hiện trong ngữ cảnh
//! của scheduler_run().
//!
//! \return Không có giá trị trả về.
//
//*****************************************************************************
void
scheduler_run(void)
{
    uint32_t ui32Loop;
    tSchedulerTask *pi16Task;

    //
    // Duyệt qua từng tác vụ trong bảng tác vụ.
    //
    for(ui32Loop = 0; ui32Loop < g_ui32SchedulerNumTasks; ui32Loop++)
    {
        //
        // Lấy con trỏ đến thông tin của tác vụ.
        //
        pi16Task = &g_pTaskTable[ui32Loop];

        //
        // Tác vụ này có đang hoạt động không và đã đến thời điểm gọi hàm của nó chưa?
        //
        if(pi16Task->bActive &&
           (scheduler_elapsed_ticks_get(pi16Task->ui32LastCall) >=
            pi16Task->ui32FrequencyTicks))
        {
            //
            // Ghi nhớ thời điểm mà chúng ta thực hiện cuộc gọi hàm.
            //
            pi16Task->ui32LastCall = g_ui32SchedulerTickCount;

            //
            // Gọi hàm tác vụ, truyền tham số đã cung cấp.
            //
            pi16Task->pfnFunction();
        }
    }
}

//*****************************************************************************
//
//! Kích hoạt một tác vụ và cho phép bộ lập lịch gọi nó định kỳ.
//!
//! \param ui32Index là chỉ số của tác vụ cần kích hoạt trong mảng toàn cục
//! \e g_pTaskTable.
//! \param bRunNow là \b true nếu tác vụ sẽ được chạy trong lần gọi tiếp theo
//! đến scheduler_run() hoặc \b false nếu phải chờ một chu kỳ đầy đủ trước khi
//! tác vụ được chạy.
//!
//! Hàm này đánh dấu một trong các tác vụ đã cấu hình là được kích hoạt và khiến
//! scheduler_run() gọi tác vụ đó định kỳ. Người gọi có thể chọn để tác vụ đã
//! kích hoạt chạy ngay lần gọi scheduler_run() tiếp theo hoặc chờ một chu kỳ
//! đầy đủ của tác vụ trước khi thực hiện cuộc gọi đầu tiên.
//!
//! \return Không có giá trị trả về.
//
//*****************************************************************************
void
scheduler_task_enable(uint32_t ui32Index, bool bRunNow)
{
    //
    // Chỉ số tác vụ được truyền có hợp lệ không?
    //
    if(ui32Index < g_ui32SchedulerNumTasks)
    {
        //
        // Có - đánh dấu tác vụ là hoạt động.
        //
        g_pTaskTable[ui32Index].bActive = true;

        //
        // Thiết lập thời điểm gọi lần cuối để đảm bảo rằng hàm được gọi hoặc
        // trong lần gọi bộ lập lịch tiếp theo hoặc sau số tick mong muốn tùy
        // thuộc vào giá trị của tham số bRunNow.
        //
        if(bRunNow)
        {
            //
            // Khiến tác vụ chạy trong lần gọi scheduler_run() tiếp theo.
            //
            g_pTaskTable[ui32Index].ui32LastCall =
                (g_ui32SchedulerTickCount -
                 g_pTaskTable[ui32Index].ui32FrequencyTicks);
        }
        else
        {
            //
            // Khiến tác vụ chạy sau một chu kỳ thời gian đầy đủ.
            //
            g_pTaskTable[ui32Index].ui32LastCall =
                g_ui32SchedulerTickCount;
        }
    }
}

//*****************************************************************************
//
//! Vô hiệu hóa một tác vụ và ngăn bộ lập lịch gọi nó.
//!
//! \param ui32Index là chỉ số của tác vụ cần vô hiệu hóa trong mảng toàn cục
//! \e g_pTaskTable.
//!
//! Hàm này đánh dấu một trong các tác vụ đã cấu hình là không hoạt động và ngăn
//! scheduler_run() gọi nó. Tác vụ có thể được kích hoạt lại bằng cách gọi
//! scheduler_task_enable().
//!
//! \return Không có giá trị trả về.
//
//*****************************************************************************
void
scheduler_task_disable(uint32_t ui32Index)
{
    //
    // Chỉ số tác vụ được truyền có hợp lệ không?
    //
    if(ui32Index < g_ui32SchedulerNumTasks)
    {
        //
        // Có - đánh dấu tác vụ là không hoạt động.
        //
        g_pTaskTable[ui32Index].bActive = false;
    }
}

//*****************************************************************************
//
//! Trả về thời gian hệ thống hiện tại tính bằng số tick kể từ khi bật nguồn.
//!
//! Hàm này có thể được gọi bởi client để lấy thời gian hệ thống hiện tại.
//! Giá trị trả về là số lượng tick đã trôi qua kể từ khi hệ thống khởi động lần cuối.
//!
//! \return Số tick kể từ lần khởi động cuối cùng.
//
//*****************************************************************************
uint32_t
scheduler_tick_count_get(void)
{
    return(g_ui32SchedulerTickCount);
}

//*****************************************************************************
//
//! Trả về số tick đã trôi qua kể từ số tick được cung cấp.
//!
//! \param ui32TickCount là số tick để xác định thời gian đã trôi qua.
//!
//! Hàm này có thể được gọi bởi client để xác định thời gian đã trôi qua kể từ
//! một số tick cụ thể được cung cấp trong tham số \e ui32TickCount. Hàm này
//! tính đến việc vòng lại của bộ đếm tick toàn cục và giả định rằng số tick
//! được cung cấp luôn đại diện cho một thời điểm trong quá khứ. Giá trị trả về
//! sẽ không chính xác nếu bộ đếm tick đã vòng lại nhiều hơn một lần kể từ
//! \e ui32TickCount đã truyền. Vì vậy, vui lòng không sử dụng hàm này nếu bạn
//! đang xử lý các khoảng thời gian chờ vượt quá 497 ngày (giả sử sử dụng
//! chu kỳ tick 10ms).
//!
//! \return Số tick đã trôi qua kể từ số tick được cung cấp.
//
//*****************************************************************************
uint32_t
scheduler_elapsed_ticks_get(uint32_t ui32TickCount)
{
    //
    // Xác định phép tính dựa trên việc bộ đếm tick toàn cục có vòng lại
    // kể từ ui32TickCount được truyền hay không.
    //
    return(scheduler_elapsed_ticks_calc(ui32TickCount, g_ui32SchedulerTickCount));
}

//*****************************************************************************
//
//! Trả về số tick đã trôi qua giữa hai thời điểm.
//!
//! \param ui32TickStart là số tick hệ thống cho thời điểm bắt đầu của khoảng thời gian.
//! \param ui32TickEnd là số tick hệ thống cho thời điểm kết thúc của khoảng thời gian.
//!
//! Hàm này có thể được gọi bởi client để xác định số tick đã trôi qua giữa
//! các số tick bắt đầu và kết thúc được cung cấp. Hàm này tính đến các trường hợp
//! vòng lại khi số tick kết thúc thấp hơn số tick bắt đầu, giả định rằng số tick
//! kết thúc luôn đại diện cho một thời điểm sau số tick bắt đầu.
//!
//! \return Số tick đã trôi qua giữa số tick bắt đầu và kết thúc được cung cấp.
//
//*****************************************************************************
uint32_t
scheduler_elapsed_ticks_calc(uint32_t ui32TickStart, uint32_t ui32TickEnd)
{
    return((ui32TickEnd > ui32TickStart) ? (ui32TickEnd - ui32TickStart) :
           ((0xFFFFFFFF - ui32TickStart) + ui32TickEnd + 1));
}

//*****************************************************************************
//
// Đóng nhóm Doxygen.
//! @}
//
//*****************************************************************************
