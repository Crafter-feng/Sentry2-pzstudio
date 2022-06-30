# oled显示屏例程：显示屏计数
from device import OLED
import time
# 初始化显示屏
oled = OLED(0x3c)
a = 0
while True:
    # 在显示屏的0行0列显示字符串
    oled.show_str("Count:" + str(a),0,0,1,0)
    a = a + 1
    oled.flush()
    time.sleep(1)
    # 显示屏清屏
    time.msleep(1)
