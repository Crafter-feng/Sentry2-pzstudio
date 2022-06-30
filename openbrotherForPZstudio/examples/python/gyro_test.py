import time
from device import IMU
from device import OLED
import time
# IMU初始化
imu = IMU()
# 初始化显示屏
oled = OLED(0x3c)
while True:
    gyro = imu.gyro()
    oled.show_str("Count:" + str(gyro),0,0,1,0)
    oled.flush()
    time.sleep(1)
