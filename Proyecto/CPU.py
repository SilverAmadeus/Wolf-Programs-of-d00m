__author__ = 'Ivan'
import threading
from Proceso_1 import *
from Proceso_2 import *
from Proceso_3 import *

p1 = Process1()
p2 = Process2()
p3 = Process3()
p4 = Process3()

class CPU(object):
    def __init__(self):
        self.max_size = 50
        self.memory = [0] * self.max_size


    def initialize(self):
        print("Iniciando repartición de memoria")
        p1.memory = self.memory[:int((len(self.memory)) * .4)] #Tomando los bloques del cpu para proceso 1
        self.memory = [0] * (self.max_size - len(p1.memory))

        p2.memory = self.memory[:int((len(self.memory)) * .35)] #Tomando los bloques del cpu para proceso 2
        self.memory = [0] * (len(self.memory)- len(p2.memory))

        p3.memory = self.memory[:int((len(self.memory)) * .25)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p3.memory))

        p4.memory = self.memory[:int((len(self.memory)) * .25)] #Tomando los bloques del cpu para proceso 3
        self.memory = [0] * (len(self.memory)- len(p4.memory))
        # newList = originalList[int(len(originalList) * .05) : int(len(originalList) * .95)]
        return 0


#class Console(object):
#    def __init__(self):
 #       self.memory = 0

  #  def initialize(self):

cpu = CPU()
print("Memoria de CPU inicial " + str(len(cpu.memory)))
cpu.initialize()
print("Memoria de CPU: " + str(len(cpu.memory)))
print("Memoria de Proceso 1: " +str(len(p1.memory)))
print("Memoria de Proceso 2: " +str(len(p2.memory)))
print("Memoria de Proceso 3: " +str(len(p3.memory)))
print("Memoria de Proceso 3: " +str(len(p3.memory)))
p1t = threading.Thread(target=p1.tasks, args=())
p2t = threading.Thread(target=p2.tasks(), args=())# Thread de Process 1
p3t = threading.Thread(target=p3.tasks(), args=())
p4t = threading.Thread(target=p4.tasks(), args=())
p1t.start()
p2t.start()
p3t.start()
p4t.start()
