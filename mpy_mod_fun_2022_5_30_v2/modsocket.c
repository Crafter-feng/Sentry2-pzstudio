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




#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "net_demo.h"
#include "net_common.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "shared/netutils/netutils.h"

static char request[] = "Hello";
typedef struct _mp_obj_socket_t {
    mp_obj_base_t base;
    int sockfd;
} mp_obj_socket_t;
const mp_obj_type_t mp_type_socket;

MP_STATIC mp_obj_socket_t *socket_new(int sockfd) {
    mp_obj_socket_t *o = m_new_obj(mp_obj_socket_t);
    o->base.type = &mp_type_socket;
    o->sockfd = sockfd;
    // o->path = path;
    // int size = 0;
    // int flag = UtilsFileStat(path,&size);
    // o->size = size;
    return o;
}

mp_obj_t mp_socket_connect(mp_obj_t self_in, mp_obj_t addr_in) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(self_in);
    // get address
    if(self == NULL){
		mp_obj_new_int(-1);
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    size_t addr_len;
    // const char *addr_str = mp_obj_str_get_data(addr_in, &addr_len);
    // printf("addr = %s\n;",addr_str);
    uint8_t ip[4];
    mp_uint_t port = netutils_parse_inet_addr(addr_in, ip, NETUTILS_BIG);
    mp_obj_t *addr_items;
    mp_obj_get_array_fixed_n(addr_in, 2, &addr_items);
    const char *host = mp_obj_str_get_data(addr_items[0], &addr_len);
    // printf("addr = %s\n;",addr_str);
    // char *host = mp_obj_str_get_str(target_host);
    // char *port = mp_obj_get_int(target_port);
    
    // ssize_t retval = 0;
    // int sockfd = socket(AF_INET, SOCK_STREAM, 0); // TCP socket

    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;  // AF_INET表示IPv4协议
    serverAddr.sin_port = htons(port);  // 端口号，从主机字节序转为网络字节序
    if (inet_pton(AF_INET, host, &serverAddr.sin_addr) <= 0) {  // 将主机IP地址从“点分十进制”字符串 转化为 标准格式（32位整数）
        printf("inet_pton failed!\r\n");
		return mp_obj_new_int(-1);
        //return;
    }
	
    // 尝试和目标主机建立连接，连接成功会返回0 ，失败返回 -1
    if (connect(self->sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        printf("connect failed!\r\n");
		return mp_obj_new_int(-1);
        //return;
    }
    printf("connect to server %s success!\r\n", host);

    return mp_obj_new_int(0);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_socket_connect_obj, mp_socket_connect);


mp_obj_t mp_socket_newsocket(size_t n_args, const mp_obj_t *args) {
    if(n_args == 0){
        ssize_t retval = 0;
        int sockfd = socket(AF_INET, SOCK_STREAM, 0); // TCP socket
        return MP_OBJ_FROM_PTR(socket_new(sockfd));
    }else if(n_args == 2){
        ssize_t retval = 0;
        int sockfd = socket(mp_obj_get_int(args[0]), mp_obj_get_int(args[1]), 0); // TCP socket
        return MP_OBJ_FROM_PTR(socket_new(sockfd));
    }
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_VAR(mp_socket_newsocket_obj, 0, mp_socket_newsocket);

mp_obj_t mp_socket_send(mp_obj_t socket, mp_obj_t content) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);

	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    char *msg = mp_obj_str_get_str(content);
    ssize_t retval = send(self->sockfd, msg, strlen(msg), 0);
    return mp_obj_new_int(retval);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_socket_send_obj, mp_socket_send);


mp_obj_t mp_socket_recv(mp_obj_t socket) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    char *buf = (char*)malloc(sizeof(char)*128);
	if(buf!=NULL){
		memset(buf,0,128);
	    // char buf[128] = "";
	    int retval = recv(self->sockfd, buf, 128, 0);
	    mp_obj_t res = mp_obj_new_str(buf, retval);
	    free(buf);
		return res;
	}
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_socket_recv_obj, mp_socket_recv);

mp_obj_t mp_socket_close(mp_obj_t socket, mp_obj_t content) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    close(self->sockfd);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_socket_close_obj, mp_socket_close);


