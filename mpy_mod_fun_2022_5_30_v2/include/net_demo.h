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

#ifndef NET_DEMO_COMMON_H
#define NET_DEMO_COMMON_H

#include <stdio.h>

void NetDemoTest(unsigned short port, const char* host);

const char* GetNetDemoName(void);

#define IMPL_GET_NET_DEMO_NAME(testFunc) \
    const char* GetNetDemoName() { \
        static const char* demoName = #testFunc; \
        return demoName; \
    }

#define CLIENT_TEST_DEMO(testFunc) \
    void NetDemoTest(unsigned short port, const char* host) { \
        (void) host; \
        printf("%s start\r\n", #testFunc); \
        printf("I will connect to %s:%d\r\n", host, port); \
        testFunc(host, port); \
        printf("%s done!\r\n", #testFunc); \
    } \
    IMPL_GET_NET_DEMO_NAME(testFunc)

#define SERVER_TEST_DEMO(testFunc) \
    void NetDemoTest(unsigned short port, const char* host) { \
        (void) host; \
        printf("%s start\r\n", #testFunc); \
        printf("I will listen on :%d\r\n", port); \
        testFunc(port); \
        printf("%s done!\r\n", #testFunc); \
    } \
    IMPL_GET_NET_DEMO_NAME(testFunc)

#endif // NET_DEMO_COMMON_H
