/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */



#ifndef MICROPY_INCLUDED_HI3861_MPTHREADPORT_H
#define MICROPY_INCLUDED_HI3861_MPTHREADPORT_H

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/semphr.h"
// #include "freertos/queue.h"
#include "los_task_pri.h"
#include "cmsis_os2.h" 
#include "los_mux.h"

typedef struct _mp_thread_mutex_t {
	int8_t flag;
    UINT32 handle;
} mp_thread_mutex_t;



typedef struct _mp_thread_sem_t {
    osSemaphoreId_t sem_handle;
} mp_thread_sem_t;



void mp_thread_init(void *stack, uint32_t stack_len);
void mp_thread_gc_others(void);
void mp_thread_deinit(void);

#endif // MICROPY_INCLUDED_ESP32_MPTHREADPORT_H
