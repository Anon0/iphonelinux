PLATFORM=3G

# Standard things
.SUFFIXES:
.SUFFIXES:	.c .s .o

# Sources
SRC_C               = aes.c arm.c buttons.c chipid.c clock.c commands.c dma.c event.c framebuffer.c ftl.c gpio.c i2c.c images.c interrupt.c lcd.c malloc.c miu.c mmu.c nand.c nor.c nvram.c openiboot.c pmu.c power.c printf.c sdio.c sha1.c spi.c tasks.c timer.c uart.c usb.c util.c wdt.c syscfg.c actions.c
SRC_S               = entry.s openiboot-asmhelpers.s

HFS_SRC_C           = hfs/btree.c hfs/catalog.c hfs/extents.c hfs/fastunicodecompare.c hfs/rawfile.c hfs/utility.c hfs/volume.c hfs/bdev.c hfs/fs.c

MENU_SRC_C          = menu.c stb_image.c

# Variables
LOAD           ?= 0x0
CFLAGS         += -O3

ARCHFLAGS          += -mlittle-endian -mfpu=vfp -mthumb -mthumb-interwork
LIBRARIES          += -lgcc -nostdlib
INC                += -Iincludes
CFLAGS             += -Wall -Werror
LDFLAGS            += -Ttext=$(LOAD) --nostdlib
VERSION             = "0.1"
COMMIT              = $(shell git log | head -n1 | cut -b8-14)
BUILD               = "$(COMMIT)"
CFLAGS             += -DOPENIBOOT_VERSION=$(VERSION) -DOPENIBOOT_VERSION_BUILD=$(BUILD)
DF                  = $(*F)
DEPDIR              = .deps
BUILDDIR            = .build
OBJS                = $(patsubst %.s,%.o,$(SRC_S)) $(patsubst %.c,%.o,$(SRC_C))

ifneq ($(SMALL),YES)
OBJS               += $(patsubst %.c,%.o,$(HFS_SRC_C)) $(patsubst %.c,%.o,$(MENU_SRC_C))
endif

CFLAGS     += -DCONFIG_3G

ifeq ($(DEBUG),YES)
	CFLAGS        += -DDEBUG
endif

# Tools
CROSS              ?= arm-elf-
CC                  = $(CROSS)gcc
OBJCOPY             = $(CROSS)objcopy
COMPILE             = $(CC) $(INC) $(CFLAGS) $(ARCHFLAGS) -c $< -o $@
MAKEDEPEND          = $(CC) -M $(INC) $(CFLAGS) $(ARCHFLAGS) -o "$(DEPDIR)/$*.d" $<

# Rules
.PHONY: clean all

all: openiboot

%.o: %.S
	@echo "Compiling $<"
	@mkdir -p $(DEPDIR)/$(dir $@)
	@touch $(DEPDIR)/$(dir $@)/$(*F).d
	@$(COMPILE)

%.o: %.c
	@echo "Compiling $<"
	@mkdir -p $(DEPDIR)/$(dir $@)
	@$(MAKEDEPEND)
#	@cp $(DEPDIR)/$(dir $@)/$(*F).d $(DEPDIR)/$(dir $@)/$(*F).P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(DEPDIR)/$(dir $@)/$(*F).d >> $(DEPDIR)/$(dir $@)/$(*F).d
#	@rm -f $(DEPDIR)/$(dir $@)/$(*F).d
	@$(COMPILE)

-include $(addprefix $(DEPDIR)/,$(OBJS:.o=.d))

openiboot: $(OBJS) $(SUBDIRS)
	@echo "Building $@"
	@$(CC) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(LIBRARIES) -o $@

#.PHONY: clean
clean:
	@rm -rf *.o $(DEPDIR) hfs/*.o openiboot
