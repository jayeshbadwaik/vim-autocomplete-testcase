all:	test diag complete

test:	test.cc
			clang++ -std=c++14 -o test test.cc

diag:	diag.cc
			g++ -lclang -std=c++14 -o diag diag.cc

complete:	complete.cc
			g++ complete.cc -o complete -lclang -L/usr/lib/llvm

clean:
				rm test diag complete
