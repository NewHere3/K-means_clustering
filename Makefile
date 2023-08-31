BUILD=builds
HEADER=headers
SOURCE=sources

all: exe

exe: exe.o window.o
	g++ $(BUILD)/exe.o $(BUILD)/window.o -o exe -lX11

exe.o: exe.cpp
	g++ -c exe.cpp -o $(BUILD)/exe.o

%.o: $(SOURCE)/%.cpp  # $(HEADER)/%.hpp
	g++ -c $^ -o $(BUILD)/$@

clean:
	rm -f $(BUILD)/*.o exe
