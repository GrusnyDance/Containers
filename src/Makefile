all: test gcov_report

test:
	g++ -g -Wall -Werror -Wextra -std=c++17 -Wpedantic tests/tests.cc -lgtest -lpthread
	./a.out

gcov_report:

clean:
	rm -rf a.out