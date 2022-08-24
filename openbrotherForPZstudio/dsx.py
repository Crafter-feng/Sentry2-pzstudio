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
import sys
from bin.IPC import *
import os
import time

# do some code insertion work
def convertDSXCode(realtimeCode):
    arr = realtimeCode.split('\n')
    result = ""
    isFunction = False
    isMain = False
    threadCnt = 0
    beforeMain = True
    iscustomFunction = False
    functionStr = ""
    initVar = ""
    varList = ""
    for i in range(0,len(arr)):
        if("= None" in arr[i]):
            initVar = initVar + arr[i][0: arr[i].find(" ")] + " = 0\n"
            varList = varList + arr[i][0: arr[i].find(" ")] + ","
    for i in range(0,20):
        if (realtimeCode.find("pwm" + str(i) + ".freq(") > -1 or realtimeCode.find("pwm" + str(i) + ".duty(") > -1):
            varList += "pwm" + str(i) + ","
        if (realtimeCode.find("pin" + str(i) + ".value(") > -1):
            varList += "pin" + str(i) + ","
        if (realtimeCode.find("adc" + str(i) + ".read(") > -1):
            varList += "adc" + str(i) + ","
        if (realtimeCode.find("servo" + str(i) + ".angle(") > -1):
            varList += "servo" + str(i) + ","
        if (realtimeCode.find("dht" + str(i) + ".temp(") > -1 or realtimeCode.find("dht" + str(i) + ".humi(") > -1):
            varList += "dht" + str(i) + ","
    for i in range(0,20):
        for j in range(0,20):
            if (realtimeCode.find("ttp_" + str(i) + "_" + str(j) + ".get_key(") > -1):
                varList += "ttp_" + str(i) + "_" + str(j) + ","
            if (realtimeCode.find("ultra_" + str(i) + "_" + str(j) + ".distance(") > -1):
                varList += "ultra_" + str(i) + "_" + str(j) + ","
    if (realtimeCode.find("iic") > -1):
        varList += "iic" + ","
    if (realtimeCode.find("mp3.") > -1):
        varList += "mp3" + ","
    if (realtimeCode.find("ltr.") > -1):
        varList += "ltr" + ","
    if (realtimeCode.find("pm.get_pm2_5") > -1):
        varList += "pm" + ","
    if (realtimeCode.find("dsx_clientlist.") > -1):
        varList += "dsx_clientlist" + ","
    if (realtimeCode.find("tq_clientlist.") > -1):
        varList += "tq_clientlist" + ","
    if (realtimeCode.find("dsx_server.") > -1):
        varList += "dsx_server" + ",";
        varList += "dsx_connlock" + ","
        varList += "dsx_clientlist" + ","
    if (realtimeCode.find("tq_server.") > -1):
        varList += "tq_server" + ","
        varList += "tq_connlock" + ","
        varList += "tq_clientlist" + ","
    if (realtimeCode.find("dsx_client.") > -1):
        varList += "dsx_client" + ","
    if (realtimeCode.find("tq_client.") > -1):
        varList += "tq_client" + ","
    if (realtimeCode.find("uart.") > -1 or realtimeCode.find("uart = ") > -1):
        varList += "uart" + ","
    if (realtimeCode.find("uart2.") > -1 or realtimeCode.find("uart2 = ") > -1):
        varList += "uart2" + ","
    if (realtimeCode.find("oled.") > -1):
        varList += "oled" + ","
    if (realtimeCode.find("btn0.") > -1):
        varList += "btn0" + ","
    if (realtimeCode.find("btn1.") > -1):
        varList += "btn1" + ","
    if (realtimeCode.find("btn2.") > -1):
        varList += "btn2" + ","
    if (realtimeCode.find("led0.") > -1):
        varList += "led0" + ","
    if (realtimeCode.find("led1.") > -1):
        varList += "led1" + ","
    if (realtimeCode.find("led2.") > -1):
        varList += "led2" + ","
    if (realtimeCode.find("led3.") > -1):
        varList += "led3" + ","
    if (realtimeCode.find("imu.") > -1):
        varList += "imu" + ","
    if (realtimeCode.find("beep.") > -1):
        varList += "beep" + ","
    if (realtimeCode.find("us516p6.") > -1):
        varList += "us516p6" + ","
    if (realtimeCode.find("motor.") > -1):
        varList += "motor" + ","
    if (realtimeCode.find("led_matrix.") > -1):
        varList += "led_matrix" + ","
    if (realtimeCode.find("sensor.") > -1):
        varList += "sensor" + ","
    if (realtimeCode.find("aht2x.") > -1):
        varList += "aht2x" + ","
    if (realtimeCode.find("touch.") > -1):
        varList += "touch" + ","
    if (realtimeCode.find("light.") > -1):
        varList += "light" + ","
    if (realtimeCode.find("mic.") > -1):
        varList += "mic" + ","
    if (realtimeCode.find("hw_board.") > -1):
        varList += "hw_board" + ","
    if (realtimeCode.find("pz_board.") > -1):
        varList += "pz_board" + ","
    if (realtimeCode.find("heartbeat.") > -1):
        varList += "heartbeat" + ","
    if (realtimeCode.find("barometer.") > -1):
        varList += "barometer" + ","
    varList = varList[0:-1]
    
    for i in range(0,len(arr)):
        if (arr[i].strip().startswith("def main():")):
            beforeMain = False
            isFunction = True
            result += arr[i] + "\n  global " + varList + "\n"
            isMain = True
            continue
        if (arr[i].strip().startswith("def thread():")):
            isFunction = True
            result += "def thread_" + str(threadCnt) + "():\n  global " + varList + "\n"
            isMain = False
            continue
        if (isFunction and arr[i].strip() != ""):
            result += "  " + arr[i] + "\n";
            continue;
        if (isFunction and arr[i].strip() == ""):
            if (isMain):
                result += "\n";
            else:
                result += "_thread.start_new_thread(thread_" + str(threadCnt) + ",())\n"
                threadCnt+=1
            isFunction = False;
            continue;
        if (arr[i].strip().startswith("def ")):
            functionStr = functionStr + arr[i] + "\n  global " + varList + "\n";
            iscustomFunction = True;
            continue;
        if (arr[i].strip() == ""):
            iscustomFunction = False
        if (iscustomFunction):
            functionStr = functionStr + "  " + arr[i] + "\n"
            arr[i] = ""
        if (not "def main()" in realtimeCode):
            if (not arr[i].strip().endswith("= None")):
                result += arr[i] + "\n"
        else:
            if (arr[i].strip().startswith("import ")):
                functionStr = functionStr + arr[i] + "\n"
    temp = result + functionStr;
    if ("_thread" in temp):
        result = "import _thread\n" + result
    if (beforeMain == False):
        result = result + "main()\n"
    dsxcode = ""
    addPWM = False
    for i in range(0,20):
        if (temp.find("pwm" + str(i) + ".freq(") > -1 or temp.find("pwm" + str(i) + ".duty(") > -1):
            if (addPWM == False):
                dsxcode += "from machine import PWM\n";
                addPWM = True;
            dsxcode += "pwm" + str(i) + " = PWM(" + str(i) + ",freq=5000,duty=50)\n"
    addPin = False
    if (temp.find("Pin(") > -1):
       dsxcode += "from machine import Pin\n";
       addPin = True;
    for i in range(0,20):
        if (temp.find("pin" + str(i) + ".value(") > -1):
            if (addPin == False):
                dsxcode += "from machine import Pin\n";
                addPin = True;
            dsxcode += "pin" + str(i) + " = Pin(" + str(i) + ",mode=Pin.IN,pull=Pin.PULL_UP)\n";
    addADC = False;
    for i in range(0,20):
        if (temp.find("adc" + str(i) + ".read(") > -1):
            if (addADC == False):
                dsxcode += "from machine import ADC\n"
                addADC = True
            dsxcode += "adc" + str(i) + " = ADC(" + str(i) + ")\n"
    addTTP = False;
    for i in range(0,20):
        for j in range(0,20):
            if (temp.find("ttp_" + str(i) + "_" + str(j) + ".get_key(") > -1):
                if (addTTP == False):
                    dsxcode += "from ext_device import Ttp229\n";
                    addTTP = True;
                dsxcode += "ttp_" + str(i) + "_" + str(j) + " = Ttp229(" + str(i) + "," + str(j) + ")\n"
    addUltra = False;
    for i in range(0,20):
        for j in range(0,20):
            if (temp.find("ultra_" + str(i) + "_" + str(j) + ".distance(") > -1):
                if (addUltra == False):
                    dsxcode += "from ext_device import Ultrasonic\n"
                    addUltra = True
                dsxcode += "ultra_" + str(i) + "_" + str(j) + " = Ultrasonic(" + str(i) + "," + str(j) + ")\n"
    addServo = False;
    for i in range(0,20):
        if (temp.find("servo" + str(i) + ".angle(") > -1):
            if (addServo == False):
                dsxcode += "from ext_device import Servo\n";
                addServo = True;
            dsxcode += "servo" + str(i) + " = Servo(" + str(i) + ")\n";
    addDHT = False;
    for i in range(0,20):
        if (temp.find("dht" + str(i) + ".temp(") > -1 or temp.find("dht" + str(i) + ".humi(") > -1):
            if (addDHT == False):
                dsxcode += "from ext_device import Dhtxx\n";
                addDHT = True;
            dsxcode += "dht" + str(i) + " = Dhtxx(" + str(i) + ")\n";
            
    if (temp.find("iic") > -1):
        dsxcode += "from machine import I2C\n"
    if (temp.find("ltr.") > -1):
        dsxcode += "from device import LTR553\n"
        dsxcode += "ltr = LTR553()\n"
    if (temp.find("mp3.") > -1):
        dsxcode += "from ext_device import MP3_JQ8400\n"
        dsxcode += "mp3 = MP3_JQ8400()\n"
    if (temp.find("hw_board.") > -1):
        dsxcode += "from ext_device import HWBOARD\n"
        dsxcode += "hw_board = HWBOARD()\n"
    if (temp.find("pz_board.") > -1):
        dsxcode += "from ext_device import PZBOARD\n"
        dsxcode += "pz_board = PZBOARD()\n"
    if (temp.find("heartbeat.") > -1):
        dsxcode += "from ext_device import HEARTBEAT\n"
        dsxcode += "heartbeat = HEARTBEAT()\n"
    if (temp.find("barometer.") > -1):
        dsxcode += "from ext_device import BARO\n"
        dsxcode += "barometer = BARO()\n"
    if (temp.find("pm.get_pm2_5") > -1):
        dsxcode += "from ext_device import PMxx\n"
        dsxcode += "pm = PMxx()\n"
    if (temp.find("_thread.") > -1):
        dsxcode += "import _thread\n"
    if (temp.find("math.") > -1):
        dsxcode += "import math\n"
    if (temp.find("random.") > -1):
        dsxcode += "import random\n"
    if (temp.find("UART(") > -1 or temp.find("uart.") > -1 or temp.find("uart = ") > -1 or temp.find("uart != ") > -1):
        dsxcode += "from machine import UART\n"
    if (temp.find("uart.") > -1 or temp.find("uart = ") > -1):
        dsxcode += "uart = 0\n"
    if (temp.find("uart2.") > -1 or temp.find("uart2 = ") > -1):
        dsxcode += "uart2 = 0\n"
    if (temp.find("led_matrix.") > -1):
        dsxcode += "from device import MATRIX_SCREEN\n";
        dsxcode += "led_matrix = MATRIX_SCREEN()\n";
    if (temp.find("sensor.") > -1):
        dsxcode += "from device import AHT2X\n";
        dsxcode += "sensor = AHT2X()\n";
    if (temp.find("aht2x.") > -1):
        dsxcode += "from device import AHT2X\n"
        dsxcode += "aht2x = AHT2X()\n"
    if (temp.find("touch.") > -1):
        dsxcode += "from device import TOUCH_PAD\n";
        dsxcode += "touch = TOUCH_PAD()\n";
    if (temp.find("light.") > -1):
        dsxcode += "from device import LIGHT_SENSOR\n";
        dsxcode += "light = LIGHT_SENSOR()\n";
    if (temp.find("mic.") > -1):
        dsxcode += "from device import MIC\n";
        dsxcode += "mic = MIC()\n";
    if (temp.find("oled.") > -1):
        dsxcode += "from device import OLED\noled = OLED(0x3c)\n";
    if (temp.find("btn0.value(") > -1 or temp.find("btn1.value(") > -1 or temp.find("btn2.value(") > -1):
        dsxcode += "from device import BUTTON\n";
    if (temp.find("btn0.value(") > -1):
        dsxcode += "btn0 = BUTTON(0)\n";
    if (temp.find("btn1.value(") > -1):
        dsxcode += "btn1 = BUTTON(1)\n";
    if (temp.find("btn2.value(") > -1):
        dsxcode += "btn2 = BUTTON(2)\n";
    if (temp.find("led0.on(") > -1 or temp.find("led0.off(") > -1 or temp.find("led1.on(") > -1 or temp.find("led1.off(") > -1 or temp.find("led1value(") > -1 or temp.find("led2.value(") > -1 or temp.find("led3.value(") > -1):
        dsxcode += "from device import LED\n";
    if (temp.find("led0.on(") > -1 or temp.find("led0.off(") > -1 or temp.find("led0.value(") > -1):
        dsxcode += "led0 = LED(0)\n";
    if (temp.find("led1.on(") > -1 or temp.find("led1.off(") > -1 or temp.find("led1.value(") > -1):
        dsxcode += "led1 = LED(1)\n";
    if (temp.find("led2.on(") > -1 or temp.find("led2.off(") > -1 or temp.find("led2.value(") > -1):
        dsxcode += "led2 = LED(2)\n";
    if (temp.find("led3.on(") > -1 or temp.find("led3.off(") > -1 or temp.find("led3.value(") > -1):
        dsxcode += "led3 = LED(3)\n";
    if (temp.find("imu.") > -1):
        dsxcode += "from device import IMU\nimu = IMU()\n";
    if (temp.find("beep.") > -1):
        dsxcode += "from device import BEEP\nbeep = BEEP()\n";
    if (temp.find("buzzer.") > -1):
        dsxcode += "import buzzer\n";
        dsxcode += "buzzer.init()\n";
    if (temp.find("time.") > -1):
        dsxcode += "import time\n";
    if (temp.find("machine.") > -1):
        dsxcode += "import machine\n";
    if (temp.find("network.") > -1):
        dsxcode += "import network\n";
    # if (temp.find("socket") > -1):
    #     dsxcode += "import socket\n";
    if (temp.find("us516p6.") > -1):
        dsxcode += "from device import US516P6\n";
        dsxcode += "us516p6 = US516P6(0)\n";
    if (temp.find("motor.") > -1):
        dsxcode += "from device import DF_MOTOR\n";
        dsxcode += "motor = DF_MOTOR()\n";
    if (temp.find("machine.getAHT2X(") > -1):
        dsxcode += "machine.initAHT2X()\n";
    if (temp.find("machine.getKey(9)") > -1):
        dsxcode += "machine.initKey(9)\n";
    if (temp.find("machine.getKey(10)") > -1):
        dsxcode += "machine.initKey(10)\n";
    if (temp.find("machine.beep_on()") > -1 or temp.find("machine.beep_off()") > -1 or temp.find("machine.music_player(") > -1 or temp.find("machinemusic_stop(") > -1):
        dsxcode += "machine.initBeep()\n";
    if (temp.find("machine.read_acc()") > -1 or temp.find("machine.read_gyro()") > -1):
        dsxcode += "machine.icm_init()\n";
    else:
        if (temp.find("machine.read_acc()") > -1 or temp.find("machine.read_gyro()") > -1):
            dsxcode += "machine.init_acc()\n";
    if (temp.find("led.clear()") > -1 or temp.find("led.dot(") > -1 or temp.find("led.showMatrix(") > -1 or temp.find("led.fill(") > -1 or temp.find("led.showString(") > -1 or temp.find("led.showChar(") > -1):
        dsxcode += "led.init()\n";
    if (temp.find("led.on(2)") > -1 or temp.find("led.off(2)") > -1):
        dsxcode += "led.init(2)\n";
    if (temp.find("led.on(7)") > -1 or temp.find("led.off(7)") > -1):
        dsxcode += "led.init(7)\n";

    if (temp.find("motorRun(") > -1 or temp.find("motorStop(") > -1 or temp.find("servoAngle(") > -1):
        dsxcode += "from machine import I2C\n"
        dsxcode += "import time\n"
        dsxcode += "i2c = I2C(0)\n"
    if (temp.find("motorRun(") > -1):
        dsxcode += "def motorRun(index, dirction, speed):\n"
        dsxcode += "  global i2c\n"
        dsxcode += "  buf = [0, dirction, speed]\n"
        dsxcode += "  if (index == 0):\n"
        dsxcode += "    buf[0] = 0x00\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 1):\n"
        dsxcode += "    buf[0] = 0x02\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 2):\n"
        dsxcode += "    buf[0] = 0x00\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "    buf[0] = 0x02\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
    if (temp.find("motorStop(") > -1):
        dsxcode += "def motorStop(index):\n"
        dsxcode += "  global i2c\n"
        dsxcode += "  buf = [0, 0, 0]\n"
        dsxcode += "  if (index == 0):\n"
        dsxcode += "    buf[0] = 0x00\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 1):\n"
        dsxcode += "    buf[0] = 0x02\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 2):\n"
        dsxcode += "    buf[0] = 0x00\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "    buf[0] = 0x02\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
    if (temp.find("servoAngle(") > -1):
        dsxcode += "def servoAngle(index, angle):\n"
        dsxcode += "  global i2c\n"
        dsxcode += "  buf = [0, 0, angle]\n"
        dsxcode += "  if (index == 3):\n"
        dsxcode += "    buf[0] = 0x03\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 4):\n"
        dsxcode += "    buf[0] = 0x04\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 5):\n"
        dsxcode += "    buf[0] = 0x05\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 6):\n"
        dsxcode += "    buf[0] = 0x06\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "  elif(index == 7):\n"
        dsxcode += "    buf[0] = 0x03\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "    buf[0] = 0x04\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "    buf[0] = 0x05\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
        dsxcode += "    buf[0] = 0x06\n"
        dsxcode += "    send = bytes(buf)\n"
        dsxcode += "    i2c.write(0x10, send)\n"
    dsxcode += initVar;

    if (realtimeCode.find("dsx_server.") > -1):
        dsxcode += "dsx_server = 0\n";
        dsxcode += "dsx_connlock = 0\n";
        dsxcode += "dsx_clientlist = []\n";
    if (realtimeCode.find("tq_server.") > -1):
        dsxcode += "tq_server = 0\n";
        dsxcode += "tq_connlock = 0\n";
        dsxcode += "tq_clientlist = []\n";
    if (realtimeCode.find("dsx_client.") > -1):
        dsxcode += "dsx_client = 0\n";
    if (realtimeCode.find("tq_client.") > -1):
        dsxcode += "tq_client = 0\n";
    dsxcode += functionStr;

    if (realtimeCode.find("dsx_server.") > -1):
        dsxcode += "dsx_connlock = _thread.allocate_lock()\n";
        dsxcode += "def get_dsxclient():\n";
        dsxcode += "  global dsx_clientlist\n";
        dsxcode += "  if(len(dsx_clientlist) > 0):\n";
        dsxcode += "    return dsx_clientlist.pop(0)\n";
        dsxcode += "  else:\n";
        dsxcode += "    return 0\n";
        dsxcode += "def dsx_conn_cnt():\n";
        dsxcode += "  global dsx_clientlist,dsx_connlock\n";
        dsxcode += "  a = len(dsx_clientlist)\n";
        dsxcode += "  return a\n";
        dsxcode += "def dsx_server_thread():\n";
        dsxcode += "  global dsx_clientlist,dsx_server\n";
        dsxcode += "  while True:\n";
        dsxcode += "    dsx_clientlist.append(dsx_server.accept())\n";
    if (realtimeCode.find("tq_server.") > -1):
        dsxcode += "tq_connlock = _thread.allocate_lock()\n";
        dsxcode += "def get_tqclient():\n";
        dsxcode += "  global tq_clientlist\n";
        dsxcode += "  if(len(tq_clientlist) > 0):\n";
        dsxcode += "    return tq_clientlist.pop(0)\n";
        dsxcode += "  else:\n";
        dsxcode += "    return 0\n";
        dsxcode += "def tq_conn_cnt():\n";
        dsxcode += "  global tq_clientlist,tq_connlock\n";
        dsxcode += "  a = len(tq_clientlist)\n";
        dsxcode += "  return a\n";
        dsxcode += "def tq_server_thread():\n";
        dsxcode += "  global tq_clientlist,tq_server\n";
        dsxcode += "  while True:\n";
        dsxcode += "    tq_clientlist.append(tq_server.accept())\n";
    dsxcode += result;
    return dsxcode;

