__author__ = 'Big Boss'
import threading, random, time, os, sys
from tkinter import *
gui = Tk()



# Cambiar el numero del proceso 3 a 4 ya que usan la misma clase pero son diferentes instancias


class CPU(object):
    def __init__(self):
        self.max_size = 50
        self.memory = [0] * self.max_size
        self.console_cpu = False
        self.console_mem1 = False
        self.status = True

    def console_stat_cpu(self):
        if self.console_cpu is True:
            self.console_cpu = False
        else:
            self.console_cpu = True

    def console_stat_mem1(self):
        if self.console_mem1 is True:
            self.console_mem1 = False
        else:
            self.console_mem1 = True

    def initialize(self):
        global CPU_memory
        print("Iniciando repartición de memoria \nMemoria inicial para los procesos .")
        p1.memory = self.memory[:int((len(self.memory)) * .4)] #Tomando los bloques del cpu para proceso 1
        self.memory = [0] * (self.max_size - len(p1.memory))

        p2.memory = self.memory[:int((len(self.memory)) * .35)] #Tomando los bloques del cpu para proceso 2
        self.memory = [0] * (len(self.memory)- len(p2.memory))

        p3.memory = self.memory[:int((len(self.memory)) * .25)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p3.memory))

        p4.memory = p3.memory #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p4.memory))
        CPU_memory = self.memory

        # newList = originalList[int(len(originalList) * .05) : int(len(originalList) * .95)]
        return 0

    def assign(self, process_memory):
        global CPU_memory
        if CPU_memory:
            process_memory.append(CPU_memory.pop())
            return True

        if not CPU_memory:
            print("Memoria de CPU vacia ")
            print(CPU_memory)
            time.sleep(2)
            return False

    def percentages(self):
        global CPU_memory
        while self.status is True:
            increase = float(len(CPU_memory)) - float(self.max_size)
            decrease = float(self.max_size) - float(len(CPU_memory))
            free_cpu_percent = ((increase / float(self.max_size)) * 100)+100
            used_cpu_percent = ((decrease/float(self.max_size))*100)
            if self.console_cpu is True: print("Memoria libre de CPU: "+str(free_cpu_percent)+ "%" + "\tMemoria en uso de CPU: "+ str(used_cpu_percent)+"%", end ='\r')
            time.sleep(2)

