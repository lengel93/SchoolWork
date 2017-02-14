#include "gameboard.h"
#include <iostream>
using namespace std;

int Gameboard::balance;
linklist Gameboard::list;
std::string Gameboard::word;
std::string Gameboard::category;
char Gameboard::guessedWord[60];
std::map<std::string, Graphics> Gameboard::imageMap;
char Gameboard::guessedLetters[26];
int Gameboard::spanValue;
int Gameboard::badGuesses;
bool Gameboard::loseTurn;
bool Gameboard::youWon;
bool Gameboard::bankrupt;


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function is the constructor for the Gameboard, from saving the
* category, and the linked list, to loading the images into the file.
*
*****************************************************************************/
Gameboard::Gameboard(){
  if(word == "")
  {
    loadImages();
    drawBackground();
    bool wordSet = false;
    while(!wordSet)
    {
      wordSet = setWordFromBank(word,category,list);
      if(wordSet)
        wordSet = drawWord(word);
    }
    guessedLetters[0] = '\0';
    guessedWord[0]='\0';
    balance = 0;
    spanValue = 0;
    badGuesses = 0;
    youWon = false;
  }
  else
 
  {
      drawBackground();
      drawWord(word);
  }
  drawLetters();
  drawCat();
  drawGuesses();
  drawBalance();
  landedOn();
  drawEnterGuess();
  Popup();
}


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function checks if the user guessed the word correctly, using Glut and
* the keyboard inputs
*
*****************************************************************************/
void Gameboard::drawEnterGuess()
{
  glRasterPos2i( 60, 70 );
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  char guessStr[24] = "Enter guess: ";
  for(int i = 0; i < (int)strlen(guessStr); i++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
  }
  for(int j = 0; j < (int)strlen(guessedWord); j++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessedWord[j]);
  }
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function takes in the char letter that was guessed, and checks it
* agsint the word. If incorrect then it adds 1 to the badGuesses. 
*
* @param[in]      letter- The letter to check
*****************************************************************************/
void Gameboard::letterEnterGuess(char letter)
{
  int len = strlen(guessedWord);
  if(letter == 13 && badGuesses < 3 && youWon != true)
  {
    string str(guessedWord);
    string wordlower = word;
    transform(wordlower.begin(), wordlower.end(), wordlower.begin(), ::tolower);
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str.compare(wordlower) != 0)
    {
      badGuesses++;
      guessedWord[0]='\0';
    }
    else
    {
      youWon = true;
    }
  }
  else if(letter == 127 && len > 0)
  {
    guessedWord[len-1] = '\0';
  }
  else if(len < 59){
    guessedWord[len] = letter;
    guessedWord[len + 1] = '\0';
  }
 
}


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function draws the guesses box using the bitmap on Glut.
*
*****************************************************************************/
void Gameboard::drawGuesses()
{
  glRasterPos2i( 60, 100 );
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  char guessStr[24] = "Missed Guesses: ";
  for(int i = 0; i < (int)strlen(guessStr); i++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
  }
  for(int j = 0; j < badGuesses; j++){
    glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'x');
  }

}


/**************************************************************************//**
* @author Samuel Patzer, Lyndon Engel
*
* @par Description:
* This function first checks to see if the the linked list has been filled with
* the catagorys and answers. If it hasnt it fills the list. It then randomly
* selects a catagory and answer then sets them to cat and puzzle. After that
* is done the it then removes that node from the list so it is not repeated. 
*  
*
* @param[in]      cat	 - Category name
* @param[in]      puzzle - Answer name
* @param[in]      list   - linked list
* @returns        true	 - If file filled and catagory/answer selected
* @returns	  false	 - If file isnt found
*****************************************************************************/
bool Gameboard::setWordFromBank(std::string &puzzle,std::string &cat,linklist &list)
{

    string ans;
    ifstream fin;
    int len = 0;
    int i = 0;

    //checks if the list has been filled yet, otherwise fills list
    if(list.is_empty()==true)
    {
        fin.open("games.dat");
        if(!fin)
        {
            cout<<"file not found"<<endl;
            return false;
        }

        list.insert(fin);
        fin.close();
    }
   
    //selects a random category and answer
    list.select(cat, ans, list);

    //removes the category and answer from the list
    list.remove(cat,ans);

    len = ans.size();
    //removes punctionation from answer
    for (i = 0;i < len; i++)
        {
            if (ispunct(ans[i]))
            {
                    ans.erase(i--, 1);
                   len = ans.size();
            }
        }
       
    //sets puzzle to the answer
    puzzle = ans;
    return true;
}

