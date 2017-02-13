package Parser;

import java.util.*;

/**
 * This class holds all the grammar functions. For checking whether the grammar
 * of the users expression is correct or not
 * @author Lyndon Engel
 */
public class Grammar
{
    /**
     * Global string that holds the expression
     */
    protected String expression;   
	
    /**
     * Global string that holds the original expression just in case the other
     * gets changed at all
     */
    protected String oExpression;

    /**
     * Fills the expression strings
     * @param s string that holds expression
     */
    public Grammar( String s )
    {
	expression = s;
	oExpression = s;
    }

    /**
     * Prints out whether the expression is valid or not 
     */
    public void testGrammar()
    {
	boolean grammarFlag = false;
        if( expr( expression ) )
	{
	    System.out.println("\"" + oExpression + "\" is a valid expression");
	}
	else
	{
	    System.out.println("\"" + oExpression + "\" is not a valid expression");
	}
    }
    
    /**
     * Checks if the expressions format is correct. It does this by first 
     * looking for addops in the expression and if they are in the correct
     * location it sets the exprFlag to true otherwise it stays false. It will
     * then run the term function to see if the terms are correct.
     * @param s string that holds expression
     * @return true or false
     */
    public boolean expr( String s )
    {
	boolean exprFlag = false;
        String[] arr;       
 
        if( s.charAt(0) == '+' )
	    return false; 
 
	//test for negitive, remove negitive
	if( s.charAt(0) == '-' )
	{
	    s = s.substring(1,s.length());
	}

	char op = getOp( s );
	
	// test for operator
	if( (op == '+' || op == '-') )
	{
            //check to see if another term is added
	    switch(op)
	    {
		case '+':
		    arr = s.split("\\+",2);
		    if( isAddop(getOp(arr[1])) == true && expr(arr[1]) == true )
		    {
			exprFlag = true;
		    } 
		    else if( term(arr[0]) == true && term(arr[1]) == true)
		    {
			exprFlag = true;
                    }
		    break;
		case '-':
		    arr = s.split("\\-",2);
		    if( isAddop(getOp(arr[1])) == true && expr(arr[1]) == true )
		    {
			exprFlag = true;
		    }
		    else if( term(arr[0]) == true && term(arr[1]) == true)
                    {
			exprFlag = true;
		    }
	            break;
	    }
	}
	else
	{
	   //call factor
	   exprFlag = term( s );
	}
	
	return exprFlag;
    }
	
    /**
     * Checks whether the grammar of the term is correct. It does this by 
     * first checking if the term starts with mulop, if it does then it 
     * returns false. Else it will check if there is another term. It will
     * then run the factor function to make sure those are correct. If it
     * passes all those tests it will then return true. 
     * @param s string that holds expression
     * @return true or false
     */
    public boolean term( String s )
    {
	boolean termFlag = false;
	char op = getOp( s );
	String[] arr;

	if( isMultop(s.charAt(0)))
		return false; 

	if ( op == '*' || op == '/' || op == '%' )
	{
	// see if nother term
	    switch(op)
	    {
		case '*':
		     arr = s.split("\\*",2);
		     if( isMultop(getOp(arr[1])) == true && term(arr[1]) == true )
		     {
			termFlag = true;
		     } 
		     if( factor(arr[0]) == true && factor(arr[1]) == true)
		     {
			termFlag = true;
		     }
		    break;
		case '/':
		    arr = s.split("\\/",2);
	             if( isMultop(getOp(arr[1])) == true && term(arr[1]) == true )
		     {
			termFlag = true;
		     }
		     if( factor(arr[0]) == true && factor(arr[1]) == true)
		     {
			termFlag = true;
		     }
		    break;
	    	case '%':
		     arr = s.split("\\%",2);
		     if( isMultop(getOp(arr[1])) == true && term(arr[1]) == true )
		     {
			termFlag = true;
		     }
                     if( factor(arr[0]) == true && factor(arr[1]) == true)
		     {
			termFlag = true;
		     }
	            break;
	    }
	}
	else
	{
	//call to factor
	    termFlag = factor( s );
	}
	return termFlag;
    }
	
