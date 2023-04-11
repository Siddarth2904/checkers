#include <iostream>
using namespace std;
#define ROWS 8
#define COLS 8

#define EMPTY 1
#define RED 2
#define BLACK 3
#define REDKING 4
#define BLACKKING 5

#define ISRED(c) (c == RED || c == REDKING)
#define ISBLACK(c) (c == BLACK || c == BLACKKING)
#define ISEMPTY(c) (c == EMPTY)

void printDisplay(int d[][COLS]);
void swapIJKL(int d[ROWS][COLS], int i, int j, int k, int l);
char value2symbol(int i);
void printDisplayFancy(int d[][COLS]);
int Playersturn(int d[][COLS], int player, int i, int j, int k, int l);

void printDisplayFancy(int d[][COLS])
{
    int rr, cc, pp;

    cout << "  +---+---+---+---+---+---+---+---+" << endl;

    for (rr = 0; rr < ROWS; ++rr)
    {
        cout << rr + 1 << " |";
        for (cc = 0; cc < COLS; ++cc)
        {
            cout << ' ' << value2symbol(d[rr][cc]) << " |";
        }
        cout << endl
             << "  +---+---+---+---+---+---+---+---+" << endl;
    }

    cout << "    a   b   c   d   e   f   g   h" << endl;
}

void swapIJKL(int d[ROWS][COLS], int i, int j, int k, int l)
{
    int temp;

    cout << "SWAP: " << i << ',' << j << " to " << k << ',' << l << endl;

    temp = d[i][j];

    d[i][j] = d[k][l];

    d[k][l] = temp;
}

char value2symbol(int i)
{
    switch (i)
    {
    case 0:
        return ' ';
    case 1:
        return 'e';
    case 2:
        return 'B';
    case 3:
        return 'R';
    }
    return ('?');
}

int Playersturn(int d[][COLS], int player, int i, int j, int k, int l)
{
    int jmp_r;
    int jmp_c;

    if (player == RED)
    {
        cout << "RED move from " << i << ',' << j << " to " << k << ',' << l << endl;
    }
    else
    {
        cout << "BLACK move from " << i << ',' << j << " to " << k << ',' << l << endl;
    }

    if (i < 0 || ROWS <= i)
    {
        cout << "i is out of bounds" << endl;
        return -1;
    }
    if (j < 0 || COLS <= j)
    {
        cout << "j is out of bound" << endl;
        return -1;
    }

    if (k < 0 || ROWS <= k)
    {
        cout << "k is out of bounds" << endl;
        return -1;
    }
    if (l < 0 || COLS <= l)
    {
        cout << "l is out of bounds" << endl;
        return -1;
    }

    if (player == RED)
    {
        if (d[i][j] != RED)
        {
            cout << "move your own piece!\n"
                 << endl;
            return -1;
        }
    }
    else
    {
        if (d[i][j] != BLACK)
        {
            cout << "move your own piece!\n"
                 << endl;
            return -1;
        }
    }

    if (d[k][l] != EMPTY)
    {
        cout << "You must move to a empty location" << endl;
        return -1;
    }

    if (player == RED)
    {
        if (i >= k)
        {
            cout << "RED player must move down\n"
                 << endl;
            return -1;
        }
    }
    else
    {
        if (i <= k)
        {
            cout << "BLACK player must move up\n"
                 << endl;
            return -1;
        }
    }

    if (i - k == -1 || i - k == 1)
    {
        if (j - l == 1 || j - l == -1)
        {
            swapIJKL(d, i, j, k, l);
            return 0;
        }
    }
    if (i - k == -2 || i - k == 2)
    {
        if (j - l == -2 || j - l == 2)
        {
            if (i < k)
            {
                jmp_r = i + 1;
            }
            else
            {
                jmp_r = i - 1;
            }
            if (j < l)
            {
                jmp_c = j + 1;
            }
            else
            {
                jmp_c = j - 1;
            }

            if (player == RED && d[jmp_r][jmp_c] != BLACK)
            {
                cout << "Enemeny is not Black at %d%d", jmp_r, jmp_c;
                return -1;
            }
            if (player == BLACK && d[jmp_r][jmp_c] != RED)
            {
                cout << "you can only jump over an enemy player\n"
                     << endl;
                return -1;
            }

            d[jmp_r][jmp_c] = 1;
            swapIJKL(d, i, j, k, l);
            return 0;
        }
    }

    cout << "You can only move diagnally\n"
         << endl;
    return -1;
}
int main()
{
    int r, c;
    int pr, pb;
    int i, k;
    char j, l;
    int d[ROWS][COLS] = {
        {0, 2, 0, 2, 0, 2, 0, 2},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},
        {3, 0, 3, 0, 3, 0, 3, 0},
        {0, 3, 0, 3, 0, 3, 0, 3},
        {3, 0, 3, 0, 3, 0, 3, 0}};
    for (;;)
    {
        printDisplayFancy(d);

        while (1)
        {
            cout << "Red's turn: ";
            scanf("%d%c", &i, &j);
            cout << "to: ";
            scanf("%d%c", &k, &l);
            if (Playersturn(d, 1, i - 1, j - 'a', k - 1, l - 'a') == 0)
                break;
            cout << "Illegal move, try again\n";
        }

        printDisplayFancy(d);

        while (1)
        {
            cout << "Black's turn: ";
            scanf("%d%c", &i, &j);
            cout << "to: ";
            scanf("%d%c", &k, &l);
            if (Playersturn(d, 2, i - 1, j - 'a', k - 1, l - 'a') == 0)
                break;
            cout << "Illegal move, try again\n";
        }
    }

    getchar();
    getchar();
    return 0;
}