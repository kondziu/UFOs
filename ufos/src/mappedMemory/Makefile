#mkInclude = sparseList.h ../unstdLib/*.h
#CC=gcc
UFO_KEY = -D__UFOs_CoreDev__
PKG_LIBS = -pthread
OBJ = sparseList.o userfaultCore.o userfaultGettersSetters.o
CFLAGS = -O2 -ggdb -Wall -Werror -fPIC
LIB = libmappedMemory.a

all: $(LIB) strideTest sparseListTest userfaultSpeedTest ufoTest

library: $(LIB)

mostlyclean: clean

clean:
	$(RM) *.o
	$(RM) *.a

%.o: %.c
	$(CC) $(CFLAGS) $(UFO_KEY) -c -o $@ $<

$(LIB): $(OBJ)
	$(AR) -rcs $@ $^

strideTest: stride.o
	$(CC) $(CFLAGS) -o $@ $^

sparseListTest: sparseListTest.o sparseList.o
	$(CC) $(CFLAGS) -o $@ $^

userfaultSpeedTest: userfaultSpeed.o $(OBJ)
	$(CC) $(CFLAGS) $(PKG_LIBS) -o $@ $^

ufoTest: ufoTest.o $(OBJ)
	$(CC) $(CFLAGS) $(PKG_LIBS) -o $@ $^