#ifndef FILEIO_HPP
#define FILEIO_HPP

#include <fstream>
#include <string>

void LoadBoard(int& num, int& size_x, int& size_y, int& max_cmds, int& min_cmds, std::string& board_data);
void WriteSolution(const char* path);

#endif // FILIO_HPP