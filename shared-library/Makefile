

build-library:
	clang -shared -fPIC -o libadd.so add.c

build-executable:
	clang -o main main.c -L. -ldl

build-executable-with-lib:
	clang -o main main.c -L. -ldl -Wl,-rpath,.

run:
	LD_LIBRARY_PATH=. ./main
