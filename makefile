files:
	cc $(wildcard ./src/*.c) -o ./bin/game -lncurses -Wall

clean:
	rm -rf ./bin/*