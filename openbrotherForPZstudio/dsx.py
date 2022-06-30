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
    if (realtimeCode.find("touch.") > -1):
        varList += "touch" + ","
    if (realtimeCode.find("light.") > -1):
        varList += "light" + ","
    if (realtimeCode.find("mic.") > -1):
        varList += "mic" + ","
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
    if (temp.find("pm.get_pm2_5") > -1):
        dsxcode += "from ext_device import PMxx\n";
        dsxcode += "pm = PMxx()\n"
    if (temp.find("_thread.") > -1):
        dsxcode += "import _thread\n"
    if (temp.find("math.") > -1):
        dsxcode += "import math\n"
    if (temp.find("random.") > -1):
        dsxcode += "import random\n"
    if (temp.find("UART(") > -1):
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
    if (temp.find("socket.") > -1):
        dsxcode += "import socket\n";
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
    blockDef = """Blockly.Python['motion_dsx_led_init'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "led.init("+index+")\n";
        };
        Blockly.Python['motion_dsx_led_on'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "led" + index + ".on()\n";
        };
        Blockly.Python['motion_dsx_led_off'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "led" + index + ".off()\n";
        };
        Blockly.Python['motion_dsx_beep_init'] = function(block) {
            return "machine.initBeep()\n";
        };
        Blockly.Python['motion_dsx_beep_on'] = function(block) {
            return "beep.on()\n";
        };
        Blockly.Python['motion_dsx_beep_off'] = function(block) {
            return "beep.off()\n";
        };
        Blockly.Python['motion_dsx_playmusic'] = function(block) {
            var music = block.getFieldValue("MUSIC");
            var type = block.getFieldValue("TYPE");
            
            if(music.startsWith("'")&&music.endsWith("'")){
                music = music.slice(1,-1)
            }
            
            if(music == "default_music"){
                music = "0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x15, 0x02,0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x17, 0x02, 0x18, 0x02,0x19, 0x01, 0x17, 0x02, 0x18, 0x02, 0x19, 0x01, 0x19, 0x03,0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02, 0x15, 0x16,0x19, 0x03, 0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02,0x15, 0x16, 0x15, 0x02, 0x0F, 0x02, 0x15, 0x01, 0x15, 0x02,0x0F, 0x02, 0x15, 0x01, 0x00, 0x00"
            }
            return "beep.player(bytes(["+music+"])," + type + ")\n";
        };
        Blockly.Python['motion_dsx_playmusic2'] = function(block) {
            var type = block.getFieldValue("TYPE");
            var music = Blockly.Python.valueToCode(block, 'MUSIC', Blockly.Python.ORDER_ATOMIC);
            
            if(music.startsWith("'")&&music.endsWith("'")){
                music = music.slice(1,-1)
            }
            return "machine.music_player(bytes(["+music+"])," + type + ")\n";
        };
        Blockly.Python['motion_dsx_stopmusic'] = function(block) {
            return "beep.stop()\n";
        };
        Blockly.Python['motion_dsx_init_key'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "machine.initKey(" + index + ")\n";
        };
        Blockly.Python['motion_dsx_get_key'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var state = block.getFieldValue("STATE")
            return ["(btn" + index + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_icm_init'] = function(block) {
            return "machine.icm_init()\n";
        };
        Blockly.Python['motion_dsx_read_acc'] = function(block) {
            return ["imu.acc()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_read_gyro'] = function(block) {
            return ["imu.gyro()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_read_a'] = function(block) {
            var index = block.getFieldValue("INDEX");
            return ["imu.acc()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_read_g'] = function(block) {
            var index = block.getFieldValue("INDEX");
            return ["imu.gyro()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_read_angle'] = function(block) {
            var index = block.getFieldValue("INDEX");
            return ["imu.angle()[" + index +"]", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_oled_init'] = function(block) {
            return "oled.init()\n";
        };
        Blockly.Python['motion_dsx_oled_flush'] = function(block) {
            return "oled.flush()\n";
        };
        Blockly.Python['motion_dsx_oled_showstr'] = function(block) {
            var row = Blockly.Python.valueToCode(block, 'ROW', Blockly.Python.ORDER_ATOMIC);
            var col = Blockly.Python.valueToCode(block, 'COL', Blockly.Python.ORDER_ATOMIC);
            var string = Blockly.Python.valueToCode(block, 'STRING', Blockly.Python.ORDER_ATOMIC);
            var color = block.getFieldValue("COLOR");
            return "oled.show_str(" + "str(" + string + ")," + row +"," + col + "," + color + ",0)\n";
        };
        Blockly.Python['motion_dsx_oled_showstr2'] = function(block) {
            var row = Blockly.Python.valueToCode(block, 'ROW', Blockly.Python.ORDER_ATOMIC);
            var string = Blockly.Python.valueToCode(block, 'STRING', Blockly.Python.ORDER_ATOMIC);
            var color = block.getFieldValue("COLOR");
            return "oled.show_str_line(" + "str(" + string + ")," + row + "," + color + ")\n";
        };
        Blockly.Python['motion_dsx_oled_fillline'] = function(block) {
            var row = Blockly.Python.valueToCode(block, 'ROW', Blockly.Python.ORDER_ATOMIC);
            var color = block.getFieldValue("COLOR");
            return "oled.fill_line(" + row + "," + color + ")\n";
        };
        Blockly.Python['motion_dsx_oled_clear'] = function(block) {
            var value = block.getFieldValue("VALUE");
            if(value == "0" || value == "2"){
                return "oled.fill_screen(0)\n";
            }else{
                return "oled.fill_screen(0xff)\n";
            }
        };
        Blockly.Python['motion_dsx_oled_pixel'] = function(block) {
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var state = block.getFieldValue('STATE');
            return "oled.pixel("+x+","+y+","+state+")\n"
        };
        Blockly.Python['motion_dsx_oled_progress'] = function(block) {
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
            var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
            var progress = Blockly.Python.valueToCode(block, 'PROGRESS', Blockly.Python.ORDER_ATOMIC);
            return "myUI.ProgressBar(" + x + ", " + y + ", " + w + ", " + h + ", " + progress +")\n"
        };
        Blockly.Python['motion_dsx_oled_histogram'] = function(block) {
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
            var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
            var progress = Blockly.Python.valueToCode(block, 'PROGRESS', Blockly.Python.ORDER_ATOMIC);
            var direction = block.getFieldValue('DIRECTION');
            return "myUI.stripBar(" + x + ", " + y + ", " + w + ", " + h + ", " + progress + ", " + direction +",1)\n"
        };
        Blockly.Python['motion_dsx_oled_line'] = function(block) {
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var length = Blockly.Python.valueToCode(block, 'LENGTH', Blockly.Python.ORDER_ATOMIC);
            var mode = block.getFieldValue('MODE');
            var direction = block.getFieldValue('DIRECTION');
            if(direction == "0"){
                return "oled.vline(" + x + ", " + y + ", " + length + ", " + mode +")\n"
            }else{
                return "oled.hline(" + x + ", " + y + ", " + length + ", " + mode +")\n"
            }
        };
        Blockly.Python['motion_dsx_oled_line2'] = function(block) {
            var x1 = Blockly.Python.valueToCode(block, 'X1', Blockly.Python.ORDER_ATOMIC);
            var y1 = Blockly.Python.valueToCode(block, 'Y1', Blockly.Python.ORDER_ATOMIC);
            var x2 = Blockly.Python.valueToCode(block, 'X2', Blockly.Python.ORDER_ATOMIC);
            var y2 = Blockly.Python.valueToCode(block, 'Y2', Blockly.Python.ORDER_ATOMIC);
            var mode = block.getFieldValue('MODE');
            return "oled.line(" + x1 + ", " + y1 + ", " + x2  + ", " + y2 + ", " + mode +")\n"
        };
        Blockly.Python['motion_dsx_oled_rect'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var mode2 = block.getFieldValue('MODE2');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
            var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
            if(mode2 == "0"){
                return "oled.draw_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + mode1 +")\n"
            }else{
                return "oled.fill_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + mode1 +")\n"
            }
        };
        Blockly.Python['motion_dsx_oled_boarder'] = function(block) {
            var mode1 = block.getFieldValue('MODE');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var w = Blockly.Python.valueToCode(block, 'W', Blockly.Python.ORDER_ATOMIC);
            var h = Blockly.Python.valueToCode(block, 'H', Blockly.Python.ORDER_ATOMIC);
            var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
            return "oled.draw_round_rectangle(" + x + ", " + y + ", " + w  + ", " + h + ", " + r + ", " + mode1 +")\n"
        };
        Blockly.Python['motion_dsx_oled_circle'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var mode2 = block.getFieldValue('MODE2');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
            if(mode2 == "0"){
                return "oled.draw_circle(" + x + ", " + y + ", " + r + ", " + mode1 +")\n"
            }else{
                return "oled.fill_circle(" + x + ", " + y + ", " + r + ", " + mode1 +")\n"
            }
        };
        Blockly.Python['motion_dsx_oled_ellipse'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var mode2 = block.getFieldValue('MODE2');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var rx = Blockly.Python.valueToCode(block, 'RX', Blockly.Python.ORDER_ATOMIC);
            var ry = Blockly.Python.valueToCode(block, 'RY', Blockly.Python.ORDER_ATOMIC);
            if(mode2 == "0"){
                return "oled.draw_ellipse(" + x + ", " + y + ", " + rx + ", " + ry + "," + mode1 +")\n"
            }else{
                return "oled.fill_ellipse(" + x + ", " + y + ", " + rx + ", " + ry + "," + mode1 +")\n"
            }
        };
        Blockly.Python['motion_dsx_oled_arc'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
            var angle1 = Blockly.Python.valueToCode(block, 'ANGLE1', Blockly.Python.ORDER_ATOMIC);
            var angle2 = Blockly.Python.valueToCode(block, 'ANGLE2', Blockly.Python.ORDER_ATOMIC);
            
            return "oled.draw_arc(" + x + ", " + y + ", " + r + ", " + angle1 + ", " + angle2 + "," + mode1 +")\n"
            
        };
        Blockly.Python['motion_dsx_oled_triangle'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var mode2 = block.getFieldValue('MODE2');
            var x1 = Blockly.Python.valueToCode(block, 'X1', Blockly.Python.ORDER_ATOMIC);
            var y1 = Blockly.Python.valueToCode(block, 'Y1', Blockly.Python.ORDER_ATOMIC);
            var x2 = Blockly.Python.valueToCode(block, 'X2', Blockly.Python.ORDER_ATOMIC);
            var y2 = Blockly.Python.valueToCode(block, 'Y2', Blockly.Python.ORDER_ATOMIC);
            var x3 = Blockly.Python.valueToCode(block, 'X3', Blockly.Python.ORDER_ATOMIC);
            var y3 = Blockly.Python.valueToCode(block, 'Y3', Blockly.Python.ORDER_ATOMIC);
            if(mode2 == "0"){
                return "oled.draw_triangle(" + x1 + ", " + y1 + ", " + x2 + ", " + y2 + ", " + x3 + ", " + y3 + ", " + mode1 +")\n"
            }else{
                return "oled.fill_triangle(" + x1 + ", " + y1 + ", " + x2 + ", " + y2 + ", " + x3 + ", " + y3 + ", " + mode1 +")\n"
            }
        };
        Blockly.Python['motion_dsx_oled_pointer'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
            var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
            return "oled.line_of_arc(" + x + ", " + y + ", " + r + ", " + angle+ ", " + mode1 + ")\n"
        };
        Blockly.Python['motion_dsx_oled_scale'] = function(block) {
            var mode1 = block.getFieldValue('MODE1');
            var x = Blockly.Python.valueToCode(block, 'X', Blockly.Python.ORDER_ATOMIC);
            var y = Blockly.Python.valueToCode(block, 'Y', Blockly.Python.ORDER_ATOMIC);
            var r = Blockly.Python.valueToCode(block, 'R', Blockly.Python.ORDER_ATOMIC);
            var angle = Blockly.Python.valueToCode(block, 'ANGLE', Blockly.Python.ORDER_ATOMIC);
            var scale = Blockly.Python.valueToCode(block, 'SCALE', Blockly.Python.ORDER_ATOMIC);
            return "oled.line_of_kedu(" + x + ", " + y + ", " + r + ", " + scale+ ", " + angle+ ", " + mode1 + ")\n"
        };

        Blockly.Python['motion_dsx_oled_image'] = function(block) {
            var image = block.getFieldValue("IMAGE");
            return "oled.bit_map(0,0,128,64,0,bytearray([" + image +"]))\n";
        };
        Blockly.Python['motion_dsx_connect_wifi'] = function(block) {
            var ssid = Blockly.Python.valueToCode(block, 'SSID', Blockly.Python.ORDER_ATOMIC);
            var password = Blockly.Python.valueToCode(block, 'PASSWORD', Blockly.Python.ORDER_ATOMIC);
            return "network.connectWifi(" + ssid + "," + password + ")\n";
        };
        Blockly.Python['motion_dsx_isconnected'] = function(block) {
            return ["network.isconnected()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_getip'] = function(block) {
            return ["network.ifconfig()[0]", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['event_dsx_whenboardkeypressed'] = function(block) {
            var key = block.getFieldValue("KEY_OPTION")
            var state = block.getFieldValue("STATE_OPTION")
            var stateStr = "up"
            if(state == 0){
                stateStr = "down"
            }
            var keyStr = "a"
            if(key == 2){
                keyStr = "b"
            }
            var code = "print('listeningBoardKey("+key+","+state+")')\n";
            code = code + "def on_button_"+keyStr+"_"+stateStr+"(_):\n"
            return code
        };
        Blockly.Python['event_dsx_whenpin'] = function(block) {
            var key = block.getFieldValue("PIN_OPTION")
            var state = block.getFieldValue("STATE_OPTION")
            var stateStr = "low"
            if(state == 1){
                stateStr = "high"
            }
            var code = "print('listeningBoardPin("+key+","+state+")')\n";
            code = code + "def on_pin"+key+"_to_"+stateStr+"(_):\n"
            return code
        };
        Blockly.Python['event_tq_whenboardkeypressed'] = function(block) {
            var key = block.getFieldValue("KEY_OPTION")
            var state = block.getFieldValue("STATE_OPTION")
            var stateStr = "up"
            if(state == 0){
                stateStr = "down"
            }
            var keyStr = "a"
            if(key == 2){
                keyStr = "b"
            }
            var code = "print('listeningBoardKey("+key+","+state+")')\n";
            code = code + "def on_button_"+keyStr+"_"+stateStr+"(_):\n"
            return code
        };
        Blockly.Python['event_tq_whentouchpadpressed'] = function(block) {
            var key = block.getFieldValue('KEY_OPTION');
            var state = block.getFieldValue('STATE_OPTION');
            var code = "def on_touchpad_"+key+"_"+state+"(_):\n"
            return code
        };
        Blockly.Python['event_tq_whenpin'] = function(block) {
            var key = block.getFieldValue("PIN_OPTION")
            var state = block.getFieldValue("STATE_OPTION")
            var stateStr = "low"
            if(state == 1){
                stateStr = "high"
            }
            var code = "print('listeningBoardPin("+key+","+state+")')\n";
            code = code + "def on_pin"+key+"_to_"+stateStr+"(_):\n"
            return code
        };
        Blockly.Python['motion_tq_isconnected'] = function(block) {
            return ["network.isconnected()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_tq_getip'] = function(block) {
            return ["network.ifconfig()[0]", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_disconnect_wifi'] = function(block) {
            return "network.disconnectWifi()\n";
        };
        Blockly.Python['motion_dsx_start_hotspot'] = function(block) {
            var ssid = Blockly.Python.valueToCode(block, 'SSID', Blockly.Python.ORDER_ATOMIC);
            var password = Blockly.Python.valueToCode(block, 'PASSWORD', Blockly.Python.ORDER_ATOMIC);
            return "network.startHotspot(" + ssid + "," + password + ")\n";
        };
        Blockly.Python['motion_dsx_config_hotspot'] = function(block) {
            var ip = Blockly.Python.valueToCode(block, 'IP', Blockly.Python.ORDER_ATOMIC);
            var netmask = Blockly.Python.valueToCode(block, 'NETMASK', Blockly.Python.ORDER_ATOMIC);
            var gw = Blockly.Python.valueToCode(block, 'GATEWAY', Blockly.Python.ORDER_ATOMIC);
            return "network.configHotspot(" + ip + "," + netmask + "," + gw + ")\n";
        };
        Blockly.Python['motion_dsx_stop_hotspot'] = function(block) {
            return "network.stopHotspot()\n";
        };
        Blockly.Python['motion_dsx_socket_create'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var type = block.getFieldValue("TYPE");
            var type2 = block.getFieldValue("TYPE2");
            return name + " = socket.socket(socket."+type+", socket."+type2+")\n";
        };
        Blockly.Python['motion_dsx_socket_close'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return name + ".close()\n";
        };
        Blockly.Python['motion_dsx_socket_bind'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return name + ".bind(("+addr+", "+port+"))\n";
        };
        Blockly.Python['motion_dsx_socket_timeout'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var timeout = Blockly.Python.valueToCode(block, 'TIMEOUT', Blockly.Python.ORDER_ATOMIC);
            return name + ".settimeout("+timeout+")\n";
        };
        Blockly.Python['motion_dsx_socket_listen'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return name + ".listen("+count+")\n";
        };
        Blockly.Python['motion_dsx_socket_setbroadcast'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return name + ".setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST,1)\n";
        };
        Blockly.Python['motion_dsx_socket_connect'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return ["("+name + ".connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_accept'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return [name + ".accept()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_send'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return name + ".send("+content+")\n";
        };
        Blockly.Python['motion_dsx_socket_sendto'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            if(addr.startsWith("'")&&addr.endsWith("'")){
                addr = addr.slice(1,-1)
            }
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            if(port.startsWith("'")&&port.endsWith("'")){
                port = port.slice(1,-1)
            }
            return name + ".sendto("+content+",(\""+addr + "\"," + port +"))\n";
        };
        Blockly.Python['motion_dsx_socket_recv'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_recvfrom'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var len = Blockly.Python.valueToCode(block, 'LENGTH', Blockly.Python.ORDER_ATOMIC);
            return [name + ".recvfrom("+len+")", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_create_server'] = function(block) {
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return "dsx_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);dsx_server.bind(('0.0.0.0'," + port + "));dsx_server.listen(" + count + ");_thread.start_new_thread(dsx_server_thread,())\n";
        };
        Blockly.Python['motion_dsx_conn_create_client'] = function(block) {
            return "dsx_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\n";
        };
        Blockly.Python['motion_dsx_conn_connect'] = function(block) {
            var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return ["(dsx_client.connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_accept'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return name + " = dsx_server.accept()\n";
        };
        Blockly.Python['motion_dsx_conn_hasconn'] = function(block) {
            return ["dsx_conn_cnt() > 0", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_getconn'] = function(block) {
            // return ["dsx_clientlist.pop(0)", Blockly.Python.ORDER_ATOMIC];
            return ["get_dsxclient()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_send'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return name + ".send("+content+")\n";
        };
        Blockly.Python['motion_dsx_conn_recv'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
            return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_client_send'] = function(block) {
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return "dsx_client.send("+content+")\n";
        };
        Blockly.Python['motion_dsx_conn_client_recv'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return ["dsx_client.recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_close_server'] = function(block) {
            return "dsx_server.close()\n";
        };
        Blockly.Python['motion_dsx_conn_close_client'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return "dsx_client.close()\n";
        };
        Blockly.Python['motion_dsx_digital_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var state = block.getFieldValue("STATE");
            return ["(pin" + pin + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_analog_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_set_digital_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var state = block.getFieldValue("STATE");
            return "pin" + pin + " = Pin(" + pin + ",mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin" + pin + ".value("+state+")\n";
        };
        Blockly.Python['motion_dsx_set_analog_pin_freq'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var freq = Blockly.Python.valueToCode(block, 'FREQ', Blockly.Python.ORDER_ATOMIC);
            return "pwm" + pin + ".freq(" + freq + ")\n";
        };
        Blockly.Python['motion_dsx_set_analog_pin_duty'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var freq = Blockly.Python.valueToCode(block, 'DUTY', Blockly.Python.ORDER_ATOMIC);
            return "pwm" + pin + ".duty(" + freq + ")\n";
        };

        Blockly.Python['motion_dsx_unisound'] = function(block) {
            return ["us516p6.recognition()", Blockly.Python.ORDER_ATOMIC];
        };

        Blockly.Python['motion_dsx_unisound_value'] = function(block) {
            var index = block.getFieldValue("INDEX");
            return [index, Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_uart_canread'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return ["uart.any()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_init_uart'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var baud = block.getFieldValue("BAUD")
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return "uart = UART(2, baudrate="+baud+", timeout=0xffff)\n";
        };
        Blockly.Python['motion_dsx_uart_isinit'] = function(block) {
            var index = block.getFieldValue("INDEX")
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return ["(uart != 0)",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_close_uart'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "uart.deinit()\n";
        };
        Blockly.Python['motion_dsx_uart_write'] = function(block) {
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            var index = block.getFieldValue("INDEX")
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            var ends = block.getFieldValue("ENDS")
            return "uart.write("+value+"+\""+ends+"\")\n";
        };
        Blockly.Python['motion_dsx_uart_read'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return ["uart.read(" + value + ")",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_uart_readline'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return ["uart.readline()",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_init_i2c'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return "i2c"+index+" = I2C("+index+", freq="+value+")\n";
        };
        Blockly.Python['motion_dsx_close_i2c'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "i2c"+index+".deinit()\n";
        };
        Blockly.Python['motion_dsx_i2c_write'] = function(block) {
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            var index = block.getFieldValue("INDEX")
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            return ["i2c"+index+".write("+ addr + ",bytearray([" + value + "]))\n",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_i2c_read'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return ["i2c"+index+".read("+ addr + "," + value + ")\n",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_disconnect_wifi'] = function(block) {
            return "network.disconnectWifi()\n";
        };
        Blockly.Python['motion_dsx_start_hotspot'] = function(block) {
            var ssid = Blockly.Python.valueToCode(block, 'SSID', Blockly.Python.ORDER_ATOMIC);
            var password = Blockly.Python.valueToCode(block, 'PASSWORD', Blockly.Python.ORDER_ATOMIC);
            return "network.startHotspot(" + ssid + "," + password + ")\n";
        };
        Blockly.Python['motion_dsx_config_hotspot'] = function(block) {
            var ip = Blockly.Python.valueToCode(block, 'IP', Blockly.Python.ORDER_ATOMIC);
            var netmask = Blockly.Python.valueToCode(block, 'NETMASK', Blockly.Python.ORDER_ATOMIC);
            var gw = Blockly.Python.valueToCode(block, 'GATEWAY', Blockly.Python.ORDER_ATOMIC);
            return "network.configHotspot(" + ip + "," + netmask + "," + gw + ")\n";
        };
        Blockly.Python['motion_dsx_stop_hotspot'] = function(block) {
            return "network.stopHotspot()\n";
        };
        Blockly.Python['motion_dsx_socket_create'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var type = block.getFieldValue("TYPE");
            var type2 = block.getFieldValue("TYPE2");
            return name + " = socket.socket(socket."+type+", socket."+type2+")\n";
        };
        Blockly.Python['motion_dsx_socket_close'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return name + ".close()\n";
        };
        Blockly.Python['motion_dsx_socket_bind'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return name + ".bind(("+addr+", "+port+"))\n";
        };
        Blockly.Python['motion_dsx_socket_timeout'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var timeout = Blockly.Python.valueToCode(block, 'TIMEOUT', Blockly.Python.ORDER_ATOMIC);
            return name + ".settimeout("+timeout+")\n";
        };
        Blockly.Python['motion_dsx_socket_listen'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return name + ".listen("+count+")\n";
        };
        Blockly.Python['motion_dsx_socket_setbroadcast'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return name + ".setsockopt(socket.SOL_SOCKET,socket.SO_BROADCAST,1)\n";
        };
        Blockly.Python['motion_dsx_socket_connect'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return ["("+name + ".connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_accept'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return [name + ".accept()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_send'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return name + ".send("+content+")\n";
        };
        Blockly.Python['motion_dsx_socket_sendto'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            var addr = Blockly.Python.valueToCode(block, 'ADDR', Blockly.Python.ORDER_ATOMIC);
            if(addr.startsWith("'")&&addr.endsWith("'")){
                addr = addr.slice(1,-1)
            }
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            if(port.startsWith("'")&&port.endsWith("'")){
                port = port.slice(1,-1)
            }
            return name + ".sendto("+content+",(\""+addr + "\"," + port +"))\n";
        };
        Blockly.Python['motion_dsx_socket_recv'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_socket_recvfrom'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'NAME', Blockly.Python.ORDER_ATOMIC);
            if(name.startsWith("'")&&name.endsWith("'")){
                name = name.slice(1,-1)
            }
            var len = Blockly.Python.valueToCode(block, 'LENGTH', Blockly.Python.ORDER_ATOMIC);
            return [name + ".recvfrom("+len+")", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_create_server'] = function(block) {
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            var count = Blockly.Python.valueToCode(block, 'COUNT', Blockly.Python.ORDER_ATOMIC);
            return "dsx_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM);dsx_server.bind(('0.0.0.0'," + port + "));dsx_server.listen(" + count + ");_thread.start_new_thread(dsx_server_thread,())\n";
        };
        Blockly.Python['motion_dsx_conn_create_client'] = function(block) {
            return "dsx_client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\n";
        };
        Blockly.Python['motion_dsx_conn_connect'] = function(block) {
            var addr = Blockly.Python.valueToCode(block, 'HOST', Blockly.Python.ORDER_ATOMIC);
            var port = Blockly.Python.valueToCode(block, 'PORT', Blockly.Python.ORDER_ATOMIC);
            return ["(dsx_client.connect(("+addr+", "+port+")) == 0)", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_accept'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return name + " = dsx_server.accept()\n";
        };
        Blockly.Python['motion_dsx_conn_hasconn'] = function(block) {
            return ["dsx_conn_cnt() > 0", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_getconn'] = function(block) {
            // return ["dsx_clientlist.pop(0)", Blockly.Python.ORDER_ATOMIC];
            return ["get_dsxclient()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_send'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return name + ".send("+content+")\n";
        };
        Blockly.Python['motion_dsx_conn_recv'] = function(block) {
            var name = Blockly.Python.valueToCode(block, 'SOCKET', Blockly.Python.ORDER_ATOMIC);
            return [name + ".recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_client_send'] = function(block) {
            var content = Blockly.Python.valueToCode(block, 'CONTENT', Blockly.Python.ORDER_ATOMIC);
            return "dsx_client.send("+content+")\n";
        };
        Blockly.Python['motion_dsx_conn_client_recv'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return ["dsx_client.recv()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_conn_close_server'] = function(block) {
            return "dsx_server.close()\n";
        };
        Blockly.Python['motion_dsx_conn_close_client'] = function(block) {
            var name = block.getFieldValue("SOCKET");
            return "dsx_client.close()\n";
        };
        Blockly.Python['motion_dsx_digital_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var state = block.getFieldValue("STATE");
            return ["(pin" + pin + ".value() == " + state + ")", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_analog_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            return ["adc" + pin + ".read()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_set_digital_pin'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var state = block.getFieldValue("STATE");
            return "pin" + pin + " = Pin(" + pin + ",mode=Pin.OUT,pull=Pin.PULL_UP);" + "pin" + pin + ".value("+state+")\n";
        };
        Blockly.Python['motion_dsx_set_analog_pin_freq'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var freq = Blockly.Python.valueToCode(block, 'FREQ', Blockly.Python.ORDER_ATOMIC);
            return "pwm" + pin + ".freq(" + freq + ")\n";
        };
        Blockly.Python['motion_dsx_set_analog_pin_duty'] = function(block) {
            var pin = block.getFieldValue("PIN");
            var freq = Blockly.Python.valueToCode(block, 'DUTY', Blockly.Python.ORDER_ATOMIC);
            return "pwm" + pin + ".duty(" + freq + ")\n";
        };

        Blockly.Python['motion_dsx_unisound'] = function(block) {
            return ["us516p6.recognition()", Blockly.Python.ORDER_ATOMIC];
        };

        Blockly.Python['motion_dsx_unisound_value'] = function(block) {
            var index = block.getFieldValue("INDEX");
            return [index, Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_uart_canread'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return ["uart.any()", Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_init_uart'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var baud = block.getFieldValue("BAUD")
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return "uart = UART(2, baudrate="+baud+", timeout=0xffff)\n";
        };
        Blockly.Python['motion_dsx_uart_isinit'] = function(block) {
            var index = block.getFieldValue("INDEX")
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return ["(uart != 0)",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_close_uart'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return "uart.deinit()\n";
        };
        Blockly.Python['motion_dsx_uart_write'] = function(block) {
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            var index = block.getFieldValue("INDEX")
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            var ends = block.getFieldValue("ENDS")
            return "uart.write("+value+"+\""+ends+"\")\n";
        };
        Blockly.Python['motion_dsx_uart_read'] = function(block) {
            var index = block.getFieldValue("INDEX")
            var value = Blockly.Python.valueToCode(block, 'VALUE', Blockly.Python.ORDER_ATOMIC);
            // var text_name = Blockly.Python.valueToCode(block, 'STEPS', Blockly.Python.ORDER_ATOMIC);
            return ["uart.read(" + value + ")",Blockly.Python.ORDER_ATOMIC];
        };
        Blockly.Python['motion_dsx_uart_readline'] = function(block) {
            var index = block.getFieldValue("INDEX")
            return ["uart.readline()",Blockly.Python.ORDER_ATOMIC];
        };"""
    return blockDef

