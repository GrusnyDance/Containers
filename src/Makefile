all: test gcov_report

test:
	g++ -g -Wall -Werror -Wextra -std=c++17 -Wpedantic tests/tests.cc -lgtest -lpthread
	./a.out

gcov_report:

lint:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.hpp

clean:
	rm -rf a.out .clang-format