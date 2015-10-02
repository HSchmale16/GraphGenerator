EXE := graphgen
CXX_FLAGS := -std=c++11 -O2

all: $(EXE)

$(EXE): main.cpp
	g++ -o $@ $(CXX_FLAGS) $^ -lm -lpthread -lX11
	
