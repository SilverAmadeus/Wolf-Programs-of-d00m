__authors__ = 'Moreno Tagle Raphael Ivan' \
              'Rodriguez Garcia Alan Julian'
import threading, random, time
import tkinter as tk
gui = tk.Tk()


class CPU(object):
    def __init__(self):
        self.max_size = 50
        self.memory = [0] * self.max_size
        self.console_cpu = False
        self.console_mem1 = False
        self.console_mem2 = False
        self.console_mem3 = False
        self.status = True

    # Función que define si se muentra o no en consola los estados de las memorias que ocupan los procesos
    # Actualiza el estado de los botones
    def console_stat_cpu(self):
        if self.console_cpu is True:
            self.console_cpu = False
            buttonPROCESSCPU["text"] = "Memoria en CPU [OFF]"
        else:
            self.console_cpu = True
            buttonPROCESSCPU["text"] = "Memoria en CPU [ON]"

    def console_stat_mem1(self):
        if self.console_mem1 is True:
            self.console_mem1 = False
            buttonPROCESSP1["text"] = "Memoria en Proceso 1 [OFF]"
        else:
            self.console_mem1 = True
            buttonPROCESSP1["text"] = "Memoria en Proceso 1 [ON]"

    def console_stat_mem2(self):
        if self.console_mem2 is True:
            self.console_mem2 = False
            buttonPROCESSP2["text"] = "Memoria en Proceso 2 [OFF]"
        else:
            self.console_mem2 = True
            buttonPROCESSP2["text"] = "Memoria en Proceso 2 [ON]"

    def console_stat_mem3(self):
        if self.console_mem3 is True:
            self.console_mem3 = False
            buttonPROCESSP3["text"] = "Memoria en Proceso 3 [OFF]"
        else:
            self.console_mem3 = True
            buttonPROCESSP3["text"] = "Memoria en Proceso 3 [ON]"

    # Se realiza una particion de tamano diferente a cada uno de los procesos
    def initialize(self):
        global CPU_memory
        print("\t\t\tIniciando repartición de memoria \n\t\t\tMemoria inicial para los procesos .")
        p1.memory = self.memory[:int((len(self.memory)) * .4)] #Tomando los bloques del cpu para proceso 1
        self.memory = [0] * (self.max_size - len(p1.memory))

        p2.memory = self.memory[:int((len(self.memory)) * .5)] #Tomando los bloques del cpu para proceso 2
        self.memory = [0] * (len(self.memory)- len(p2.memory))

        p3.memory = self.memory[:int((len(self.memory)) * .35)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p3.memory))

        CPU_memory = self.memory

        return 0

    # Asigna mas memoria en casa de que alguno de los procesos la llege a requerir, si al CPU no le es posible
    # asignar mas memoria le hace saber al proceso para que termine se ejecucion
    def assign(self, process_memory):
        global CPU_memory
        if CPU_memory:
            process_memory.append(CPU_memory.pop())
            return True

        if not CPU_memory:
            print("Memoria de CPU vacia ", end='\r')
            print(CPU_memory)
            time.sleep(2)
            return False

    # Calcula el porcentaje de memoria libre y en uso del CPU y los diferentes procesos
    # Esta funcion la lleva acabo el hilo cput, botones seleccionan que va a imprimir el hilos dependiendo de
    # Los estados de las variables de la clase CPU
    def percentages(self):
        global CPU_memory, Mem_P1, Mem_Max_P1, Mem_P2, Mem_Max_P2, Mem_P3, Mem_Max_P3
        while self.status is True:
            increase = float(len(CPU_memory)) - float(self.max_size)
            decrease = float(self.max_size) - float(len(CPU_memory))
            free_cpu_percent = ((increase / float(self.max_size)) * 100)+100
            used_cpu_percent = ((decrease/float(self.max_size))*100)

            increase_p1 = float(len(Mem_P1)) - float(Mem_Max_P1)
            decrease_p1 = float(Mem_Max_P1) - float(len(Mem_P1))
            used_p1_percent = ((increase_p1 / float(Mem_Max_P1)) * 100)+100
            free_p1_percent = ((decrease_p1/float(Mem_Max_P1))*100)

            increase_p2 = float(len(Mem_P2)) - float(Mem_Max_P2)
            decrease_p2 = float(Mem_Max_P2) - float(len(Mem_P2))
            used_p2_percent = ((increase_p2 / float(Mem_Max_P2)) * 100)+100
            free_p2_percent = ((decrease_p2/float(Mem_Max_P2))*100)

            increase_p3 = float(len(Mem_P3)) - float(Mem_Max_P3)
            decrease_p3 = float(Mem_Max_P3) - float(len(Mem_P3))
            used_p3_percent = ((increase_p3 / float(Mem_Max_P3)) * 100)+100
            free_p3_percent = ((decrease_p3/float(Mem_Max_P3))*100)



            if self.console_cpu is True: print("Memoria libre de CPU: "+str(round(free_cpu_percent, 2))+ "%"+"\tMemoria en uso de CPU: "+ str(round(used_cpu_percent, 2))+"%", end ='\r')
            if self.console_mem1 is True: print("Memoria libre de Proceso 1: "+str(round(free_p1_percent, 2))+"%"+"\tMemoria en uso de Proceso 1: "+ str(round(used_p1_percent, 2))+"%", end ='\r')
            if self.console_mem2 is True: print("Memoria libre de Proceso 2: "+str(round(free_p2_percent, 2))+"%"+"\tMemoria en uso de Proceso 2: "+ str(round(used_p2_percent, 2))+"%", end ='\r')
            if self.console_mem3 is True: print("Memoria libre de Proceso 3: "+str(round(free_p3_percent, 2))+"%"+"\tMemoria en uso de Proceso 3: "+ str(round(used_p3_percent, 2))+"%", end ='\r')

            time.sleep(1)

