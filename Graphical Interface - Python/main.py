import serial
import tkinter
from tkinter import *
import clickButton

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM13'
ser.open()
c = 0


window = tkinter.Tk()
window.title('Graphical Interface Monitor')
window.geometry("650x650")
window.configure(background = 'black')
label = Label(window, text='Car Controller', background = 'black', foreground = 'white', font = ('Times New Roman', 30))
labelAvoidMode = Label(window, text='Avoid Obstacles Mode', background = 'black', foreground = 'white', font = ('Times New Roman',14))

# Es necesario utilizar lambda para que solo se ejecute la función cuando se haga click en el botón, sino solo se ejecutarán los métodos sin el manejo de eventos

button1 = Button(window, text='Forward', width = 15, height = 5, command=lambda:clickButton.clickButton1(ser), bg = 'grey', font = ('Times New Roman', 12))
button2 = Button(window, text='Stop', width = 15, height = 5, command=lambda:clickButton.clickButton2(ser), bg = 'red', font = ('Times New Roman', 12))
button3 = Button(window, text='Back', width = 15, height = 5, command=lambda:clickButton.clickButton3(ser), bg = 'orange', font = ('Times New Roman', 12))
button4 = Button(window, text='Turn Left', width = 15, height = 5, command=lambda:clickButton.clickButton4(ser), bg = 'blue', font = ('Times New Roman', 12))
button5 = Button(window, text='Turn Right', width = 15, height = 5, command=lambda:clickButton.clickButton5(ser), bg = 'yellow', font = ('Times New Roman', 12))
button6 = Button(window, text='Turn ON', width = 15, height = 5, command=lambda:clickButton.clickButton6(ser), bg = 'green', font = ('Times New Roman', 12))

label.pack(side = "top")
labelAvoidMode.place(relx=0.85, rely=0.78, anchor='center')
button1.place(relx=0.5, rely=0.3, anchor='center')
button2.place(relx=0.5, rely=0.5, anchor='center')
button3.place(relx=0.5, rely=0.7, anchor='center')
button4.place(relx=0.2, rely=0.5, anchor='center')
button5.place(relx=0.8, rely=0.5, anchor='center')
button6.place(relx=0.85, rely=0.9, anchor='center')

window.mainloop()

ser.close() # Cerrar la conexión serial cuando se termina la ejecución del programa


