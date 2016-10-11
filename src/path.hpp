#ifndef PATH_HPP
#define PATH_HPP

#define nullptr 0

#include "step.hpp"

class Path
{
private:
	int m_max;
	int m_min;
	
	Step* m_commands;
	int m_command_ptr;
    
    char* m_path;
    
	void Cleanup();

public:
	Path(int max, int min);
	Path(const Path& copy);
	~Path();
	Path& operator=(const Path& rhs);

	void Push(char cmd);
	Step Pop();
	Step& Peek();
	Step& GetCommand(int pos);

	int GetNumberCommands();
	const char* GetPath();
};

#endif // PATH_HPP
