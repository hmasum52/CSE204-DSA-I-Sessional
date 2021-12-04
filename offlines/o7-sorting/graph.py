import matplotlib.pyplot as plt
import numpy as np

def draw_graph(data):
    plt.title("Average Running Time for QuickSort and MergeSort")
    plt.xlabel("Number of Elements in the Array, N")
    plt.ylabel("Time Required to Sort (sec)")

    # plt.ylim([-200, 2000])
    # plt.xlim(0, 100000)

    types = []
    for key_type in data:
        types.append(key_type)
        x = []
        y = []
        for key_number in data[key_type]:
            x.append(int(key_number))
            y.append(data[key_type][key_number])
        x = np.array(x, dtype='i8')
        y = np.array(y, dtype='f8')
        plt.plot(x, y)
    plt.legend(types)
    plt.show()

""" data = {
    'Merge Ascending': {
        '10': 0.001, '100': 0.001, '1000': 0.001, '10000': 0.002, '100000': 0.012, '1000000':0.107
    },
    'Quick Ascending': {
        '10': 0.001, '100': 0.001, '1000': 0.0042, '10000': 0.1942, '100000': 18.9216, '1000000':1927.413
    },
    'Merge Descending': {
        '10': 0.001, '100': 0.001, '1000': 0.001, '10000': 0.0022, '100000': 0.013, '1000000':0.108
    },
    'Quick Descening': {
        '10': 0.001, '100': 0.001, '1000': 0.003, '10000': 0.1524, '100000': 14.4112, '1000000':1325.369
    },
    'Merge Random': {
        '10': 0.001, '100': 0.001, '1000': 0.001, '10000': 0.0024, '100000': 0.0176, '1000000':0.1835
    },
    'Quick Random': {
        '10': 0.001, '100': 0.001, '1000': 0.001, '10000': 0.0026, '100000': 0.0202, '1000000':0.229
    }
} """

data = {
   'Quick Ascending': {
        '10': 0.001, '100': 0.001, '1000': 0.0042, '10000': 0.1942, '100000': 18.9216, '1000000':1927.413
    },
}

plt.grid(True)

""" fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
ax.spines['left'].set_position('zero')
ax.spines['bottom'].set_position('zero')
ax.spines['left'].set_color('red')
ax.spines['bottom'].set_color('red')
ax.spines["right"].set_color('none')
ax.spines["top"].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.yaxis.set_ticks_position('left') """

draw_graph(data)