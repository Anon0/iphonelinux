ARCH=x86_64-ubu10
MKIMAGEOBJS=imagetool.o
LIBRARIES=-L/usr/lib -lm -ldl -lcrypto -lz -lpng
CFLAGS +=

ifeq ($(ARCH), x86_64)
	LIBXPWN=x86_64/libxpwn.a x86_64/libcommon.a
else
	ifeq ($(ARCH), x86_64-ubu10)
		LIBXPWN=x86_64-Ubuntu10.04/libxpwn.a x86_64-Ubuntu10.04/libcommon.a
	else
		LIBXPWN=x86/libxpwn.a x86/libcommon.a
	endif
endif

%.o:	%.c
	@echo "Compiling $@"
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

img3decrypt:	$(MKIMAGEOBJS) $(LIBXPWN)
	@echo "Building $@"
	@$(CC) $(CFLAGS) -Iinclude $(MKIMAGEOBJS) $(LIBXPWN) $(LIBRARIES) -o $@

clean:
	@echo "Cleaning up img3decrypt.."
	@rm -f *.o
	@rm -f img3decrypt