     /**
     * Checks if the grammar of factor is correct. It does this by running the 
     * isInteger, ifFloat, and id functions. If it passes one of those it 
     * returns true. If not it then checks if the factor is a parentheses if it
     * is it then it runs the expression function on the substring inside the
     * parentheses to check if its true. If it passes all those tests it returns
     * true.
     * @param s string that holds expression
     * @return true or false
     */
    public boolean factor( String s)
    {
	int fo, lo;
	String sub, rest = "";

	boolean factorFlag = false;
	char op = getOp(s);
	if( isInteger( s ) )
	{
	    factorFlag = true;
	}
        else if( isFloat( s ) )
	{
	    factorFlag = true;
	}
	else if( id( s ) )
        {
	    factorFlag = true;
        }
        else if( op == '(' )
	{
	    int count = 0;
	    if( s.charAt(0) != '(' )
		return false;
	
	    for( int i = 0; i < s.length(); i++)
	    {
		//find beginning and end
		if( s.charAt(i) == '(' )
		{
		   count++;
		}
		else if( s.charAt(i) == ')' )
		{
		    count--;
		}

                //if the end is found it is an expression
		if( s.charAt(i) == ')' && count == 0 )
		{
		    try{
		    fo = s.indexOf("(");
		    lo = i;
		    System.out.println("end peren at: " + i);
		    sub = s.substring(fo + 1, lo);
		
		    if( lo != s.length() )
		    rest = s.substring(lo+1, s.length() );

	            }catch (StringIndexOutOfBoundsException e){
		        return false;
	            }
		
		    if( expr( sub ) == true ) 
	            {
			
			if( !rest.isEmpty() )
			{
			    if( isMultop( rest.charAt(0) ) == true || isAddop( rest.charAt(0) ) == true )
			    {
				rest = rest.substring(1, rest.length() );
				if( expr( rest ) == true )
				    return true;
			    }
			    return false;
			}
			return true;
			
		    }
		    break;
                }
	    }
	}
	else if( s.charAt(0) == '-' )
	{
	    sub = s.substring(1 , s.length() );
	    factorFlag = factor( sub );
	}
	return factorFlag;
    }

    /**
     * Checks if the id is valid. It does this by first checking if the starting
     * character is a letter. If it is then it continues to make sure the rest 
     * of the string contains letters and digits. It will then return true or 
     * false depending on if it passed all the tests.
     * @param s string that holds expression
     * @return true or false
     */
    public boolean id(String s)
    {
	System.out.println( " in id: " + s );
        boolean lFlag = false;
	boolean dFlag = false;   
	char d = 0;
        int o = 0;
	
	if( isLetter(s.charAt(0)) == false)
	{
	    return false;
        } 
	for( int i = 0; i < s.length(); i++)
        {
	    lFlag = isLetter(s.charAt(i));
	   
            try{
                d = s.charAt(i);
		o = Integer.parseInt(s.valueOf( d ));
		dFlag = isDigit( o );
            } catch (NumberFormatException e){
	    }

	    if( dFlag == false && lFlag == false)
	    {
		return false;
            }
	}	

	//test rest to make sure int or letter
	return true;
    }

    /**
     * Checks if the string contains only digits. 
     * @param s string that holds expression
     * @return true or false
     */
    public boolean isInteger(String s)
    {
        boolean intFlag = false;
        int d;
	char c;

	for( int i = 0; i < s.length(); i++ )
        {
            try{
	       c = s.charAt(i);
               d = Integer.parseInt(s.valueOf( c ));
	       intFlag = isDigit( d );
            } catch (NumberFormatException e){
	    return false;
	    }
	    if( intFlag == false )
		return false;
	}
       
       return intFlag;
    }
 
    /**
     * Checks if the character is a letter using regex. 
     * @param c character in expression being checked
     * @return true or false
     */
    public boolean isLetter(char c)
    {
	return (Character.toString(c).matches("[a-zA-Z_]"));
    }
 
    /**
     * Checks if the vale is a digit of 0-9 using regex.
     * @param i digit in expression being checked
     * @return true or false
     */
    public boolean isDigit(int i)
    {
	return (Integer.toString(i).matches("[0-9]"));
    }

    /**
     * Checks if the string is a float. It does this by splitting the string 
     * at the '.' and then checking if both sides are integers. 
     * @param s string of expression
     * @return true or false
     */
    public boolean isFloat(String s)
    {

	String arr[] = s.split("\\.");
	boolean floatFlag = false;
	try{
	if( isInteger(arr[0]) && isInteger(arr[1]) )
	{
	    floatFlag = true;	
	}} catch (ArrayIndexOutOfBoundsException e){
		return false;
	}
	return floatFlag;
    }
    
    /**
     * returns the operator at a point in the string
     * @param segment segment of the expression
     * @return true or false
     */
    public char getOp(String segment)
    {

        for(int i = 0; i < segment.length(); i++)
        {
	    switch( segment.charAt(i) )
	    {
		case '+':
		    return '+';
		case '-':
		    return '-';
		case '*':
		    return '*';
		case '/':
		    return '/';
		case '%':
		    return '%';
		case '(':
		    return '(';
		case ')':
		    return ')';
	    }
	    
        }
	
	return 'x';
    }
	
    /**
     * Checks if the character is a '+' or '-' using regex matches. 
     * @param c character being checked
     * @return true or false
     */
    public boolean isAddop(char c)
    {
    	return (Character.toString(c).matches("[+-]"));
    }	  
    
    /**
     * Checks if the character is a '*' , '/' , or '%' using regex matches. 
     * @param c character being checked
     * @return true or false
     */
    public boolean isMultop(char c)
    {
	return (Character.toString(c).matches("[*/%]"));
    }
   
}


