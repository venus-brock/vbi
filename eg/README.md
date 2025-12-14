## Directory listing

### fib.b93
A program that prints fibonacci numbers. Unfortunately, since there's no easy
way to write this without using g and p to store integers, this program can only
print numbers up to 127 (with the last fibonnaci number in this range being 89).
However, some non-compliant interpreters store the playfield as an array of long
integers, and this program is written such that if this is the case, it can
calculate fibonacci numbers up to the 64 bit int limit.

### hello_world.b93
A hello world program without using string mode.

### quine.b93
A program which produces an output identical to its source. This is the first
quine I've written in befunge.

### quine2.b93
A significantly shorter and significatly more convoluted quine. Not quite
perfect as it prints 49 spaces after the program, but shhh don't tell anyone

### unicode.b93
This program demonstrates that even though the playfield is limited to single-
byte characters, there's nothing stopping us from printing unicode symbols using
UTF-8 encoding. It simply prints the "§" character, and though it doesn't work
on many interpreters, both vbi and the Befunge-93 reference implementation are
able to correctly print it. Cutting edge stuff.
