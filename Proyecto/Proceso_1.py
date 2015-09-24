__author__ = 'Ivan'
import random, time
class Process1(object):
    def __init__(self):
        self.memory = []
        self.status = True

    def initialize(self):
        print("Este es el proceso 1")

        return 0
    def tasks(self):
        while self.status is True:
            i = random.randint(0, 99)
            print("Proceso 1: Trabajando...")
            time.sleep(2)
            print(i)
            if (i < 40):
                print("Proceso 1: Eliminando...")
                time.sleep(2)
                self.memory.pop()
                print("Proceso 1: Tamaño de bloque ", len(self.memory))
                if not self.memory:
                    print("Proceso 1 sin memoria")
                    self.status = False

        return 0
