/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020, HiHope Community.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef NET_COMMON_H
#define NET_COMMON_H

// __arm__ and __aarch64__ for HarmonyOS with liteos-a kernel, __i386__ and __x86_64__ for Unix like OS
#if defined(__arm__) || defined(__aarch64__) || defined(__i386__) || defined(__x86_64__)
#define HAVE_BSD_SOCKET 1
#else
#define HAVE_BSD_SOCKET 0
#endif

#if defined(__riscv) // for wifiiot(HarmonyOS on Hi3861 with liteos-m kernel)
#define HAVE_LWIP_SOCKET 1
#else
#define HAVE_LWIP_SOCKET 0
#endif

#if HAVE_BSD_SOCKET
#include <sys/types.h>  // for AF_INET SOCK_STREAM
#include <sys/socket.h> // for socket
#include <netinet/in.h> // for sockaddr_in
#include <arpa/inet.h> // for inet_pton
#elif HAVE_LWIP_SOCKET
#include "lwip/sockets.h"
#ifndef close
#define close(fd) lwip_close(fd)
#endif
#else
#error "Unknow platform!"
#endif

#endif  // NET_COMMON_H