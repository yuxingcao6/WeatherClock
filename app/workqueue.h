#ifndef __APP_WORKQUEUE_H__
#define __APP_WORKQUEUE_H__

typedef void (*work_t)(void *param);

void workqueue_init(void);
void workqueue_run(work_t work, void *param);

#endif /* __APP_WORKQUEUE_H__ */
