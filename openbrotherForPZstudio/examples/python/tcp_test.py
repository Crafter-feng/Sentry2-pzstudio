# 
# Copyright (C) 2022 PolygonZone Open Source Organization .
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
    # http:// www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# 
# limitations under the License.
# 
# TCP客户端例程
import network
import socket
# 连接Wifi
while ( not network.isconnected()) :
    network.connectWifi("POLYGON_ZONE","DB095438")
# 初始化TCP socket
soc = socket.socket()
# 连接TCP服务器
soc.connect(("192.168.0.106",12345))

while True:

    #接收服务器发出的数据
    b = soc.recv()
    #把接收到的数据返回给服务器
    c = soc.send(b)
# 关闭socket
soc.close()
