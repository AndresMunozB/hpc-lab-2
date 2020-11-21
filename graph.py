import pandas as pd
import matplotlib.pyplot as plt
def read_file(name_file):
	data_frame = pd.read_csv(name_file)
	return data_frame

def graph_data(x,y):
    plt.plot(x,y)
    plt.show()

data = []
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
plt.show()

