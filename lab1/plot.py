#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv


n = []
t0 = []
t1 = []
t2 = []
t3 = []
t4 =[]

with open('theoritical.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# print(row)
		# n.append(int(row[0]))
		t4.append(int(row[1]))



with open('myfile.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# print(row)
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
		# print(row[1])
		t2.append(int(row[1]))
		# print(row[1])

with open('myfile3_64.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# n.append(int(row[0]))
		t3.append(int(row[1]))
print(t0)
print(t1)
print(t2)
print(t3)
plt.figure()
plt.xlabel('Matrix size (n)')
plt.ylabel('Time in sec')
plt.plot(n,t0,label="naive")
plt.plot(n,t1,label="opt1")
plt.plot(n,t2,label="opt2")
plt.plot(n,t3,label="opt3")
plt.plot(n,t4,label="theoritical")
plt.legend(loc="upper left")
plt.show()
# load()
