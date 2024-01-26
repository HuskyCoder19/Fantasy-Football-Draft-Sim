CC = g++
SRCS = draftSim.cpp
HDRS = draft.hpp players.hpp
OBJS = $(SRCS:.cpp=.o)
EXEC = draftSimulator
all: $(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
%.o: %.cpp $(HDRS)
	$(CC) -c $< -o $@
clean:
	rm -f $(OBJS) $(EXEC)
