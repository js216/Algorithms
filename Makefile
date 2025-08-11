CFLAGS = -Wall -Wextra -pedantic -std=c99 -static

ch2 := gcd frac hello rgcd rchars bin alluv three largest fgcd
ch3 := b2d move jos dbl push safter qafter lqueue
ch4 := orders
ch5 := center extlen

prog = $(ch2) $(ch3) $(ch4) $(ch5)

.PHONY: all

all: $(prog)

%: %.rs
	rustc $< -o $@

%: %.f90
	gfortran $< -o $@

clean:
	rm -f $(prog)

# Extra depedencies

rgcd rchars: utils.rs
