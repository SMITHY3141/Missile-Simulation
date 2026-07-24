

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import subprocess

result = subprocess.run(["./sim"])


csv_file = "logs/log.csv"
spacing = 20 # draw basis vectors every N points
axis_length = 0.1 # scale size of vectors

# Load data
df = pd.read_csv(csv_file)
positions = df[['x', 'y', 'z']].to_numpy()
right = df[['r_x','r_y','r_z']].to_numpy()
forward = df[['f_x','f_y','f_z']].to_numpy()
up = df[['u_x','u_y','u_z']].to_numpy()

# Plot
fig = plt.figure(figsize=(10,8))
fig.canvas.manager.set_window_title("Trajectory")
ax = fig.add_subplot(111, projection='3d')

mins = positions.min(axis=0) # need these to scale the axes
maxs = positions.max(axis=0)
center = (mins + maxs) / 2 
radius = np.max(maxs - mins) / 2

# plot position
ax.plot(
    positions[:,0],
    positions[:,1],
    positions[:,2],
    'k:', # black and dotted
    linewidth=2
)

# plot rotation
for i in range(0, len(df), spacing):
    p = positions[i]
    ax.quiver(*p, *right[i], color='r', length=axis_length * radius, normalize=True)
    ax.quiver(*p, *forward[i], color='g', length=axis_length * radius, normalize=True)
    ax.quiver(*p, *up[i], color='b', length=axis_length * radius, normalize=True)


ax.set_xlim(center[0]-radius, center[0]+radius)
ax.set_ylim(center[1]-radius, center[1]+radius)
ax.set_zlim(center[2]-radius, center[2]+radius)
ax.set_box_aspect((1, 1, 1))

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")

plt.show()
