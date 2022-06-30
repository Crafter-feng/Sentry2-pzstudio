# 蜂鸣器例程：蜂鸣器重复打开关闭
from device import BEEP
import time
# 初始化蜂鸣器
beep = BEEP()
while True:
    # 打开蜂鸣器
    beep.on()
    time.sleep(1)
    # 关闭蜂鸣器
    beep.off()
    time.sleep(1)
