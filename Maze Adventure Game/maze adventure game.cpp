#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Stack and Queue.h"

const int MAXSIZE = 99;    // 迷宫最大长宽度
const int MAZEBORDER = 2;  // 定义迷宫边界，确保是奇数

const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };

enum MazeType {
    WALL = 0,
    PATH,
    START,
    END,
    WAY,
};

// 表示坐标点结构体
struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};


/* 迷宫的类定义 */
class Maze {
private:
    int MazeX = MAXSIZE;    // 迷宫宽度（列数）
    int MazeY = MAXSIZE;    // 迷宫高度（行数)
    int pathLength = 0;
    bool visited[MAXSIZE][MAXSIZE] = { 0 };
    MazeType maze[MAXSIZE][MAXSIZE];
    Point start, end;
public:
    void initMaze();
    void menu();
    void input(int& inputNum);
    void outputMaze();
    void generateMazeRecursive(int x, int y);
    int findShortestPathDFS(int x, int y);
    void printPathCoordinates();
    bool isValid(int x, int y) {
        return x > 0 && x < MazeX + 2 && y > 0 && y < MazeY + 2;
    }
    void Exit() {
        std::cout << "按任意键继续...\n";
        // 清除输入缓冲区
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // 等待用户按键
        std::cin.get();
    }
};

void Maze::initMaze()
{
    for (int i = 0; i < MazeY + 2; i++) {
        for (int j = 0; j < MazeX + 2; j++) {
            maze[i][j] = WALL;
        }
    }
    start.x = start.y = 1;
    end.x = MazeX;
    end.y = MazeY;
}

void Maze::menu()
{
    std::cout << "···················\n";
    std::cout << "·          勇闯迷宫游戏            ·\n";
    std::cout << "·      Maze Adeventure Game        ·\n";
    std::cout << "···················\n";
    std::cout << "---------------游戏开始---------------\n";
    std::cout << "请输入迷宫宽度MazeX : （奇数）";
    input(MazeX);
    std::cout << "请输入迷宫高度MazeY : （奇数）";
    input(MazeY);
    std::cout << "---------------生成迷宫---------------\n";
}

void Maze::input(int& inputNum) {
    while (1) {
        std::cin >> inputNum;
        if (std::cin.fail() || inputNum <= 0 || inputNum > MAXSIZE || inputNum % 2 == 0) {
            std::cin.clear();
            std::cin.ignore(65536, '\n');
            std::cout << "输入数据有误，请重新输入\n";
        }
        else {
            if (std::cin.get() == '\n')
                break;
            else {
                std::cin.clear();
                std::cin.ignore(65536, '\n');
                std::cout << "输入数据有误，请重新输入\n";
            }
        }
    }
}

void Maze::generateMazeRecursive(int x, int y)
{
    // 定义方向数组，顺序随机打乱
    int directions[4] = { 1, 2, 3, 4 };

    // 随机打乱方向数组
    for (int i = 0; i < 4; i++) {
        int j = std::rand() % 4;
        std::swap(directions[i], directions[j]);
    }

    for (int i = 0; i < 4; i++) {
        int dir = directions[i];
        int x_next = x, y_next = y;
        if (dir == 1)
            x_next = x + 2;
        else if (dir == 2)
            x_next = x - 2;
        else if (dir == 3)
            y_next = y + 2;
        else if (dir == 4)
            y_next = y - 2;

        if (x_next > 0 && x_next < MazeX + 2 && y_next > 0 && y_next < MazeY + 2) {
            if (maze[y_next][x_next] == WALL) {
                maze[y_next][x_next] = PATH;
                maze[y_next - (y_next - y) / 2][x_next - (x_next - x) / 2] = PATH;
                generateMazeRecursive(x_next, y_next);
            }
        }
    }
}

int Maze::findShortestPathDFS(int x, int y) {
    if (x == end.x && y == end.y) {
        return 1;  // 找到终点，返回1表示成功
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny) && maze[ny][nx] == PATH) {
            maze[y][x] = WAY; // Mark the current point as part of the path
            if (findShortestPathDFS(nx, ny)) {
                return true;
            }
            maze[y][x] = PATH; // Unmark the current point if no path is found
        }
    }

    return false;
}

void Maze::outputMaze()
{
    maze[end.y][end.x] = END;
    maze[1][1] = START;
    for (int i = 0; i < MazeY + 2; i++) {
        for (int j = 0; j < MazeX + 2; j++) {
            if (maze[i][j] == WALL)
                std::cout << "■";
            else if (maze[i][j] == PATH)
                std::cout << "  ";
            else if (maze[i][j] == START)
                std::cout << "始";
            else if (maze[i][j] == END)
                std::cout << "终";
            else if (maze[i][j] == WAY)
                std::cout << "·";
        }
        std::cout << "\n";
    }
}

void Maze::printPathCoordinates() {
    std::cout << "路径坐标：" << std::endl;
    bool flag = 1;
    for (int y = 1; y < MazeY + 2; y++) {
        for (int x = 1; x < MazeX + 2; x++) {
            if (maze[y][x] == WAY) {
                std::cout << " (" << x << ", " << y << ") ";
                if ((x == end.x && y == end.y - 1) || (x == end.x - 1 && y == end.y)) {
                    std::cout << " ";
                    flag = 0;
                    break;
                }
                else
                    std::cout << "->";
            }
        }
        if (!flag)
            break;
    }
    std::cout << std::endl;
}

int main()
{
    std::srand(std::time(0)); // 随机种子初始化
    Maze maze;
    maze.menu();
    maze.initMaze();
    maze.generateMazeRecursive(1, 1);
    if (maze.findShortestPathDFS(1,1)) {
        maze.outputMaze();
        maze.printPathCoordinates();
    }
    else
        std::cout << "无路径！";
    maze.Exit();
    return 0;
}
