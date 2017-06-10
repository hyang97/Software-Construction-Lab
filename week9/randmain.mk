randmain : randmain.o randcpuid.o
	$(CC) $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randcpuid.o randmain.o

randmain.o : randcpuid.h randmain.c
	$(CC) $(CFLAGS) -c randmain.c -o randmain.o

randcpuid.o : randcpuid.h randcpuid.c
	$(CC) $(CFLAGS) -c randcpuid.c -o randcpuid.o

randlibhw.so : randlibhw.o
	$(CC) $(CFLAGS) -shared -fPIC -o randlibhw.so randlibhw.o

randlibsw.so : randlibsw.o
	$(CC) $(CFLAGS) -shared -fPIC -o randlibsw.so randlibsw.o

randlibhw.o : randlibhw.c randlib.h
	$(CC) $(CFLAGS) -Wall -fPIC -c randlibhw.c

randlibsw.o : randlibsw.c randlib.h
	$(CC) $(CFLAGS) -Wall -fPIC -c randlibsw.c
