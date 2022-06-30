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
