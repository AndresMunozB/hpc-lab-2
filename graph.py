import pandas as pd
import matplotlib.pyplot as plt
def read_file(name_file):
	data_frame = pd.read_csv(name_file)
	return data_frame

def graph_data(x,y):
    plt.plot(x,y)
    plt.show()

data = read_file("65536_2l_1h.csv")
data2 = read_file("65536_2l_4h.csv")
metrics = data['time'].describe()
metrics2 = data2['time'].describe()
print(metrics)
print(metrics2)
graph_data(list(range(1,len(data['time'])+1)), data['time'])
graph_data(list(range(1,len(data2['time'])+1)), data2['time'])
