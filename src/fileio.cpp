#include "fileio.hpp"

void LoadBoard(int& num, int& size_x, int& size_y, int& max_cmds, int& min_cmds, std::string& board_data)
{
	std::ifstream in("board.dat");
	if (in.is_open())
	{
		in >> board_data;
		in >> max_cmds;
		in >> min_cmds;
		in >> size_x;
		in >> size_y;
		in >> num;

		in.close();
	}
}

void WriteSolution(const char* path)
{
	std::ofstream out("solution.dat");
	if (out.is_open())
	{
		out << path << std::endl;
		out.close();
	}
}
