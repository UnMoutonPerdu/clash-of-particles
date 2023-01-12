#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import sys

data = np.genfromtxt('data_complexity_heap.csv' if len(sys.argv) == 1 else sys.argv[1],
                     delimiter=',',
                     names=['nb', 'insert', 'extract'])

fig, axes = plt.subplots(1,1)

axes.set_title("Time to insert/extract all (min) nodes in/from heap")
axes.set_xlabel('# of nodes')
axes.set_ylabel('time')

# time to insert
axes.plot(data['nb'], data['insert'], c='r', label='insert')

# time to extract
axes.plot(data['nb'], data['extract'], c='b', label='extract_min')

#print log function
foo = np.log(data['nb'])/np.log(2)
axes.plot(data['nb'], foo, c='b', label = 'log(n)')

# legend
axes.legend()

plt.show()
