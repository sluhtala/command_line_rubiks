#define RESET_BG "\u001B[0m"
#define BLACK_BACKGROUND "\u001B[40m"
#define RED_BG "\u001B[41;38;5;0m"
#define GREEN_BG "\u001B[42;38;5;0m"
#define YELLOW_BG "\u001B[43;38;5;0m"
#define BLUE_BG "\u001B[44;38;5;0m"
#define PURPLE_BG "\u001B[45;38;5;0m"
#define CYAN_BG "\u001B[46;38;5;0m"
#define WHITE_BG "\u001B[47;38;5;0m"
#define ORANGE_BG "\033[48;5;208;38;5;0m"
#include <string>
typedef struct	s_side
{
	int *side[3][3];
	int *top[3];
	int *right[3];
	int *down[3];
	int *left[3];
}				t_side;

class Cube
{
	private:
		int id;
	public:
		t_side sides_struct[6];
		static int next_id;
		int sides[6][3][3];
	Cube();
	int get_id();
	int check_cube();
	void print_cube();
	void rotate(int side, int direction);
	void rotate_notation(int notation);
	void file_input(const char *filename);
	void file_save(const char *filename);
};

enum e_colors
{
	WHITE, RED, BLUE, ORANGE, GREEN, YELLOW
};

enum e_direction
{
	CLOCK_WISE, COUNTER_CLOCK_WISE
};

enum e_notation
{
	U, L, F, R, B, D, 
	UI, LI, FI, RI, BI, DI
};