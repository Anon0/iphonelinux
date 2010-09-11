OBJS = src/loader.o src/UsbInterface.o
LIBS = -L/opt/local-universal-10.4/lib -lusb-1.0 -lusb -lpthread -lreadline
CFLAGS += -DHAVE_GETEUID -I/opt/local-universal-10.4/include -Iinclude/ -Werror -Wall
CPP=g++

%.o:	%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:	iutil

iutil: ${OBJS}
	$(CPP) $(CFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	@echo "Cleaning up.."
	@rm -f src/*.o
	@rm -f iutil