class Process1(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"
        self.id = 1
        self.console = False

        super(Process1, self).__init__() # Constructor para la super-clase

    def initialize_p1(self):
        print("Este es el proceso 1")
        #end='\r'

    def console_stat(self):
        if self.console is True:
            self.console = False
        else:
            self.console = True

    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Trabajando...", end='\r')
            time.sleep(2)
            if len(self.memory) < 5:
                self.probability = 80
            elif len(self.memory) == 17:
                self.probability = 30

            if (i > self.probability):
                if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                #print("Proceso 1: Tamaño de bloque ", len(self.memory), end='\r')
                time.sleep(2)
                self.memory.pop()
                if not self.memory:
                    if self.console is True: print("Proceso 1 sin memoria, solicitando memoria a CPU", end='\r')
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        if self.console is True: print("Proceso 1 sin memoria suficiente: TERMINANDO", end='\r')
                        time.sleep(2)
                        self.status = False
                    else:
                        if self.console is True: print("Memoria extra asiganada a Proceso 1 ", end='\r')
                        time.sleep(2)
            else:
                if len(self.memory) == 20:
                    print("\nProceso 1: TERMINADO", end='\r')
                    time.sleep(2)
                    self.status = False
                else:
                    self.memory.append(0)

        return 0

class Process2(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"
        self.id = 2
        self.console = False
        super(Process2, self).__init__()

    def initialize_p2(self):
        print("Este es el proceso 2")

    def console_stat(self):
        if self.console is True:
            self.console = False
        else:
            self.console = True

    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            if self.console is True: print("Proceso 2 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...", end='\r')
            time.sleep(2)
            if len(self.memory) == 3:
                self.probability = 95
            elif len(self.memory) == 8:
                self.probability = 25

            if (i > self.probability):
                if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                time.sleep(2)
                self.memory.pop()
                #print("Proceso 2: Tamaño de bloque ", len(self.memory))
                if not self.memory:
                    if self.console is True: print("Proceso 2 sin memoria, solicitando memoria a CPU", end='\r')
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        if self.console is True: print("Proceso 2 sin memoria suficiente: TERMINANDO", end='\r')
                        time.sleep(2)
                        self.status = False
                    else:
                        if self.console is True: print("Memoria extra asiganada a Proceso 2 ", end='\r')
                        time.sleep(2)
            else:
                if len(self.memory) == 10:
                    print("\nProceso 2: TERMINADO", end='\r')
                    time.sleep(2)
                    self.status = False
                else:
                    self.memory.append(0)

        return 0

class Process3(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"
        self.id = 3
        self.console = False
        super(Process3, self).__init__()

    def initialize_p3(self):
        print("Este es el proceso 3")

    def console_stat(self):
        if self.console is True:
            self.console = False
        else:
            self.console = True

    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            if self.console is True: print("Proceso 3 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...", end='\r')
            time.sleep(2)
            if len(self.memory) == 1:
                self.probability = 98
            if len(self.memory) == 4:
                self.probability = 15

            if (i > self.probability):
                if self.console is True: print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") "+": Eliminando...", end ='\r')
                time.sleep(2)
                self.memory.pop()
                if self.console is True: print("Proceso 3: Tamaño de bloque ", len(self.memory), end='\r')
                if not self.memory:
                    if self.console is True: print("Proceso 3 sin memoria, solicitando memoria a CPU", end='\r')
                    # print(CPU_memory)
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        if self.console is True: print("\nProceso 3 sin memoria suficiente: TERMINANDO")
                        time.sleep(2)
                        self.status = False
                    else:
                        if self.console is True: print("Memoria extra asiganada a Proceso 3 ", end='\r')
                        time.sleep(2)
            else:
                if len(self.memory) == 5:
                    if self.console is True: print("\nProceso 3: TERMINADO")
                    time.sleep(2)
                    self.status = False
                else:
                    self.memory.append(0)

        return 0


#class Console(object):
#    def __init__(self):
 #       self.memory = 0

  #  def initialize(self):
global CPU_memory
p1 = Process1()
p2 = Process2()
p3 = Process3()
p4 = Process3()
cpu = CPU()
# Chequeo inicial de estados
print("Memoria de CPU inicial " + str(len(cpu.memory)))
cpu.initialize()
print("Memoria de CPU: " + str(len(cpu.memory)))
print("Memoria de Proceso 1: " +str(len(p1.memory)))
print("Memoria de Proceso 2: " +str(len(p2.memory)))
print("Memoria de Proceso 3: " +str(len(p3.memory)))
print("Memoria de Proceso 4: " +str(len(p4.memory)))
print("\n")
p1t = threading.Thread(target=p1.tasks, args=())
p2t = threading.Thread(target=p2.tasks, args=()) # Thread de Process 1
p3t = threading.Thread(target=p3.tasks, args=())
#p4t = threading.Thread(target=p4.tasks(), args=())
cput = threading.Thread(target=cpu.percentages, args=())
p1t.start()
p2t.start()
p3t.start()
#p4t.start()
cput.start()
buttonPROCESS1 = Button (gui, text="Process 1",command = p1.console_stat).place(x=50,y=50)
# gui.quit se sustituye por la funcion que deseemos
buttonPROCESS2 = Button (gui, text="Process 2",command = p2.console_stat).place(x=50,y=80)
buttonPROCESS3 = Button (gui, text="Process 3",command = p3.console_stat).place(x=50,y=110)
buttonPROCESSCPU = Button (gui, text="Procesos en CPU",command = cpu.console_stat_cpu).place(x=400,y=70)

gui.geometry("600x200")#dimensiones ancho x alto
gui.title("Memory Management Unit")
gui.mainloop()