#include <iostream>
#include <string>

#include "board.hpp"
#include "path.hpp"
#include "fileio.hpp"

int main(int argc, char** argv)
{
    // Load board data
    int lvl_num;
    int size_x;
    int size_y;
    std::string board_data;
    int max_cmds;
    int min_cmds;

    LoadBoard(lvl_num, size_x, size_y, max_cmds, min_cmds, board_data);

    std::cout << "Starting solving level: " << lvl_num << std::endl;
    std::cout << "Min Commands: " << min_cmds << std::endl;
    std::cout << "Max Commands: " << max_cmds << std::endl;
    std::cout << "Board Size: " << size_x << "/" << size_y << std::endl;
    
    // Solve Board
    Board gameboard(size_x, size_y, board_data.c_str());
    Path path(max_cmds, min_cmds);
    
    std::cout << "Board Data: " << std::endl;
    gameboard.OutputBoard();

    try
    {
        char last_push = 'R';
        path.Push(last_push);
        
        bool done = false;
        while (!done)
        {
            TestResult result = gameboard.EvaluatePathOnce(path);
            if (result.boom || path.GetNumberCommands() == max_cmds)
            {
                while (path.Peek().Exhausted())
                    path.Pop();
                
                path.Peek().ChangeDirection();
                last_push = path.Peek().GetStep();
                //path.Push(last_push);
            }
            else
            {
                path.Push(last_push);
            }

            if (!(path.GetNumberCommands() < min_cmds))
            {
                if (gameboard.LinkPointsWork(path))
                {
                    TestResult result2 = gameboard.PathIsCorrect(path, result.x, result.y);
                    if (!result2.boom)
                    {
                        done = true;
                    }
                }
            }
        }

        // Write Solution
        std::cout << "Solved! Path: " << path.GetPath() << std::endl;
        WriteSolution(path.GetPath());

    }
    catch (const char* c)
    {
        std::cout << "Error: " << c << std::endl;
        if (path.GetNumberCommands() == 0)
        {
            std::cout << "Brute force failed!" << std::endl;
        }
    }

    return 0;
}
