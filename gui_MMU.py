<<<<<<< HEAD
from tkinter import *

gui = Tk()
#gui = tk()
def imprimir():
	print ("Esto es un mensaje")






buttonPROCESS1 = Button (gui, text="Processs 1",command = imprimir).place(x=50,y=50) #gui.quit se sustituye por la funcion que deseemos
buttonPROCESS2 = Button (gui, text="Processs 2",command = gui.quit).place(x=50,y=80)



gui.geometry("200x200")#dimensiones ancho x alto
gui.title("Memory Management Unit")
gui.mainloop()

=======
from tkinter import *

gui = Tk()
#gui = tk()
def imprimir():
	print ("Esto es un mensaje")






buttonPROCESS1 = Button (gui, text="Processs 1",command = imprimir).place(x=50,y=50) #gui.quit se sustituye por la funcion que deseemos
buttonPROCESS2 = Button (gui, text="Processs 2",command = gui.quit).place(x=50,y=80)



gui.geometry("200x200")#dimensiones ancho x alto
gui.title("Memory Management Unit")
gui.mainloop()

>>>>>>> origin/master
