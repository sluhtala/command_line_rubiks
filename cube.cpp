#include "cube.h"
#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

typedef std::string string;

int Cube::next_id = 0;

struct	s_edge
{
	int top[2];
	int right[2];
	int down[2];
	int left[2];
};

static struct s_edge find_edges(int side)
{
	switch (side)
	{
		case 0:
			return ((struct s_edge){{4, 1}, {3, 1}, {2, 1}, {1, 1}});
		case 1:
			return ((struct s_edge){{0, 4}, {2, 4}, {5, 4}, {4, 2}});
		case 2:
			return ((struct s_edge){{0, 3}, {3, 4}, {5, 1}, {1, 2}});
		case 3:
			return ((struct s_edge){{0, 2}, {4, 4}, {5, 2}, {2, 2}});
		case 4:
			return ((struct s_edge){{0, 1}, {1, 4}, {5, 3}, {3, 2}});
		case 5:
			return ((struct s_edge){{2, 3}, {3, 3}, {4, 3}, {1, 3}});
		default:
			return ((struct s_edge){{0,0}, {0,0}, {0,0}, {0,0}});
	}
}

//  0
//1 2 3 4
//  5
// links all the sides and their neighbourin edges
static void link_sides(Cube *c)
{
	struct s_edge edges_connections;

	for (int i = 0; i < 6; i++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				c->sides_struct[i].side[y][x] = &c->sides[i][y][x]; 
			}	
		}
		edges_connections = find_edges(i);
		int e = edges_connections.top[1];
		int y = ((e - 1) / 2) * 2;
		int x = (e > 1 && e < 4) * 2;
		for (int j = 0; j < 3; j++)
		{
			c->sides_struct[i].top[j] = &(c->sides[edges_connections.top[0]][y][x]);
			y += -cos(e * (M_PI / 2.0f));
			x += cos((e - 1) * (M_PI / 2.0f));
		}
	
		e = edges_connections.right[1];
		y = ((e - 1) / 2) * 2;
		x = (e > 1 && e < 4) * 2;
		for (int j = 0; j < 3; j++)
		{
			c->sides_struct[i].right[j] = &(c->sides[edges_connections.right[0]][y][x]);
			y += -cos(e * (M_PI / 2.0f));
			x += cos((e - 1) * (M_PI / 2.0f));
		}

		e = edges_connections.down[1];
		y = ((e - 1) / 2) * 2;
		x = (e > 1 && e < 4) * 2;
		for (int j = 0; j < 3; j++)
		{
			c->sides_struct[i].down[j] = &c->sides[edges_connections.down[0]][y][x];
			y += -cos(e * (M_PI / 2.0f));
			x += cos((e - 1) * (M_PI / 2.0f));
		}

		e = edges_connections.left[1];
		y = ((e - 1) / 2) * 2;
		x = (e > 1 && e < 4) * 2;
		for (int j = 0; j < 3; j++)
		{
			c->sides_struct[i].left[j] = &c->sides[edges_connections.left[0]][y][x];
			y += -cos(e * (M_PI / 2.0f));
			x += cos((e - 1) * (M_PI / 2.0f));
		}
	}
}

//Constructor

Cube::Cube()
{
	int i;
	this->id = next_id;
	next_id++;
	i = 0;
	while (i < 6)
	{
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				this->sides[i][y][x] = i;
		i++;
	}
	link_sides(this);
}

int Cube::get_id()
{
	return (this->id);
}

string get_bg_color(int color)
{
	if (color == RED)
		return (RED_BG);
	if (color == WHITE)
		return (WHITE_BG);
	if (color == BLUE)
		return (BLUE_BG);
	if (color == ORANGE)
		return (ORANGE_BG);
	if (color == GREEN)
		return (GREEN_BG);
	if (color == YELLOW)
		return (YELLOW_BG);
	return (BLACK_BACKGROUND);
}

void print_edge(int c1, int c2, int c3)
{
	std::cout << get_bg_color(c1) << c1 << RESET_BG;
	std::cout << get_bg_color(c2) << c2 << RESET_BG;
	std::cout << get_bg_color(c3) << c3 << RESET_BG;
}

void Cube::print_cube()
{
	int l = 0;
	string bg;
	while (l < 9)
	{
		if (l < 3 || l >= 6)
		{
			std::cout << "    ";
		}
		if (l == 0 || l == 1 || l == 2)
			print_edge(this->sides[0][l % 3][0], this->sides[0][l % 3][1], this->sides[0][l % 3][2]);
		if (l == 3 || l == 4 || l == 5)
		{
			print_edge(this->sides[1][l % 3][0], this->sides[1][l % 3][1], this->sides[1][l % 3][2]);
			std::cout << " ";
			print_edge(this->sides[2][l % 3][0], this->sides[2][l % 3][1], this->sides[2][l % 3][2]);
			std::cout << " ";
			print_edge(this->sides[3][l % 3][0], this->sides[3][l % 3][1], this->sides[3][l % 3][2]);
			std::cout << " ";
			print_edge(this->sides[4][l % 3][0], this->sides[4][l % 3][1], this->sides[4][l % 3][2]);
		}
		if (l == 6 || l == 7 || l == 8)
			print_edge(this->sides[5][l % 3][0], this->sides[5][l % 3][1], this->sides[5][l % 3][2]);
		std::cout << std::endl;
		l++;
	}
}

