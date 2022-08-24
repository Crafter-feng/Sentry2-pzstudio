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
