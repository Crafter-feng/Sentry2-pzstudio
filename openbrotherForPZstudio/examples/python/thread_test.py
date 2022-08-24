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
# 多线程例程
import _thread
import time
def _func1():   
    while True:
        print("how")

def _func2():   
    while True:
        print("are")

def _func3():   
    while True:
        print("you")

# 启动线程
_thread.start_new_thread(_func1,())
_thread.start_new_thread(_func2,())
_thread.start_new_thread(_func3,())

while True:
    print("hello_world")
