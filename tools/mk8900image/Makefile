ARCH=x86_64-ubu10
MKIMAGEOBJS=mk8900image.o
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
	@$(CC) $(CFLAGS) -c $< -o $@

mk8900image:	$(MKIMAGEOBJS) $(LIBXPWN)
	@echo "Building $@"
	@$(CC) $(CFLAGS) $(MKIMAGEOBJS) $(LIBXPWN) $(LIBRARIES) -o $@

clean:
	@echo "Cleaning up mk8900image.."
	@rm -f *.o
	@rm -f mk8900image
