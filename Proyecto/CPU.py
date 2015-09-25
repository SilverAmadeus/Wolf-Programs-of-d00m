__author__ = 'Ivan'
import threading, random, time

# Cambiar el numero del proceso 3 a 4 ya que usan la misma clase pero son diferentes instancias

class CPU(object):
    def __init__(self):
        self.max_size = 50
        self.memory = [0] * self.max_size


    def initialize(self):
        global CPU_memory
        print("Iniciando repartición de memoria")
        p1.memory = self.memory[:int((len(self.memory)) * .4)] #Tomando los bloques del cpu para proceso 1
        self.memory = [0] * (self.max_size - len(p1.memory))

        p2.memory = self.memory[:int((len(self.memory)) * .35)] #Tomando los bloques del cpu para proceso 2
        self.memory = [0] * (len(self.memory)- len(p2.memory))

        p3.memory = self.memory[:int((len(self.memory)) * .25)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p3.memory))

        p4.memory = self.memory[:int((len(self.memory)) * .25)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p4.memory))
        CPU_memory = self.memory

        p4.memory = [0] *5
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



class Process1(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"
        self.id = 1

        super(Process1, self).__init__() # Constructor para la super-clase

    def initialize(self):
        print("Este es el proceso 1")
        #end='\r'

        return 0
    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            print("Proceso 1 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...")
            time.sleep(2)
            if len(self.memory) < 5:
                self.probability = 80
            elif len(self.memory) == 17:
                self.probability = 30

            if (i > self.probability):
                print("Proceso 1: Eliminando...")
                time.sleep(2)
                self.memory.pop()
                print("Proceso 1: Tamaño de bloque ", len(self.memory))
                if not self.memory:
                    print("\nProceso 1 sin memoria, solicitando memoria a CPU")
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        print("Proceso 1 sin memoria suficiente: TERMINANDO")
                        time.sleep(2)
                        self.status = False
                    else:
                        print("Memoria extra asiganada a Proceso 2 ")
                        time.sleep(2)
            else:
                if len(self.memory) == 20:
                    print("\nProceso 1: TERMINADO")
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
        super(Process2, self).__init__()

    def initialize(self):
        print("Este es el proceso 2")

        return 0
    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            print("\nProceso 2 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...")
            time.sleep(2)
            if len(self.memory) == 3:
                self.probability = 95
            elif len(self.memory) == 8:
                self.probability = 25

            if (i > self.probability):
                print("\nProceso 2: Eliminando...")
                time.sleep(2)
                self.memory.pop()
                print("\nProceso 2: Tamaño de bloque ", len(self.memory))
                if not self.memory:
                    print("\nProceso 2 sin memoria, solicitando memoria a CPU")
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        print("Proceso 2 sin memoria suficiente: TERMINANDO")
                        time.sleep(2)
                        self.status = False
                    else:
                        print("Memoria extra asiganada a Proceso 2 ")
                        time.sleep(2)
            else:
                if len(self.memory) == 10:
                    print("\nProceso 2: TERMINADO")
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
        super(Process3, self).__init__()

    def initialize(self):
        print("Este es el proceso 3")

        return 0
    def tasks(self):
        global CPU_memory
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            print("\nProceso 3 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...")
            time.sleep(2)
            if len(self.memory) == 1:
                self.probability = 98
            if len(self.memory) == 4:
                self.probability = 15

            if (i > self.probability):
                print("\nProceso 3: Eliminando...")
                time.sleep(2)
                self.memory.pop()
                print("\nProceso 3: Tamaño de bloque ", len(self.memory))
                if not self.memory:
                    print("\nProceso 3 sin memoria, solicitando memoria a CPU")
                    # print(CPU_memory)
                    time.sleep(2)
                    if CPU.assign(self, self.memory) is False:
                        print("Proceso 3 sin memoria suficiente: TERMINANDO")
                        time.sleep(2)
                        self.status = False
                    else:
                        print("Memoria extra asiganada a Proceso 3 ")
                        time.sleep(2)
            else:
                if len(self.memory) == 5:
                    print("\nProceso 3: TERMINADO")
                    time.sleep(2)
                    self.status = False
                else:
                    self.memory.append(0)

        return 0


#class Console(object):
#    def __init__(self):
 #       self.memory = 0

  #  def initialize(self):
p1 = Process1()
p2 = Process2()
p3 = Process3()
p4 = Process3()
cpu = CPU()
print("Memoria de CPU inicial " + str(len(cpu.memory)))
cpu.initialize()
print("Memoria de CPU: " + str(len(cpu.memory)))
print("Memoria de Proceso 1: " +str(len(p1.memory)))
print("Memoria de Proceso 2: " +str(len(p2.memory)))
print("Memoria de Proceso 3: " +str(len(p3.memory)))
print("Memoria de Proceso 4: " +str(len(p4.memory)))
p1t = threading.Thread(target=p1.tasks, args=())
p2t = threading.Thread(target=p2.tasks(), args=()) # Thread de Process 1
p3t = threading.Thread(target=p3.tasks(), args=())
p4t = threading.Thread(target=p4.tasks(), args=())
p1t.start()
p2t.start()
p3t.start()
p4t.start()
