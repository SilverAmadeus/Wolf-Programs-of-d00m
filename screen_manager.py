from kivy.app import App
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.scrollview import ScrollView
from kivy.uix.screenmanager import ScreenManager, Screen

import subprocess
import psutil 
import sys
import os
import numpy
import matplotlib.pyplot as pyplot  

# Usando el lenguaje kivy
# Creamos ambas pantallas, con root.manager.current: es como controlamos
# el ScreenManager desde kv. Por lo que lei cada pantalla tiene de default un
# property manager que te da la instancia del ScreenManager usado.
Builder.load_string("""
<MainScreen>:
    BoxLayout:
        BoxLayout:
            orientation: 'vertical'
            id: main_box
            size_hint: 0.5, .9
            spacing: 10
            Label:
                id: main_lbl
                markup: True
                size_hint: 1, 5

            BoxLayout:
                Button:
                    size_hint: 1, .8
                    text: 'Run Memory Processses Scan'
                    on_release: root.run_virtual_memory()
        BoxLayout:
            orientation: 'vertical'
            id: secondary_box
            size_hint: 0.5, 1
            spacing: 10
            Label:
                id: secondary_box_lbl
                markup: True
                text: 'Box'
                size_hint: 1, 1

            BoxLayout:
                Button:
                    size_hint: 1, .2
                    text: 'Graficar SWAP Memory'
                    on_release: root.graficar_swap_memory()
                Button:
                    size_hint: 1, .2
                    text: 'Graficar Virtual Memory'
                    on_release: root.grafica_virtual_memory()

            BoxLayout:
                Button:
                    text: 'Ir a otra pantalla'
                    size_hint: 1, .2
                    on_press: root.manager.current = 'settings'

<SettingsScreen>:
    BoxLayout:
        id: graph_scren
        orientation: 'vertical'
        size_hint: 1, 1
        AsyncImage:
            source: '/Users/Ivan/Documents/5th_Semester/OS/Wolf-Programs-of-d00m/swap_memory.png'
        Button:
            text: 'Back to Memory menu'
            size_hint: 1, .15
            on_press: root.manager.current = 'menu'
        Button:
            text: 'Ir a pantalla de PIDS'
            size_hint: 1, .15
            on_press: root.manager.current = 'pid_s'

<PidScreen>:
    BoxLayout:
        BoxLayout:
            orientation: 'vertical'
            id: pid_screen
            size_hint: 1, 1
            Label:
                text: 'OMG'
            Button:
                text: 'Back to Memory menu'
                size_hint: 1, .5
                on_press: root.manager.current = 'menu'
            Button:
                text: 'Mostrar PIDs activos en el sistema'
                size_hint: 1, .5
                on_press: root.run_pids()
        BoxLayout:
            Label:
                text: 'Aqui va la info de los pids'
        ScrollView:
            size_hint: 0.5, 1
            do_scroll_x: False
            BoxLayout:
                orientation: 'vertical'
                id: nodes
                size_hint: (1, None)

""")

