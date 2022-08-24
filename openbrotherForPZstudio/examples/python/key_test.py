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
