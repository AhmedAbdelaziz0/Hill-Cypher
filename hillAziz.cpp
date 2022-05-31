#include "hillcypher.h"

// 3
//multiply the plain text with the key or the cyphered text with keyinv
//if useKey is false use keyinv
void Hill::matMUL(int**& res, int**& op1, bool isKEY, int maxrows) const
{
	int K_Kinv[3][3];

    //set res to 0
    for(int i = 0; i < maxrows; i++)
    {
        for(int j = 0; j < 3; j++)
            res[i][j] = 0;
    }

	//transpose key as it is easer to do multiplication that way
	//as we multiply row by row instead of row by column
	if(isKEY == true)
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                K_Kinv[i][j] = key[j][i];
    }
    else
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                K_Kinv[i][j] = keyinv[j][i];
    }

    //C = P*Key
    for(int i = 0; i < maxrows; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            for(int k = 0; k < 3; k++)
                res[i][j] += op1[i][k] * K_Kinv[j][k];
            res[i][j] = mod(res[i][j]);
        }
    }
}

// 3
//get the inverse of key[3][3] and store it in keyinv[3][3]
//this method is called after checkKey method
void Hill::getKeyInverse()
{
    //calculating the inverse matrix of matrix key and store it in keyinv
    for(int row = 0; row < 3; row++)
        for(int col = 0; col < 3; col++)
                /*calculate the minor of key and store it in keyinv*/
                keyinv[row][col] = key[(row+1)%3][(col+1)%3] * key[(row+2)%3][(col+2)%3]
                                                    - key[(row+1)%3][(col+2)%3] * key[(row+2)%3][(col+1)%3];

    //getting the transpose of the matrix
    for(int row = 0; row < 3; row++)
        for(int col = row+1; col < 3; col++)
        {
            //swap([row][col] , [col][row])
            int temp = keyinv[row][col];
            keyinv[row][col] = keyinv[col][row];
            keyinv[col][row] = temp;
        }

    int det = mod(determinant()); //handle the negative values first
    det = mod(det, true);          // then get the multiplicative inverse

    //keyinv % 26
    //keyinv should be positive integers from 0 to 25 after this loop
    for(int row = 0; row < 3; row++)
        for(int col = 0; col < 3; col++)
            keyinv[row][col] = mod(keyinv[row][col] * det);
}

//called in main()
void Interact()
{
    Hill hill;
    char choose;
    cout << "Hill cypher\n" << "[0] Test key\n" << "[1] set key\n" << "[2] generate random key\n";
    choose = getch();
    switch (choose)
    {
    case '0': //test number of keys
        while(true)
        {
            cout << "\nEnter 9 integers: \n";
            int k[3][3];
            for(int row = 0; row < 3; row++)
                for(int col = 0; col < 3; col++)
                    cin >> k[row][col];
            hill.setKey(k);
            if(hill.checkKey())
            {
                cout << "The key is valid\n";
                cout << "Use that Key? (y/n): ";
                choose = getche();
                cout << '\n';
                if(choose == 'y' || choose == 'Y')
                {
                    hill.getKeyInverse();//calculate the key inverse and store it in keyinv
                    break;
                }
                else
                {
                    cout << "\nTry another? (y/n): ";
                    choose = getche();
                    if(choose == 'n' || choose == 'N')
                        break; //break loop
                    else
                        continue;
                }
            }
            else
            {
                cout << "The key is invalid\n";
                cout << "\nTry another? (y/n): ";
                    choose = getche();
                    if(choose == 'n' || choose == 'N')
                        return; //current key is invalid and don't want to enter valid one
                    else
                        continue;
            }
        }
        break; //end case 0

    case '1': //set key by user
        cout << "\nEnter 9 integers: \n";
        int k[3][3];
        for(int row = 0; row < 3; row++)
            for(int col = 0; col < 3; col++)
                cin >> k[row][col];
        hill.setKey(k);
        if(hill.checkKey())
        {
            cout << "The key is valid\n";
            hill.getKeyInverse(); //calculate the key inverse and store it in keyinv
        }
        else
            cout << "The key is invalid\n";
        break;
    case '2':
        //the key and key inverse are generated in the constructor
        hill.generateKey();
        cout << "The generated key is:\n";
        hill.printK(true);
        hill.getKeyInverse();
        break;
    }

    //choose plain text from
    cout << "Enter the text you want to cypher:\n";
    string text;

    while(text.back() != 13) //ASCII for enter key
        text += getche();
    cout << '\n';
    cleanString(text);


    //The encryption part
    text = hill.hillEncryption(text);
    cout << "Encryption:\n";
    cout << text << "\n";

    //The decryption part
    text = hill.hillDecryption(text);
    cout << "Decryption:\n";
    cout << text << "\n";
}
