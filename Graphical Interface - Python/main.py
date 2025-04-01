import serial
import tkinter
from tkinter import *
import clickButton
import threading


ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM13'
ser.open()
c = 0


window = tkinter.Tk()
window.title('Graphical Interface Monitor')
window.geometry("650x650")
window.configure(background = 'black')
label = Label(window, text='Car Controller', background = 'black', foreground = 'white', font = ('Roboto', 30))
labelAvoidMode = Label(window, text='Avoid Obstacles Mode', background = 'black', foreground = 'white', font = ('Roboto',14))
distanceLabel = Label(window, text='Distance: cm', background='black',foreground='white', font=('Roboto',16))

# Es necesario utilizar lambda para que solo se ejecute la función cuando se haga click en el botón, sino solo se ejecutarán los métodos sin el manejo de eventos

button1 = Button(window, text='Forward', width = 15, height = 5, command=lambda:clickButton.clickButton1(ser), bg = 'grey', font = ('Arial', 12))
button2 = Button(window, text='Stop', width = 15, height = 5, command=lambda:clickButton.clickButton2(ser), bg = 'red', font = ('Roboto', 12))
button3 = Button(window, text='Backward', width = 15, height = 5, command=lambda:clickButton.clickButton3(ser), bg = 'orange', font = ('Roboto', 12))
button4 = Button(window, text='Turn Left', width = 15, height = 5, command=lambda:clickButton.clickButton4(ser), bg = 'blue', font = ('Roboto', 12))
button5 = Button(window, text='Turn Right', width = 15, height = 5, command=lambda:clickButton.clickButton5(ser), bg = 'yellow', font = ('Roboto', 12))
button6 = Button(window, text='Turn ON', width = 15, height = 5, command=lambda:clickButton.clickButton6(ser), bg = 'green', font = ('Roboto', 12))
button7 = Button(window, text = 'Left Servo', width = 10, height = 5, command=lambda:clickButton.clickButton7(ser), bg = 'green', font = ('Roboto', 12))
button8 = Button(window, text = 'Right Servo', width = 10, height = 5, command=lambda:clickButton.clickButton8(ser), bg = 'green', font = ('Roboto', 12))


label.pack(side = "top")
labelAvoidMode.place(relx=0.85, rely=0.78, anchor='center')
distanceLabel.place(relx=0.5, rely=0.1, anchor='center')

button1.place(relx=0.5, rely=0.3, anchor='center')
button2.place(relx=0.5, rely=0.5, anchor='center')
button3.place(relx=0.5, rely=0.7, anchor='center')
button4.place(relx=0.2, rely=0.5, anchor='center')
button5.place(relx=0.8, rely=0.5, anchor='center')
button6.place(relx=0.85, rely=0.9, anchor='center')
button7.place(relx=0.15, rely=0.9, anchor='center')
button8.place(relx=0.30, rely=0.9, anchor='center')

window.mainloop()

ser.close() # Cerrar la conexión serial cuando se termina la ejecución del programa


