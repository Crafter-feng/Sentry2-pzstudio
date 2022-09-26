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





#include "pz_queue.h"



int Msg_Queue_Init(Msg_Pqueue_t queue,int buf_len){
	queue->buf = malloc(buf_len*sizeof(uint8_t));
	if(queue->buf==NULL){
		return -1;
	}
	queue->buf_len = buf_len;
	queue->msg_len = 0;
	queue->front = 0;
	queue->rear = 0;
    LOS_MuxCreate(&queue->mux);
	return 0;
}










inline int Is_FullQueue(Msg_Pqueue_t queue_q)
{
    if((queue_q->rear +1)%queue_q->buf_len == queue_q->front)
    {
        return 1;
    }else
        return 0;
}



int Queue_Residue(Msg_Pqueue_t queue_q){
	LOS_MuxPend(queue_q->mux, LOS_WAIT_FOREVER);
	int len = (queue_q->buf_len-queue_q->msg_len-1);
	LOS_MuxPost(queue_q->mux);
	return len;
}



inline int In_Queue(Msg_Pqueue_t queue_q , elem value)
{
	if(queue_q->buf==NULL || queue_q->buf_len == 0){
		return -1;
	}
    if(Is_FullQueue(queue_q) != 1)        //队列未满
    {
        queue_q->buf[queue_q->rear] = value;
        queue_q->rear = (queue_q->rear + 1)%queue_q->buf_len ;    //尾指针偏移
        queue_q->msg_len++;
        return 0;
    }else{
		return -1;
	}
}







inline int Isempty_Queue(Msg_Pqueue_t queue_q)
{
    if(queue_q->front == queue_q->rear)
    {
        return 1;
    }else{
        return 0;
    }
}







inline int Out_Queue(Msg_Pqueue_t queue_q , elem *value)
{
	if(queue_q->buf == NULL || queue_q->buf_len == 0){
		return -1;
	}
	if(Isempty_Queue(queue_q) != 1)        //队列未空
	{
		*value = queue_q->buf [queue_q->front];
		queue_q->front = (queue_q->front + 1)%queue_q->buf_len ;
		queue_q->msg_len--;
		return 0;
	}else{
		return -1;
	}
}





void Bianli_A(Msg_Pqueue_t queue_q)
{
    if(Isempty_Queue(queue_q) != 1)
    {
        int ret=queue_q->front;
        while(ret != queue_q->rear)
        {
            //printf("%d  ",queue_q->buf[ret]);
            ret=(ret+1)%queue_q->buf_len;
        }
    }
}







int Msg_Queue_Append(Msg_Pqueue_t queue_q, uint8_t *buf, int len){
	int ret = 0;
	for(int i=0; i<len; i++){
		ret = In_Queue(queue_q,buf[i]);
	}
	return ret;
}






int Msg_Queue_Dequeue(Msg_Pqueue_t queue_q, uint8_t *buf, int len){
	int cnt = 0;
	while(cnt<len && Out_Queue(queue_q,buf+cnt)==0){
		cnt ++;
	}
	return cnt;
}





int Msg_Queue_Dequeue_Lock(Msg_Pqueue_t queue_q, uint8_t *buf, int len){
	int ret =0;
	//portENTER_CRITICAL(&pz_queue_spinlock);
	//xSemaphoreTake(queue_q->mux, portMAX_DELAY);
	LOS_MuxPend(queue_q->mux, LOS_WAIT_FOREVER);
	ret = Msg_Queue_Dequeue(queue_q,buf, len);
	LOS_MuxPost(queue_q->mux);
	//xSemaphoreGive(queue_q->mux);
	//portEXIT_CRITICAL(&pz_queue_spinlock);
	return ret;
}





int Msg_Queue_Append_Lock(Msg_Pqueue_t queue_q, uint8_t *buf, int len){
	int ret =0;
	//portENTER_CRITICAL(&pz_queue_spinlock);
	//xSemaphoreTake(queue_q->mux, portMAX_DELAY);
	LOS_MuxPend(queue_q->mux, LOS_WAIT_FOREVER);
	ret = Msg_Queue_Append(queue_q, buf, len);
	LOS_MuxPost(queue_q->mux);
	//xSemaphoreGive(queue_q->mux);
	//portEXIT_CRITICAL(&pz_queue_spinlock);
	return ret;
}

void Msg_Queue_Clean(Msg_Pqueue_t queue){
	//portENTER_CRITICAL(&pz_queue_spinlock);
	//xSemaphoreTake(queue->mux, portMAX_DELAY);
	LOS_MuxPend(queue->mux, LOS_WAIT_FOREVER);
	if(queue->buf!= NULL){
		queue->front = 0;
		queue->rear = 0;
		queue->msg_len = 0;
		memset(queue->buf,0,queue->buf_len);
	}
	LOS_MuxPost(queue->mux);
	//xSemaphoreGive(queue->mux);
	//portEXIT_CRITICAL(&pz_queue_spinlock);
}




