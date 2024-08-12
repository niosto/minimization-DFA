This project by student Nicolás Ospina Torres, looks to implement the algorithm of minimization of a DFA by Kozen in 'Automata and Computability' (1997), 
for the asignature 'Formal Languages and Compilers' at EAFIT University, lectured by professor Adolfo Castro Sanchez. 
The code was made in C++ version 17. 
The input consists of: 
1- First line with a number c > 0 indicating how many cases it will receive.
2. For each case, in a single line the number n > 0 of states of M.
3. Then, a single line with the alphabet of M. Symbols are separated by a single blank space.
4. Then, the final states of M separated by blank spaces.
5. Finally, n lines, one for each state. Each line contains a row of the table that represents M.

An input example for the code could be:
2
6
a b
1 2 5
0 1 2
1 3 4
2 4 3
3 5 5
4 5 5
5 5 5
6
a b
3 4 5
0 1 2
1 3 4
2 4 3
3 5 5
4 5 5
5 5 5
