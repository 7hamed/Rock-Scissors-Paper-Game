#include <iostream>
#include <ctime>
using namespace std;

enum enTool { Stone=1 , Paper=2 , Scissors=3 };
enum enWinner { Player=1 , Computer=2 , Draw=3 };

struct stRoundInfo{
    enTool playerChoice;
    enTool computerChoice;
    short roundNumber;
    enWinner roundWinner;
    string roundWinnerName;
};

struct stResultsGame{
    short allGameRounds;
    short playerWinTimes;
    short computerWinTimes;
    short drawTimes;
    enWinner gameWinner;
    string gameWinnerName;
};

string tab(short number)
{
    string t = "";
    for (short i = 0; i < number; i++)
    {
        t = t + '\t';
    }

    return t;
}

short readHowManyRounds()
{
    short numberOfRounds;
    do{
        cout << "enter how many rounds : ";
        cin >> numberOfRounds;
    }while((numberOfRounds < 1) || (numberOfRounds > 10));

    return numberOfRounds;
}

enTool readPlayerChoice()
{
    short number;
    do{
        cout << "enter your choice [ 1-Stone | 2-Paper | 3-Scissors ] : ";
        cin >> number;
    }while((number < 1) || (number > 3));

    return (enTool)number;
}

int randomNumber(int From, int To)
{
    return rand()%(To - From +1) + From ;
}

enTool getComputerChoice()
{
    return (enTool)randomNumber(1, 3);
}

enWinner whoWinTheRound(stRoundInfo roundInfo)
{
    if(roundInfo.playerChoice == roundInfo.computerChoice)
        return enWinner::Draw;
    
    switch (roundInfo.playerChoice)
    {
    case enTool::Paper:
        if(roundInfo.computerChoice == enTool::Scissors)
            return enWinner::Computer;
        break;
    
    case enTool::Stone:
        if(roundInfo.computerChoice == enTool::Paper)
            return enWinner::Computer;
        break;

    case enTool::Scissors:
        if(roundInfo.computerChoice == enTool::Stone)
            return enWinner::Computer;
        break;
    }

    // if the code reach here thats mean not draw, and computer not win
    return enWinner::Player;
    
}

string getWinnerName(enWinner winnerName)
{
    string nameOfWinners[3] = {"Player :)" , "Computer" , "no one :/"};
    return nameOfWinners[winnerName -1];
}

string getToolName(enTool numberOfTool)
{
    string nameOfTool[3] = {"Stone" , "Paper" , "Scissors"};
    return nameOfTool[numberOfTool -1];
}

void setWinnerScreenColor(enWinner roundWinner)
{
    if(roundWinner == enWinner::Player) // screen GREEN
        system("color 2F");
    else if(roundWinner == enWinner::Computer) // screen RED
        system("color 4F");
    else
        system("color 6F"); // when Draw screen YELLOW
}

void showResultsRound(stRoundInfo roundInfo)
{
    setWinnerScreenColor(roundInfo.roundWinner);
    
    cout << "__________Round[" << roundInfo.roundNumber << "] Results__________" << endl;
    cout << "Player choice   : " << getToolName(roundInfo.playerChoice) << endl;
    cout << "Computer choice : " << getToolName(roundInfo.computerChoice) << endl;
    cout << "  Winner name   : " << roundInfo.roundWinnerName << endl;
    cout << "____________________________________" << endl;
}

enWinner whoWonTheGame(stResultsGame resultsGame)
{
    if(resultsGame.playerWinTimes == resultsGame.computerWinTimes)
        return enWinner::Draw;
    
    if(resultsGame.playerWinTimes > resultsGame.computerWinTimes)
        return enWinner::Player;
    else
        return enWinner::Computer;
}

stResultsGame fillResultsGame(short numberOfRounds, short playerWinTimes, short computerWinTimes, short drawTimes)
{
    stResultsGame resultsGame;
    resultsGame.allGameRounds = numberOfRounds;
    resultsGame.playerWinTimes = playerWinTimes;
    resultsGame.computerWinTimes = computerWinTimes;
    resultsGame.drawTimes = drawTimes;
    resultsGame.gameWinner = whoWonTheGame(resultsGame);
    resultsGame.gameWinnerName = getWinnerName(resultsGame.gameWinner);

    return resultsGame;
}

stResultsGame playRounds(short numberOfAllRounds)
{
    stRoundInfo roundInfo;
    short playerWinTimes=0 , computerWinTimes=0 , drawTimes=0 ;
    
    for(short roundNo=1 ; roundNo<=numberOfAllRounds ; roundNo++)
    {
        cout << "  Round " << roundNo << ", Begins" << endl;
        roundInfo.roundNumber = roundNo;
        roundInfo.playerChoice = readPlayerChoice();
        roundInfo.computerChoice = getComputerChoice();
        roundInfo.roundWinner = whoWinTheRound(roundInfo);
        roundInfo.roundWinnerName = getWinnerName(roundInfo.roundWinner);

        showResultsRound(roundInfo);

        // calculate the times of winning
        if(roundInfo.roundWinner == enWinner::Player)
            playerWinTimes ++;
        else if(roundInfo.roundWinner == enWinner::Computer)
            computerWinTimes ++;
        else
            drawTimes ++;
    }

    // after the loop finish -> win times it clear
    stResultsGame resultsGame = fillResultsGame(numberOfAllRounds, playerWinTimes, computerWinTimes, drawTimes);

    return resultsGame;
}

void showGameOver()
{
    cout << tab(3) << "_______________________________" << endl;
    cout << tab(3) << "        +++GAME OVER+++" << endl;
    cout << tab(3) << "_______________________________" << endl << endl;
}

void showFinalResults(stResultsGame theResults)
{
    cout << tab(3) << "__________THE RESULTS__________" << endl;
    cout << tab(3) << "Player  win  times : " << theResults.playerWinTimes << endl;
    cout << tab(3) << "Computer win times : " << theResults.computerWinTimes << endl;
    cout << tab(3) << "Draw  times        : " << theResults.drawTimes << endl;
    cout << tab(3) << "     The Winner is : " << theResults.gameWinnerName << endl;
    cout << tab(3) << "_______________________________" << endl;
}

void resetScreen()
{
    system("cls");
    system("color 0F");
}

void startGame()
{
    char answer;
    do{
        resetScreen();
        stResultsGame finalResultsGame = playRounds(readHowManyRounds());
        showGameOver();
        showFinalResults(finalResultsGame);

        cout << tab(3) << "do you want to play again [y-YES | n-NO] : ";
        cin >> answer;
    }while(answer == 'y');
}

int main(){

    srand((unsigned)time(NULL)); // set random seed

    startGame();

    resetScreen(); // be cuz VS CODE terminal

    return 0;
}