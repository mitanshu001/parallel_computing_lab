#!/usr/bin/env python
import matplotlib.pyplot as plt
import csv


n = []
t0 = []
t1 = []
t2 = []
t3 = []
t4 =[]

# with open('myfile3_8.csv','r') as csvfile:
# 	plots = csv.reader(csvfile, delimiter=',')
# 	for row in plots:
# 		# print(row)
# 		# n.append(int(row[0]))
# 		t0.append(int(row[1]))



with open('odd_even_sort.csv','r') as csvfile:
	plots = csv.reader(csvfile, delimiter=',')
	for row in plots:
		# print(row)
		n.append(int(row[0]))
		t1.append(float(row[1]))


# with open('myfile3.csv','r') as csvfile:
# 	plots = csv.reader(csvfile, delimiter=',')
# 	for row in plots:
# 		# n.append(int(row[0]))
# 		t2.append(int(row[1]))

# with open('myfile3_64.csv','r') as csvfile:
# 	plots = csv.reader(csvfile, delimiter=',')
# 	for row in plots:
# 		# n.append(int(row[0]))
# 		# print(row[1])
# 		t3.append(int(row[1]))
# 		# print(row[1])


print(t0)
print(t1)
# print(t2)
# print(t3)
plt.figure()
plt.title('Execution Time of odd even sort')
plt.xlabel('value of s')
plt.ylabel('Time in sec')
# plt.plot(n,t0,label="s=8")
plt.scatter(n,t1,label="s=16")
# plt.plot(n,t2,label="s=32")
# plt.plot(n,t3,label="s=64")
# plt.plot(n,t4,label="theoritical")
plt.legend(loc="upper left")
plt.show()
# load()
