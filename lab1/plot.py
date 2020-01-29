import matplotlib.pyplot as plt
import csv


n = []
t0 = []
t1 = []
t2 = []
t3 = []

with open('myfile.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        n.append(int(row[0]))
        t0.append(int(row[1]))


with open('myfile1.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        # n.append(int(row[0]))
        t1.append(int(row[1]))

with open('myfile2.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        # n.append(int(row[0]))
        t2.append(int(row[1]))


with open('myfile3.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        # n.append(int(row[0]))
        t3.append(int(row[1]))

plt.figure()
plt.xlabel('Matrix size (n)')
plt.ylabel('Time in sec')
plt.plot(n,t0)
plt.plot(n,t1)
plt.plot(n,t2)
plt.plot(n,t3)

# load()
