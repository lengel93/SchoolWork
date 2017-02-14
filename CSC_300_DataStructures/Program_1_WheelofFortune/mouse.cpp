/***************************************************************************//**
 * @file
 ******************************************************************************/
#include "mouse.h"
#include <iostream>
#include "gameboard.h"
using namespace std;

/***************************************************************************//**
 * @author Paul Hinker, Jake Miller
 *
 * @date Jan 5, 2016
 *
 * @par Course - 2016
 *
 * @par Description:
 * Process a mouse click event and checks to see if the user clicked
 * in a specific area. If the user did then preform an action.
 *
 * @param[in] button - describes which button was clicked
 * @param[in] state  - describes whether the button went down or up
 * @param[in] x      - the x-coordinate of where the click took place
 * @param[in] y      - the y-coordinate of where the click took place
 ******************************************************************************/

void Mouse::mouseClick(int button, int state, int x, int y)
{
   Gameboard g;

   if (state == GLUT_DOWN)
   {
      if (button == GLUT_LEFT_BUTTON) leftDown = true;
      else if (button == GLUT_RIGHT_BUTTON) rightDown = true;
      downX = x;
      downY = y;
      clicked = 0;
   }
   else if (state == GLUT_UP)
   {
      if (button == GLUT_LEFT_BUTTON)
      {
#ifdef DEBUG
         std::cout << "Left mouse released ";
#endif
         leftDown = false;
         if (abs(x-downX) < 5 && abs(y-downY) < 5)
            clicked |= LEFT_CLICKED;
      }
      else if (button == GLUT_RIGHT_BUTTON)
      {
#ifdef DEBUG
         std::cout << "Right mouse released ";
#endif
         rightDown = false;
         if (abs(x-downX) < 5 && abs(y-downY) < 5)
            clicked |= RIGHT_CLICKED;
      }
#ifdef DEBUG
         std::cout << "[" << x << ", " << y << "]" << std::endl;
#endif

	//total area of letters
	if( ((x >= 791 && x <= 955) && (y >= 80 && y<=465)) && g.badGuesses != 3 && g.youWon != true )
	{
		//letters are split up into rows
		//last row of letters Z and Y
		if(y < 465 && y > 410)
		{
			if(x < 872 && x > 832)
			{
                g.guessLetter('Z');
            }
           
            else if(x < 832 && x > 792)
            {

                g.guessLetter('Y');
                
            }
        }
       //letters U through X
        else if(y < 410 && y > 355)
        {
            if(x < 955 && x > 915)
            {

                g.guessLetter('X');
            }
           
            else if(x < 915 && x > 875)
            {

                g.guessLetter('W');

            }
           
            else if(x < 875 && x > 835)
            {

                g.guessLetter('V');

            }
           
            else if(x < 835 && x > 791)
            {

                g.guessLetter('U');

            }
        }
       //letters Q through T
        else if(y < 355 && y > 300)
        {
            if(x < 955 && x > 915)
            {

                g.guessLetter('T');
            }
           
            else if(x < 915 && x > 875)
            {

                g.guessLetter('S');

            }
           
            else if(x < 875 && x > 835)
            {

                g.guessLetter('R');

            }
           
            else if(x < 835 && x > 791)
            {

                g.guessLetter('Q');

            }
        }
       //Letters M through P
        else if(y < 300 && y > 245)
        {
            if(x < 955 && x > 915)
            {

                g.guessLetter('P');

            }
           
            else if(x < 915 && x > 875)
            {

                g.guessLetter('O');

            }
           
            else if(x < 875 && x > 835)
            {
                g.guessLetter('N');
            }
           
            else if(x < 835 && x > 791)
            {
                g.guessLetter('M');
            }
        }
       //letter I through L
        else if(y < 245 && y > 190)
        {
            if(x < 955 && x > 915)
            {
                g.guessLetter('L');
            }
           
            else if(x < 915 && x > 875)
            {
                g.guessLetter('K');
            }
           
            else if(x < 875 && x > 835)
            {
                g.guessLetter('J');
            }
           
            else if(x < 835 && x > 791)
            {
                g.guessLetter('I');
            }
        }
       //leeters E through H
        else if(y < 190 && y > 135)
        {
            if(x < 955 && x > 915)
            {
                g.guessLetter('H');
            }
           
            else if(x < 915 && x > 875)
            {
                g.guessLetter('G');
            }
           
            else if(x < 875 && x > 835)
            {
                g.guessLetter('F');
            }
           
            else if(x < 835 && x > 791)
            {
                g.guessLetter('E');
            }
        }
       //letters D through A
        else if(y < 135 && y > 80)
        {
            if(x < 955 && x > 915)
            {
                g.guessLetter('D');
            }
           
            else if(x < 915 && x > 875)
            {
                g.guessLetter('C');
            }
           
            else if(x < 875 && x > 835)
            {
                g.guessLetter('B');
            }
           
            else if(x < 835 && x > 791)
            {
                g.guessLetter('A');
            }
        }
    }
    //40 in the x
    //55 in the y

	//activates spin if clicked in this region
	if((x >= 670 && x <= 724) && g.badGuesses != 3 && g.youWon != true)
      {
            if(y >= 299 && y <= 351)
            {
                  g.spin();
            }
      }
	//activates play again at the end of a game
    if((x >= 226 && x<= 350) && (y >= 253 && y <= 292) && (g.badGuesses == 3 || g.youWon == true))
    {
        g.Result(1);
    }
	//activates quit at the end of the game
    if((x >= 450 && x<= 576) && (y >= 255 && y <= 292) && (g.badGuesses == 3 || g.youWon == true))
    {
        g.Result(0);
    }
      downX = -1;
      downY = -1;
   }
}

/***************************************************************************//**
 * @brief
 *    Process a mouse drag event.  This means one or more buttons are in the
 *    down state and the mouse position is moving.
 *
 * @param[in] x - the x-coordinate of the mouse drag event
 * @param[in] y - the y-coordiante of the mouse drag event
 ******************************************************************************/
void Mouse::mouseDrag(int x, int y)
{
   if (leftDown && rightDown)
   {
#ifdef DEBUG
      std::cout << "Dragging left and right\n";
#endif
   }
   else if (leftDown)
   {
#ifdef DEBUG
      std::cout << "Dragging left\n";
#endif
   }
   else if (rightDown)
   {
#ifdef DEBUG
      std::cout << "Dragging right\n";
#endif
   }
}