# define custom hardware name and image
def getHardwareDef():
    hardwareDef = """
    {
        "name": "大师兄板",
        "image":"ef3b01f6fc1ffa1270fbbf057f7ded61.svg"
    }""";
    return hardwareDef

# define custom blocks
def getBlockDef():
    blockDef = "dsxblocks.js"
    return blockDef

# define toolbox category for scratch
def getCategory():
    jsonstr = "["
    jsonstr += """{"name":"程序", "xml":"<category name='程序' id='program' colour='#9ad669' secondaryColour='#BD42BD' iconURI='/static/program.png'><block type='event_main_thread'></block><block type='event_sub_thread'></block></category>"},""";
    jsonstr += """{"name":"硬件", "xml" : "<category name='硬件' id='dsxhardware' colour='#4C97FF' secondaryColour='#3373CC' iconURI='/static/board.png'>
        <label text='蜂鸣器'></label>
        <block type='motion_dsx_beep_on'>
        </block>
        <block type='motion_dsx_beep_off'>
        </block>
        <block type='motion_dsx_playmusic'>
        </block>
        <block type='motion_dsx_stopmusic'>
        </block>
        <label text='按键'></label>
        <block type='motion_dsx_get_key'>
            <value name='INDEX'>
                <shadow type='math_number'>
                    <field name='NUM'>1</field>
                </shadow>
            </value>
        </block>
        <label text='IMU'></label>
        <block type='motion_dsx_read_acc'>
        </block>
        <block type='motion_dsx_read_gyro'>
        </block>
        <block type='motion_dsx_read_a'>
        </block>
        <block type='motion_dsx_read_g'>
        </block>
        <label text='OLED显示屏'></label>
        <block type='motion_dsx_oled_flush'>
        </block>
        <block type='motion_dsx_oled_clear'>
        </block>
        <block type='motion_dsx_oled_showstr'>
            <value name='ROW'>
                <shadow type='math_number'>
                    <field name='NUM'>1</field>
                </shadow>
            </value>
            <value name='COL'>
                <shadow type='math_number'>
                    <field name='NUM'>1</field>
                </shadow>
            </value>
            <value name='STRING'>
                <shadow type='text'>
                    <field name='TEXT'>你好大师兄</field>
                </shadow>
            </value>
        </block>
        <block type='motion_dsx_oled_showstr2'>
            <value name='ROW'>
                <shadow type='math_number'>
                    <field name='NUM'>1</field>
                </shadow>
            </value>
            <value name='STRING'>
                <shadow type='text'>
                    <field name='TEXT'>你好大师兄</field>
                </shadow>
            </value>
        </block>
        <block type='motion_dsx_oled_fillline'>
            <value name='ROW'>
                <shadow type='math_number'>
                    <field name='NUM'>1</field>
                </shadow>
            </value>
        </block>
        <block type='motion_dsx_oled_pixel'>
            <value name='X'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
        </block>
        <label text='OLED画图'></label>
        <block type='motion_dsx_oled_line'>
            <value name='X'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='LENGTH'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_line2'>
            <value name='X1'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y1'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='X2'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y2'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_arc'>
            <value name='X'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='R'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='ANGLE1'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
            <value name='ANGLE2'><shadow type='math_number'><field name='NUM'>90</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_rect'>
            <value name='X'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='W'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
            <value name='H'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_boarder'>
            <value name='X'><shadow type='math_number'><field name='NUM'>50</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='W'><shadow type='math_number'><field name='NUM'>40</field></shadow></value>
            <value name='H'><shadow type='math_number'><field name='NUM'>30</field></shadow></value>
            <value name='R'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_circle'>
            <value name='X'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='R'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_ellipse'>
            <value name='X'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='RX'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
            <value name='RY'><shadow type='math_number'><field name='NUM'>15</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_triangle'>
            <value name='X1'><shadow type='math_number'><field name='NUM'>64</field></shadow></value>
            <value name='Y1'><shadow type='math_number'><field name='NUM'>20</field></shadow></value>
            <value name='X2'><shadow type='math_number'><field name='NUM'>30</field></shadow></value>
            <value name='Y2'><shadow type='math_number'><field name='NUM'>60</field></shadow></value>
            <value name='X3'><shadow type='math_number'><field name='NUM'>90</field></shadow></value>
            <value name='Y3'><shadow type='math_number'><field name='NUM'>60</field></shadow></value>
        </block>
        <block type='motion_dsx_oled_image'>
            <value name='X'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
            <value name='Y'><shadow type='math_number'><field name='NUM'>0</field></shadow></value>
        </block>
        <label text='输入输出'></label>
        <block type='motion_dsx_digital_pin'></block>
        <block type='motion_dsx_analog_pin'></block>
        <block type='motion_dsx_set_digital_pin'></block>
        
        <block type='motion_dsx_set_analog_pin_freq'>
            <value name='FREQ'><shadow type='math_number'><field name='NUM'>512</field></shadow></value>
        </block>
        <block type='motion_dsx_set_analog_pin_duty'>
            <value name='DUTY'><shadow type='math_number'><field name='NUM'>50</field></shadow></value>
        </block>
        <label text='温湿度传感器'></label>
        <block type='motion_dsx_temperature'>
        </block>
        <block type='motion_dsx_humi'>
        </block>
        <label text='光敏传感器'></label>
        <block type='motion_dsx_get_light'>
        </block>
        <label text='云知声'></label>
        <block type='motion_dsx_unisound'>
        </block>
        <block type='motion_dsx_unisound_value'>
        </block>
        <label text='串口'></label>
        <block type='motion_dsx_init_uart'></block>
        <block type='motion_dsx_close_uart'></block>
        <block type='motion_dsx_uart_isinit'></block>
        <block type='motion_dsx_uart_write'>
            <value name='VALUE'><shadow type='text'><field name='TEXT'>hello</field></shadow></value></block>
        <block type='motion_dsx_uart_write2'>
            <value name='VALUE'><shadow type='text'><field name='TEXT'>65,66,67</field></shadow></value></block>
        <block type='motion_dsx_uart_read'>
            <value name='VALUE'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_uart_readline'></block>
        <block type='motion_dsx_uart_canread'></block>
        <label text='I2C'></label>
        <block type='motion_dsx_init_i2c'>
        <value name='FREQ'><shadow type='math_number'><field name='NUM'>400000</field></shadow></value>
        </block>
        <block type='motion_dsx_i2c_write'>
        <value name='ADDR'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        <value name='VALUE'><shadow type='text'><field name='TEXT'>0,1,100</field></shadow></value></block>
        <block type='motion_dsx_i2c_read'>
        <value name='ADDR'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        <value name='LEN'><shadow type='math_number'><field name='NUM'>1</field></shadow></value>
        </block>
        <block type='motion_dsx_i2c_scan'>
        </block>
        </category>"},""";
    jsonstr += """{"name":"Socket", "xml":"<category name='Socket' id='dsxsocket' colour='#f09f2d' secondaryColour='#BD42BD' iconURI='/static/Socket.png'>
            <block type='motion_dsx_socket_create'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='PASSWORD'><shadow type='text'><field name='TEXT'>12345678</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_close'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_bind'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='ADDR'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
                <value name='PORT'><shadow type='math_number'><field name='NUM'>1000</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_timeout'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='TIMEOUT'><shadow type='math_number'><field name='NUM'>5</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_listen'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='COUNT'><shadow type='math_number'><field name='NUM'>5</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_setbroadcast'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_connect'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='HOST'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
                <value name='PORT'><shadow type='math_number'><field name='NUM'>1000</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_accept'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_send'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='CONTENT'><shadow type='text'><field name='TEXT'>hello</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_sendto'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='CONTENT'><shadow type='text'><field name='TEXT'>hello</field></shadow></value>
                <value name='ADDR'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
                <value name='PORT'><shadow type='text'><field name='TEXT'>8888</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_recv'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='LENGTH'><shadow type='math_number'><field name='NUM'>1</field></shadow></value>
            </block>
            <block type='motion_dsx_socket_recvfrom'>
                <value name='NAME'><shadow type='text'><field name='TEXT'>soc</field></shadow></value>
                <value name='LENGTH'><shadow type='math_number'><field name='NUM'>1</field></shadow></value>
            </block>
        </category>"},""";
    jsonstr += """{"name":"网络", "xml":"<category name='通信' id='dsxconn' colour='#BD42BD' secondaryColour='#f09f2d' iconURI='/static/communicate.png'>
            <block type='motion_dsx_conn_create_server'>
                <value name='PORT'><shadow type='math_number'><field name='NUM'>1000</field></shadow></value>
                <value name='COUNT'><shadow type='math_number'><field name='NUM'>5</field></shadow></value>
            </block>
            <block type='motion_dsx_conn_create_client'>
            </block>
            <block type='motion_dsx_conn_connect'>
                <value name='HOST'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
                <value name='PORT'><shadow type='math_number'><field name='NUM'>1000</field></shadow></value>
            </block>
            <block type='motion_dsx_conn_hasconn'>
            </block>
            <block type='motion_dsx_conn_getconn'>
            </block>
            <block type='motion_dsx_conn_recv'>
                <value name='SOCKET'><shadow type='text'><field name='TEXT'>client</field></shadow></value>
            </block>
            <block type='motion_dsx_conn_send'>
                <value name='SOCKET'><shadow type='text'><field name='TEXT'>client</field></shadow></value>
                <value name='CONTENT'><shadow type='text'><field name='TEXT'>hello</field></shadow></value>
            </block>
            <block type='motion_dsx_conn_client_recv'>
            </block>
            <block type='motion_dsx_conn_client_send'>
                <value name='CONTENT'><shadow type='text'><field name='TEXT'>hello</field></shadow></value>
            </block>
            <block type='motion_dsx_conn_close_server'>
            </block>
            <block type='motion_dsx_conn_close_client'>
            </block>
        </category>"},""";
    jsonstr += """{"name":"通信", "xml":"<category name='网络' id='dsxnetwork' colour='#3c4cad' secondaryColour='#BD42BD' iconURI='/static/network.png'>
        <block type='motion_dsx_connect_wifi'>
            <value name='SSID'><shadow type='text'><field name='TEXT'>my_wifi</field></shadow></value>
            <value name='PASSWORD'><shadow type='text'><field name='TEXT'>12345678</field></shadow></value>
        </block>
        <block type='motion_dsx_getip'></block>
        <block type='motion_dsx_isconnected'></block>
        <block type='motion_dsx_disconnect_wifi'></block>
        <block type='motion_dsx_start_hotspot'>
            <value name='SSID'><shadow type='text'><field name='TEXT'>my_wifi</field></shadow></value>
            <value name='PASSWORD'><shadow type='text'><field name='TEXT'>12345678</field></shadow></value>
        </block>
        <block type='motion_dsx_config_hotspot'>
            <value name='IP'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
            <value name='NETMASK'><shadow type='text'><field name='TEXT'>255.255.255.0</field></shadow></value>
            <value name='GATEWAY'><shadow type='text'><field name='TEXT'>192.168.1.1</field></shadow></value>
        </block>
        <block type='motion_dsx_stop_hotspot'></block>
        
        </category>"},""";
    jsonstr +="]"
    jsonstr = jsonstr.replace("\n","")
    return jsonstr