# Creamos las pantallas que vamos a usar en la app
# Todo esto se va a manejar desde el lenguaje kivy de arriba
class MainScreen(Screen):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)

        self.main_lbl = self.ids['main_lbl']
        self.main_box = self.ids['main_box']
        self.secondary_box = self.ids['secondary_box']
        self.secondary_box_lbl = self.ids['secondary_box_lbl']

        #Lo dividimos entre 1048576 ya que psutil te regresa los valores en bytes, lo pasamos a Mb
        self.total_swap = psutil.swap_memory().total/1048576
        self.percent_swap = psutil.swap_memory().percent
        self.sin_swap = psutil.swap_memory().sin/1048576
        self.sout_swap = psutil.swap_memory().sout/1048576
        self.used_swap = psutil.swap_memory().used/1048576
        self.free_swap = psutil.swap_memory().free/1048576


        self.total_mem = psutil.virtual_memory().total/1048576
        self.percent_mem = psutil.virtual_memory().percent
        self.active_mem = psutil.virtual_memory().active/1048576
        self.inactive_mem = psutil.virtual_memory().inactive/1048576
        self.used_mem = psutil.virtual_memory().used/1048576
        self.available_mem = psutil.virtual_memory().available/1048576
        self.free_mem = psutil.virtual_memory().free/1048576



    def run_virtual_memory(self):
        "Funcion que... corre y usa los metodods de psutil lol"
        mem = psutil.virtual_memory()
        print mem

        self.main_lbl.text = ('[color=00ff00][i][b]System Memory Status[/b][/i]' + '\n\n' + '[b]Total Virtual Memory: [/b]'
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.total_mem) +' Mb'+ '\n\n' + 'Percent: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.percent_mem) +'%'+ '\n\n' + 'Active: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.active_mem) +' Mb'+ '\n\n' + 'Inactive: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.inactive_mem) +' Mb'+ '\n\n' + 'Used: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.used_mem) +' Mb'+ '\n\n' + 'Available: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.available_mem) +' Mb'+ '\n\n' + 'Free: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.free_swap) +' Mb'+ '\n\n' + '[b]Total Swap Memory: [/b]'
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.total_swap) +' Mb'+ '\n\n' + 'Percent: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.percent_swap) +'%'+ '\n\n' + 'SIN: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.sin_swap) +' Mb'+ '\n\n' + 'SOUT: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.sout_swap) +' Mb'+ '\n\n' + 'Used: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.used_swap) +' Mb'+ '\n\n' + 'Free: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.free_swap) +' Mb'+ '\n\n'

        )

    def graficar_swap_memory(self):
        totalswapMeans  = [numpy.array(self.total_swap), 0, 0]
        sinswapMeans    = [0, numpy.array(self.sin_swap), 0]
        soutswapMeans   = [0, numpy.array(self.sout_swap), 0] 
        usedswapMeans   = [0, 0, numpy.array(self.used_swap)]
        freeswapMeans   = [0, 0, numpy.array(self.free_swap)]

        ind = numpy.arange(3)
        width = .5

        b1 = pyplot.bar(ind, totalswapMeans, width, color = 'red')
        b2 = pyplot.bar(ind, sinswapMeans, width, color = 'blue')
        b3 = pyplot.bar(ind, soutswapMeans, width, color = 'green')
        b4 = pyplot.bar(ind,sinswapMeans,width,color = 'cyan')
        b5 = pyplot.bar(ind, usedswapMeans, width, color = 'gold')
        b6 = pyplot.bar(ind, freeswapMeans, width, color = 'yellow')
        b7 = pyplot.bar(ind,usedswapMeans,width,color = 'magenta')

        pyplot.ylabel('Megabytes')
        pyplot.title('Graph SWAP Memory')
        pyplot.xticks(ind+width/2., ('total','sout/sin','used/free' ))
        pyplot.legend((b1[0], b2[0],b3[0],b4[0],b5[0]), ('total', 'sin','sout','used','free'))

        pyplot.savefig('swap_memory.png')
        pyplot.show()

    def grafica_virtual_memory(self):
        arrTotal = [numpy.array(self.total_mem),0,0,0,0,0]
        arrAvailable = [0,numpy.array(self.available_mem),0,0,0,0]
        arrUsed = [0,0,numpy.array(self.used_mem),0,0,0]
        arrFree = [0,0,0,numpy.array(self.free_mem),0,0]
        arrActive = [0,0,0,0,numpy.array(self.active_mem),0]
        arrInactive = [0,0,0,0,0,numpy.array(self.inactive_mem)]
        
        rango = numpy.arange(6)
        width = .5
        ##CHECAR CUALES ESTAN DISPONIBLES EN OSX
        d1 = pyplot.bar(rango,arrTotal,width, color = 'c')
        d2 = pyplot.bar(rango,arrAvailable,width, color = 'm')
        d3 = pyplot.bar(rango,arrUsed,width, color = 'b')
        d4 = pyplot.bar(rango,arrFree,width, color = 'g')
        d5 = pyplot.bar(rango,arrActive,width, color = 'r')
        d6 = pyplot.bar(rango,arrInactive,width, color = 'b')

        pyplot.ylabel("MB's")
        pyplot.title("Virtual Memory")
        pyplot.xticks(rango+width/2,('Total','Available','Used','Free','Active','Inactive'))
        #pyplot.legend((p1[0],p2[0],p3[0],p4[0],p5[0],p6[0]),('Rss','Vms','Shared','Text','LIb','Data','Dirty'))
        pyplot.savefig('virtual_memory.png')
        pyplot.show()

        labels = ['Available','Used']
        slices = [float(100*self.available_mem/self.total_mem),float(100*self.used_mem/self.total_mem)]
        colors = ['blue','red']

        pyplot.pie(slices,labels=labels,colors=colors, explode = (0.05,0),autopct='%1.1f%%')
        pyplot.title('Virtual Memory')        
        pyplot.savefig('virtual_average.png')
        pyplot.show()



class SettingsScreen(Screen):
    pass

class PidScreen(Screen):
    #self.nodes.clear_widgets()
    def __init__(self, **kwargs):
        super(PidScreen, self).__init__(**kwargs)
        self.nodes = self.ids['nodes']

    def run_pids(self):
        self.nodes.clear_widgets()
        self.lista = []
        var = subprocess.check_output(['ps','-u',psutil.users()[0].name]) # tercer parametro selecciona el usuario del sistema
        ren = var.split('\n') #obteniendo reglones
        cont = 0 #control ignora primera y ultima linea
        for n in ren:
            cont = cont + 1
            if cont == 1:
                pass
            elif  cont == len(ren):
                pass #ultima linea a ignorar         
            else:
                process = n.split()
                if sys.platform.startswith("linux"):
                    selected = 0
                elif sys.platform.startswith("darwin"): #OSX
                    selected = 1
                else:
                    print "NOT SUPPORTED" #EXCEPTION?
                self.lista.append(int(process[selected]))


        #Vamos a introducir cada uno de los PIDs que se puedan usar en la lista de scroll .:D
        for p in self.lista:
            self.nodes.add_widget(Button(text='[color=00ff00]PID: {0}[/color]'.format(p), markup= True, font_size = '15sp', 
                height='200sp'))

        self.nodes.size = (200, 40000)

# Creamos el manager de las pantallas
sm = ScreenManager()
sm.add_widget(MainScreen(name='menu'))
sm.add_widget(SettingsScreen(name='settings'))
sm.add_widget(PidScreen(name='pid_s'))

class TestApp(App):


    def build(self):
        return sm

if __name__ == '__main__':
    TestApp().run()