# define toolbox category for scratch
def getCategory():
    jsonstr = "["
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
                    <field name='TEXT'>hello</field>
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
                    <field name='TEXT'>hello</field>
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
        <block type='motion_dsx_uart_read'>
            <value name='VALUE'><shadow type='math_number'><field name='NUM'>10</field></shadow></value>
        </block>
        <block type='motion_dsx_uart_readline'></block>
        <block type='motion_dsx_uart_canread'></block>
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
    jsonstr += """{"name":"电机", "xml":"
    <category name='电机' id='motor' colour='#9966FF' secondaryColour='#774DCB'>
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
    <block type='motion_get_soil2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"火焰", "xml":"
    <category name='火焰' id='flame' colour='#2F4F4F' secondaryColour='#BD42BD'>
    <block type='motion_get_flame'>
    </block>
    <block type='motion_get_flame2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"烟雾", "xml":"
    <category name='烟雾' id='smoke' colour='#c71585' secondaryColour='#BD42BD'>
    <block type='motion_get_smoke'>
    </block>
    <block type='motion_get_smoke2'>
    </block>
    </category>"},""";
    jsonstr += """{"name":"红外热释电", "xml":"
    <category name='红外热释电' id='infrared' colour='#ffc0a0' secondaryColour='#BD42BD'>
    <block type='motion_get_infrared'>
    </block>
    </category>"},""";
    jsonstr +="]"
    jsonstr = jsonstr.replace("\n","")
    return jsonstr

# define extension devices
def getExtensions():
    extensions = """[{
        'name': '电机',
        'tags': [
            'executor'
        ],
        'costumes': [
            {
                'md5ext': 'ef3b01f6fc1ffa1270fbbf057f7ded47.svg',
            }
        ]
    },
            {
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
                            sys.exit(0)
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
    pac = Packet(0x12, msg.encode("utf8"))
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
        AppendMessage("写入中 ");
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
                elif data[4] == 0x07:
                    SendSerialData(ohos_data)
                elif data[4] == 0x10:
                    firmwareVersion = str(data[5]) + "." + str(data[6]) + "." + str(data[7]) + "." + str(data[8])