# define extension devices toolbox category
def getExtensionCategory():
    jsonstr = "["
    jsonstr += """{"name":"大师兄扩展板Plus", "xml":"
    <category name='大师兄扩展板Plus' id='motor' colour='#9999CC' secondaryColour='#774DCB'>
        <block type='motion_hw_set_servo'>
            <value name='ANGLE'>
                <shadow type='math_number'>
                    <field name='NUM'>60</field>
                </shadow>
            </value>
        </block>
        <block type='motion_hw_set_motor'>
            <value name='SPEED'>
                <shadow type='math_number'>
                    <field name='NUM'>255</field>
                </shadow>
            </value>
        </block>
        <block type='motion_hw_get_motor'>
        </block>
        <block type='motion_hw_stop_motor'>
        </block>
        <block type='motion_hw_set_light'>
        </block>
        </category>"},""";
    jsonstr += """{"name":"大师兄扩展板-G", "xml":"
    <category name='大师兄扩展板-G' id='pzboard' colour='#D2691E' secondaryColour='#774DCB'>
        <block type='motion_pz_set_servo'>
            <value name='ANGLE'>
                <shadow type='math_number'>
                    <field name='NUM'>60</field>
                </shadow>
            </value>
        </block>
        <block type='motion_pz_set_motor'>
            <value name='SPEED'>
                <shadow type='math_number'>
                    <field name='NUM'>255</field>
                </shadow>
            </value>
        </block>
        <block type='motion_pz_stop_motor'>
        </block>
        <block type='motion_pz_set_light'>
        </block>
        </category>"},""";
    jsonstr += """{"name":"PZCar", "xml":"
    <category name='PZCar' id='carrobot' colour='#CDAD00' secondaryColour='#774DCB'>
        <block type='motion_carrobot_get_sonic'>
        </block>
        <block type='motion_carrobot_get_tracked_init'>
        </block>
        <block type='motion_carrobot_get_tracked'>
        </block>
        <block type='motion_carrobot_set_light'>
        </block>
        <block type='motion_carrobot_set_motor'>
            <value name='SPEED'>
                <shadow type='math_number'>
                    <field name='NUM'>255</field>
                </shadow>
            </value>
        </block>
        <block type='motion_carrobot_stop_motor'>
        </block>
        </category>"},""";
    jsonstr += """{"name":"大师兄扩展板-M", "xml":"
    <category name='大师兄扩展板-M' id='eduboard' colour='#EED8AE' secondaryColour='#774DCB'>
        <block type='motion_edu_get_sonic'>
        </block>
        <block type='motion_edu_get_pm25'>
        </block>
        <block type='motion_edu_get_blocked2'>
        </block>
        <block type='motion_edu_get_key'>
        </block>
        <block type='motion_edu_fan'>
        </block>
        <block type='motion_edu_pump'>
        </block>
        <block type='motion_edu_set_light'>
        </block>
        <block type='motion_edu_get_soil'>
        </block>
        <block type='motion_edu_get_light'>
        </block>
        <block type='motion_edu_get_flame2'>
        </block>
        <block type='motion_edu_get_smoke2'>
        </block>
        <block type='motion_edu_matrix_key_init'>
        </block>
        <block type='motion_edu_matrix_key'>
        </block>
        <block type='motion_edu_dht_temperature'>
        </block>
        <block type='motion_edu_dht_humidity'>
        </block>
        <block type='motion_edu_set_servo'>
            <value name='ANGLE'>
                <shadow type='math_number'>
                    <field name='NUM'>60</field>
                </shadow>
            </value>
        </block>
        </category>"},""";
    jsonstr += """{"name":"micro:bit扩展板", "xml":"
    <category name='micro:bit扩展板' id='motor' colour='#9966FF' secondaryColour='#774DCB'>
        <block type='motion_set_motor'>
            <value name='SPEED'>
                <shadow type='math_number'>
                    <field name='NUM'>255</field>
                </shadow>
            </value>
        </block>
        <block type='motion_stop_motor'>
        </block>
        </category>"},""";
    jsonstr += """{"name":"舵机", "xml":"
    <category name='舵机' id='servo' colour='#FF00FF' secondaryColour='#3373CC'>
        <block type='motion_set_servo'>
            <value name='ANGLE'>
                <shadow type='math_number'>
                    <field name='NUM'>60</field>
                </shadow>
            </value>
        </block>
        </category>"},""";
    jsonstr += """{"name":"超声波", "xml":"
    <category name='超声波' id='sonic' colour='#FF0000' secondaryColour='#3373CC'>
    <block type='motion_get_sonic'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"温湿度", "xml":"
    <category name='温湿度' id='dht' colour='#c71585' secondaryColour='#BD42BD'>
    <block type='motion_dht_temperature'></block>
    <block type='motion_dht_humidity'></block>
    </category>"},""";
    jsonstr += """{"name":"矩阵键盘", "xml":"
    <category name='矩阵键盘' id='matrixkey' colour='#867892' secondaryColour='#BD42BD'>
    <block type='motion_matrix_key_init'>
    </block>
    <block type='motion_matrix_key'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"PM2.5", "xml":"
    <category name='PM2.5' id='pm25' colour='#ffbf00' secondaryColour='#BD42BD'>
    <block type='motion_get_pm25'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"土壤湿度", "xml":"
    <category name='土壤湿度' id='soil' colour='#808000' secondaryColour='#BD42BD'>
    <block type='motion_get_soil'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"火焰", "xml":"
    <category name='火焰' id='flame' colour='#2F4F4F' secondaryColour='#BD42BD'>
    <block type='motion_get_flame_init'>
    </block>
    <block type='motion_get_flame'>
    </block>
    <block type='motion_get_flame2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"烟雾", "xml":"
    <category name='烟雾' id='smoke' colour='#c71585' secondaryColour='#BD42BD'>
    <block type='motion_get_smoke_init'>
    </block>
    <block type='motion_get_smoke'>
    </block>
    <block type='motion_get_smoke2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"红外热释电", "xml":"
    <category name='红外热释电' id='infrared' colour='#ffc0a0' secondaryColour='#BD42BD'>
    <block type='motion_get_infrared_init'>
    </block>
    <block type='motion_get_infrared'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"光敏传感器", "xml":"
    <category name='光敏传感器' id='light' colour='#b7ff85' secondaryColour='#BD42BD'>
    <block type='motion_get_light'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"灰度传感器", "xml":"
    <category name='灰度传感器' id='gray' colour='#a725ff' secondaryColour='#BD42BD'>
    <block type='motion_get_gray'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"气压传感器", "xml":"
    <category name='气压传感器' id='airpressure' colour='#975565' secondaryColour='#BD42BD'>
    <block type='motion_get_airpressure'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"雨滴传感器", "xml":"
    <category name='雨滴传感器' id='raindrop' colour='#ff4555' secondaryColour='#BD42BD'>
    <block type='motion_get_raindrop_init'>
    </block>
    <block type='motion_get_raindrop'>
    </block>
    <block type='motion_get_raindrop2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"红外避障", "xml":"
    <category name='红外避障' id='blocked' colour='#7755bb' secondaryColour='#BD42BD'>
    <block type='motion_get_blocked_init'>
    </block>
    <block type='motion_get_blocked'>
    </block>
    <block type='motion_get_blocked2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"心率传感器", "xml":"
    <category name='心率传感器' id='heartbeat' colour='#0055bb' secondaryColour='#BD42BD'>
    <block type='motion_get_heartbeat'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"浊度传感器", "xml":"
    <category name='浊度传感器' id='tur' colour='#77ddbb' secondaryColour='#BD42BD'>
    <block type='motion_get_tur_init'>
    </block>
    <block type='motion_get_tur'>
    </block>
    <block type='motion_get_tur2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"LED灯", "xml":"
    <category name='LED灯' id='setlight' colour='#775500' secondaryColour='#BD42BD'>
    <block type='motion_set_light'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"MP3", "xml":"
    <category name='MP3' id='mp3' colour='#775555' secondaryColour='#BD42BD'>
    <block type='motion_mp3_set_vol'>
    <value name='VOL'><shadow type='math_number'><field name='NUM'>30</field></shadow></value>
    </block>
    <block type='motion_mp3_play'>
    </block>
    <block type='motion_mp3_pause'>
    </block>
    <block type='motion_mp3_stop'>
    </block>
    <block type='motion_mp3_next'>
    </block>
    <block type='motion_mp3_pre'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"按键", "xml":"
    <category name='按键' id='setkey' colour='#00ddbb' secondaryColour='#BD42BD'>
    <block type='motion_get_key'>
    </block>
    </category>"},""";
    jsonstr +="]"
    jsonstr = jsonstr.replace("\n","")
    return jsonstr

