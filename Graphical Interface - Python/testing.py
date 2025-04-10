import tkinter as tk
from tkinter import ttk

window = tk.Tk()

# Creamos una variable para guardar el valor
valor = tk.DoubleVar()

# Vinculamos la variable al Scale
scale = ttk.Scale(window, from_=0, to=180, length=200, variable=valor)
scale.pack(padx=30, pady=10)

# Botón para mostrar el valor actual
def mostrar_valor():
    print("Valor guardado:", valor.get())

boton = ttk.Button(window, text="Mostrar valor", command=mostrar_valor)
boton.pack(pady=10)

window.mainloop()
