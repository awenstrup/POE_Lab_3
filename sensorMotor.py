import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

file = open('motorout1.txt', 'r')

leftSense = []
rightSense = []
leftMotor = []
rightMotor = []
for num, line in enumerate(file):
    data = line.split(" ")
    leftSense.append(int(data[0]))
    rightSense.append(int(data[1]))
    leftMotor.append(int(data[2]))
    rightMotor.append(int(data[3]))
# fig = plt.figure()
# ax = fig.add_subplot(111)
# ax.plot(leftSense,leftMotor)
# every_nth = 10
# for n, label in enumerate(ax.xaxis.get_ticklabels()):
#     if n % every_nth != 0:
#         label.set_visible(False)
# fig = plt.figure()
# ax = fig.add_subplot(111)
# ax.scatter(rightSense, rightMotor)
# for n, label in enumerate(ax.xaxis.get_ticklabels()):
#     if n % every_nth != 0:
#         label.set_visible(False)
# plt.show()
print(leftSense)
print(rightSense)
print(leftMotor)
print(rightMotor)
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.set_zlim(-10,40)
plt.scatter(leftSense,rightSense, leftMotor)
plt.scatter(leftSense,rightSense, rightMotor)
plt.show()