# define extension devices
def getExtensions():
    extensions = """[{
        'name': '大师兄扩展板Plus',
        'tags': [
            'expander'
        ],
        'costumes': [
            {
                'md5ext': 'huawei.png',
            }
        ]
    },{
        'name': '大师兄扩展板-G',
        'tags': [
            'expander'
        ],
        'costumes': [
            {
                'md5ext': 'pzboard.png',
            }
        ]
    },{
        'name': '大师兄扩展板-M',
        'tags': [
            'expander'
        ],
        'costumes': [
            {
                'md5ext': 'eduboard.png',
            }
        ]
    },{
        'name': 'micro:bit扩展板',
        'tags': [
            'expander'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded47.svg',
            }
        ]
    },{
        'name': 'PZCar',
        'tags': [
            'robot'
        ],
        'costumes': [
            {
                'md5ext': 'dsxcar.png',
            }
        ]
    },{
        'name': '舵机',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded48.svg',
            }
        ]
    },
            {
        'name': '矩阵键盘',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded63.svg',
            }
        ]
    },
            {
        'name': '超声波',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded49.svg',
            }
        ]
    },
            {
        'name': '温湿度',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded51.svg',
            }
        ]
    },
            {
        'name': 'PM2.5',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded64.svg',
            }
        ]
    },
            {
        'name': '土壤湿度',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded65.svg',
            }
        ]
    },
            {
        'name': '火焰',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded66.svg',
            }
        ]
    },
            {
        'name': '烟雾',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded67.svg',
            }
        ]
    },
            {
        'name': '红外热释电',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded59.svg',
            }
        ]
    },
            {
        'name': '光敏传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded68.svg',
            }
        ]
    },
            {
        'name': '灰度传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded69.svg',
            }
        ]
    },
            {
        'name': '气压传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6a.svg',
            }
        ]
    },
            {
        'name': '雨滴传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6b.svg',
            }
        ]
    },
            {
        'name': '红外避障',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6c.svg',
            }
        ]
    },
            {
        'name': '心率传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6e.svg',
            }
        ]
    },
            {
        'name': 'MP3',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6d.svg',
            }
        ]
    },
            {
        'name': '浊度传感器',
        'tags': [
            'sensor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded6f.svg',
            }
        ]
    },
            {
        'name': 'LED灯',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded70.svg',
            }
        ]
    },
            {
        'name': '按键',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded71.svg',
            }
        ]
    }]"""
    return extensions

