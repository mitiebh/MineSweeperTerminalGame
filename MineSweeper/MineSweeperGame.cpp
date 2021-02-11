// Copyright ©, written by mitiebh.
#include <iostream>
#include <random>
#include <time.h>
#include <windows.h>
#include "AsciiArt.h"
#include "Members.h"
using namespace std;

int main()
{
    GameScreen(WidthScreen,HeightScreen);
    MainPage();
    cin.ignore();
}
void GameScreen(int Width, int Height) // fix size of the game screen or game window and centerilize it in your computer 
{
    int posX, posY;
    HWND console = GetConsoleWindow();
    RECT rectClient, rectWindow;
    posX = GetSystemMetrics(SM_CXSCREEN) / 2 - Width / 2;
    posY = GetSystemMetrics(SM_CYSCREEN) / 2 - Height / 2;
    MoveWindow(console, posX, posY, Width, Height, TRUE);
    //centerilize screen window game
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    COORD removescrollbar =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), removescrollbar);
}
void GameOver()
{
    cout << "\n\n\t\t\t\t    ";
    for (int i = 0; i < Col; i++)
        cout << i << " ";
    cout << "\n\n";
    for (int i = 0; i < Row; i++)
    {
        cout << "\t\t\t\t " << i << "  ";
        for (int j = 0; j < Col; j++)
        {
            if (OrginalBoardGame[i][j] == 'B')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << OrginalBoardGame[i][j] << " ";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << OrginalBoardGame[i][j] << " ";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << endl;
    }
    int Mode = 0;
    cout << "\n\n 1. Back to Main page\n\n 2. Exit Game\n";
ChooseLabel: cout << "\n\n\n\n\n Choose your Option : ";
    cin >> Mode;
    switch (Mode)
    {
    case 1:
        system("CLS");
        MainPage();
        break;
    case 2:
        exit(0);
    default:
        cout << " Not Valid\n";
        goto ChooseLabel;
    }
}
void Victory()
{
    cout << "\n\t\t\t\t    ";
    for (int i = 0; i < Col; i++)
        cout << i << " ";
    cout << "\n\n";
    for (int i = 0; i < Row; i++)
    {
        cout << "\t\t\t\t " << i << "  ";
        for (int j = 0; j < Col; j++)
        {
            if (OrginalBoardGame[i][j] == 'B')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << OrginalBoardGame[i][j] << " ";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << OrginalBoardGame[i][j] << " ";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << endl;
    }
    int Mode = 0;
    cout << "\n\n 1. Back to Main page\n\n 2. Exit Game\n";
ChooseLabel: cout << "\n\n\n\n\n Choose your Option : ";
    cin >> Mode;
    switch (Mode)
    {
    case 1:
        system("CLS");
        MainPage();
        break;
    case 2:
        exit(0);
    default:
        cout << " Not Valid\n";
        goto ChooseLabel;
    }
}
int CountGameDone()
{
    // numerate al the non bomb cells in orginal board game
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            if (OrginalBoardGame[i][j] != 'B')
                counterNonBombCells++;
    return counterNonBombCells;
}
void GenerateMines(int MineNumber)
{
    //init table
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            OrginalBoardGame[i][j] = '0';
    //generate bomb location randomly and diffrent value in every time that program run
    srand(time(NULL));
    for (int count = 0; count < MineNumber; count++)
    {
        // generate random number between 0 to 9
        int BombLocation_i = rand() % 10;
        int BombLocation_j = rand() % 10;
        OrginalBoardGame[BombLocation_i][BombLocation_j] = 'B';
    }
    // init flag counter every per enter to game -> not every per running
    FlagCounter = 10;
}
void WarningAroundBomb()
{
    for (int i = 0; i < Row; i++)
    {
        for (int j = 0; j < Col; j++)
        {
            if (OrginalBoardGame[i][j] == 'B') // if Bomb cell.
            {
                // check around of cell.
                /*
                    +   +   +
                    +   B   +
                    +   +   +
                */
                // check each cell where if it is not Bomb then increase it.
                if (OrginalBoardGame[i - 1][j - 1] != 'B' && (-1 < i - 1 < 10) && (-1 < j - 1 < 10))
                    OrginalBoardGame[i - 1][j - 1]++;
                if (OrginalBoardGame[i - 1][j] != 'B' && (-1 < i - 1 < 10) && (-1 < j < 10))
                    OrginalBoardGame[i - 1][j]++;
                if (OrginalBoardGame[i - 1][j + 1] != 'B' && (-1 < i - 1 < 10) && (-1 < j + 1 < 10))
                    OrginalBoardGame[i - 1][j + 1]++;
                if (OrginalBoardGame[i][j - 1] != 'B' && (-1 < i < 10) && (-1 < j - 1 < 10))
                    OrginalBoardGame[i][j - 1]++;
                if (OrginalBoardGame[i][j + 1] != 'B' && (-1 < i < 10) && (-1 < j + 1 < 10))
                    OrginalBoardGame[i][j + 1]++;
                if (OrginalBoardGame[i + 1][j - 1] != 'B' && (-1 < i + 1 < 10) && (-1 < j - 1 < 10))
                    OrginalBoardGame[i + 1][j - 1]++;
                if (OrginalBoardGame[i + 1][j] != 'B' && (-1 < i + 1 < 10) && (-1 < j < 10))
                    OrginalBoardGame[i + 1][j]++;
                if (OrginalBoardGame[i + 1][j + 1] != 'B' && (-1 < i + 1 < 10) && (-1 < j + 1 < 10))
                    OrginalBoardGame[i + 1][j + 1]++;
            }
        }
    }
}
void ExpandPlayerBoard(int row, int col)
{
    if (0 < col + 1 < 10 && 0 < row + 1 < 10)
    {
        int i = row, j = col;
        bool check = false;
        for (i = row; (i < Row) && (OrginalBoardGame[i][j] != 'B'); i++) // Search Right-Bottom of the Table
        {
            if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
            {
                playerBoardGame[i][j] = OrginalBoardGame[i][j];
                check = true;
            }
            if (check)
            {
                check = false;
                break;
            }
            for (j = col; (j < Col) && (OrginalBoardGame[i][j] != 'B'); j++)
            {
                if (OrginalBoardGame[i][j] == '0')
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
                {
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                    check = true;
                }
                if (check)
                {
                    check = false;
                    j = col;
                    break;
                }
            }
        }
    }
    if (0 < col - 1 < 10 && 0 < row + 1 < 10)
    {
        int i = row, j = col;
        bool check = false;
        for (i = row; (i < Row) && (OrginalBoardGame[i][j] != 'B'); i++) // Search Left-Bottom of the Table
        {
            if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
            {
                playerBoardGame[i][j] = OrginalBoardGame[i][j];
                check = true;
            }
            if (check)
            {
                check = false;
                break;
            }
            for (j = col; (j > 0) && (OrginalBoardGame[i][j] != 'B'); j--)
            {
                if (OrginalBoardGame[i][j] == '0')
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
                {
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                    check = true;
                }
                if (check)
                {
                    check = false;
                    j = col;
                    break;
                }
            }
        }
    }
    if (0 < col + 1 < 10 && 0 < row - 1 < 10)
    {
        int i = row, j = col;
        bool check = false;
        for (i = row; (i > 0) && (OrginalBoardGame[i][j] != 'B'); i--) // Search Right-Up of the Table
        {
            if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
            {
                playerBoardGame[i][j] = OrginalBoardGame[i][j];
                check = true;
            }
            if (check)
            {
                check = false;
                break;
            }
            for (j = col; (j < Col) && (OrginalBoardGame[i][j] != 'B'); j++)
            {
                if (OrginalBoardGame[i][j] == '0')
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
                {
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                    check = true;
                }
                if (check)
                {
                    check = false;
                    j = col;
                    break;
                }
            }
        }
    }
    if (0 < col - 1 < 10 && 0 < row - 1 < 10)
    {
        int i = row, j = col;
        bool check = false;
        for (i = row; (i > 0) && (OrginalBoardGame[i][j] != 'B'); i--) // Search Left-Up of the Table
        {
            if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
            {
                playerBoardGame[i][j] = OrginalBoardGame[i][j];
                check = true;
            }
            if (check)
            {
                check = false;
                break;
            }
            for (j = col; (j > 0) && (OrginalBoardGame[i][j] != 'B'); j--)
            {
                if (OrginalBoardGame[i][j] == '0')
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                if (OrginalBoardGame[i][j] != '0' && OrginalBoardGame[i][j] != 'B')
                {
                    playerBoardGame[i][j] = OrginalBoardGame[i][j];
                    check = true;
                }
                if (check)
                {
                    check = false;
                    j = col;
                    break;
                }
            }
        }
    }
}
bool IsWin()
{
    // check if cells that open by the player is equal to oprginal board game cells that is not bomb or not
    // in the other hand, check for win, check if all the cells that is not bomb, is opened or not
    if (counterForWin == counterNonBombCells)
        return true;
    else
        return false;
}
void ShowCurrentState()
{
    NoticeDisable();
    cout << "\n\t\t\t\t    ";
    for (int i = 0; i < Col; i++)
        cout << i << " ";
    cout << "\n\n";
    for (int i = 0; i < Row; i++)
    {
        cout << "\t\t\t\t " << i << "  ";
        for (int j = 0; j < Col; j++)
        {
            if (playerBoardGame[i][j] != 'B' && playerBoardGame[i][j] != '+' && playerBoardGame[i][j] != 'F')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << playerBoardGame[i][j] << " ";
            }
            else if (playerBoardGame[i][j] == '+')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                cout << playerBoardGame[i][j] << " ";
            }
            else if (playerBoardGame[i][j] == 'F')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
                cout << playerBoardGame[i][j] << " ";
            }
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << endl;
    }
    PlayerSelect();
}
void Flag(int row, int col)
{
    // pop the flag or cancel the flag
    if (playerBoardGame[row][col] == 'F')
    {
        playerBoardGame[row][col] = '+';
        FlagCounter++;
    }
    // put the flag
    else
    {
        playerBoardGame[row][col] = 'F';
        FlagCounter--;
    }
    system("CLS");
    ShowCurrentState();
}
void OpenCell(int row, int col)
{

    if (OrginalBoardGame[row][col] == 'B')
    {
        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\n\n\t\t  * BOOoooOOOoooOOM * YOU LOSE THE GAME, HA HA HA HA\n"
             << "\t\t   Your mistake caused the area bombs to explode :/\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        GameOver();
    }
    else
    {
        if (OrginalBoardGame[row][col] == '0')
        {
            /* expand table */
            ExpandPlayerBoard(row, col);
            system("CLS");
            ShowCurrentState();
        }
        else
        {
            /* show current state table */
            playerBoardGame[row][col] = OrginalBoardGame[row][col];
            system("CLS");
            ShowCurrentState();
        }
    }
}
void PlayerSelect()
{
    counterForWin = 0;
    for (int i = 0; i < Row; i++)
        for (int j = 0; j < Col; j++)
            if (playerBoardGame[i][j] != '+' && playerBoardGame[i][j] != 'F')
                counterForWin++;
    if (IsWin() == false) // check for win
    {
        string operation;
        int RowSelected = 0, ColSelected = 0;
        cout << "\n\n Select your operation\n"
             << "- Open cell(Type any of these keys for open cell(Open - O - o - open)\n"
             << "- Put,Pop Flag(Type any of these keys for put or pop the flag(Flag - F - f - flag)\n"
             << "- Back to main page(Type b or B key for cancel the game)\n"
             << "- Exit Game(type exit command or e key for terminate the game)\n\n\n"
             << "-> Flags remain = " << FlagCounter << endl;
    ChooseLabel: cout << " Type your operation >> ";
        cin >> operation;
        if (operation == "exit" || operation == "E" || operation == "Exit" || operation == "e")
            exit(0);
        else if (operation == "b" || operation == "B" || operation == "Back" || operation == "back")
        {
            system("CLS");
            MainPage();
        }
        cout << " Enter cell number(row col) : ";
        cin >> RowSelected >> ColSelected;
        if (operation == "Flag" || operation == "flag" || operation == "f" || operation == "F")
            /* put,pop flag */
            Flag(RowSelected, ColSelected);
        if (operation == "Open" || operation == "O" || operation == "open" || operation == "o")
            /* open cell */
            OpenCell(RowSelected, ColSelected);
        else
        {
            cout << "Not Valid\n";
            goto ChooseLabel;
        }
    }
    else
    {   
        system("CLS");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\n\n\t\t  (: Conragulation :) YOU win THE GAME, YOOOOHOOOO\n"
             << "\t\t\t\t\t  You cleared the area from Mine\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        Victory();
    }
}
void PlayerBoard()
{
    // init player board game for the first time
    cout << "\n\t\t\t\t    ";
    for (int i = 0; i < Col; i++)
        cout << i << " ";
    cout << "\n\n";
    for (int i = 0; i < Row; i++)
    {
        cout << "\t\t\t\t " << i << "  ";
        for (int j = 0; j < Col; j++)
        {
            playerBoardGame[i][j] = '+';
            cout << "+ ";
        }
        cout << endl;
    }
    PlayerSelect();
}
void NoticeEnable() 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "\n\t\t\t\t Do not have rush and stress.\n"
         << "  Time does not make any sense, you can think on the PuzZZEL as much as you want in Easy Mode\n"
         << " \t\tBut the Easy Mode is not always Easy. So think well and be carefull.\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void NoticeDisable()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
    cout << "\n\t\t\t\t Do not have rush and stress.\n"
         << "  Time does not make any sense, you can think on the PuzZZEL as much as you want in Easy Mode\n"
         << " \t\tBut the Easy Mode is not always Easy. So think well and be carefull.\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void StartGame()
{
    NoticeEnable();
    GenerateMines(BombNumber); WarningAroundBomb(); CountGameDone();
    PlayerBoard();
}
void GetHelp()
{
    // this page is the term & rules of game;
    cout << endl
         << "---------- Introduction\n"
         << "- MINESWEEPER is a puzzle and single player game.\n"
         << "- In this game, the goal is to find the position of mines (bombs) on the game board\n"
         << "  using and getting notice from the guide in cells of the game board or (numbered cells)\n"
         << "  each numbered cell show you that how many bombs are there near your cells.\n"
         << "- You have to open the game table completely and identify all the mines to win the game.\n\n\n"
         << "---------- Rules\n"
         << "- For type your operation in game, first type KEYWORD operation that you want then type row\n"
         << "  and column with space seprated for example : Open 12, it means open the cell 1-2 located in\n"
         << "  row1 and column2.\n"
         << "- You are allowed to open one cell at a time in each selection.\n"
         << "- Flagging occurs when a player guesses and thinks that the house contains a bomb\n"
         << "  So the marked cells does not have a specific status.\n"
         << "- You can also place a limited number of flags to guess the position of the mines.\n"
         << "- You have ONE flag operation for both put it on the board or pop it back(cancel the flag).\n"
         << "- In hard mode playing, you have to only solve puzzles at the specified time.\n\n\n\n";
    int Mode = 0;
    cout << " 1. Back to Main page\n\n 2. Exit Game\n\n\n";
ChooseLabel: cout << "\n\n\n\n Choose your Option : ";
    cin >> Mode;
    switch (Mode)
    {
    case 1:
        system("CLS");
        MainPage();
        break;
    case 2:
        exit(0);
    default:
        cout << " Not Valid\n";
        goto ChooseLabel;
    }
}
void MainPage()
{
    SetConsoleTitle(L"Mine Sweeper");
    int Mode = 0;
    srand(time(NULL));
    int ColorTheme = rand() % 14 + 1;
    cout << "\n\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorTheme);
    AsciiArt("  minesweeper");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\n\n\n\n\t\t\t\t\t 1. Start Game\n\n\n\n"
         << "\t\t\t\t\t 2. Term & Rules\n\n\n\n"
         << "\t\t\t\t\t 3. Exit Game\n\n\n\n\n\n\n";
ChooseLabel: cout << "\n\n\n Choose your Option : ";
    cin >> Mode;
    switch (Mode)
    {
    case 1:
        system("CLS");
        StartGame();
        break;
    case 2:
        system("CLS");
        GetHelp();
        break;
    case 3:
        exit(0);
    default:
        cout << " Not Valid\n";
        goto ChooseLabel;
    }
}
