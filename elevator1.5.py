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
            self.destinations.append(q1.get())
            self.nextfloor = self.destinations.pop()
            print("Voy por el douche al piso ", self.nextfloor )
            time.sleep(.5)
            self.current_Floor = self.nextfloor
            print ("Dejo al douche en el piso ", self.current_Floor)
            q2.put(self.current_Floor)
            time.sleep(.5)
            # Los sleep son solo para ver como se comportan los hilos sin que flasheen de un jalón en la pantalla LOL
            self.time += random.random()

class Student ():
    def __init__(self):
        self.Guy_number = 1
        self.Floor_request = 0
        self.Floor_destination = 0
        self.time = 0
    def run (self):
        global mut, q1, q2
        while (time.clock() < 10):
        # Mientras no hayan pasado 10 segundos o el tiempo que tengo sea menor a 10 hará la llamada a nuevos tipos.
            v = random.randint(1, 5)
            q1.put(v)
            self.Floor_destination = v
            print ("Soy el tipo ", self.Guy_number ," estoy en el piso ", self.Floor_request, "quiero ir a el piso ", self.Floor_destination)
            self.Guy_number += 1
            time.sleep (3)
            #mut.acquire ()
            #print ("I should finish first")
            self.time += random.random() * 2
            # es * 2 para que le dé tiempo al elevador de repartir a los tipos que tiene adentro

q1 = Queue.Queue(5)
q2 = Queue.Queue(5)


e = Elevator ()
s = Student()
et = threading.Thread(target=e.run, args=()) # Elevator thread
st = threading.Thread(target=s.run, args=()) #Student Thread
st.start ()
et.start ()