mp_obj_t mp_socket_bind(mp_obj_t socket, mp_obj_t addr_in) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    uint8_t ip[4];
    mp_uint_t port = netutils_parse_inet_addr(addr_in, ip, NETUTILS_BIG);
    struct sockaddr_in serverAddr = {0};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);  // 端口号，从主机字节序转为网络字节序
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // 允许任意主机接入， 0.0.0.0

    int retval = bind(self->sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); // 绑定端口
    return mp_obj_new_int(retval);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_socket_bind_obj, mp_socket_bind);

mp_obj_t mp_socket_listen(mp_obj_t socket, mp_obj_t count) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    int c = mp_obj_get_int(count);
    int ret = listen(self->sockfd, c);
    return mp_obj_new_int(ret);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_socket_listen_obj, mp_socket_listen);


mp_obj_t mp_socket_accept(mp_obj_t socket) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    int connfd = -1;
    struct sockaddr_in clientAddr = {0};
    socklen_t clientAddrLen = sizeof(clientAddr);
    connfd = accept(self->sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    return MP_OBJ_FROM_PTR(socket_new(connfd));
}
MP_DEFINE_CONST_FUN_OBJ_1(mp_socket_accept_obj, mp_socket_accept);


mp_obj_t mp_socket_sendto(mp_obj_t socket, mp_obj_t data_in, mp_obj_t addr_in) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
	if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    size_t addr_len;
    uint8_t ip[4];
    mp_uint_t port = netutils_parse_inet_addr(addr_in, ip, NETUTILS_BIG);
    mp_obj_t *addr_items;
    mp_obj_get_array_fixed_n(addr_in, 2, &addr_items);
    const char *host = mp_obj_str_get_data(addr_items[0], &addr_len);
    struct sockaddr_in toAddr = {0};
    toAddr.sin_family = AF_INET;
    toAddr.sin_port = htons(port); // 端口号，从主机字节序转为网络字节序
    if (inet_pton(AF_INET, host, &toAddr.sin_addr) <= 0) { // 将主机IP地址从“点分十进制”字符串 转化为 标准格式（32位整数）
        printf("inet_pton failed!\r\n");
        return mp_const_none;
    }
    char *msg = mp_obj_str_get_str(data_in);
    int retval = sendto(self->sockfd, msg, strlen(msg), 0, (struct sockaddr *)&toAddr, sizeof(toAddr));
    return mp_obj_new_int(retval);
}
MP_DEFINE_CONST_FUN_OBJ_3(mp_socket_sendto_obj, mp_socket_sendto);



mp_obj_t mp_socket_recvfrom(mp_obj_t socket, mp_obj_t len) {
    mp_obj_socket_t *self = MP_OBJ_TO_PTR(socket);
    if(self == NULL){
		return mp_const_none;
	}
	if(self->base.type!= &mp_type_socket){
		mp_raise_msg(&mp_type_TypeError,MP_ERROR_TEXT("socket type error"));
	}
    struct sockaddr_in fromAddr = {0};
    socklen_t fromLen = sizeof(fromAddr);
    int recvlen = mp_obj_get_int(len);
    char *response = (char*)malloc(sizeof(char)*recvlen);
    int retval = recvfrom(self->sockfd, response, recvlen, 0, (struct sockaddr *)&fromAddr, &fromLen);
    // return mp_obj_new_str(response, retval);
    free(response);
    return mp_obj_new_str(response, retval);
}
MP_DEFINE_CONST_FUN_OBJ_2(mp_socket_recvfrom_obj, mp_socket_recvfrom);






