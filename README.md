🧱 Folder Structure
linux-i2c-temp-driver/
├── src/
│   ├── tmp102_sim.c
│   └── userspace_read.c
├── Makefile
└── README.md

⚙️ Build Instructions
make


This builds:

tmp102_sim.ko → kernel module

userspace_read → user-space app

▶️ Run & Test
Insert the module
sudo insmod src/tmp102_sim.ko simulate_temp=30000
dmesg | tail -n 10

(Optional) Create a virtual I²C adapter
sudo modprobe i2c-stub
echo tmp102_sim 0x50 | sudo tee /sys/bus/i2c/devices/i2c-0/new_device

Read temperature
./src/userspace_read


or directly:

cat /sys/bus/i2c/devices/0-0050/temp

Remove driver
sudo rmmod tmp102_sim

📘 Example Output
tmp_sim: init
tmp_sim: probe called for tmp102_sim
Temperature: 30.00 C
tmp_sim: exit
