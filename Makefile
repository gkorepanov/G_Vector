.PHONY: clean

TARGET = bin/G_Vector
FLAGS = -std=c++11 -Wall -g
OBJS = G_Test.o
DEPS = $(OBJS:.o=.d)

$(TARGET): $(OBJS)
	g++ -o $@ $^

-include $(DEPS)
    
%.o: %.cpp
	g++ $(FLAGS) -c -o $@ $<
	g++ $(FLAGS) -MM -o $(patsubst %.o, %.d, $@) $<

clean:
	rm $(OBJS) $(TARGET) ./*.d

run:
	$(TARGET)