/**************************************************************************//**
* @author Samuel Patzer, Jake Miller
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      cat	- Category name
* @param[in]      ans	- Answer name
* @returns        true	- If node is successfully removed
* @returns		  false	- If node isn't found
*****************************************************************************/
void Gameboard::loadImages(){
    char letter = 'A';
    std::string location = "./resources/Wheel";
    for(int i = 0; i < 26; i++)
    {
        imageMap.insert(std::pair<std::string, Graphics>(std::string(1,letter), Graphics(location+letter+".bmp")));
    letter++;
    }
    imageMap.insert(std::pair<std::string, Graphics>("blank", Graphics(location+"Blank.bmp")));
    imageMap.insert(std::pair<std::string, Graphics>("background", Graphics(location+"Background.bmp")));
    imageMap.insert(std::pair<std::string, Graphics>("spin", Graphics("./resources/Spin.bmp")));
    imageMap.insert(std::pair<std::string, Graphics>("popup", Graphics("./resources/Popup.bmp")));
}


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      cat	- Category name
* @param[in]      ans	- Answer name
* @returns        true	- If node is successfully removed
* @returns		  false	- If node isn't found
*****************************************************************************/
bool Gameboard::drawWord(std::string word)
{
  std::map<std::string, Graphics>::iterator it = imageMap.find("blank");
  Graphics whiteBackground = it->second;
  std::vector<std::string> collection;
  std::stringstream ssin(word);
  std::string temp;
 
  int validRows = 3;
  int count = 0;
  while(ssin.good())
  {
    ssin >> temp;
   
    count += temp.length();
    if(count > 12 && validRows == 3)
    {
        validRows--;
        count = temp.length()+1;
    }
    else if(count > 14 && (validRows == 1 || validRows == 2))
    {
        validRows--;
        count = temp.length()+1;
    }
    else if (count > 12 && validRows==0){
        count = temp.length()+1;
        break;
    } else {
        count++; //Adds space?
    }
    collection.push_back(temp);

  }

  int wordCount=0;
  int prevWordCount=0;
  int letterCount = 0, location = 0, totalLength=0;
  int limit_low = 0;
  int limit_high = 0;
  int offset = 0;
  bool guessed = false;
  for(int i = 3; i >= validRows; i--)
  {
    count = 0;
    letterCount = 0;
    totalLength = 0;
    if(i == 0 || i == 3){limit_low=1; limit_high=13;}
    else{limit_low=0; limit_high=14;}
    while(wordCount < (int) collection.size() && count + (int) collection[wordCount].length() <= (limit_high-limit_low))
    {
      count += collection[wordCount].length() + 1;
      wordCount = wordCount+1;
    }
    count = count -1;
    offset = ((limit_high - limit_low)-count)/2  + limit_low;
   
    location = wordCount-prevWordCount;
    for (int j = limit_low; j < limit_high; j++){
      if(j >= offset && letterCount < count){
        temp = collection[wordCount-location];
        if((unsigned) letterCount == collection[wordCount-location].length() + totalLength)
        {
          totalLength+=collection[wordCount-location].length()+1;
          location--;
        }
        else
        {
          //std::cout << "letter: "<< temp[test-test3] << " word: "<< temp <<std::endl;
          for(int k=0; k<(int)strlen(guessedLetters); k++)
          {
            if(guessedLetters[k] == toupper(temp[letterCount-totalLength])){
              guessed = true;
              break;
            }
          }
          if(!guessed)
            whiteBackground.drawGraphic(j*whiteBackground.imgCols+50+j, i*whiteBackground.imgRows+200 + i);
          else
          {
            guessed = false;
            std::map<std::string, Graphics>::iterator it = imageMap.find(std::string(1,toupper(temp[letterCount-totalLength])));
            Graphics letterGraphic = it->second;
            letterGraphic.drawGraphic(j*letterGraphic.imgCols+50+j, i*letterGraphic.imgRows+200 + i);
          }
        }
        letterCount++;
      }
    }
    prevWordCount = wordCount;
   
  }
  return true;
 
}


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      cat	- Category name
* @param[in]      ans	- Answer name
* @returns        true	- If node is successfully removed
* @returns		  false	- If node isn't found
*****************************************************************************/
void Gameboard::drawLetters()
{
  char letter = 92;
  bool guessed = false;
  bool isVowel = false;
  for (int i = 0; i<7; i++)
  {
    for(int j = 4; j>0; j--)
    {
      switch(letter)
      {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
          isVowel = true;
          break;
        default:
          isVowel = false;
          break;
      }
      for(int k=0; k<(int)strlen(guessedLetters); k++)
      {
        if(guessedLetters[k] == letter){
          guessed = true;
          break;
        }
      }
      if(!guessed && ((isVowel && balance>=250) || !isVowel)){
        std::map<std::string, Graphics>::iterator it = imageMap.find(std::string(1,letter));
        Graphics letterGraphic = it->second;
        letterGraphic.drawGraphic(j*letterGraphic.imgCols + 750 + j, i*letterGraphic.imgRows + 50 + i);
      }
      else{
        std::map<std::string, Graphics>::iterator it = imageMap.find("blank");
        Graphics letterGraphic = it->second;
        letterGraphic.drawGraphic(j*letterGraphic.imgCols + 750 + j, i*letterGraphic.imgRows + 50 + i);
        guessed = false;
      }
      letter--;
    }
  }
}


