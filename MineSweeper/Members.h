#programa once
void MainPage();
void GameOver();
void Victory();
void GenerateMines(int MineNumber);
void WarningAroundBomb();
void ExpandPlayerBoard(int row, int col);
void GameScreen(int Width, int Height);
bool IsWin();
void ShowCurrentState();
void NoticeDisable();
void NoticeEnable();
void Flag(int row, int col);
void OpenCell(int row, int col);
void PlayerSelect();
void PlayerBoard();
void StartGame();
void GetHelp();
int  CountGameDone();

const int Row = 10;
const int Col = 10;
const int WidthScreen = 800;
const int HeightScreen = 500;
const int BombNumber = 10;
int FlagCounter;
int counterNonBombCells = 0;
int counterForWin;
char OrginalBoardGame[Row][Col];
char playerBoardGame[Row][Col];
