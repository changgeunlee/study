KDIR := /lib/modules/4.10.0-27-generic/build

obj-m += nothing2.o

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.cmd .module* modules* Module* .*.cmd .tmp*
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
