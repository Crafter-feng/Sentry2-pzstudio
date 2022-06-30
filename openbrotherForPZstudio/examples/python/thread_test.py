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
