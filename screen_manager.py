from kivy.app import App
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.scrollview import ScrollView
from kivy.uix.screenmanager import ScreenManager, Screen

from subprocess import check_output

import psutil #Debes hacer uso de la linea de comando que te mande por WA para hacer uso de psutil
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
            size_hint: 0.5, 1
            spacing: 10
            Label:
                id: main_lbl
                markup: True
                size_hint: 1, 5

            BoxLayout:
                Button:
                    size_hint: 1, 1
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
                size_hint: 1, 1

            BoxLayout:
                Button:
                    size_hint: 1, .2
                    text: 'Nuevo boton'
                    on_release: root.graficar()
                TextInput:
                    id: iface_name
                    size_hint: 1, .2
                    multiline: False

            BoxLayout:
                Button:
                    text: 'Ir a otra pantalla'
                    size_hint: 1, .2
                    on_press: root.manager.current = 'settings'

<SettingsScreen>:
    BoxLayout:
        BoxLayout:
            size_hint: 1, 1
            AsyncImage:
                source: '/Users/Ivan/Documents/5th_Semester/OS/Wolf-Programs-of-d00m/swap_memory.png'
        Button:
            text: 'Back to Memory menu'
            size_hint: 1, .15
            on_press: root.manager.current = 'menu'
""")

# Creamos las pantallas que vamos a usar en la app
# Todo esto se va a manejar desde el lenguaje kivy de arriba
class MainScreen(Screen):
    def __init__(self, **kwargs):
        super(MainScreen, self).__init__(**kwargs)

        self.iface_name = self.ids['iface_name']
        self.main_lbl = self.ids['main_lbl']
        self.main_box = self.ids['main_box']
        self.secondary_box = self.ids['secondary_box']
        self.secondary_box_lbl = self.ids['secondary_box_lbl']
        self.pids = psutil.pids()
        self.str1 = ' '.join(str(e) for e in self.pids)

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



    def run_virtual_memory(self):
        "Funcion que... corre y usa los metodods de psutil lol"
        mem = psutil.virtual_memory()
        print mem




        self.main_lbl.text = ('[color=00ff00][i][b]System Memory Status[/b][/i]' + '\n\n' + 'Total Memory: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.total_mem) +' Mb'+ '\n\n' + 'Percent: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.percent_mem) +'%'+ '\n\n' + 'Active: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.active_mem) +' Mb'+ '\n\n' + 'Inactive: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.inactive_mem) +' Mb'+ '\n\n' + 'Used: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.used_mem) +' Mb'+ '\n\n' + 'Available: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.available_mem) +' Mb'+ '\n\n' + 'Total Swap Memory: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.total_swap) +' Mb'+ '\n\n' + 'Percent: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.percent_swap) +'%'+ '\n\n' + 'SIN: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.sin_swap) +' Mb'+ '\n\n' + 'SOUT: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.sout_swap) +' Mb'+ '\n\n' + 'Used: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.used_swap) +' Mb'+ '\n\n' + 'Free: '
        + '[color=00ff00][i]{0}[/i][/color]'.format(self.free_swap) +' Mb'+ '\n\n'

        )

    def graficar(self):
        totalswapMeans = [numpy.array(self.total_swap), 0, 0]
        sinswapMeans = [0, numpy.array(self.sin_swap), 0]
        soutswapMeans = [0, numpy.array(self.sout_swap), 0] 
        usedswapMeans = [0, 0, numpy.array(self.used_swap)]
        freeswapMeans = [0, 0, numpy.array(self.free_swap)]

        ind = numpy.arange(3)
        width = .5

        b1 = pyplot.bar(ind, totalswapMeans, width, color = 'red')
        b2 = pyplot.bar(ind, sinswapMeans, width, color = 'blue')
        b3 = pyplot.bar(ind, soutswapMeans, width, color = 'green', bottom = sinswapMeans)
        b4 = pyplot.bar(ind, usedswapMeans, width, color = 'gold')
        b5 = pyplot.bar(ind, freeswapMeans, width, color = 'yellow', bottom = usedswapMeans)

        pyplot.ylabel('Megabytes')
        pyplot.title('Graph SWAP Memory')
        pyplot.xticks(ind+width/2., ('total','sout/sin','used/free' ))
        pyplot.legend((b1[0], b2[0],b3[0],b4[0],b5[0]), ('total', 'sin','sout','used','free'))

        pyplot.savefig('swap_memory.png')
        pyplot.show()




    def run_pids(self):
        #self.comp = datetime.now().strftime(' %H:%M:%S')
        self.secondary_box_lbl.text = (self.str1)



class SettingsScreen(Screen):
    pass

# Creamos el manager de las pantallas
sm = ScreenManager()
sm.add_widget(MainScreen(name='menu'))
sm.add_widget(SettingsScreen(name='settings'))

class TestApp(App):


    def build(self):
        return sm

if __name__ == '__main__':
    TestApp().run()