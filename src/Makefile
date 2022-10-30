FLAGS:=-lgtest -lpthread -fprofile-arcs -ftest-coverage

all: test gcov_report

test:
	mkdir -p build
	g++ -g -Wall -Werror -Wextra -std=c++17 -Wpedantic \
	tests/tests.cc -o build/out $(FLAGS)
	build/./out

gcov_report: test
	lcov/bin/./lcov -q -c -d build/. -o build/coverage.info
	@lcov/bin/./lcov -q --remove build/coverage.info '*/src/test*' '*/include/*' '11*' \
    -o build/coverage.info
	lcov/bin/./genhtml build/coverage.info --output-directory out

lint:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.hpp

clean:
	rm -rf a.out .clang-format build \
	*gcda *gcno out