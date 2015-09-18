__author__ = 'Ivan'

import threading, time, random


# Noté que usas python 2.7~ lo de abajo es para que los dos podamos manejar el programa sin problemas de compatibilidad
# Como sidenote uso python 3.4. :P
try:
    import Queue

except:
    import queue as Queue



mut = threading.Lock ()

class Elevator ():
    def __init__(self):
        self.destinations = []
        self.requests = []
        self.nextfloor = 0
        self.current_Floor = 0
        self.time = 0
    def run (self):
        global mut, q1, q2   # q1 = requests, q2 = destinations
        #self.requests.append(q1.get())
        while (time.clock() < 10):
            print ("Estoy en el piso ", self.current_Floor)
            time.sleep(.5)
            self.nextfloor = q2.get()
            print("Voy por el douche al piso ", self.nextfloor )
            self.destinations.append(self.nextfloor)
            time.sleep(.5)
            self.current_Floor = q1.get()
            print ("Dejo al douche en el piso ", self.current_Floor)
            time.sleep(.5)
            # Los sleep son solo para ver como se comportan los hilos sin que flasheen de un jalón en la pantalla LOL
            self.time += random.random() * 1.5

class Student ():
    def __init__(self):
        self.Guy_number = 1
        self.Floor_request = 0
        self.Floor_destination = 0
        self.time = 0
        self.Guy_cap = 0
    def run (self):
        global mut, q1, q2
        while (time.clock() and self.Guy_cap < 10):
        # Mientras no hayan pasado 10 segundos o el tiempo que tengo sea menor a 10 hará la llamada a nuevos tipos.
            v = random.randint(1, 5)
            v2 = random.randint(1, 5)
            while (v == v2):
                v = random.randint(1, 5)
                v2 = random.randint(1, 5)
            q1.put(v)
            q2.put(v2)
            self.Floor_destination = v
            self.Floor_request = v2
            print ("Soy el tipo ", self.Guy_number ," estoy en el piso ", self.Floor_request, "quiero ir a el piso ", self.Floor_destination)
            self.Guy_number += 1
            self.Guy_cap += 1
            #time.sleep (3)
            #mut.acquire ()
            #print ("I should finish first")
            self.time += random.random()
            # es * 2 para que le dé tiempo al elevador de repartir a los tipos que tiene adentro

q1 = Queue.Queue(5)
q2 = Queue.Queue(5)

e = Elevator ()
s = Student()
s2 = Student()
et = threading.Thread(target=e.run, args=()) # Elevator thread
st = threading.Thread(target=s.run, args=()) #Student Thread
st2 = threading.Thread(target=s2.run, args=()) # Student 2 Thread
st.start ()
st2.start()
et.start ()