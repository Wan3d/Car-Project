import serial
import tkinter
from tkinter import *
import clickButton
from threading import Thread
import time
import tkinter as tk
from tkinter import ttk

ser = serial.Serial()
ser.baudrate = 9600
ser.port = 'COM13'
ser.open()
c = 0
    
window = tkinter.Tk()
window.title('Graphical Interface Monitor')
window.geometry("800x800")
window.configure(background = 'black')

label = Label(window, text='Car Controller', background = 'black', foreground = 'white', font = ('Roboto', 30))
#labelAvoidMode = Label(window, text='Avoid Obstacles Mode', background = 'black', foreground = 'white', font = ('Roboto',14))
#distanceLabel = Label(window, text='Distance: y cm', background='black',foreground='white', font=('Roboto',16))
labelServoControl = Label(window, text='Servo Controller', background='black', foreground='white', font = ('Roboto',18))
labelServoControlSlider = Label(window, text='Servo Controller (With slider)', background='black', foreground='white', font = ('Roboto',14))


# Es necesario utilizar lambda para que solo se ejecute la función cuando se haga click en el botón, sino solo se ejecutarán los métodos sin el manejo de eventos

button1 = Button(window, text='Forward', width = 15, height = 5, command=lambda:clickButton.clickButton1(ser), bg = 'grey', font = ('Arial', 12))
button2 = Button(window, text='Stop', width = 15, height = 5, command=lambda:clickButton.clickButton2(ser), bg = 'red', font = ('Roboto', 12))
button3 = Button(window, text='Backward', width = 15, height = 5, command=lambda:clickButton.clickButton3(ser), bg = 'orange', font = ('Roboto', 12))
button4 = Button(window, text='Turn Left', width = 15, height = 5, command=lambda:clickButton.clickButton4(ser), bg = 'blue', font = ('Roboto', 12))
button5 = Button(window, text='Turn Right', width = 15, height = 5, command=lambda:clickButton.clickButton5(ser), bg = 'yellow', font = ('Roboto', 12))
#button6 = Button(window, text='Turn ON', width = 15, height = 5, command=lambda:clickButton.clickButton6(ser), bg = 'green', font = ('Roboto', 12))
button6 = Button(window, text = 'Turn Left', width = 9, height = 5, command=lambda:clickButton.clickButton6(ser), bg = 'white', font = ('Roboto', 12))
button7 = Button(window, text = 'Turn Right', width = 9, height = 5, command=lambda:clickButton.clickButton7(ser), bg = 'white', font = ('Roboto', 12))
button8 = Button(window, text = 'Initial Position', width = 12, height = 5, command=lambda:clickButton.clickButton8(ser), bg = 'blue', font = ('Roboto', 12))

label.pack(side = "top")
#labelAvoidMode.place(relx=0.85, rely=0.78, anchor='center')
#distanceLabel.place(relx=0.5, rely=0.1, anchor='center')
labelServoControl.place(relx=0.25, rely=0.78, anchor='center')
labelServoControlSlider.place(relx=0.80, rely=0.85, anchor='center')

button1.place(relx=0.5, rely=0.3, anchor='center')
button2.place(relx=0.5, rely=0.5, anchor='center')
button3.place(relx=0.5, rely=0.7, anchor='center')
button4.place(relx=0.2, rely=0.5, anchor='center')
button5.place(relx=0.8, rely=0.5, anchor='center')
button6.place(relx=0.10, rely=0.9, anchor='center')
button7.place(relx=0.40, rely=0.9, anchor='center')
button8.place(relx=0.25, rely=0.9, anchor='center')

valor = tk.IntVar()
ultimoValor = None

valor.set(90)

def showValue(_=None): # Se le pasa None implicar que si la función no recibe un valor, se le asignará None por defecto
    global ultimoValor # Declaras la variable como local, para que cuando se modifique sea general
    val = valor.get() # Obtiene el valor que se va a enviar
    if val != ultimoValor: # Si no se repite el valor nuevo con el anterior, se envía el valor. De esta forma se evita que se sobrecargue de datos
        ser.write(f"{val}\n".encode()) # Envías la comunicación serial codificado en byte
        ultimoValor = val # Ahora el ultimoValor valdrá el valor actual para comparar la siguiente iteración

scale = ttk.Scale(window, from_=180, to=0, length=200, variable=valor, command=showValue)
scale.place(relx=0.80, rely=0.9, anchor='center')

'''def read_distance():
    while True:
        if ser.in_waiting > 0:
            try:
                data = ser.readline().decode().strip()  # Leer la línea y limpiar espacios
                if data.isdigit():  # Verificar que es un número
                    data = int(data)
                    if data >= 0 and data <= 13:
                        #ser.write("2".encode())
                        distanceLabel.config(text=f"Car stopped...", foreground='purple')
                    elif data > 13 and data <= 20:
                        distanceLabel.config(text=f"STOOOP!!!!! Distance: {data} cm", foreground='red')
                    elif data > 20 and data <= 50:
                        distanceLabel.config(text=f"WARNING!! Distance: {data} cm", foreground='yellow')
                    elif data > 50:
                        distanceLabel.config(text=f"Distance: {data} cm", foreground='green')
            except Exception as e:
                print(f"Error en la lectura serial: {e}")'''

# Crear un hilo para leer los datos sin bloquear la interfaz
'''def start_reading():
    # Aquí se ejecuta la función que lee la distancia en un hilo separado
    threading.Thread(target=read_distance, daemon=True).start()

start_reading()  # Llamar a la función que inicia el hilo para leer la distancia'''

window.mainloop()

ser.close() # Cerrar la conexión serial cuando se termina la ejecución del programa


