obj-m := tmp102_sim.o
KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD)/src modules
	gcc -o src/userspace_read src/userspace_read.c

clean:
	$(MAKE) -C $(KDIR) M=$(PWD)/src clean
	rm -f src/userspace_read