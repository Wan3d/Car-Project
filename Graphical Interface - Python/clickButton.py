def clickButton1(ser):
    ser.write("1".encode())
    print("Going forward...")
def clickButton2(ser):
    ser.write("2".encode())
    print("Stopping!")
def clickButton3(ser):
    ser.write("3".encode())
    print("Going back...")
def clickButton4(ser):
    ser.write("4".encode())
    print("Turning left")
def clickButton5(ser):
    ser.write("5".encode())
    print("Turning right")
def clickButton6(ser):
    ser.write("6".encode())
    print("Turning ON Avoid Obstacles Mode...")