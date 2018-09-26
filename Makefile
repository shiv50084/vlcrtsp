include ./Makefile.inc

INCLUDE += -I /usr/local/include
INCLUDE += -I ./ -I ../

LDLIBS += -lipcdevice -lvlc -lvlccore -pthread
LDLIBS += -L /usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc 

CFLAGS += -std=gnu++11

SRCS :=                                 \
	ipc_core.cpp 						\
	videostream_abstract.cpp         	\
	videostream_instance.cpp            \
	videostream_mediaplayer.cpp         \
	videostream.cpp
	
OBJS := $(patsubst %.cpp, $(TEMPDIR)%.o, $(filter %.cpp, $(SRCS)))


PROGRAM := vlcplayer

SHAREDLIB := libvlcipc.so

RTSPFRAME := rtspframe

all: $(PROGRAM) $(SHAREDLIB) $(RTSPFRAME)

$(PROGRAM) : $(OBJS) main.o

	$(CXX) -o $@ $(OBJS) main.o $(LDLIBS) 

$(SHAREDLIB) : $(OBJS) main.o

	$(CXX) -shared -o $@ $(OBJS) main.o $(LDLIBS) 

$(RTSPFRAME) : $(OBJS) 	opencv_ipc.o

	$(CXX) -o $@ $(OBJS) opencv_ipc.o $(LDLIBS) 
	
.PHONY: install 

install:
	@ sudo cp $(SHAREDLIB) /usr/lib

clean:
	rm -rf $(OBJS) $(PROGRAM) $(SHAREDLIB) $(RTSPFRAME)
