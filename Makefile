TARGET="ccalc"
SRC="*.cpp"

all:
	g++ *.cpp -o $(TARGET)

run:
	./$(TARGET)

test:
	./test.sh

format:
	clang-format -i -style=file *.cpp *.hpp

clean:
	rm $(TARGET)