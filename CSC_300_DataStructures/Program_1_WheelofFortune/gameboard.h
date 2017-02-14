/**************************************************************************//**
* @file
*****************************************************************************/
#include "DrawFunctions.h"
#include "linkedlist.h"
#include <map>
#include <algorithm>
#include <cstring>

/** @brief Gameboard Class that runs the entire Gameboard*/
class Gameboard : public linklist
{
private:
	static std::map<std::string, Graphics> imageMap;
	static linklist list;
	static bool bankrupt;
	static int spanValue;
    static char guessedLetters[26];
    static bool loseTurn;
    static char guessedWord[60];
    static int balance;
    static std::string word;
    static std::string category;
    void Popup();
    void drawCat();
    bool setWordFromBank(std::string &,std::string &cat,linklist &list);
    bool drawWord(std::string);
    void loadImages();
    void drawBackground();
    void drawLetters();
    void showLoseTurn();
    void showBankrupt();
    void landedOn();
    void drawGuesses();
    void drawBalance();
    void drawEnterGuess();
    int letterIsPresentCount(char);
public:
    static int badGuesses; /*!< contains the number of bad guesses */
    static bool youWon; /*!< is true if the user won his game*/
    Gameboard();
    ~Gameboard(){}
    void guessLetter(char);
    void spin();
    void Result(int);
    void letterEnterGuess(char);
};
