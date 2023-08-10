CC = gcc -Wextra -Werror -Wall
SRC = 	s21_strerror.c s21_memset.c s21_strcat.c s21_strncat.c \
		s21_strchr.c s21_memchr.c s21_memcmp.c s21_memcpy.c s21_strlen.c \
 		s21_memmove.c s21_strcspn.c s21_strpbrk.c s21_strcmp.c s21_strncmp.c \
		s21_strcpy.c s21_strncpy.c  s21_strrchr.c s21_strspn.c s21_strstr.c \
 		s21_strtok.c s21_insert.c s21_trim.c s21_to_lower.c s21_to_upper.c \
		s21_sprintf.c
OBJ = $(SRC:%.c=%.o)

all: s21_string.a test gcov_report

s21_string.a: $(OBJ)
	ar rcs s21_string.a $^ 

%.o: %.c s21_string.h
	$(CC) -c $<

test:
	$(CC) -lgcov -coverage string_test.c $(SRC) -lcheck -lm -lpthread -o test
	./test


gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o test_output test.info
	@cd ./test_output ; open index.html

clean:
	rm -rf $(OBJ)
	rm -rf test
	rm -rf *.gcda *.gcno *.info
	rm -rf ./test_output/ 
	rm -rf s21_string.a
	rm -rf test_leaks
	rm -rf CPPLINT.cfg
	rm -rf RESULT_VALGRIND.txt
	rm -rf test_leaks.dSYM

re: clean all

check:
	cppcheck *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h

valgrind: s21_string.a
	$(CC) string_test.c s21_string.a -lcheck -o test_leaks
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test_leaks
