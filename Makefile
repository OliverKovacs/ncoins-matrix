CXX = clang++
CXXFLAGS = -fsanitize=address

debug: 		CXXFLAGS += -g
release: 	CXXFLAGS += -O3

name = main

default: $(name)

debug: default
release: default

run: $(name)
	./$^

$(name): $(name).cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

