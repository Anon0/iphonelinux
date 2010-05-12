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
MKIMAGE		    = ../bin/mk8900image
IMGTEMPLATES	    = ../bin/templates

ifneq ($(SMALL),YES)
OBJS               += $(patsubst %.c,%.o,$(HFS_SRC_C)) $(patsubst %.c,%.o,$(MENU_SRC_C))
endif

CFLAGS     += -DCONFIG_3G
IMG3TEMPLATE    = $(IMGTEMPLATES)/template-3g.img3

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

all:	openiboot.img2 openiboot-wtf.img2 openiboot.img3 openiboot.bin

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

all-payload: openiboot-payload.img2 openiboot-payload.bin

openiboot: $(OBJS) $(SUBDIRS)
	@echo "Building $@"
	@$(CC) $(ARCHFLAGS) $(LDFLAGS) $(OBJS) $(LIBRARIES) -o $@

payload.o:	payload.bin
	$(OBJCOPY) -I binary -O elf32-little -B arm $< $@

openiboot-payload: $(OBJS) payload.o
	$(CC) --no-warn-mismatch $(LDFLAGS) $(OBJS) payload.o $(LIBRARIES) -o $@

openiboot.bin: openiboot
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot openiboot.bin

openiboot.img2:	openiboot
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot openiboot.img2 $(IMGTEMPLATES)/template.img2 $(IMGTEMPLATES)/iphonelinux.der

openiboot-wtf.img2:	openiboot
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot openiboot-wtf.img2 $(IMGTEMPLATES)/template-wtf.img2

openiboot.img3:	openiboot
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot openiboot.img3 $(IMG3TEMPLATE)
	@cp openiboot.img3 ../bin/images/

openiboot-payload.bin: openiboot-payload
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot-payload openiboot-payload.bin

openiboot-payload.img2: openiboot-payload
	@echo "Creating image $@"
	@$(MKIMAGE) openiboot-payload openiboot-payload.img2 $(IMGTEMPLATES)/template.img2 $(IMGTEMPLATES)/iphonelinux.der

#.PHONY: clean
clean:
	@rm -rf *.o $(DEPDIR) hfs/*.o openiboot openiboot.img2 openiboot-wtf.img2 openiboot.img3 openiboot-payload.bin openiboot-payload.img2
