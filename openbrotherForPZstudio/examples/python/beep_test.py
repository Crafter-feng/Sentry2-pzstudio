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
