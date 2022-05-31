//
// Created by eslam on 4/1/22.
//

#include "hillcypher.h"

//constructor takes key and put in into key
//then call getKeyInverse
//by Eslam
Hill::Hill(int k[3][3])
{
    for (int i = 0; i < 3; ++i)    //loop to got through the rows
    {
        for (int j = 0; j < 3; ++j)  //loop to got through the cols
        {
            key[i][j] = k[i][j]; //i is the row index, j is the column index
        }
    }
    getKeyInverse();//to generate the inverse key
}

//constructor generate random key
//then call getKeyInverse
//by Eslam
Hill::Hill()
{
    generateKey();//function generates key
    getKeyInverse();//to generate the inverse key
}

/*function set the key  */
void Hill::setKey(int k[3][3])
{
    for (int i = 0; i < 3; ++i)   //loot to got through the rows
    {
        for (int j = 0; j < 3; ++j)  //loot to got through the cols
        {
            key[i][j] = k[i][j];//go through the key digits and put the passed key digits, i is the row index, j is the column index
        }
    }
    getKeyInverse();
}

//get the determinant of the matrix
int Hill::determinant() const  //pass matrix of 3*3
{
    //int result = 0;//put the determinant int result variable
    //use the first row to calculate the determinant,
    //sum of  the subs determinant multiplied by row element with sign[+ - +]
    int sub_det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]),//sub determinant 2*2 * cof[0][0]
        sub_det1 = key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]),//sub determinant 2*2 cof[0][1]
        sub_det2 = key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);//sub determinant 2*2 cof[0][2]
    return sub_det - sub_det1 + sub_det2;//return the result
}

bool Hill::checkKey() const
{
    /*the key must have inverse and the elements of the key must be relatively prime with 26*/

    int det = determinant();

    det = mod(det);
    if(det == 0)
        return false;//no inverse for the key cause the determinant is 0

    //multiplicative inverse check
    else
    {
        det = mod(det, true);
        if(det % 2 == 0 || det % 13 == 0)
            return false;
        return true;
    }
}

//function to return the modulus we can't use % due to negative numbers(-7%26=-7)
//find multiplicative inverses (operand1^-1 mod operand2) when inverse is true
int Hill::mod(int operand1, bool inverse, int operand2) const
{
    if(inverse) //if we need multiplicative inverses
    {
        int result = 0;
        for(int i = 1; i < 26; ++i)//iterate over all possibles 1:25
        {
            if((operand1 * i) % operand2 == 1)//if mod*i==1 then it is the multiplicative inverses
            {
                return i;
            }
        }
        return result;
    }
    else
    {
        //if the operand1 in positive just use %
        //else it is negative use % then add one operand to get the smallest positive result
        return operand1 >= 0 ? operand1 % operand2 : (operand1 % operand2) + operand2;
    }
}

/****/
void Hill::string_to_matrix_int(string &text, int maxrows,int**& mat) const
{
    //convert string to matrix
    for(int row = 0; row < maxrows; row++)
        for(int col = 0; col < 3; col++)
            mat[row][col] = text[row*3 + col] - 'a';
}

void Hill::matrix_int_to_string(int**& mat, int maxrows, string& text) const
{
    //make sure text is empty
    text.clear();

    //convert matrix to string
    for(int row = 0; row < maxrows; row++)
        for(int col = 0; col < 3; col++)
            text += mat[row][col] + 'a';
}


void cleanString(string& text)
{
    int Size = text.size();

    //we go backward because after erase the string shrinks and text[i] become out of index
    for(int i =Size-1; i >=0; i--)
    {
        if(text[i] >= 'A' && text[i] <= 'Z')
            text[i] = text[i] + 'a' - 'A';
        if(text[i] < 'a' || text[i] > 'z')
            text.erase(i, 1);
    }
}
