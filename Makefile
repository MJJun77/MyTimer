.PHONY: all
OBJS=MyTimer.o timer_test.o
FLAGS=-lrt

%.o: %.c
	gcc -o $@ $^ -c $(FLAGS)

%.o: %.cpp
	g++ -o $@ $^ -c $(FLAGS)

timer_test: $(OBJS)
	g++ -o $@ $^ $(FLAGS)

clean:
	rm -f $(OBJS) timer_test

