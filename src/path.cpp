#include "path.hpp"

Path::Path(int max, int min) : m_max(max), m_min(min), m_commands(nullptr), m_command_ptr(0)
{
	m_commands = new Step[m_max];
    m_path = new char[m_max + 1];
}

Path::Path(const Path& copy) : m_max(copy.m_max), m_min(copy.m_min), m_commands(nullptr), m_command_ptr(copy.m_command_ptr)
{
	m_commands = new Step[m_max];
    m_path = new char[m_max + 1];
	for (int i = 0; i < m_command_ptr; i++)
	{
		m_commands[i] = copy.m_commands[i];
	}
}

Path::~Path()
{
	Cleanup();
}

Path& Path::operator=(const Path& rhs)
{
	if (this != &rhs)
	{
		Cleanup();

		m_max = rhs.m_max;
		m_min = rhs.m_min;
		m_command_ptr = rhs.m_command_ptr;
		m_commands = new Step[m_max];
        m_path = new char[m_max + 1];
		for (int i = 0; i < m_command_ptr; i++)
		{
			m_commands[i] = rhs.m_commands[i];
		}
	}

	return *this;
}

void Path::Cleanup()
{
	if (m_commands != nullptr)
	{
		delete[] m_commands;
        delete[] m_path;
		m_commands = nullptr;
	}
}

void Path::Push(char cmd)
{
	if (m_command_ptr == m_max)
		throw "OVERFLOW!";

	m_commands[m_command_ptr++] = Step(cmd);
}

Step Path::Pop()
{
	if (m_command_ptr == 0)
		throw "UNDERFLOW!";

	Step ret = m_commands[m_command_ptr - 1];
	m_commands[m_command_ptr--] = Step();
	return ret;
}

Step& Path::Peek()
{
	if (m_command_ptr == 0)
		throw "UNDERFLOW!";

	return m_commands[m_command_ptr - 1];
}

Step& Path::GetCommand(int pos)
{
	if (pos >= m_command_ptr)
		throw "OVERFLOW!";
	else if (pos < 0)
		throw "UNDERFLOW!";

	return m_commands[pos];
}

int Path::GetNumberCommands()
{
	return m_command_ptr;
}

const char* Path::GetPath()
{
    for (int i = 0; i < m_command_ptr; i++)
    {
        m_path[i] = m_commands[i].GetStep();
    }
    m_path[m_command_ptr] = 0;
    
	return m_path;
}
