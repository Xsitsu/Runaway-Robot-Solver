#include "board.hpp"

#define PRE_PROCESS

Board::Board(int size_x, int size_y, const char* board_data) : m_size_x(size_x), m_size_y(size_y), m_gameboard(nullptr)
{
	m_gameboard = new bool*[m_size_x];
	for (int x = 0; x < m_size_x; x++)
	{
		m_gameboard[x] = new bool[m_size_y];
	}

	int c = 0;
	for (int y = 0; y < m_size_y; y++)
	{
		for (int x = 0; x < m_size_x; x++)
		{
			m_gameboard[x][y] = (board_data[c] == 'X');
			c++;
		}
	}

#ifdef PRE_PROCESS

    // Board pre-process by X-lines
    for (int y = 0; y < m_size_y; y++)
	{
        bool set_next_bomb = false;
		for (int x = 0; x < m_size_x; x++)
		{
            m_gameboard[x][y] = m_gameboard[x][y] || set_next_bomb;
            set_next_bomb = false;
            
            if (m_gameboard[x][y])
            {
                if (SquareIsValid(x+1, y-1))
                {
                    set_next_bomb = m_gameboard[x+1][y-1];
                }
                else
                {
                    set_next_bomb = true;
                }
            }
		}
	}

    // Board pre-process by Y-lines
    for (int x = 0; x < m_size_x; x++)
	{
        bool set_next_bomb = false;
		for (int y = 0; y < m_size_y; y++)
		{
            m_gameboard[x][y] = m_gameboard[x][y] || set_next_bomb;
            set_next_bomb = false;
            
            if (m_gameboard[x][y])
            {
                if (SquareIsValid(x-1, y+1))
                {
                    set_next_bomb = m_gameboard[x-1][y+1];
                }
                else
                {
                    set_next_bomb = true;
                }
            }
		}
	}
    
    //Board pre-process individual cave squares
    for (int y = m_size_y - 1; y >= 0; y--)
    {
        for (int x = m_size_x - 1; x >= 0; x--)
        {
            if (!m_gameboard[x][y])
            {
                bool can_move_right = true;
                bool can_move_down = true;
                if (SquareIsValid(x+1, y))
                    can_move_right = !m_gameboard[x+1][y];
                if (SquareIsValid(x, y+1))
                    can_move_down = !m_gameboard[x][y+1];
                
                m_gameboard[x][y] = !can_move_right && !can_move_down;
                
            }
        }
    }

#endif

}

Board::Board(const Board& copy) : m_size_x(copy.m_size_x), m_size_y(copy.m_size_y), m_gameboard(nullptr)
{
	m_gameboard = new bool*[m_size_x];
	for (int x = 0; x < m_size_x; x++)
	{
		m_gameboard[x] = new bool[m_size_y];
		for (int y = 0; y < m_size_y; y++)
		{
			m_gameboard[x][y] = copy.m_gameboard[x][y];
		}
	}
}

Board::~Board()
{
	DeleteBoard();
}

Board& Board::operator=(const Board& rhs)
{
	if (this != &rhs)
	{
		DeleteBoard();

		m_size_x = rhs.m_size_x;
		m_size_y = rhs.m_size_y;

		m_gameboard = new bool*[m_size_x];
		for (int x = 0; x < m_size_x; x++)
		{
			m_gameboard[x] = new bool[m_size_y];
			for (int y = 0; y < m_size_y; y++)
			{
				m_gameboard[x][y] = rhs.m_gameboard[x][y];
			}
		}
	}

	return *this;
}


void Board::DeleteBoard()
{
	if (m_gameboard != nullptr)
	{
		for (int i = 0; i < m_size_x; i++)
		{
			delete[] m_gameboard[i];
		}
		delete m_gameboard;
		m_gameboard = nullptr;
	}
}

void Board::OutputBoard()
{
	for (int y = 0; y < m_size_y; y++)
	{
		for (int x = 0; x < m_size_x; x++)
		{
            if (m_gameboard[x][y])
                std::cout << "X ";
            else
                std::cout << ". ";
		}
        std::cout << std::endl;
	}
}

bool Board::ReadSquare(int x, int y) const
{
	return m_gameboard[x][y];
}

TestResult Board::PathIsCorrect(Path& path, int start_x, int start_y)
{
	TestResult result;
	result.x = start_x;
	result.y = start_y;
	result.boom = false;
    
    result.x = 0;
    result.y = 0;
    
	int c = 0;
	while (result.boom == false && result.x < m_size_x && result.y < m_size_y)
	{
		if (m_gameboard[result.x][result.y])
		{
			result.boom = true;
		}
		else
		{
			Step& cmd = path.GetCommand(c);
			if (cmd.GetStep() == 'R')
			{
				result.x++;
			}
			else if (cmd.GetStep() == 'D')
			{
				result.y++;
			}
			else
			{
				std::cout << "Error: Got command \"" << cmd.GetStep() << "\". Should only be D or R!" << std::endl;
			}

			c++;
			c %= path.GetNumberCommands();
		}
		
	}

	return result;
}


TestResult Board::EvaluatePathOnce(Path& path)
{
	TestResult result;
	result.x = 0;
	result.y = 0;
	result.boom = false;

	int c = 0;
	while (result.boom == false && c < path.GetNumberCommands())
	{
		if (m_gameboard[result.x][result.y])
		{
			result.boom = true;
		}
		else
		{
			Step cmd = path.GetCommand(c);
			if (cmd.GetStep() == 'R')
			{
				result.x++;
			}
			else if (cmd.GetStep() == 'D')
			{
				result.y++;
			}
			else
			{
				std::cout << "Error: Got command \"" << cmd.GetStep() << "\". Should only be D or R!" << std::endl;
			}

			c++;
		}

	}

	return result;
}

bool Board::SquareIsValid(int x, int y)
{
    return (x >= 0 && x < m_size_x && y >= 0 && y < m_size_y);
}

bool Board::LinkPointsWork(Path& path)
{
    int move_x = 0;
    int move_y = 0;
    
    int num = path.GetNumberCommands();
    for (int i = 0; i < num; i++)
    {
        if (path.GetCommand(i).GetStep() == 'R')
            move_x++;
        else
            move_y++;
    }
    
    int pos_x = 0;
    int pos_y = 0;
    bool boom = false;
    while (!boom && SquareIsValid(pos_x, pos_y))
    {
        boom = m_gameboard[pos_x][pos_y];
        pos_x += move_x;
        pos_y += move_y;
    }
    
    return !boom;
}
