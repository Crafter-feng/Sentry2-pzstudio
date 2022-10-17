def getCRC(x,invert=True):
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