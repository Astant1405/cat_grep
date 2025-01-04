GCC=gcc -Wall -Werror -Wextra

GREP=grep.c

TEST=test_scr_grep.sh

SH=sh

all: grep format

grep:
	$(GCC) $(GREP) -o grep

format:
	clang-format -style=Google -i *.c
	clang-format -style=Google -i *.h
	clang-format -style=Google -n *.c
	clang-format -style=Google -n *.h

test:
	$(SH) $(TEST)

clean:
	rm -rf grep

rebuild: 
	clean all
