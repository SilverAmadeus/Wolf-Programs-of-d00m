__author__ = 'Ivan'
import random, time
class Process3(object):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"

    def initialize(self):
        print("Este es el proceso 3")

        return 0
    def tasks(self):
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            print("\nProceso 3 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...",  end='\r')
            time.sleep(2)
            if len(self.memory) == 1:
                self.probability = 98
            elif len(self.memory) == 4:
                self.probability = 15

            if (i > self.probability):
                print("\nProceso 3: Eliminando...", end='\r')
                time.sleep(2)
                self.memory.pop()
                print("\nProceso 3: Tamaño de bloque ", len(self.memory), end='\r')
                if not self.memory:
                    print("\nProceso 3 sin memoria", end='\r')
                    self.status = False
            else:
                if len(self.memory) == 5:
                    print("\nProceso 3: Memoria maxima",  end='\r')
                else:
                    self.memory.append(0)

        return 0
