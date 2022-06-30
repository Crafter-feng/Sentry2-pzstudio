# 按键例程：按下引脚9按键打开蜂鸣器，按下引脚10按键关闭蜂鸣器
from device import BEEP
from device import BUTTON
import time
# 初始化蜂鸣器
beep = BEEP()
# 初始化按键0
btn0 = BUTTON(0)
# 初始化按键1
btn1 = BUTTON(1)
while True:
    # 获取按键状态（引脚9），返回0代表按下按键
    if btn0.value() == 0:
        #消抖
        while btn0.value() == 0:
            pass
        beep.on()
    # 获取按键状态（引脚10），返回0代表按下按键
    if btn1.value() == 0:
        #消抖
        while btn1.value() == 0:
            pass
        beep.off()
