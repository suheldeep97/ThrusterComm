
"""Refer the binary codes for speed and
    0000 is universal acknowledgement signal
    handshake signal binary(int) 0000 sent from the arduino
    handshake signal binary(int) 1111 sent from the computer

    0101 full thrust forward
    0111 right turn
    1101 left turn
    0001 stop

"""

import time
import serial

command_start = '1'
command_stop = '2'
computer_acknowledgement = '0'
arduino_acknowledgement = '0'

ser = serial.Serial(port='COM9', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS,timeout=1)
print("Connected to serial port "+ser.portstr)
# file = open("C:\\Pond_test_logs\\Pond_text.txt" , "a")


def handshake():
    time.sleep(5)
    rec = ser.readline()
    rec = rec.decode()
    if rec == arduino_acknowledgement:
        print("Acknowledgement recieved")
        ser.write(computer_acknowledgement.encode())
        print("Acknowledgement sent")
        time.sleep(5)
        print("Handshake done")
        return True


def run_forward():
    ser.write(command_start.encode())
    rec1 = ser.readline()
    rec1 = rec1.decode()
    if rec1 == arduino_acknowledgement:
        print("Running forward")


def stop_run():
    ser.write(command_stop.encode())
    rec11 = ser.readline()
    rec11 = rec11.decode()
    if rec11 == arduino_acknowledgement:
        print("Stopped Run")


def turn_left():
    sen2 = '1101'
    ser.write(sen2.encode())
    rec2 = ser.readline()
    rec2 = rec2.decode()
    if rec2 == '0000':
        print("Turning left")


def turn_right():
    sen3 = '1101'
    ser.write(sen3.encode())
    rec3 = ser.readline()
    rec3 = rec3.decode()
    if rec3 == '0000':
        print("Turning right")


def main():
    choice = 0
    handshake()
    while choice != -1:
        choice = input("1 - START\n2 - STOP\n-1 - EXIT\n ? ")
        if choice == 1:
            run_forward()
        elif choice == 2:
            stop_run()


if __name__ == "__main__":
    main()




