__author__ = 'Ivan'
import threading
from Proceso_1 import *
p1 = Process1()

class CPU(object):
    def __init__(self):
        self.max_size = 20
        self.memory = [0] * self.max_size


    def initialize(self):
        print("Iniciando repartición de memoria")
        p1.memory = self.memory[:int((len(self.memory)) * .4)] #Tomando los bloques del cpu
        self.memory = [0] * (self.max_size - len(p1.memory))

        # newList = originalList[int(len(originalList) * .05) : int(len(originalList) * .95)]
        return 0

cpu = CPU()
print("Memoria de CPU inicial " + str(len(cpu.memory)))
cpu.initialize()
print("Memoria de CPU: " + str(len(cpu.memory)))
print("Memoria de Proceso 1: " +str(len(p1.memory)))
p1t = threading.Thread(target=p1.tasks, args=()) # Thread de Process 1
p1t.start()