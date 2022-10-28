/*************************************************************************
 *
 * Copyright (C) 2018-2020 Ruilin Peng (Nick) <pymumu@gmail.com>.
 *
 * smartdns is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * smartdns is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
 

#ifndef _KOS_LIST_H_
#define _KOS_LIST_H_


#define container_of(ptr, type, member) \
	((type *)(((unsigned char *)(ptr)) - ((unsigned int)(&((type *)0)->member))))


struct list_head {
	struct list_head *next, *prev;
};


/* 获得type类型结构体地址 */
#define kos_list_entry(ptr, type, member) \
	container_of(ptr, type, member)


#define kos_list_first_entry(ptr, type, member) \
	container_of((ptr)->next, type, member)

/* 静态创建list_head */

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)


/* 动态初始化list_head */
static __inline void list_head_init(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}


/* 添加节点 */
static __inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}



/* 新节点在head之后 */
static __inline void list_add(struct list_head *head, struct list_head *new)
{
	__list_add(new, head, head->next);
}


/* 新节点在head之前 */
static __inline void list_add_tail(struct list_head *head, struct list_head *new)
{
	__list_add(new, head->prev, head);
}


/* 删除节点 */
static __inline void __list_delete(struct list_head *prev, struct list_head *next)
{
	next->prev = prev;
	prev->next = next;
}



static __inline void list_delete(struct list_head *del)
{
	__list_delete(del->prev, del->next);
}



static __inline void list_delete_init(struct list_head *node)
{
	list_delete(node);
	list_head_init(node);
}



/* 判断节点是否为空 */
static __inline int list_empty(const struct list_head *head)
{
	return (head->next == head);
}


/* 遍历双向链表 */
#define list_for_each(pos, head) 			\
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, nl, head) 			\
    for (pos = (head)->next, nl = pos->next; pos != (head); pos = nl, nl = pos->next)


#endif
