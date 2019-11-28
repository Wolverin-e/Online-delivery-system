all:
	g++ main.cpp -o main
run:
	g++ main.cpp -o main
	./main
test:
	g++ main.cpp -o main
	rm -rf main
clean:
	rm -rf main