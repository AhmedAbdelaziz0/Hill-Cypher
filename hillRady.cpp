#include "hillcypher.h"


void Hill::generateKey()
{
    srand(time(0));
    while(true)
    {
        //Here the array[3][3] is randomly generated
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
            {
                key[i][j]=rand()%52; //52 It was found to be a little faster through experiments
            }
        if(checkKey())//matrix test
                break;
    }
    getKeyInverse();
}

string Hill::hillEncryption(string &text) const
{
    int textSize = text.size();
    if(textSize % 3 == 1)
        text += "ab";
    else if(textSize % 3 == 2)
        text += "a";

    int maxrows = text.size() / 3;

    int** plain = new int* [maxrows];

    for(int i = 0; i <maxrows; i++)
        plain[i] = new int[3];

    int** cypher = new int* [maxrows];

    for(int i = 0; i <maxrows; i++)
        cypher[i] = new int[3];

    string_to_matrix_int(text, maxrows, plain);

    matMUL(cypher, plain, true, maxrows);
    //mod(cypher)
    for(int row = 0; row < maxrows; row++)
        for(int col = 0; col < 3; col++)
            cypher[row][col] = mod(cypher[row][col]);

    string cypherstring;

    matrix_int_to_string(cypher, maxrows, cypherstring);


    //cleaning
    for(int i = 0; i <maxrows; i++)
        delete[] plain[i];
    delete[] plain;

    for(int i = 0; i <maxrows; i++)
        delete[] cypher[i];
    delete[] cypher;

    return cypherstring;
}

string Hill::hillDecryption(string &text) const
{
    int maxrows = text.size() / 3;

    int** cypher = new int* [maxrows];

    for(int i = 0; i <maxrows; i++)
        cypher[i] = new int[3];

    int** plain = new int* [maxrows];

    for(int i = 0; i <maxrows; i++)
        plain[i] = new int[3];

    string_to_matrix_int(text, maxrows, cypher);

    matMUL(plain, cypher, false, maxrows);

    //mod(plain)
    for(int row = 0; row < maxrows; row++)
        for(int col = 0; col < 3; col++)
            plain[row][col] = mod(plain[row][col]);

    string plainstring;

    matrix_int_to_string(plain, maxrows, plainstring);

    //cleaning
    for(int i = 0; i <maxrows; i++)
        delete[] plain[i];
    delete[] plain;

    for(int i = 0; i <maxrows; i++)
        delete[] cypher[i];
    delete[] cypher;

    return plainstring;
}

/****/
void Hill::printK(bool choise) const
{
    //print key
    if(choise == true)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int col = 0; col < 3; col++)
                cout << key[row][col] << '\t';
            cout << '\n';
        }
    }

    //print keyinv
    else if(choise == false)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int col = 0; col < 3; col++)
                cout << keyinv[row][col] << '\t';
            cout << '\n';
        }
    }
}
