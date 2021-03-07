// Title: Slot Machine
// Author: Kevin Barone
// Date: 06 Mar. 2021

/* Description: 
 * This program will be used to implement a slot machine for the user
 * to play and test their luck. This will also be included in the HackCU - 007
 * hackathon submission for 2021.
 * The user will be asked to "pull the lever" and then three random numbers
 * will be generated. If they match the user wins and gets some money.
*/

#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define SLOTS 3

void displayMachine(string results[]);
int generateRandom(int iteration, int pastRolls[]);
string imageFromRand(int random);
bool isWinner(string results[]);
void updateMoney(int &currMoney, int increase);

int main()
{
    srand(time(NULL));
    string images[SLOTS] = {"   ", "   ", "   "};
    int randomRolls[SLOTS] = {0, 0, 0};
    bool keepPlay = true;
    int amountWon, moneyCount, amountIn;
    string userIn = "";

    cout << "~~~~----~~~~//~~~~----~~~~" << endl
        << " Welcome to CASINO ROYALE" << endl 
        << "~~~~----~~~~//~~~~----~~~~" << endl;

    cout << "How much money do you have? (whole #)" << endl;
    getline(cin, userIn);
    moneyCount = stoi(userIn);

    do 
    {
        cout << "How much do you want to risk? (>= $10)" << endl;
        getline(cin, userIn);
        amountIn = stoi(userIn);

        if (amountIn < 10 || amountIn > moneyCount)
        {
            cerr << "INVALID MONEY IN" << endl;
        }
        else
        {
            displayMachine(images);

            cout << endl << "Press <enter> to pull the lever!" << endl;
            getchar();

            // generating slot results
            for (int i = 0; i < SLOTS; i++)
            {
                randomRolls[i] = generateRandom(i, randomRolls);
                images[i] = imageFromRand(randomRolls[i]);
            }
            
            for (int i = 0; i < 20; i++)
            {
                cout << endl;
            }
            displayMachine(images);

            // different results for if the user won or not
            if (isWinner(images))
            {
                char middleChar = images[0][1];
                switch (middleChar)
                {
                    case '@':   if (images[0] == "@@@")
                                {
                                    cout << "WOW! Big @ Win! You won $600" << endl;
                                    amountWon = 600;
                                }
                                else
                                {
                                    cout << "Nice! You won $200 for this one!" << endl;
                                    amountWon = 200;
                                }
                        break;
                    case '&':   if (images[0] == "&&&")
                                {
                                    cout << "Luck is on your side! You won big & for $450" << endl;
                                    amountWon = 450;
                                }
                                else
                                {
                                    cout << "Not too bad! Didn't win extra but you got your money back!" << endl;
                                    amountWon = 0;
                                }
                        break;
                    case '+':   cout << "Keep on adding that money! You won double the amount you put in for $" << 2 * amountIn << endl;
                                amountWon = 2 * amountIn;
                        break;
                    case '|':   cout << "Straight up dubs only! You won $300" << endl;
                                amountWon = 300;
                        break;
                    case '}':   cout << "Weird coincidence or skill? Either way you won $500" << endl;
                                amountWon = 500;
                        break;
                    case ';':   cout << "Someone's got their eye on the money! You won $700" << endl;
                                amountWon = 700;
                        break;
                    case '$':   if (images[0] == "$$$")
                                {
                                    cout << "EPIC WINSSSSS! You got the jackpot!! That's $" << 5 * amountIn << " to you!" << endl;
                                    amountWon = 5 * amountIn;
                                }
                                else
                                {
                                    cout << "The luck is strong with this one! ;) Lower-level jackpot for $1000" << endl;
                                    amountWon = 1000;
                                }
                        break;
                    default:    cerr << "INVALID IMAGE RETURNED" << endl;
                        break;
                }
            }
            else
            {
                cout << "Unlucky no win! But don't give up, there is still money to be won!" << endl;
                amountWon = -1 * amountIn;
            }

            updateMoney(moneyCount, amountWon);
            cout << "You now have $" << moneyCount << endl << endl;

            if (moneyCount > 0)
            {
                cout << "Would you like to go again? (y/n)" << endl;
                getline(cin, userIn);

                if (userIn == "y" || userIn == "Y")
                {
                    keepPlay = true;
                }
                else
                {
                    keepPlay = false;
                }
            }
        }

    } while (keepPlay && moneyCount > 0);

    return 0;
}

/* This function will display the slot machine.
 * Parameters: results - array of the three slot results
 * Return: none
*/

void displayMachine(string results[])
{
    cout << "  ___________________" << endl
        << " /                   \\" << endl
        << "|     C~A~S~I~N~O     |" << endl
        << "|                     |" << endl
        << "|  [" << results[0] << "] [" << results[1] << "] [" << results[2] << "]  |" << endl
        << "|                     |" << endl
        << "|     R~O~Y~A~L~E     |" << endl
        << "-----------------------" << endl;

    return;
}

/* This function will generate a random number for the slot machine.
 * Parameters: none
 * Return: randomNum - number randomly generated
*/

int generateRandom(int iteration, int pastRolls[])
{
    int randomNum;

    randomNum = rand() % 10 + 1; // generate random number between 1 and 10
    
    if (iteration > 0)
    {
        if (iteration == 2 && pastRolls[iteration - 2] == pastRolls[iteration - 1])
        {
            randomNum = rand() % 3;
            randomNum = pastRolls[iteration - 1] - randomNum;
        }
        else
        {
            if (pastRolls[iteration - 1] > 5)
            {
                randomNum = rand() % 5 + 6;
            }
            else
            {
                randomNum = rand() % 5 + 1;
            }
        }
    }
    return randomNum;
}

/* This function will return the slot image to be displayed based on the
 * random numbers generated.
 * Parameters: random - randomly generated number
 * Return: image - string to return for display
*/

string imageFromRand(int random)
{
    string image;

    switch (random)
    {
        case 1: image = " @ ";
            break;
        case 2: image = " & ";
            break;
        case 3: image = " + ";
            break;
        case 4: image = "|||";
            break;
        case 5: image = "&&&";
            break;
        case 6: image = "@@@";
            break;
        case 7: image = "-}{";
            break;
        case 8: image = "/;)";
            break;
        case 9: image = "~$~";
            break;
        case 10: image = "$$$";
            break;
        default: image = "   ";
                cerr << "INVALID NUMBER GENERATED" << endl;
            break;
    }

    return image;
}

/* This function will return true if the user won money and false if not
 * Parameters: results - array of the three slot results
 * Return: userWon - whether the user won or not
*/

bool isWinner(string results[])
{
    bool userWon = false;

    for (int i = 0; i < SLOTS - 1; i++)
    {
        if (results[i] == results[i + 1])
        {
            userWon = true;
        }
        else
        {
            return false;
        }
    }

    return userWon;
}

/* This function will update the amount of money the user has currently.
 * Parameters: currMoney - current user money amount (reference), increase - money won or lost
 * Return: none
*/

void updateMoney(int &currMoney, int increase)
{
    currMoney += increase;

    return;
}
