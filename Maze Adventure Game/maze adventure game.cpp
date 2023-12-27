#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Stack and Queue.h"

const int MAXSIZE = 99;    // �Թ���󳤿��
const int MAZEBORDER = 2;  // �����Թ��߽磬ȷ��������

const int dx[] = { 1, -1, 0, 0 };
const int dy[] = { 0, 0, 1, -1 };

enum MazeType {
    WALL = 0,
    PATH,
    START,
    END,
    WAY,
};

// ��ʾ�����ṹ��
struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};


/* �Թ����ඨ�� */
class Maze {
private:
    int MazeX = MAXSIZE;    // �Թ���ȣ�������
    int MazeY = MAXSIZE;    // �Թ��߶ȣ�����)
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
        std::cout << "�����������...\n";
        // ������뻺����
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // �ȴ��û�����
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
    std::cout << "��������������������������������������\n";
    std::cout << "��          �´��Թ���Ϸ            ��\n";
    std::cout << "��      Maze Adeventure Game        ��\n";
    std::cout << "��������������������������������������\n";
    std::cout << "---------------��Ϸ��ʼ---------------\n";
    std::cout << "�������Թ����MazeX : ��������";
    input(MazeX);
    std::cout << "�������Թ��߶�MazeY : ��������";
    input(MazeY);
    std::cout << "---------------�����Թ�---------------\n";
}

void Maze::input(int& inputNum) {
    while (1) {
        std::cin >> inputNum;
        if (std::cin.fail() || inputNum <= 0 || inputNum > MAXSIZE || inputNum % 2 == 0) {
            std::cin.clear();
            std::cin.ignore(65536, '\n');
            std::cout << "����������������������\n";
        }
        else {
            if (std::cin.get() == '\n')
                break;
            else {
                std::cin.clear();
                std::cin.ignore(65536, '\n');
                std::cout << "����������������������\n";
            }
        }
    }
}

void Maze::generateMazeRecursive(int x, int y)
{
    // ���巽�����飬˳���������
    int directions[4] = { 1, 2, 3, 4 };

    // ������ҷ�������
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
        return 1;  // �ҵ��յ㣬����1��ʾ�ɹ�
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
                std::cout << "��";
            else if (maze[i][j] == PATH)
                std::cout << "  ";
            else if (maze[i][j] == START)
                std::cout << "ʼ";
            else if (maze[i][j] == END)
                std::cout << "��";
            else if (maze[i][j] == WAY)
                std::cout << "��";
        }
        std::cout << "\n";
    }
}

void Maze::printPathCoordinates() {
    std::cout << "·�����꣺" << std::endl;
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
    std::srand(std::time(0)); // ������ӳ�ʼ��
    Maze maze;
    maze.menu();
    maze.initMaze();
    maze.generateMazeRecursive(1, 1);
    if (maze.findShortestPathDFS(1,1)) {
        maze.outputMaze();
        maze.printPathCoordinates();
    }
    else
        std::cout << "��·����";
    maze.Exit();
    return 0;
}
