import numpy as np
import matplotlib.pyplot as plt
import os

# --- CONFIG ---
input_file = "./../3body_hermite_0.1.csv"
frames_dir = "frames"
frameSkip = 2  # <-- change this to skip every N frames
os.makedirs(frames_dir, exist_ok=True)

# --- READ DATA ---
with open(input_file, "r") as f:
    raw = f.read().strip()

# Split by double newlines -> each timestep
blocks = [b for b in raw.split("\n\n") if b.strip()]
timesteps = [np.loadtxt(block.splitlines(), delimiter=",") for block in blocks]

# --- PLOT SETUP (reuse figure) ---
lim = 1.1 * np.max([np.abs(t[:, 1:4]).max() for t in timesteps])  # fixed 1:2 → 1:4
fig = plt.figure(figsize=(6, 6))
ax = fig.add_subplot(111, projection="3d")

# Initial empty scatter plot
scat = ax.scatter([], [], [], s=40.0)
ax.set_xlim(-lim, lim)
ax.set_ylim(-lim, lim)
ax.set_zlim(-lim, lim)

# --- PLOT EACH FRAME ---
for i, data in enumerate(timesteps[::frameSkip]):
    t = data[0, 0]
    x, y, z = data[:, 1], data[:, 2], data[:, 3]

    # Update scatter data
    scat._offsets3d = (x, y, z)

    # Update title
    ax.set_title(f"Time = {t:.2f}")

    # Rotate camera if desired
    azimuth = 40  # or: 40 + i * some_angle
    elevation = 30
    ax.view_init(elev=elevation, azim=azimuth)

    # Save frame
    fname = f"{frames_dir}/frame_{i:04d}.png"
    fig.savefig(fname)

print(f"Saved {len(timesteps[::frameSkip])} frames in '{frames_dir}/'")
plt.close(fig)
