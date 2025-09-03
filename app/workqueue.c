#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "workqueue.h"

typedef struct
{
    work_t work;
    void *param;
} work_message_t;

static QueueHandle_t work_msg_queue;

static void work_func(void *param)
{
    work_message_t msg;
    
    while (1)
    {
        xQueueReceive(work_msg_queue, &msg, portMAX_DELAY);
        msg.work(msg.param);
    }
}

void workqueue_init(void)
{
    work_msg_queue = xQueueCreate(16, sizeof(work_message_t));
    configASSERT(work_msg_queue);
    xTaskCreate(work_func, "workqueue", 1024, NULL, 5, NULL);
}

void workqueue_run(work_t work, void *param)
{
    configASSERT(work_msg_queue);
    work_message_t msg = { work, param };
    xQueueSend(work_msg_queue, &msg, portMAX_DELAY);
}
