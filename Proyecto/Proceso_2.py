import random, time
class Process2(object):
    def __init__(self):
        self.max_size = 0
        self.memory = []
        self.status = True
        self.probability = 0
        self.process = "Trabajando"

    def initialize(self):
        print("Este es el proceso 2")

        return 0
    def tasks(self):
        self.max_size = len(self.memory)
        while self.status is True:
            i = random.randint(0, 99)
            print("\nProceso 2 (Tamaño: " + str(len(self.memory))+ ") " +str(i)+": Trabajando...",  end='\r')
            time.sleep(2)
            if len(self.memory) == 3:
                self.probability = 95
            elif len(self.memory) == 8:
                self.probability = 25

            if (i > self.probability):
                print("\nProceso 2: Eliminando...", end='\r')
                time.sleep(2)
                self.memory.pop()
                print("\nProceso 2: Tamaño de bloque ", len(self.memory), end='\r')
                if not self.memory:
                    print("\nProceso 2 sin memoria", end='\r')
                    self.status = False
            else:
                if len(self.memory) == 10:
                    print("\nProceso 2: Memoria maxima",  end='\r')
                else:
                    self.memory.append(0)

        return 0
