#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

export TARGET	:=	$(shell basename $(CURDIR))
export TOPDIR	:=	$(CURDIR)

include $(DEVKITARM)/ds_rules

.PHONY: check9 check7 clean

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all: check9 check7

#---------------------------------------------------------------------------------
check9:
	$(MAKE) -C libtwl9

#---------------------------------------------------------------------------------
check7:
	$(MAKE) -C libtwl7

#---------------------------------------------------------------------------------
clean:
	$(MAKE) -C libtwl9 clean
	$(MAKE) -C libtwl7 clean
