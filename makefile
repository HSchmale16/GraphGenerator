EXE := graphgen
CXX_FLAGS := -std=c++11 -O0

all: $(EXE) showoff.pdf

$(EXE): main.cpp
	g++ -o $@ $(CXX_FLAGS) $^ -lm -lpthread -lX11

showoff.pdf: showoff.tex
	pdflatex $<

clean:
	rm -f $(EXE)
	rm -f showoff.pdf
