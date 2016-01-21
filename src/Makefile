INCLUDE += -I../inc
SRC += SmartMutex.cpp 
OBJ += SmartMutex.o 
TEST_SRC += test.cpp
TEST_OBJ += test.o
PROGRAM = testMutex
CPPFLAGS += $(INCLUDE) -g -lpthread	 -lrt
	

$(OBJ) : $(SRC)

.PHONY: test
test: $(PROGRAM)

$(PROGRAM):$(OBJ) $(TEST_OBJ)
	g++ $(OBJ) $(TEST_OBJ) -o $(PROGRAM) $(CPPFLAGS)
$(TEST_OJB):$(TEST_SRC)

clean:
	rm *.o $(PROGRAM)
