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
# UDP通信例程
import network
import socket
# 连接WiFi
while ( not network.isconnected()) :
    network.connectWifi("POLYGON_ZONE","DB095438")
# 初始化UDP socket
soc = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
# 绑定地址（IP和端口）
soc.bind(("0.0.0.0",12345))

while True:
    # 向指定地址发送数据
    c = soc.sendto("hello_world",("192.168.0.106",12345))
# 关闭socket
soc.close()
