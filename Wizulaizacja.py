import serial
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation
import time

fig, ax = plt.subplots(figsize=(10, 10))

circle1 = plt.Circle((0, 0), 200, color='r', fill=False, linewidth=0.5)
circle2 = plt.Circle((0, 0), 150, color='r', fill=False, linewidth=0.5)
circle3 = plt.Circle((0, 0), 100, color='r', fill=False, linewidth=0.5)
circle4 = plt.Circle((0, 0), 50, color='r', fill=False, linewidth=0.5)
for i in range(10, 200, 10):
    if i != 50 or i!= 100 or i!= 150 or i!= 200:
        circle = plt.Circle((0, 0), i, color='grey', fill=False, linewidth=0.5)
    ax.add_artist(circle)

# Select length of axes and the space between tick labels
xmin, xmax, ymin, ymax = -250, 250, -30, 200
#ticks_frequency = 1

# Plot points
ax.scatter(10, 200)

ax.add_artist(circle1)
ax.add_artist(circle2)
ax.add_artist(circle3)
ax.add_artist(circle4)
label1 = ax.annotate("200", xy=(0, 200), fontsize=10, ha="center", color="r")
label2 = ax.annotate("150", xy=(0, 150), fontsize=10, ha="center", color="r")
label3 = ax.annotate("100", xy=(0, 100), fontsize=10, ha="center", color="r")
label4 = ax.annotate("50", xy=(0, 50), fontsize=10, ha="center", color="r")

# Set identical scales for both axes
ax.set(xlim=(xmin-1, xmax+1), ylim=(ymin-1, ymax+1), aspect='equal')

# Set bottom and left spines as x and y axes of coordinate system
ax.spines['bottom'].set_position('zero')
ax.spines['left'].set_position('zero')

# Remove top and right spines
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
plt.xticks([])
plt.yticks([])

# Create 'x' and 'y' labels placed at the end of the axes
ax.set_xlabel('x', size=14, labelpad=15)
ax.set_ylabel('y', size=14, labelpad=15, rotation=0)
ax.xaxis.set_label_coords(1.03, 0.15)
ax.yaxis.set_label_coords(0.5, 1.1)


# Draw major and minor grid lines
#ax.grid(which='both', color='grey', linewidth=1, linestyle='-', alpha=0.2)

# Enter x and y coordinates of points and colors

ser = serial.Serial(
    port='COM4',
    baudrate=28800,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.01)

print("connected to: " + ser.portstr)
i = 0
pomiary=[]
index =[]
while True:
    data = ser.readline()
    if data:
        x = data.decode('utf-8')
        print(x)
        if x == '':
            x=0
        if float(x)<=200:
            #pomiary.append(float(x))
            i=i+1

            dane = ax.scatter(0, float(x), s=150, c='b')
            plt.pause(0.0001)
            time.sleep(0.0001)
            pomiary.append(float(x))
            dane.remove()

plt.show()
plt.clf()







plt.show()