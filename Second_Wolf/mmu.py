__author__ = 'Alan'
__author__ = 'Ivan'

import psutil

class monitor():
    def __init__(self):
        self.name = "Monitor"
        self.bytes = 1048576 #1 MB



    def memory_general(self):
        print "Total Memory: ",psutil.virtual_memory().total/self.bytes,"MB"
        print "Available Memory: ", psutil.virtual_memory().available/self.bytes,"MB"
        print "Percent of use: ",psutil.virtual_memory().percent,"%"
        print "Memory used: ",psutil.virtual_memory().used/self.bytes,"MB"
        print "Memory free: ",psutil.virtual_memory().free/self.bytes,"MB"

    def swap_memory(self):
        print "Total Swap Memory: ",psutil.swap_memory().total/self.bytes,"MB"
        print "Swap Memory used: ",psutil.swap_memory().used/self.bytes,"MB"
        print "Swap Memory free: ",psutil.swap_memory().free/self.bytes,"MB"
        print "Percent of use: ",psutil.swap_memory().percent,"%"
        print "Sin?: ",psutil.swap_memory().sin/self.bytes,"MB"
        print "Sout?: ",psutil.swap_memory().sout/self.bytes,"MB"

    def show_process(self):
        return psutil.pids()

    def select_process(self,processes,number):
        if processes.count(number)!=0:
            return processes.pop(processes.index(number))
        else:
            return None

    def memory_process(self,selected):
        if selected!=None:
            process = psutil.Process(selected)
            print "Process<pid>: %s , Name: %s" %(process.pid,process.name())
            templ = "%-16s %10s  %-7s %s"
            print(templ % ("Address", "RSS", "Mode", "Mapping"))
            total_rss = 0
            for m in process.memory_maps(grouped=False):
                total_rss += m.rss
                print(templ % (m.addr.split('-')[0].zfill(16),str(m.rss / 1024) + 'K', m.perms, m.path))
            print("-" * 33)
            print(templ % ("Total", str(total_rss / 1024) + 'K', '', ''))

        else:
            print "The process doesn't exist. Sorry bro!"

n = monitor()
#print n.name
#n.memory_general()
#n.swap_memory()
list = n.show_process()
#print list
inte = n.select_process(list,376)
print inte

n.memory_process(inte)