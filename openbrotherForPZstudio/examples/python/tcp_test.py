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
