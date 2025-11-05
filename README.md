# 🌡️ 2️⃣ Linux I2C Temperature Sensor Driver – Simulated TMP102

A simulated Linux I2C client driver that mimics the behavior of a TMP102 temperature sensor.
It demonstrates I2C driver registration, sysfs interface creation, and probe/remove routines — all runnable without actual hardware.

## 🧠 What This Project Demonstrates

I2C driver structure (i2c_driver, probe, remove)

Sysfs interface for user-space communication

Module parameters for simulated readings

Kernel module build and debugging

Works on any system — no hardware required

## 🛠️ Requirements

Linux with kernel headers (sudo apt install build-essential linux-headers-$(uname -r))

GCC, Make

Optional: i2c-tools for virtual device testing

##🧱 Folder Structure
```bash
linux-i2c-temp-driver/
├── src/
│   ├── tmp102_sim.c
│   └── userspace_read.c
├── Makefile
└── README.md
```

⚙️ Build Instructions
```bash
make
```
This compiles:

tmp102_sim.ko → kernel module

userspace_read → user-space app

▶️ Run & Test

Insert module
```bash
sudo insmod src/tmp102_sim.ko simulate_temp=32000
dmesg | tail -n 10
```

Simulate an I2C device (software-only)
```bash
sudo modprobe i2c-stub chip_addr=0x50
echo tmp102_sim 0x50 | sudo tee /sys/bus/i2c/devices/i2c-0/new_device
```

Read temperature
```bash
cat /sys/bus/i2c/devices/0-0050/temp
```

Or use the user-space program
```bash
./src/userspace_read
```

Remove module
```bash
sudo rmmod tmp102_sim
```
🧩 Output Example
```bash
tmp_sim: init
tmp_sim: probe called for tmp102_sim
Temperature: 32.00 °C
```
