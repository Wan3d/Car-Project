def clickButton1(ser):
    ser.write("A".encode())
    print("Going forward...")
def clickButton2(ser):
    ser.write("B".encode())
    print("Stopping!")
def clickButton3(ser):
    ser.write("C".encode())
    print("Going back...")
def clickButton4(ser):
    ser.write("D".encode())
    print("Turning left")
def clickButton5(ser):
    ser.write("E".encode())
    print("Turning right")
'''def clickButton6(ser):
    ser.write("6".encode())
    print("Turning ON Avoid Obstacles Mode...")'''
def clickButton6(ser):
    ser.write("F".encode())
    print("Turning left Servo")
def clickButton7(ser):
    ser.write("G".encode())
    print("Turning right Servo")
def clickButton8(ser):
    ser.write("H".encode())
    print("Putting servo on initial position")




