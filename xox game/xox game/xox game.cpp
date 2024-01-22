#include <iostream>
#include <time.h>

class XOXgame
{
    public:
        char gameTable[3][3]; // game table 1-9
        char player; 
        char AI;

        bool running;
        bool playerTurn; 

        int result = -2; //  1 is winning, 0 is tie, -1 is losing

        XOXgame(bool running, char player) 
        {
            this->running = running;
            this->player = player;

            // set playerturn and characters
            if (player == 'X')
            {
                this->playerTurn = true;
                this->player = 'X';
                this->AI = 'O';
            }
            else
            {
                this->playerTurn = false;
                this->player = 'O';
                this->AI = 'X';
            }

            int temp = 49;
            for (int i = 0; i < 3; i++) // 49 is 1 in ascii table , 50 -> 2 51 -> 3 ... 57 -> 9. so set temp as 49 to start
            {
                for (int j = 0; j < 3; j++)
                {
                    this->gameTable[i][j] = temp; // put the number in the table
                    temp++; // increase the number
                }
            }
        }
};

void clearTable()
{
    system("CLS"); //clears console
}

void drawTable(XOXgame* gameGiven)
{
    clearTable();

    std::cout << "_________________________" << '\n';
    std::cout << "|       |       |       |" << '\n';
    std::cout << "|   " << gameGiven->gameTable[0][0] << "   |   " << gameGiven->gameTable[1][0] << "   |   " << gameGiven->gameTable[2][0] << "   |" << '\n';
    std::cout << "|_______|_______|_______|" << '\n';
    std::cout << "|       |       |       |" << '\n';
    std::cout << "|   " << gameGiven->gameTable[0][1] << "   |   " << gameGiven->gameTable[1][1] << "   |   " << gameGiven->gameTable[2][1] << "   |" << '\n';
    std::cout << "|_______|_______|_______|" << '\n';
    std::cout << "|       |       |       |" << '\n';
    std::cout << "|   " << gameGiven->gameTable[0][2] << "   |   " << gameGiven->gameTable[1][2] << "   |   " << gameGiven->gameTable[2][2] << "   |" << '\n';
    std::cout << "|_______|_______|_______|" << '\n';

}

void playPlayer(XOXgame* gameGiven)
{
    bool playValid = false; 
    int x;
    do
    {
        std::cout << "Where do you want to play? (1-9): " << '\n';
        std::cin >> x;

        x += 48; // add 48 to match the ascii since we use char

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (gameGiven->gameTable[i][j] == x) //if the number we gave is in the table (which means its unused) we can place there
                {
                    playValid = true;
                    gameGiven->gameTable[i][j] = gameGiven->player;
                }
    } while (playValid != true);
            
    gameGiven->playerTurn = false;
}

void playAI(XOXgame* gameGiven)
{
    int x, y;

    srand(time(0));
    do
    {

        x = (rand() % 3);
        y = (rand() % 3);
        std::cout << x << " " << y << '\n';
    } while (gameGiven->gameTable[x][y] == 'O' || gameGiven->gameTable[x][y] == 'X'); // select random number and check if ai can place there

    gameGiven->gameTable[x][y] = gameGiven->AI;
    gameGiven->playerTurn = true;
}

void printStatus(XOXgame* gameGiven)
{
    if (gameGiven->result == 1)
    {
        std::cout << "You won!" << '\n';
        gameGiven->running = false;
    }
    else if (gameGiven->result == -1)
    {
        std::cout << "You lose!" << '\n';
        gameGiven->running = false;
    }
    else if (gameGiven->result == 0)
    {
        std::cout << "Its a tie!" << '\n';
        gameGiven->running = false;
    }

    std::cout << "Game by Batuhan Arda" << '\n';
}

void decideWinner(XOXgame* gameGiven)
{
 
    if      (gameGiven->gameTable[0][0] == gameGiven->gameTable[0][1] && gameGiven->gameTable[0][1] == gameGiven->gameTable[0][2])
        gameGiven->gameTable[0][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;

    else if (gameGiven->gameTable[1][0] == gameGiven->gameTable[1][1] && gameGiven->gameTable[1][1] == gameGiven->gameTable[1][2])  // check winners in y diagonal line
        gameGiven->gameTable[1][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;

    else if (gameGiven->gameTable[2][0] == gameGiven->gameTable[2][1] && gameGiven->gameTable[2][1] == gameGiven->gameTable[2][2])
        gameGiven->gameTable[2][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;



    else if (gameGiven->gameTable[0][0] == gameGiven->gameTable[1][0] && gameGiven->gameTable[1][0] == gameGiven->gameTable[2][0])
        gameGiven->gameTable[0][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;

    else if (gameGiven->gameTable[0][1] == gameGiven->gameTable[1][1] && gameGiven->gameTable[1][1] == gameGiven->gameTable[2][1])   // check winners in x diagonal line
        gameGiven->gameTable[0][1] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;
    
    else if (gameGiven->gameTable[0][2] == gameGiven->gameTable[1][2] && gameGiven->gameTable[1][2] == gameGiven->gameTable[2][2])
        gameGiven->gameTable[0][2] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;


    else if (gameGiven->gameTable[0][0] == gameGiven->gameTable[1][1] && gameGiven->gameTable[1][1] == gameGiven->gameTable[2][2])
        gameGiven->gameTable[0][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;
                                                                                                                                     // check winners in crossings
    else if (gameGiven->gameTable[2][0] == gameGiven->gameTable[1][1] && gameGiven->gameTable[1][1] == gameGiven->gameTable[0][2])
        gameGiven->gameTable[2][0] == gameGiven->player ? gameGiven->result = 1 : gameGiven->result = -1;


    if (gameGiven->result == 1 || gameGiven->result == -1) // -1 for losing, 1 for winning
        return;
    

    bool checkTie = true;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (gameGiven->gameTable[i][j] != 'X' && gameGiven->gameTable[i][j] != 'O') // if we have a space which has a number in it, we can still play therefore its not a tie (yet)
                checkTie = false;

    if (checkTie) // if its a tie put 0
        gameGiven->result = 0;
}

int main()
{
    char s;

    do
    { 
        clearTable();
        std::cout << "Choose character X or O :";
        std::cin >> s; 
        s = toupper(s);
    }
    while (s != 'X' && s != 'O');
    // ^^ get the character player wants to play, and then uppercase it just in case
    

    XOXgame game(true, s);
    drawTable(&game);

    while (game.running == true)
    {
        if (game.playerTurn)
            playPlayer(&game);
        else
            playAI(&game);

        drawTable(&game);
        decideWinner(&game);
        printStatus(&game);
    }

    return 0;
}