# communication protocol Packet object
class Packet:
    length = 0
    packet_type = 0
    content = b''
    def __init__(self, packet_type, packet_content):
        self.packet_type = packet_type
        self.content = packet_content

    # encode Packet object to bytedata
    def Encoder(self):
        mainBuf = self.content
        buf = b'\xA5\x5A' + (len(mainBuf) + 7).to_bytes(2, 'big') + self.packet_type.to_bytes(1,'big') + mainBuf
        buf = buf + self.crc16(buf)
        return buf

    def crc16(self, x, invert=True):
        a = 0xFFFF
        b = 0xA001
        tmp = 0
        for byte in x:
            a ^= byte
            for i in range(8):
                last = a % 2
                a >>= 1
                if last == 1:
                    a ^= b
        if invert == True:
            tmp |= 0xff & a >> 8
            tmp |= a << 8 & 0xff00
        else:
            tmp = a
        return tmp.to_bytes(2, 'big')

        
# ------------------------------ download script protocol process  -------------------------------
ohos_upload = 0;
ohos_time = 0;
ohos_resend = 0;
tempOhosBuf = b''
ohos_file = ""
block_size = 64;
ohos_bytes = b''
ohos_data = b''
ohos_str = "";
ohos_tempstr = "";
ohos_filearr = []
ohos_fileindex = 0;
uploadtaskFlag = False;
uploadMode = False;

