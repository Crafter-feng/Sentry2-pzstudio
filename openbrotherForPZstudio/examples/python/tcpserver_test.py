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
# TCP服务端例程
import network
import socket
from device import OLED
oled = OLED(0x3c)
# 连接WiFi
network.connectWifi("POLYGON_ZONE","DB095438")
oled.show_str("本机IP:" + str(network.ifconfig()[0]),1,1,1,0)
oled.flush()
# 初始化TCP socket
soc = socket.socket()
# 绑定地址（IP和端口）
soc.bind(("0.0.0.0",12345))
# 监听连接
soc.listen(1)
# 接收连接
client = soc.accept()

while True:
    # 向客户端发送数据
    a = client.send("hello_world")
   
# 关闭socket
client.close()
soc.close()