MP_STATIC mp_obj_t socket_setsockopt(size_t n_args, const mp_obj_t *args) {
    (void)n_args; // always 4
    //socket_obj_t *self = MP_OBJ_TO_PTR(args[0]);
	mp_obj_socket_t *self = MP_OBJ_TO_PTR(args[0]);
    int opt = mp_obj_get_int(args[2]);

    switch (opt) {
        // level: SOL_SOCKET
        case SO_REUSEADDR: {
            int val = mp_obj_get_int(args[3]);
            int ret = lwip_setsockopt(self->sockfd, SOL_SOCKET, opt, &val, sizeof(int));
            if (ret != 0) {
                mp_raise_OSError(errno);
            }
            break;
        }
		case SO_BROADCAST:{
			int val = mp_obj_get_int(args[3]);
            int ret = lwip_setsockopt(self->sockfd, SOL_SOCKET, opt, &val, sizeof(int));
			if (ret != 0) {
                mp_raise_OSError(errno);
            }
			break;
		}


        // level: IPPROTO_IP
        case IP_ADD_MEMBERSHIP: {
            mp_buffer_info_t bufinfo;
            mp_get_buffer_raise(args[3], &bufinfo, MP_BUFFER_READ);
            if (bufinfo.len != sizeof(ip4_addr_t) * 2) {
                mp_raise_ValueError(NULL);
            }

            // POSIX setsockopt has order: group addr, if addr, lwIP has it vice-versa
            err_t err = igmp_joingroup((const ip4_addr_t *)bufinfo.buf + 1, bufinfo.buf);
            if (err != ERR_OK) {
                mp_raise_OSError(-err);
            }
            break;
        }

        default:
            mp_printf(&mp_plat_print, "Warning: lwip.setsockopt() option not implemented\n");
    }

    return mp_const_none;
}
MP_STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(socket_setsockopt_obj, 4, 4, socket_setsockopt);



MP_STATIC const mp_rom_map_elem_t socket_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_socket) },
    { MP_ROM_QSTR(MP_QSTR_socket), MP_ROM_PTR(&mp_socket_newsocket_obj) },
    { MP_ROM_QSTR(MP_QSTR_setsockopt), MP_ROM_PTR(&socket_setsockopt_obj) },
    { MP_ROM_QSTR(MP_QSTR_AF_INET), MP_ROM_INT(AF_INET) },
    { MP_ROM_QSTR(MP_QSTR_AF_INET6), MP_ROM_INT(AF_INET6) },

    { MP_ROM_QSTR(MP_QSTR_SOCK_STREAM), MP_ROM_INT(SOCK_STREAM) },
    { MP_ROM_QSTR(MP_QSTR_SOCK_DGRAM), MP_ROM_INT(SOCK_DGRAM) },
    { MP_ROM_QSTR(MP_QSTR_SOCK_RAW), MP_ROM_INT(SOCK_RAW) },
		

	{ MP_ROM_QSTR(MP_QSTR_SOL_SOCKET), MP_ROM_INT(SOL_SOCKET) },
    { MP_ROM_QSTR(MP_QSTR_SO_REUSEADDR), MP_ROM_INT(SO_REUSEADDR) },
	{ MP_ROM_QSTR(MP_QSTR_SO_BROADCAST), MP_ROM_INT(SO_BROADCAST) },
	
    { MP_ROM_QSTR(MP_QSTR_connect), MP_ROM_PTR(&mp_socket_connect_obj) },
    { MP_ROM_QSTR(MP_QSTR_send), MP_ROM_PTR(&mp_socket_send_obj) },
    { MP_ROM_QSTR(MP_QSTR_recv), MP_ROM_PTR(&mp_socket_recv_obj) },
    { MP_ROM_QSTR(MP_QSTR_close), MP_ROM_PTR(&mp_socket_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_bind), MP_ROM_PTR(&mp_socket_bind_obj) },
    { MP_ROM_QSTR(MP_QSTR_listen), MP_ROM_PTR(&mp_socket_listen_obj) },
    { MP_ROM_QSTR(MP_QSTR_accept), MP_ROM_PTR(&mp_socket_accept_obj) },
    { MP_ROM_QSTR(MP_QSTR_sendto), MP_ROM_PTR(&mp_socket_sendto_obj) },
    { MP_ROM_QSTR(MP_QSTR_recvfrom), MP_ROM_PTR(&mp_socket_recvfrom_obj) },
};


MP_STATIC MP_DEFINE_CONST_DICT(socket_locals_dict, socket_module_globals_table);

const mp_obj_type_t mp_type_socket = {
    { &mp_type_type },
    .name = MP_QSTR_socket,
    .make_new = socket_new,
    .getiter = NULL,
    .iternext = NULL,
    .locals_dict = (mp_obj_dict_t *)&socket_locals_dict,
};
