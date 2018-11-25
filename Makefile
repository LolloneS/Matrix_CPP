CXXFLAGS = -Wall -Wextra -pedantic-errors -pedantic -std=c++11
CXXFLAGS_DEBUG = -Wall -Wextra -pedantic-errors -pedantic -std=c++11 -g



.PHONY: clean release rebuild doc debug run_valgrind matrix.exe


clang:
	clang++ $(CXXFLAGS) matrix.cpp -o matrix.exe


release:
	g++ $(CXXFLAGS) matrix.cpp -o matrix.exe


debug:
	g++ $(CXXFLAGS_DEBUG) matrix.cpp -o matrix.exe

clean:
	rm -rf *.exe *.o doc/ *.pdf


doc:
	doxygen Doxyfile > /dev/null 2>&1


pdf:
	pandoc -t latex --toc --listings --include-in-header ./misc/header.tex -o Report.pdf Report.md && xdg-open Report.pdf


rebuild: clean release


debug: matrix.exe


run_valgrind: debug
	valgrind --leak-check=yes ./matrix.exe
