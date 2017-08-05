'''
    Arduino waits for 0
    1-Start
    2-Stop
'''

import serial
import time


COM_port = 'COM9'
baudRate = 9600
command_start = '1'
command_stop = '2'
computer_acknowledgement = '0'
arduino_acknowledgement = '0'



def main():
    s = serial.Serial(COM_port, baudRate)
    print("Connected to port : " + s.portstr)
    time.sleep(1)
    s.write(computer_acknowledgement.encode())
    time.sleep(1)
    rec = s.readline()
    print(rec.decode())
    ch = '0'
    while ch != '3' :
        print("1-Start\n2-Stop\n3-Exit\nChoice = ")
        ch = input()
        if ch == '1' :
            s.write(command_start.encode())
            time.sleep(1)
            rec1 = s.readline()
            print(rec1.decode())
        elif ch == '2' :
            s.write(command_stop.encode())
            time.sleep(1)
            rec2 = s.readline()
            print(rec2.decode())
        elif ch == '3' :
            s.close()
            print("Port Closed")


if __name__ == "__main__":
    main()
