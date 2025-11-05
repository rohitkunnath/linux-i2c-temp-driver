Build module: make

Load: sudo insmod src/tmp102_sim.ko simulate_temp=30000

Create device in sysfs for simulation (example instructions included): echo tmp102_sim 0x50 > /sys/bus/i2c/devices/i2c-0/new_device (if i2c adapter present) or document how to use i2c-stub module for simulation.

Read: cat /sys/bus/i2c/devices/0-0050/temp or ./src/userspace_read
