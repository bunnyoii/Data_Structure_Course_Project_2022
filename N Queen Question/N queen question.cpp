#include <iostream>

const int MAXSIZE = 10;

class NQueen {
private:
    bool board[MAXSIZE][MAXSIZE] = { 0 };
    int count = 0;
    int N = 0;
public:
    void menu();
    void input();
    void solveNQueens(int row);
    bool isSafe(int row, int col);
    void Exit() {
        std::cout << "按任意键继续...\n";
        // 清除输入缓冲区
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // 等待用户按键
        std::cin.get();
    }
};

void NQueen::menu()
{
    std::cout << "···················\n";
    std::cout << "·            N皇后问题             ·\n";
    std::cout << "·        N Queen Question          ·\n";
    std::cout << "···················\n";
    std::cout << "---------------游戏开始---------------\n";
    std::cout << ">>>>请输入皇后的个数N(4~10)：\n";
}

void NQueen::input()
{
    while (1) {
        std::cin >> N;
        if (std::cin.fail() || N <= 3 || N > MAXSIZE) {
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

bool NQueen::isSafe(int row, int col) {
    // 检查同一列
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1)
            return false;

    // 检查左上对角线
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // 检查右上对角线
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j] == 1)
            return false;

    return true;
}

void NQueen::solveNQueens(int row) {
    if (row == N) {
        // 找到一个解，打印它
        count++;
        std::cout << "Solution " << count << ":\n";
        for (int i = 0; i < 2 * N; i++)
            std::cout << '-';
        std::cout << '\n';
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << (board[i][j] == 1 ? "●" : "×");
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < 2 * N; i++)
            std::cout << '-';
        std::cout << '\n';
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            solveNQueens(row + 1);
            board[row][col] = 0; // 回溯
        }
    }
}

int main() {
    NQueen NQ;
    NQ.menu();
    NQ.input();
    NQ.solveNQueens(0);
    NQ.Exit();
    return 0;
}