class Process1(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = -1
        self.insufficient_memory = False
        self.id = 1
        self.console = False

        # Constructor para la super-clase CPU, todos los procesos heredan de ella
        super(Process1, self).__init__()

    #  Actualiza boton y estado de impresion en consola
    def console_stat(self):
        if self.console is True:
            self.console = False
            buttonPROCESS1["text"] = "Proceso 1 [OFF]"
        else:
            self.console = True
            buttonPROCESS1["text"] = "Proceso 1 [ON]"

    def tasks(self):
        #Variables globales que llevan los valores de la memoria actual y la maxima del CPU y cada uno de los procesos
        global CPU_memory, Mem_P1, Mem_Max_P1, Mem_P2, Mem_Max_P2, Mem_P3, Mem_Max_P3
        self.max_size = len(self.memory)
        Mem_Max_P1 = self.max_size

        while True:
            # Si el proceso sigue vivo realizara operaciones para eliminar o agregar bloques de memoria,
            # el si borra o agrega bloques esta definido por una porcentaje de probabilidad dado que cambia
            # dependiendo de cuantos bloques que tenga la probabilidad de agregado y borrado cambian
            # para simular un proceso cualquiera en CPU
            if self.status is True:
                i = random.randint(0, 99)
                Mem_P1 = self.memory
                # Muestra la cantidad de bloques que está usando y lo que hace con el
                if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Trabajando...", end='\r')
                time.sleep(1.5)

                # Cambiando probabilidades de Proceso 1 dependiendo de los bloques de memoria que tenga
                if len(self.memory) == 5:
                    self.probability = 80
                elif len(self.memory) == 17:
                    self.probability = 30

                if (i > self.probability):
                    if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                    time.sleep(1.5)
                    self.memory.pop()
                    Mem_P1 = self.memory

                    if not self.memory:
                        # Solicita mas memoria directamente al CPU en caso de que el CPU no tenga, el proceso termina
                        if self.console is True: print("Proceso 1 sin memoria, solicitando memoria a CPU", end='\r')
                        time.sleep(1.5)
                        if CPU.assign(self, self.memory) is False:
                            if self.console is True: print("Proceso 1 memoria insuficiente en CPU: TERMINANDO", end='\r')
                            for block in Mem_P1:
                                CPU_memory.append(block)
                            time.sleep(1.5)
                            self.insufficient_memory = True
                            self.status = False
                        else:
                            if self.console is True: print("Memoria extra asiganada a Proceso 1 ", end='\r')
                            time.sleep(1.5)
                else:
                    # Cuando el proceso termina regresa todos los bloques que ocupo al CPU
                    if len(self.memory) == 20:
                        print("\nProceso 1: TERMINANDO", end='\r')
                        for block in Mem_P1:
                            CPU_memory.append(block)
                        time.sleep(1.5)
                        self.status = False
                    else:
                        self.memory.append(0)
                        Mem_P1 = self.memory
            else:
                # El proceso puede terminar por dos razones, se termia la memoria o termino de forma normal
                if self.insufficient_memory is True:
                    if self.console is True: print("Proceso 1: TERMINADO: Memoria insuficiente en CPU", end='\r')
                    time.sleep(1.5)
                else:
                    if self.console is True: print("Proceso 1: TERMINADO", end='\r')
                    time.sleep(1.5)


        return 0

class Process2(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = -1
        self.insufficient_memory = False
        self.id = 2
        self.console = False
        super(Process2, self).__init__()

    def console_stat(self):
        if self.console is True:
            self.console = False
            buttonPROCESS2["text"] = "Proceso 2 [OFF]"
        else:
            self.console = True
            buttonPROCESS2["text"] = "Proceso 2 [ON]"

    def tasks(self):
        global CPU_memory, Mem_P1, Mem_Max_P1, Mem_P2, Mem_Max_P2, Mem_P3, Mem_Max_P3
        self.max_size = len(self.memory)
        Mem_Max_P2 = self.max_size

        while True:
            if self.status is True:
                i = random.randint(0, 99)
                Mem_P2 = self.memory
                if self.console is True: print("Proceso 2 (Tamaño: " + str(len(self.memory))+ ") "+": Trabajando...", end='\r')
                time.sleep(1.5)

                # Probabilidades del Proceso 2 dependiendo de los bloques que tenga
                if len(self.memory) == 2:
                    self.probability = 90
                elif len(self.memory) == 13:
                    self.probability = 20

                if (i > self.probability):
                    if self.console is True: print("Proceso 2 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                    time.sleep(1.5)
                    self.memory.pop()
                    Mem_P2 = self.memory

                    if not self.memory:
                        if self.console is True: print("Proceso 2: Sin memoria, solicitando memoria a CPU", end='\r')
                        time.sleep(1.5)
                        if CPU.assign(self, self.memory) is False:
                            if self.console is True: print("Proceso 2: Memoria insuficiente en CPU: TERMINANDO\n", end='\r')
                            for block in Mem_P2:
                                CPU_memory.append(block)
                            time.sleep(1.5)
                            self.insufficient_memory = True
                            self.status = False
                        else:
                            if self.console is True: print("Memoria extra asiganada a Proceso 2 ", end='\r')
                            time.sleep(1.5)
                else:
                    if len(self.memory) == 15:
                        print("\nProceso 2: TERMINANDO\n", end='\r')
                        for block in Mem_P2:
                            CPU_memory.append(block)
                        time.sleep(1.5)
                        self.status = False
                    else:
                        self.memory.append(0)
                        Mem_P2 = self.memory
            else:
                if self.insufficient_memory is True:
                    if self.console is True: print("Proceso 2: TERMINADO: Memoria insuficiente en CPU", end='\r')
                    time.sleep(1.5)
                else:
                    if self.console is True: print("Proceso 2: TERMINADO", end='\r')
                    time.sleep(1.5)

        return 0

class Process3(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = -1
        self.insufficient_memory = False
        self.id = 3
        self.console = False
        super(Process3, self).__init__()

    def console_stat(self):
        if self.console is True:
            self.console = False
            buttonPROCESS3["text"] = "Proceso 3 [OFF]"
        else:
            self.console = True
            buttonPROCESS3["text"] = "Proceso 3 [ON]"

    def tasks(self):
        global CPU_memory, Mem_P1, Mem_Max_P1, Mem_P2, Mem_Max_P2, Mem_P3, Mem_Max_P3
        self.max_size = len(self.memory)
        Mem_Max_P3 = self.max_size

        while True:

            if self.status is True:
                i = random.randint(0, 99)
                Mem_P3 = self.memory
                if self.console is True: print("Proceso 3 (Tamaño: " + str(len(self.memory))+ ") " +": Trabajando...", end='\r')
                time.sleep(1.5)

                # Cambiando probabilidades de Proceso 1 dependiendo de los bloques de memoria que tenga
                if len(self.memory) == 1:
                    self.probability = 90
                if len(self.memory) == 4:
                    self.probability = 10

                if (i > self.probability):
                    if self.console is True: print("Proceso 3 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                    time.sleep(1.5)
                    self.memory.pop()
                    Mem_P3 = self.memory

                    if not self.memory:
                        if self.console is True: print("Proceso 3: Sin memoria, solicitando memoria a CPU", end='\r')
                        time.sleep(1.5)
                        if CPU.assign(self, self.memory) is False:
                            if self.console is True: print("\nProceso 3: Memoria insuficiente en CPU: TERMINANDO")
                            for block in Mem_P3:
                                CPU_memory.append(block)
                            time.sleep(1.5)
                            self.insufficient_memory = True
                            self.status = False
                        else:
                            if self.console is True: print("Memoria extra asiganada a Proceso 3 ", end='\r')
                            time.sleep(1.5)

                else:
                    if len(self.memory) == 5:
                        print("\nProceso 3: TERMINANDO\n", end='\r')
                        for block in Mem_P3:
                            CPU_memory.append(block)
                        time.sleep(1.5)
                        self.status = False
                    else:
                        self.memory.append(0)
                        Mem_P3 = self.memory
            else:
                if self.insufficient_memory is True:
                    if self.console is True: print("Proceso 3: TERMINADO: Memoria insuficiente en CPU", end='\r')
                    time.sleep(1.5)
                else:
                    if self.console is True: print("Proceso 3: TERMINADO", end='\r')
                    time.sleep(1.5)

        return 0


global CPU_memory
p1 = Process1()
p2 = Process2()
p3 = Process3()

cpu = CPU()

# Chequeo inicial de estados
print("\n\n\t\t\t.:: MEMORY MANAGEMENT UNIT ::.\n")
print("\t\t\tMemoria de CPU inicial " + str(len(cpu.memory)))
cpu.initialize()
print("\t\t\t\tMemoria de CPU: " + str(len(cpu.memory)))
print("\t\t\t\tMemoria de Proceso 1: " +str(len(p1.memory)))
print("\t\t\t\tMemoria de Proceso 2: " +str(len(p2.memory)))
print("\t\t\t\tMemoria de Proceso 3: " +str(len(p3.memory)))
print("\n")

#Hilos de los procesos, su función target es la que lleva acabo el uso de la memoria que se les asigno
p1t = threading.Thread(target=p1.tasks, args=())
p2t = threading.Thread(target=p2.tasks, args=())
p3t = threading.Thread(target=p3.tasks, args=())
cput = threading.Thread(target=cpu.percentages, args=())

p1t.start()
p2t.start()
p3t.start()
cput.start()

#Creando los objetos de Boton y ventando
char = tk.PhotoImage(file="char.gif")
fondo = tk.Label (gui,image=char).place(x=50,y=-20)

buttonPROCESSCPU = tk.Button(gui, text="Memoria en CPU [OFF]",command = cpu.console_stat_cpu)

buttonPROCESS1 = tk.Button(gui, text="Proceso 1 [OFF]",command = p1.console_stat)
buttonPROCESS2 = tk.Button(gui, text="Proceso 2 [OFF]",command = p2.console_stat)
buttonPROCESS3 = tk.Button(gui, text="Proceso 3 [OFF]",command = p3.console_stat)

buttonPROCESSP1 = tk.Button(gui, text="Memoria en Proceso 1 [OFF]",command = cpu.console_stat_mem1)
buttonPROCESSP2 = tk.Button(gui, text="Memoria en Proceso 2 [OFF]",command = cpu.console_stat_mem2)
buttonPROCESSP3 = tk.Button(gui, text="Memoria en Proceso 3 [OFF]",command = cpu.console_stat_mem3)

#Se define la posicion de los botones y el tamaño de la GUI
buttonPROCESSCPU.place(x=400,y=70)
buttonPROCESS1.place(x=50,y=50)
buttonPROCESS2.place(x=50,y=80)
buttonPROCESS3.place(x=50,y=110)

buttonPROCESSP1.place(x=400,y=100)
buttonPROCESSP2.place(x=400,y=130)
buttonPROCESSP3.place(x=400,y=160)

gui.geometry("650x300")#dimensiones ancho x alto
gui.title("Memory Management Unit")
gui.mainloop()