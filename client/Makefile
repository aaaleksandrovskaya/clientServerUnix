OBJS = Client.cpp Client.hpp ../common/SocketUser.cpp ../common/SocketUser.hpp main.cpp
CC = g++
COMPILER_FLAGS = -w -std=c++17
OBJ_NAME = client

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
	
clean:
	rm -f $(OBJ_NAME)
	rm -dfr .vscode
