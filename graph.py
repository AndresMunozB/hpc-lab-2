import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from numpy import mean

def read_file(name_file):
	data_frame = pd.read_csv(name_file)
	return data_frame

def graph_data(x,y):
    plt.plot(x,y)
    plt.show()

def graph_boxplot(data, filename, title, evaluation_criteria):
    ax = sns.boxplot(x='instance', y= evaluation_criteria, data= data, palette = "BuGn_r")
    ax = sns.swarmplot(x="instance", y= evaluation_criteria, data= data, color=".25")
    ax.set_title(title)
    ax.figure.savefig(filename,format='jpeg')
    plt.clf()

def graph_barplot(data,x,y,filename):
    ax = sns.barplot(x=x, y=y, data=data, estimator=mean)
    ax.figure.savefig(filename+".jpeg",format='jpeg')
def append_data(data,threads,filename):
    file = open(filename, 'a+')
    for i in data:
        file.write(""+str(threads)+","+str(i)+"\n")
    file.close()
    

def unify_data(name_list,outputfile):
    file = open(outputfile, 'a+')
    file.write("threads,time\n")
    file.close()
    for name in name_list:
        data = read_file(name[0])
        append_data(data['time'],name[1],outputfile)


    
'''data = []
threads = ["1h", "4h", "10h", "15h"]
for thread in threads:
    tmp = read_file("65536_2l_" + thread+ ".csv")
    data.append(tmp['time'])
count = 0
colors = ['black','red','gray','orange','gold','yellow','green','aqua','blue','indigo','pink']
for instancia in data:
    plt.scatter(list(range(1,len(instancia)+1)),instancia,c=colors[count],label="Iteración" + str(count+1),s=15)
    count = count + 1
plt.title("Los 11 mejores resultados")
plt.ylabel("Cantidad de trabajadores normalizado")
plt.xlabel("Iteraciones")
plt.legend(loc='best')
plt.show()'''

def get_name_list(base, levels, threads):
    names = []
    for i in threads:
        names.append(base+"_"+str(levels)+"l"+"_"+str(i)+"h.csv")
    return names
 
threads = [1,5,10,15,20,25,30,35]
name_list = get_name_list("16000000",2,threads)
unify_data(name_list,"2_levels.csv")
data = read_file("2_levels.csv")
graph_barplot(data,"threads", "time", "barplot2")

