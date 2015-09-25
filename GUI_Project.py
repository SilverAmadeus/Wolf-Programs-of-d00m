__author__ = 'Alan'
from _tkinter import * #Para python 3.x.x debes importar como: tkinter
from tkinter import *
from tkinter import messagebox

gui = Tk() #Instancia de la interfaz


def imprimir():
	a = messagebox.askyesno("Mensaje","El mensaje es:"+mensaje.get())
	if a == True:
		print ("Fue verdadera")
	else:
		print ("False")

	#showwarning para mandar advertencia
	#askquestion pregunta, si = (String)yes, no = (String)no
	#askokcancel pregunta, si=True, no = Fase
	#askyesno pregunta, si =True, no = False
	#askretrycanel pregunta a reintentar, reintentar = True, no = False
	#messagebox.showinfo("el mensaje es"+mensaje.get())
mensaje = StringVar()
tag1 = Label (gui, text="Inicia").place(x=10,y=10)#place indica coordenadas de localización

box1 = Entry(gui,textvariable=mensaje).place(x=50,y=10) 
buttonQUIT = Button (gui, text= "QUIT",fg="red",command=gui.quit).place(x=500,y=120)
buttonSHOW = Button (gui, text = "Show msg",command=imprimir).place(x=40,y=150)
#buttonQUIT.pack(side = RIGHT) #aparece el boton

gui.geometry("550x200") #Dimensiones
gui.title("Memory Management Unit") #Titulo de la ventana
gui.mainloop() #Evento que permite que aparezca la ventana
