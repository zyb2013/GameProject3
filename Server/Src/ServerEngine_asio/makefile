CC=g++ -std=c++11
CCLIB=ar
CC_INCLUDE=-I/usr/include \
-I/usr/include/mysql

DEFS = -DSERVER_ENGINE
	 
MY_INCLUDE=-I$(PWD) \
		-I../ServerEngine \
		-I../../Common \
		-I../../Common/Mysql 
					 
CC_LIB=-L/usr/lib \
	-L/lib \
	-L/usr/lib64\mysql \
	-L/usr/lib/mysql \
			 
MY_LIB=

TARGET=libServerEngine.a

OBJPATH=./Linux/

SRCS= $(wildcard ./*.cpp)
SRCS:=$(SRCS) $(wildcard ../../Common/Utility/*.cpp)
SRCS:=$(SRCS) $(wildcard ../../Common/CmdHandler/*.cpp)
SRCS:=$(SRCS) $(wildcard ../../Common/DataBuffer/*.cpp)
SRCS:=$(SRCS) $(wildcard ../../Common/Utility/Log/*.cpp)
SRCS:=$(SRCS) $(wildcard ../../Common/Utility/IniFile/*.cpp)

#//SRCS=$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

OBJS=$(SRCS:.cpp=.o)

#OBJS:=$(notdir $(OBJS))

#OBJS:=$(addprefix $(OBJPATH),$(OBJS))

#$(TARGET):$(OBJS)
#	$(CC) -g -o $(TARGET) $(OBJS) $(CC_LIB) $(MY_LIB)

$(TARGET):$(OBJS)
	$(CCLIB) -rs -o $(TARGET) $(OBJS)
	mv $(OBJS) ../Linux

$(OBJS):%.o:%.cpp
	$(CC) -g -w -c $< -o $@ $(CC_INCLUDE) $(MY_INCLUDE)
	
clean:
	rm $(OBJS) $(TARGET)