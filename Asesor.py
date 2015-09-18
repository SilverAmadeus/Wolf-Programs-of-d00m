__author__ = 'Ivan'

import threading, time, random

# Noté que usas python 2.7~ lo de abajo es para que los dos podamos manejar el programa sin problemas de compatibilidad
# Como sidenote uso python 3.4. :P
try:
    import Queue

except:
    import queue as Queue

mut_s = threading.Lock ()
mut_t = threading.Lock()
sem = threading.Semaphore(2)

class Teacher ():
    def __init__(self):
        self.espera = []
        self.time = 0
        self.count_student = []
        self.priority = 0
    def run (self):
        global mut, q1, q2, id # q1 = sillas, q2 = espera

        while (self.espera.count != 0 ):
            self.priority =  self.count_student.pop()
            print("Voy atender al alumno ",  self.priority)
            mut_s.release()
            sem.acquire()
            mut_t.acquire()
            print("Libero una vacante")
            sem.release()

class Student():
    def __init__(self):

        self.preguntas = 0

    def run (self):
        global mut, q1, q2, id    # q1 = sillas, q2 = espera
        while True :

            self.preguntas = random.randint(1, 3)
            print("QUESTION TIME MOFO!")
            q2.put(self.id)
            if (q1.full is True):
                print("Estoy esperando...")
                
            q1.put(q2.get())
            id += 1

            time.sleep(random.randint(1, 6))



s = Student()
s2 = Student()

st = threading.Thread(target=s.run, args=())
st2 = threading.Thread(target=s2.run, args=())
st.start()
st2.start()