fileContent = "";

uploadStarttime = 0;
def SendSerialData(data):
    SendData(Packet(0x02,data).Encoder())

# start download script to hardware
def startUpload():
    global ohos_tempstr,ohos_resend,uploadtaskFlag,ohos_data,ohos_upload
    ohos_tempstr = "";
    ohos_resend = 0;
    ohos_tempstr = "";
    uploadtaskFlag = False;
    ohos_data = b'\xA5\x5A\x00\x05\x03'
    ohos_upload = 1;
    SendSerialData(ohos_data)

# process protocol data
def codeProtocolProcess(data):
    global ohos_upload,ohos_time,uploadtaskFlag,ohos_tempstr,ohos_data,ohos_fileindex,block_size,tempOhosBuf,firmwareVersion
    if len(data) >= 7:
        data = data[5:-2]
    if ohos_upload == 1:
        ohos_time = time.time()
        time.sleep(0.2)
        ohos_data = b'\xA5\x5A\x04\x00\x00'
        SendSerialData(ohos_data)
        uploadtaskFlag = True
        ohos_upload = 2
        return
    elif ohos_upload == 2:
        recvStr = b''
        for i in range(0,len(data)):
            if data[i] < 128:
                recvStr+=data[i:i+1]
        ohos_tempstr += recvStr.decode("utf8")
        if ">>>" in ohos_tempstr:
            ohos_time = time.time()
            ohos_tempstr = ""
            ohos_data = b'\xA5\x5A\x00\x05\x04'
            SendSerialData(ohos_data)
        elif len(ohos_tempstr)>4 and "FF" in ohos_tempstr:
            ohos_time = time.time()
            ohos_tempstr = ""
            uploadtaskFlag = False
            ohos_upload = 0
        else:
            # read firmware version
            for i in range(0,len(data)):
                if data[i] == 0xa5 and (i+8) < len(data):
                    if data[i+4] == 0x04:
                        v1 = data[i+5]
                        v2 = data[i+6]
                        v3 = data[i+7]
                        v4 = data[i+8]
                        shouldUpdate = False
                        if(firmwareVersion != ""):
                            curV1 = int(firmwareVersion.split('.')[0])
                            curV2 = int(firmwareVersion.split('.')[1])
                            curV3 = int(firmwareVersion.split('.')[2])
                            curV4 = int(firmwareVersion.split('.')[3])
                            if(curV2 > v2):
                                shouldUpdate = True
                            else:
                                if(curV3 > v3):
                                    shouldUpdate = True
                                else:
                                    if(curV4 > v4):
                                        shouldUpdate = True
                        if(shouldUpdate):
                            pac = Packet(0x11,b'')
                            SendData(pac.Encoder())
                            return
                            # sys.exit(0)
                        else:
                            if(len(ohos_file) < block_size):
                                ohos_str = ohos_file
                            else:
                                ohos_str = ohos_file[ohos_fileindex:ohos_fileindex + block_size]
                            ohos_bytes = ohos_str.encode("utf8")
                            ohos_data = b'\xA5\x5A'
                            ohos_data += (len(ohos_bytes) + 11).to_bytes(2,'big')
                            ohos_data += b'\x01'
                            ohos_data += int(ohos_fileindex / block_size).to_bytes(2,'big')
                            ohos_data += len(ohos_bytes).to_bytes(2,'big')
                            ohos_data += ohos_bytes
                            crc = getCRC(ohos_data)
                            ohos_data += crc
                            SendSerialData(ohos_data);
                            ohos_fileindex += block_size;
                            ohos_upload = 4;
                            ohos_time = time.time()
                        
        return
    elif ohos_upload == 4:
        if len(tempOhosBuf) > 0:
            tempOhosBuf = b''
            data = tempOhosBuf + data
        dataLen = len(data)
        if(dataLen < 4):
            tempOhosBuf = data
            return
        if data[0] == 0xa5 and data[1] == 0x5a:
            ohos_time = time.time()
            mainLen = data[2] * 256 + data[3]
            if dataLen >= mainLen:
                if data[4] == 0x01:
                    recvID = data[5] * 256 + data[6]
                    if recvID == int(int(ohos_fileindex - block_size)/block_size):
                        if data[7] == 0:
                            if len(ohos_file) <= ohos_fileindex:
                                ohos_data = b'\xA5\x5A\x00\x05\x02'
                                SendSerialData(ohos_data)
                                ohos_upload = 5
                                return
                            if len(ohos_file) < ohos_fileindex + block_size:
                                ohos_str = ohos_file[ohos_fileindex:]
                            else:
                                ohos_str = ohos_file[ohos_fileindex:(ohos_fileindex + block_size)]
                            ohos_bytes = ohos_str.encode("utf8")
                            ohos_data = b'\xA5\x5A' + (len(ohos_bytes) + 11).to_bytes(2,'big') + b'\x01' + int(ohos_fileindex/block_size).to_bytes(2,'big') + len(ohos_bytes).to_bytes(2,'big') + ohos_bytes
                            crc = getCRC(ohos_data)
                            ohos_data += crc
                            SendSerialData(ohos_data)
                            ohos_fileindex += block_size
                            percent = int((ohos_fileindex/len(ohos_file))*100)
                            pac = Packet(6,percent.to_bytes(1,'big'))
                            SendData(pac.Encoder())
                        else:
                            SendSerialData(ohos_data)
        time.sleep(0.01)
        return
    elif ohos_upload == 5:
        if len(tempOhosBuf) > 0:
            tempOhosBuf = b''
            data = tempOhosBuf + data
        dataLen = len(data)
        if(dataLen < 4):
            tempOhosBuf = data
            return
        if data[0] == 0xa5 and data[1] == 0x5a:
            ohos_time = time.time()
            mainLen = data[2] * 256 + data[3]
            if dataLen >= mainLen:
                if data[4] == 0x02:
                    ohos_tempstr = ""
                    ohos_fileindex = 0
                    ohos_upload = 0
                    ohos_time = 0
                    uploadMode = False
                    uploadStarttime = 0
                    pac = Packet(4,b'')
                    SendData(pac.Encoder())
                    sys.exit(0)
                    return
        return
    strData = data.decode("utf8")