/**************************************************************************//**
* @author Samuel Patzer, Jake Miller
*
* @par Description:
* This function takes in the name of a category and its answer. It then goes 
* through the linked list looking for the node that contains a matching category
* and answer. Once the node is found it is removed and true is returned. If the
* node isn't found false is returned. 
*
* @param[in]      cat	- Category name
* @param[in]      ans	- Answer name
* @returns        true	- If node is successfully removed
* @returns		  false	- If node isn't found
*****************************************************************************/
void Gameboard::drawBackground()
{
  std::map<std::string, Graphics>::iterator it = imageMap.find("background");
  Graphics background = it->second;
  it = imageMap.find("spin");
  Graphics spin = it->second;
  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 14; i++)
    {
      if((j==0 || j==3)&& (i == 0 || i == 13))
     {

      }
      else
        {
          background.drawGraphic(i*background.imgCols+50+i, j*background.imgRows+200+j);
        }
    }
   
  spin.drawGraphic(11 * spin.imgCols + 75, -1 * spin.imgRows + 215);
}


/**************************************************************************//**
* @author Samuel Patzer, Jake Miller
*
* @par Description:
* This function out puts a fail or a lose a turn or the money you win. All
* The things that can be triggered by the spin.
*
* @returns		  void
*****************************************************************************/
void Gameboard::spin()
{
  if((spanValue == 0 || loseTurn  || bankrupt) && youWon == false ){
    bankrupt = false;
    loseTurn = false;
    int num;
    num = rand() % 12;
    if(num == 0)
      showLoseTurn();
    else if(num == 11)
      showBankrupt();
    else
      spanValue = num*100;
  }
  glutPostRedisplay();
}