void rotate_edges(Cube *cube, int side, int direction)
{
	int temp;

	temp = cube->sides[side][0][0];
	if (direction == CLOCK_WISE)
	{
		cube->sides[side][0][0] = cube->sides[side][2][0];
		cube->sides[side][2][0] = cube->sides[side][2][2];
		cube->sides[side][2][2] = cube->sides[side][0][2];
		cube->sides[side][0][2] = temp;
	}
	else
	{
		cube->sides[side][0][0] = cube->sides[side][0][2];
		cube->sides[side][0][2] = cube->sides[side][2][2];
		cube->sides[side][2][2] = cube->sides[side][2][0];
		cube->sides[side][2][0] = temp;
	}
}
void rotate_sides(Cube *cube, int side, int direction)
{
	int temp;

	temp = cube->sides[side][0][1];
	if (direction == CLOCK_WISE)
	{
		cube->sides[side][0][1] = cube->sides[side][1][0];
		cube->sides[side][1][0] = cube->sides[side][2][1];
		cube->sides[side][2][1] = cube->sides[side][1][2];
		cube->sides[side][1][2] = temp;
	}
	else
	{
		cube->sides[side][0][1] = cube->sides[side][1][2];
		cube->sides[side][1][2] = cube->sides[side][2][1];
		cube->sides[side][2][1] = cube->sides[side][1][0];
		cube->sides[side][1][0] = temp;
	}
}

void rotate_other_edges (Cube *cube, int side, int direction)
{
	int temp[3];

	for (int i = 0; i < 3; i++)
		temp[i] = *cube->sides_struct[side].top[i];
	if (direction == CLOCK_WISE)
	{
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].top[i] = *cube->sides_struct[side].left[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].left[i] = *cube->sides_struct[side].down[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].down[i] = *cube->sides_struct[side].right[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].right[i] = temp[i];
	}
	else
	{
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].top[i] = *cube->sides_struct[side].right[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].right[i] = *cube->sides_struct[side].down[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].down[i] = *cube->sides_struct[side].left[i];
		for (int i = 0; i < 3; i++)
			*cube->sides_struct[side].left[i] = temp[i];
	}
}

void Cube::rotate(int side, int direction)
{
	rotate_edges(this, side, direction);
	rotate_sides(this, side, direction);
	rotate_other_edges(this, side, direction);
}

void Cube::rotate_notation(int notation)
{
	int dir;
	int side;

	if (notation == -1)
		return ;
	if (notation > 5)
		dir = COUNTER_CLOCK_WISE;
	else
		dir = CLOCK_WISE;
	if (notation > 5)
		side = notation % 6;
	else
		side = notation;
	this->rotate(side, dir);
}

int get_notations(string notation)
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

void Cube::file_save(const char *filename)
{
	std::ofstream file(filename);
	int y = 0;
	int x = 0;
	file << "    " << this->sides[0][0][0] << this->sides[0][0][1] << this->sides[0][0][2] << std::endl;
	file << "    " << this->sides[0][1][0] << this->sides[0][1][1] << this->sides[0][1][2] << std::endl;
	file << "    " << this->sides[0][2][0] << this->sides[0][2][1] << this->sides[0][2][2] << std::endl;
	file << this->sides[1][0][0] << this->sides[1][0][1] << this->sides[1][0][2] << " ";
	file << this->sides[2][0][0] << this->sides[2][0][1] << this->sides[2][0][2] << " ";
	file << this->sides[3][0][0] << this->sides[3][0][1] << this->sides[3][0][2] << " ";
	file << this->sides[4][0][0] << this->sides[4][0][1] << this->sides[4][0][2] << std::endl;
	file << this->sides[1][1][0] << this->sides[1][1][1] << this->sides[1][1][2] << " ";
	file << this->sides[2][1][0] << this->sides[2][1][1] << this->sides[2][1][2] << " ";
	file << this->sides[3][1][0] << this->sides[3][1][1] << this->sides[3][1][2] << " ";
	file << this->sides[4][1][0] << this->sides[4][1][1] << this->sides[4][1][2] << std::endl;
	file << this->sides[1][2][0] << this->sides[1][2][1] << this->sides[1][2][2] << " ";
	file << this->sides[2][2][0] << this->sides[2][2][1] << this->sides[2][2][2] << " ";
	file << this->sides[3][2][0] << this->sides[3][2][1] << this->sides[3][2][2] << " ";
	file << this->sides[4][2][0] << this->sides[4][2][1] << this->sides[4][2][2] << std::endl;
	file << "    " << this->sides[5][0][0] << this->sides[5][0][1] << this->sides[5][0][2] << std::endl;
	file << "    " << this->sides[5][1][0] << this->sides[5][1][1] << this->sides[5][1][2] << std::endl;
	file << "    " << this->sides[5][2][0] << this->sides[5][2][1] << this->sides[5][2][2] << std::endl;
	file.close();
}

void Cube::file_input(const char *filename)
{
	std::ifstream file(filename);
	string line;
	string notations;
	string nota;
	int pos = 0;
	int len;
	while (getline(file, line))
	{
		len = line.length();
		while (pos < len)
		{
			nota = line.substr(0, line.find(' '));
			if (nota.length() == 0)
				break ;
			pos += nota.length();
			line.erase(0, nota.length() + 1);
			this->rotate_notation(get_notations(nota));
		}
	}
	//std::cout << notations;
	file.close();
}

int Cube::check_cube()
{
	for (int i = 0; i < 6; i++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				if (this->sides[i][y][x] != i )
				{
					return (0);
				}
			}
		}
	}
	return (1);
}