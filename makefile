EXE := graphgen
CXX_FLAGS := -std=c++11 -O0

all: $(EXE)

$(EXE): main.cpp
	g++ -o $@ $(CXX_FLAGS) $^ -lm -lpthread -lX11
	