/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function uses glitBitmap to pinpoint what was clicked on by the mouse 
*
* @returns	void
*****************************************************************************/
void Gameboard::landedOn()
{
  glRasterPos2i( 640, 125 );
  char guessStr[24] = "You landed on:";
  for(int i = 0; i < (int)strlen(guessStr); i++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
  }
  if(spanValue > 0)
  {
    glRasterPos2i( 670, 100 );
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '$');
    string spanString = to_string(spanValue);
    char *spa = new char[spanString.length()+1];
    strcpy(spa, spanString.c_str());
    for(int i = 0; i < (int)strlen(spa); i++){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, spa[i]);
    }
    delete[] spa;
  } else if (loseTurn)
  {
    glRasterPos2i( 640, 100 );
    char guessStr[24] = "You lose a turn!";
    for(int i = 0; i < (int)strlen(guessStr); i++){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
    }
  } else if (bankrupt)
  {
    glRasterPos2i( 640, 100 );
    char guessStr[24] = "Bankrupt!";
    for(int i = 0; i < (int)strlen(guessStr); i++){
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
    }
  }
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function deals with lose a turn 
*
* @returns		void
*****************************************************************************/
void Gameboard::showLoseTurn()
{
  badGuesses++;
  loseTurn = true;
  //Draw lose turn
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function deals with bankruptcy emptying the wallet and such.
*
* @returns		void
*****************************************************************************/
void Gameboard::showBankrupt()
{
  balance=0;
  badGuesses++;
  bankrupt = true;
  //Draw bankrupt
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function Removes letters as they are guessed, from the options to
* choose from 
*
* @param[in]      letter  - holds the letter to be removed
* @returns	  void
*****************************************************************************/
void Gameboard::guessLetter(char letter)
{
  if(spanValue != 0 && !(letter == 'A' || letter =='E' || letter=='I' || letter =='O' || letter == 'U'))
  {
    int len = 0;
    bool found = false;
 
    len = strlen(guessedLetters);
 
    for(int i = 0; i < len; i++)
    {
      if(letter == guessedLetters[i])
      {
        found = true;
        break;
      }
    }
 
    if(found == false)
    {
      guessedLetters[len] = letter;
      guessedLetters[len + 1] = '\0';
      int numberOfTimes = letterIsPresentCount(letter);
      if(numberOfTimes > 0){
        balance += spanValue*numberOfTimes;
      }
      else{
        badGuesses++;
      }
      spanValue = 0;
    }
    glutPostRedisplay();
  }
  else if((letter == 'A' || letter =='E' || letter=='I' || letter =='O' || letter == 'U') && balance >= 250 && spanValue == 0)
  {
    balance=balance-250;
    int len = 0;
    bool test = false;
 
    len = strlen(guessedLetters);
 
    for(int i = 0; i < len; i++)
    {
      if(letter == guessedLetters[i])
      {
        test = true;
        break;
      }
    }
 
    if(test == false)
    {
      guessedLetters[len] = letter;
      guessedLetters[len + 1] = '\0';
      if (letterIsPresentCount(letter) == 0)
        badGuesses++;
    }
    glutPostRedisplay();
  }
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* Number of present letters
*
* @param[in]      letter- a char array holding the letters for counting
* @returns	  int	- the present count of letters
*****************************************************************************/
int Gameboard::letterIsPresentCount(char letter)
{
  return count(word.begin(), word.end(), letter) + 
	 count(word.begin(), word.end(), tolower(letter));
}

/**************************************************************************//**
* @author Jimmy Hinker
*
* @par Description:
* This function takes draws the category into the top left corner of screen
*
* @returns	void
*****************************************************************************/
void Gameboard::drawCat()
{
  char *Cat = new char[category.length()+1];
  strcpy(Cat, category.c_str());
  glRasterPos2i( 100, 430);
  for(int i = 0; i < (int)strlen(Cat); i++){
    glutBitmapCharacter( GLUT_BITMAP_8_BY_13, Cat[i]);
  }
  delete[] Cat;
}

/**************************************************************************//**
* @author Samuel Patzer
*
* @par Description:
* This function draws the balance of the wallet
*
* @returns		  void
*****************************************************************************/
void Gameboard::drawBalance()
{
  glRasterPos2i( 660, 250 );
  char guessStr[15] = "Balance:";
  for(int i = 0; i < (int)strlen(guessStr); i++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, guessStr[i]);
  }
  glRasterPos2i( 660, 225 );
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '$');
  string balanceString = to_string(balance);
  char *bal = new char[balanceString.length()+1];
  strcpy(bal, balanceString.c_str());
  for(int i = 0; i < (int)strlen(bal); i++){
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, bal[i]);
  }
  delete[] bal;
}

/**************************************************************************//**
* @author Jake Miller
*
* @par Description:
* This function tells the user if he won or lost, displaying an image
* and showing the win or lost.
*
* @returns		void
*****************************************************************************/
void Gameboard::Popup()
{
  char win[15] = "You Won!!!";
  char lose[15] = "You Lost.";

  std::map<std::string, Graphics>::iterator it = imageMap.find("popup");
  Graphics popup = it->second;
  
  
  if(badGuesses == 3)
  {
    popup.drawGraphic(200,200);
    glRasterPos2i( 350, 350 );
    for(int i = 0; i < (int)strlen(lose); i++)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, lose[i]);
  }
  if(youWon)
  {
    popup.drawGraphic(200,200);
    glRasterPos2i( 350, 350 );
    for(int i = 0; i < (int)strlen(win); i++)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, win[i]);
  }
}

/**************************************************************************//**
* @author Jake Miller
*
* @par Description:
* This function displays the Results 
*
* @param[in]      cont	- integer holding the Results thing 
* @returns	  void 
*****************************************************************************/
void Gameboard::Result(int cont)
{
  if(cont == 0)
    exit(1);
  else{
    word = "";
    glutPostRedisplay();
  }
    
}
 

