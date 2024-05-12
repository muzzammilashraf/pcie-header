# Makefile for The PCIE Header
# Copyright (c) 2023 - Muzammil Ashraf <m.muzzammilashraf@gmail.com>

OPT=-O2
CFLAGS=$(OPT) -Wall -W -Wno-parentheses -Wstrict-prototypes -Wmissing-prototypes

TARGET_NAME = pcie-header

SUBDIRS := pciutils

$(SUBDIRS):
	$(MAKE) -C $@ SHARED=yes

all: $(SUBDIRS)
	gcc -o $(TARGET_NAME) -I pciutils/lib src/main.c -l:libpci.so.3.12.0 -Lpciutils/lib

run:
	./$(TARGET_NAME)

clean:	
	$(MAKE) -C $(SUBDIRS) clean
	rm -r $(TARGET_NAME)

.PHONY: all $(SUBDIRS)
