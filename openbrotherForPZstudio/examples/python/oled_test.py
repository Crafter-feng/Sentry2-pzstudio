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
