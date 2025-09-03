#ifndef __FREERTOS_CONFIG_H__
#define __FREERTOS_CONFIG_H__

/* Here is a good place to include header files that are required across
   your application. */
#include "stm32f4xx.h"
extern uint32_t SystemCoreClock;

#define configUSE_PREEMPTION                                        1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION                     1
#define configUSE_TICKLESS_IDLE                                     0
#define configCPU_CLOCK_HZ                                          SystemCoreClock
#define configTICK_RATE_HZ                                          1000
#define configMAX_PRIORITIES                                        10
#define configMINIMAL_STACK_SIZE                                    128
#define configMAX_TASK_NAME_LEN                                     16
#define configUSE_16_BIT_TICKS                                      0
#define configIDLE_SHOULD_YIELD                                     1
#define configUSE_TASK_NOTIFICATIONS                                1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES                       3
#define configUSE_MUTEXES                                           1
#define configUSE_RECURSIVE_MUTEXES                                 1
#define configUSE_COUNTING_SEMAPHORES                               1
#define configUSE_ALTERNATIVE_API                                   0 /* Deprecated! */
#define configQUEUE_REGISTRY_SIZE                                   10
#define configUSE_QUEUE_SETS                                        1
#define configUSE_TIME_SLICING                                      1
#define configUSE_NEWLIB_REENTRANT                                  0
#define configENABLE_BACKWARD_COMPATIBILITY                         0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS                     5
#define configUSE_MINI_LIST_ITEM                                    1
#define configSTACK_DEPTH_TYPE                                      uint32_t
#define configMESSAGE_BUFFER_LENGTH_TYPE                            size_t

/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION                             0
#define configSUPPORT_DYNAMIC_ALLOCATION                            1
#define configTOTAL_HEAP_SIZE                                       (92 * 1024)
#define configAPPLICATION_ALLOCATED_HEAP                            0

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK                                 0
#define configUSE_TICK_HOOK                                 0
#define configCHECK_FOR_STACK_OVERFLOW                      1
#define configUSE_MALLOC_FAILED_HOOK                        1
#define configUSE_DAEMON_TASK_STARTUP_HOOK                  0
#define configUSE_SB_COMPLETED_CALLBACK                     0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS                       0
#define configUSE_TRACE_FACILITY                            0
#define configUSE_STATS_FORMATTING_FUNCTIONS                0

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES                               0
#define configMAX_CO_ROUTINE_PRIORITIES                     1

/* Software timer related definitions. */
#define configUSE_TIMERS                                    1
#define configTIMER_TASK_PRIORITY                           (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH                            32
#define configTIMER_TASK_STACK_DEPTH                        configMINIMAL_STACK_SIZE

/* Interrupt nesting behaviour configuration. */
#define configPRIO_BITS                         4
#define configKERNEL_INTERRUPT_PRIORITY         (15 << (8 - configPRIO_BITS))
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (5 << (8 - configPRIO_BITS))
#define configMAX_API_CALL_INTERRUPT_PRIORITY   configMAX_SYSCALL_INTERRUPT_PRIORITY

/* Define to trap errors during development. */
void vAssertCalled(const char *file, int line);
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_uxTaskGetStackHighWaterMark2    1
#define INCLUDE_xTaskGetIdleTaskHandle          1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTimerPendFunctionCall          0
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xTaskResumeFromISR              1

/* A header file that defines trace macro can be included here. */

#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler
#define vPortSVCHandler SVC_Handler

#endif /* FREERTOS_CONFIG_H */

