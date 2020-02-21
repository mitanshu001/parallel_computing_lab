#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv


n = []
t0 = []
t1 = []
t2 = []
t3 = []
t4 =[]

# with open('summation_method3.csv','r') as csvfile:
# 	plots = csv.reader(csvfile, delimiter=',')
# 	for row in plots:
# 		# print(row)
# 		# n.append(int(row[0]))
# 		t4.append(int(row[1]))


scale = 1000
with open('summation_naive.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# print(row)
		n.append(int(row[0]))
		t0.append(float(row[1]))


with open('summation_method2.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# n.append(int(row[0]))
		t1.append(float(row[1]))

with open('summation_method3.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# n.append(int(row[0]))
		# print(row[1])
		t2.append(float(row[1]))
		# print(row[1])

# with open('myfile3_64.csv','r') as csvfile:
# 	plots = csv.reader(csvfile, delimiter=',')
# 	for row in plots:
# 		# n.append(int(row[0]))
# 		t3.append(int(row[1]))
print(t0)
print(t1)
print(t2)
# print(t3)
plt.figure()
plt.xlabel('Matrix size (n)')
plt.ylabel('Time in sec')
plt.plot(n,t0,label="Naive")
plt.plot(n,t1,label="Recursive")
plt.plot(n,t2,label="Reduce")
# plt.plot(n,t3,label="opt3")
# plt.plot(n,t4,label="theoritical")
plt.legend(loc="upper right")
plt.show()
# load()
