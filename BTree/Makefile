CC=g++
CFLAGS=  -g
BIN=testbtree
OBJS=TestBTree.o
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
clean:
	rm -f *.o $(BIN)