# ------------------------------ download firmware protocol process  -------------------------------
m_toFlash = 0
def AppendMessage(msg):
    print(msg)
    pac = Packet(0x12, msg.encode("utf8"))
    SendData(pac.Encoder())
def SetMessage(msg):
    print(msg)
    pac = Packet(0x13, msg.encode("utf8"))
    SendData(pac.Encoder())
def firmwareProtocolProcess(data):
    global m_toFlash
    if len(data) >= 7:
        data = data[5:-2]
    if ((m_toFlash == 0) and (data.startswith(b'\xEF\xBE\xAD\xDE\x12\x00\xF0\x0F\x00\xC2\x01\x00\x08\x01\x00\x00\xE0\x64'))):
        m_toFlash+=1
        AppendMessage("正在连接,请按下开发板上的复位键...\r\n\r\n")
    elif ((m_toFlash == 2) and ( not (data.startswith(b'EF\xBE\xAD\xDE\x12\x00\xF0\x0F\x00\xC2\x01\x00\x08\x01\x00\x00\xE0\x64')))):
        m_toFlash+=1
        SetMessage("写入中 ");
    elif (m_toFlash >= 3):
        m_toFlash+=1
        if (m_toFlash % 15 == 0):
            AppendMessage(">");
def firmwareProtocolProcess2(data):
    global m_toFlash
    if len(data) >= 7:
        data = data[5:-2]
    if((m_toFlash == 1) and (data.startswith(b'\xEF\xBE\xAD\xDE\x0C'))):
        m_toFlash+=1

