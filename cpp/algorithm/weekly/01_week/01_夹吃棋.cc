#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 判断棋子是否被夹吃
bool isCaptured(char board[3][3], int x, int y, char player) {
    // 横向夹吃
    if (x > 0 && x < 2 && board[x-1][y] == player && board[x+1][y] == player) {
        return true;
    }
    // 纵向夹吃
    if (y > 0 && y < 2 && board[x][y-1] == player && board[x][y+1] == player) {
        return true;
    }
    return false;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        char board[3][3];
        for (int i = 0; i < 3; ++i) {
            string row;
            cin >> row;
            for (int j = 0; j < 3; ++j) {
                board[i][j] = row[j];
            }
        }

        bool blackCaptured = false, whiteCaptured = false;

        // 检查每个棋子是否被夹吃
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '*') {
                    if (isCaptured(board, i, j, 'o')) {
                        whiteCaptured = true;
                    }
                }
                if (board[i][j] == 'o') {
                    if (isCaptured(board, i, j, '*')) {
                        blackCaptured = true;
                    }
                }
            }
        }

        if (blackCaptured && whiteCaptured) {
            cout << "draw" << endl;
        } else if (blackCaptured) {
            cout << "kou" << endl; // 小紫获胜
        } else if (whiteCaptured) {
            cout << "yukan" << endl; // 小红获胜
        } else {
            cout << "draw" << endl;
        }
    }

    return 0;
}
