GCC=gcc -Wall -Werror -Wextra

CAT=cat.c

TEST=test_scr_cat.sh

SH=sh

all: cat format

cat:
	$(GCC) $(CAT) -o cat

format:
	clang-format -style=Google -i *.c
	clang-format -style=Google -i *.h
	clang-format -style=Google -n *.c
	clang-format -style=Google -n *.h

test:
	$(SH) $(TEST)


clean:
	rm -rf cat

rebuild: 
	clean all