# different startup parameters process
if(sys.argv[1] == "-convertcode"):
    filepath = sys.argv[2]
    if(os.path.exists(filepath)):
        f = open(filepath,"r",encoding = "utf-8")
        tempCode = f.read()
        print(convertDSXCode(tempCode))
    sys.exit(0)
elif(sys.argv[1] == "-hardware"):
    print(getHardwareDef())
    sys.exit(0)
elif(sys.argv[1] == "-blockdef"):
    print(getBlockDef())
    sys.exit(0)
elif(sys.argv[1] == "-category"):
    print(getCategory())
    sys.exit(0)
elif(sys.argv[1] == "-extension"):
    print(getExtensions())
    sys.exit(0)
elif(sys.argv[1] == "-extensionCategory"):
    print(getExtensionCategory())
    sys.exit(0)

# receive data from PZstudio process
DOWNLOAD_CODE = 1
DOWNLOAD_FIRMWARE = 2
mode = int(sys.argv[1])
init()
firmwareVersion = ""
startUpload()
while True:
    data = RecvData()
    # print(data)
    dataLen = len(data)
    if(dataLen >= 7):
        if data[0] == 0xa5 and data[1] == 0x5a:
            mainLen = data[2] * 256 + data[3]
            if dataLen >= mainLen:
                if data[4] == 0x02:
                    if(mode == DOWNLOAD_CODE):
                        codeProtocolProcess(data)
                    elif mode == DOWNLOAD_FIRMWARE:
                        firmwareProtocolProcess(data)
                elif data[4] == 0x03:
                    # read script file to download
                    filenameLen = mainLen - 7
                    filename = data[5:-2].decode("utf-8")
                    if(os.path.exists(filename)):
                        f = open(filename,"r",encoding = "utf-8")
                        ohos_file = f.read()
                        f.close()
                elif data[4] == 0x55:
                    firmwareProtocolProcess2(data)
                elif data[4] == 0x05:
                    sys.exit(0)
                elif data[4] == 0x06:
                    ohos_time = time.time()
                    ohos_resend = 0
                    ohos_tempstr = ""
                    ohos_upload = 3
                    if(len(ohos_file) < block_size):
                        ohos_str = ohos_file
                    else:
                        ohos_str = ohos_file[ohos_fileindex:ohos_fileindex + block_size]
                    ohos_bytes = ohos_str.encode("utf8")
                    ohos_data = b'\xA5\x5A'
                    ohos_data += (len(ohos_bytes) + 11).to_bytes(2,'big')
                    ohos_data += b'\x01'
                    ohos_data += int(ohos_fileindex / block_size).to_bytes(2,'big')
                    ohos_data += len(ohos_bytes).to_bytes(2,'big')
                    ohos_data += ohos_bytes
                    crc = getCRC(ohos_data)
                    ohos_data += crc
                    SendSerialData(ohos_data);
                    ohos_fileindex += block_size;
                    ohos_upload = 4;
                    ohos_time = time.time()
                elif data[4] == 0x07:
                    SendSerialData(ohos_data)
                elif data[4] == 0x10:
                    firmwareVersion = str(data[5]) + "." + str(data[6]) + "." + str(data[7]) + "." + str(data[8])

