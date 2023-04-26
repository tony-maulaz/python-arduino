
import serial
import time

def send_command(cmd, data):
    id = 0x55
    checksum = id + cmd + data
    nbr = ser.write([id,cmd,data,checksum])
    print("Send command : {0} - {1} / crc : {2}".format(cmd, nbr, checksum))

    hello = ser.readline()
    print(hello)

ser = serial.Serial('COM4', 115200, timeout=0.1)
print(ser.name)


print("wait reset")
time.sleep(1)

for i in range(1,5):
    send_command(1,0)
    time.sleep(1)

# led off
send_command(3,0)
time.sleep(3)

# led on 
send_command(2,0)
time.sleep(3)

# led off
send_command(3,0)

ser.close()
