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
    ax = sns.boxplot(x='threads', y= evaluation_criteria, data= data, palette = "BuGn_r")
    ax = sns.swarmplot(x="threads", y= evaluation_criteria, data= data, color=".25")
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

def get_name_list(base, levels, threads):
    names = []
    for j in range(0,levels):
        for i in threads:
            names.append([base+"_"+str(j)+"l"+"_"+str(i)+"h.csv" , j , i])
    return names

def mean(names,name_out):
    file_out = open(name_out, 'w')
    file_out.write("name,levels,threads,mean\n")
    for name in names:
        data = read_file(name[0])
        mean = data['time'].mean()
        file_out.write(name[0] + "," + str(name[1]) + "," + str(name[2]) + "," + str(mean) + "\n")
    file_out.close()

def graph(name):
    data = read_file(name)
    print(data)

threads = [1,5,9,13,17,21,25,29,33,37,41]
levels = 20
file_out = "promedios.csv"
name_list = get_name_list("64",levels,threads)
mean(name_list,file_out)
graph(file_out)
