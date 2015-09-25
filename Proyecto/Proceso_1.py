__author__ = 'Ivan'
import random, time
class Process1(CPU):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"

    def initialize(self):
        print("Este es el proceso 1")
        #end='\r'

        return 0
    def tasks(self):
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
                    print("Proceso 1 sin memoria")
                    self.status = False
            else:
                if len(self.memory) == 20:
                    print("Proceso 1: Memoria maxima")
                else:
                    self.memory.append(0)

        return 0
