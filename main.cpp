#include <iostream>
#include "cube.h"
#include <string>
#include <fstream>

typedef std::string string;

int get_notation(string notation)
{
	if (notation.compare("f") == 0)
		return (F);
	if (notation.compare("u") == 0)
		return (U);
	if (notation.compare("r") == 0)
		return (R);
	if (notation.compare("d") == 0)
		return (D);
	if (notation.compare("l") == 0)
		return (L);
	if (notation.compare("b") == 0)
		return (B);
	if (notation.compare("fi") == 0)
		return (FI);
	if (notation.compare("ui") == 0)
		return (UI);
	if (notation.compare("ri") == 0)
		return (RI);
	if (notation.compare("di") == 0)
		return (DI);
	if (notation.compare("li") == 0)
		return (LI);
	if (notation.compare("bi") == 0)
		return (BI);
	return (-1);
}

#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	Cube c = Cube();
	int i = 1;
	printf("Welcome to Cube!\n");
	printf("commands: q: quit, f, b, u, d, r, l, fi, bi, ui, di, ri, li\n");
	std::cout << "\033[s";
	if (argc > 1)
		c.file_input(argv[1]);
	c.print_cube();
	string nota;
	int playing = 1;
	while (playing == 1)
	{
		std::cin >> nota;
		std::cout << "\033[u";
		std::cout <<"\033[0J";
		if (nota.compare("q") == 0)
			break;
		c.rotate_notation(get_notation(nota));
		c.print_cube();
		i++;
	}
	c.file_save("save.cube");
	printf("Good bye\n");
	return (0);
}
