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




#ifndef PZ_QUEUE_H
#define PZ_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "py/mpconfig.h"
#include "py/obj.h"
#include "los_mux.h"

#define elem uint8_t

typedef struct queue {
    elem *buf;
    int32_t front;
    int32_t rear;
    int32_t buf_len;
	int32_t msg_len;
	UINT32 mux; 
}Msg_Queue_t, *Msg_Pqueue_t;





void Msg_Queue_Clean(Msg_Pqueue_t queue);
int Msg_Queue_Init(Msg_Pqueue_t queue,int buf_len);
int Is_FullQueue(Msg_Pqueue_t queue_q);
int Queue_Residue(Msg_Pqueue_t queue_q);

int In_Queue(Msg_Pqueue_t queue_q , elem value);
int Isempty_Queue(Msg_Pqueue_t queue_q);
int Out_Queue(Msg_Pqueue_t queue_q , elem *value);
void Bianli_A(Msg_Pqueue_t queue_q);
int Msg_Queue_Append(Msg_Pqueue_t queue_q, uint8_t *buf, int len);
int Msg_Queue_Dequeue(Msg_Pqueue_t queue_q, uint8_t *buf, int len);
int Msg_Queue_Append_Lock(Msg_Pqueue_t queue_q, uint8_t *buf, int len);
int Msg_Queue_Dequeue_Lock(Msg_Pqueue_t queue_q, uint8_t *buf, int len);






#endif

