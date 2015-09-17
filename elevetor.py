import threading 
import random 
import time
import Queue

llamadas = Queue.Queue()
destinos = Queue.Queue()
mut = threading.Semaphore(1)
elevador = threading.Semaphore(5) # 4 por el numero (n-1) pasajeros permitidos
personas_dentro = 0
piso_actual = 1
personas_fuera = 0

def comparar(num1,num2):
	while num1 != num2:
		return num1,num2
	num1 = random.randrange(1,6,1)
	num2 = random.randrange(1,6,1)
	return comparar(num1,num2)


def lift (i,entrada,destino):
	global personas_dentro, personas_fuera, mut, elevador
	print "Soy el usuario ",i,".Piso entrada: ",entrada," piso destino: ",destino,"."
	elevador.acquire()
	#while llamadas.empty():
	mut.acquire()
	piso_actual = llamadas.get()
	print "Estoy en el piso",piso_actual," recogiendo al usuario",i+1
	personas_dentro += 1
	mut.release()
	
	#print "Se ha dejado al usuario",i+1," en el piso: ",piso_actual
	
	print personas_dentro
	if personas_dentro % 5 == 0:
		personas_dentro-=1
		print "Esta lleno"
		elevador.release()
		mut.acquire()
		piso_actual = destinos.get()
		print	"Dejando al usuario",i,"en el piso",piso_actual
		mut.release()
			

		

	
for i in range (1,11):
	entrada,destino = comparar(random.randrange(1,6,1),random.randrange(1,6,1))
	llamadas.put(entrada)
	destinos.put(destino)
	usu = threading.Thread(target = lift,args = (i,entrada,destino,))
	usu.daemon = True
	usu.start()
	time.sleep(0.1)
