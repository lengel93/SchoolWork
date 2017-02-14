
CC = gcc
COBJS = bigint.o 
ASMOBJS = bigint_adc.o bigint_mul_uint.o bigint_free.o
#ASMOBJS = 
DEFINES = -DUSE_ASM
#ASMOBJS = 
DEFINES = -DUSE_ASM
#ASMOBJS = 
DEFINES = -DUSE_ASM
#ASMOBJS = 
DEFINES = -DUSE_ASM
#DEFINES =
INCLUDES = -I.
LIBDIRS = 
LIBS = 
#CFLAGS = -finline-functions -flto -Wall -marm -O2
#LFLAGS = -finline-functions -flto -marm -O2
CFLAGS = -pg -Wall -marm -O2
LFLAGS = -pg -marm -O2
#CFLAGS = -g -Wall -marm -O2
#LFLAGS = -g -marm -O2
#CFLAGS = -g -Wall -O2 
#LFLAGS = -g -O2 
DEPENDFLAGS = -M 

bigfact: $(COBJS) $(ASMOBJS) bigfact.o
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(COBJS) $(ASMOBJS) bigfact.o $(LIBDIRS) $(LIBS) -lm


testbigint: $(COBJS) $(ASMOBJS) testbigint.o
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(COBJS) $(ASMOBJS) testbigint.o $(LIBDIRS) $(LIBS) -lm

.c.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

.s.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

.S.o:
	$(CC) -c $(DEFINES) $(CFLAGS) $(INCLUDES) $<

clean:
	rm -f *.o testbigint

realclean: clean
	rm -f *~ .depend

# make depend will create a file ".depend" with all the C dependencies
depend:
	rm -f .depend
	$(CC) $(DEFINES) $(INCLUDES) $(DEPENDFLAGS) $(COBJS:.o=.c) > .depend

# if we have a .depend file, include it
ifeq (.depend,$(wildcard .depend))
include .depend
endif
