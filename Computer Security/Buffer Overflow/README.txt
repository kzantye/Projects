Kunal Zantye
kzantye1@binghamton.edu

**********************************************************************************************
EASY PROJECT 3
gcc ./vuln_program.c -fno-stack-protector -z execstack -static -o vuln_program
gcc -o input input.c

./input $'(target address)' [#ARGS] > attack.input
#ARGS - number of A's

./vuln_program < attack.input
**********************************************************************************************

HARD PROJECT 3
gcc ./vuln_program.c -fno-stack-protector -z execstack -static -o vuln_program
gcc -o input input.c

./input $'(target address)' [#ARGS] > attack.input
#ARGS - number of A's

./vuln_program 0 < attack.input

**********************************************************************************************