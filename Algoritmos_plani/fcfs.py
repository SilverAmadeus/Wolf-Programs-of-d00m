import threading, time, random, queue

aux = []

class Processor():
	def __init__(self):
		self.time = 1
		#self.history = []
	def run(self):
		global history
		while not (comes.empty()):
			a=comes.get()
			a.start() #Aranca el hilo
		
		#for i in range (len(aux)):
		#	print (aux[i][2])
		while (len(aux)!=0):
			if self.time==aux[0][0]:	#tiempo igual a 
				for j in range (aux[0][1]):
					history.append(aux[0][2])
					self.time+=1
				aux.pop(0)

			elif self.time > aux[0][0]:
				for j in range (aux[0][1]):
					history.append(aux[0][2])
					self.time+=1
				aux.pop(0)				
			else:
				history.append('IDLE')
				self.time+=1
		print(history)


class Process():
	def __init__(self,name):
		self.name = name
		self.t_come = random.randint(1,20)
		self.t_exe = random.randint(1,6)
		

	def run (self):
		aux.append([self.t_come,self.t_exe,self.name])
		aux.sort()
		print(aux)
			


comes = queue.Queue()
history = []		
A = Process('A')
B = Process('B')
C = Process('C')
D = Process('D')
E = Process('E')

At = threading.Thread(target=A.run,args=())
Bt = threading.Thread(target=B.run,args=())
Ct = threading.Thread(target=C.run,args=())
Dt = threading.Thread(target=D.run,args=())
Et = threading.Thread(target=E.run,args=())


comes.put(At)
comes.put(Bt)
comes.put(Ct)
comes.put(Dt)
comes.put(Et)

CPU = Processor()
CPUt = threading.Thread(target=CPU.run,args=())
CPUt.start()
