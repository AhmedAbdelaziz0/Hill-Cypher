#ifndef hillcypher_h
#define hillcypher_h
#include <cstdlib> //for rand
#include <time.h> //for rand
#include <iostream>
#include <string>
#include <conio.h> //for interact function
using namespace std;

//3
void Interact();
void cleanString(string& text);

class Hill
{
private:
    int key[3][3];
    int keyinv[3][3];


public:
    // 1
    //construct identity matrix key     //there is no reason for choosing identity matrix
    Hill();

    // 1
    //construct with the key k
    Hill(int k[3][3]);

    // 1
    //set key from the user input
    void setKey(int k[3][3]);

    // 1
    //calculate the determinant and return it
    int determinant() const;

    // 1
    //check if the key determinant is non-zero and relatively prime to 26
    bool checkKey() const;


    // 1
    //return the modulus of operand1 whither it is positive or negative
    //if isDevisor is true ... (1/9)mod 26 = 3 // where oprand1 = 9
    int mod(int operand1, bool isDevisor = false, int oprand2 = 26) const;


    // 2
    //this will randomly generate a key
    //use checkKey() method to validate the key
    //use getKeyInverse() method to get the inverse
    void generateKey();

    // 2
    //use the key to encrypt the text and return the encrypted text
    string hillEncryption(string &text)const;

    // 2
    //use the keyinv to decrypt the text and return the decrypted text
    string hillDecryption(string &text)const;


    // 3
    //get the inverse of key[3][3] and store it in keyinv[3][3]
    //calculate the keyInverse using adjoint
    void getKeyInverse();

    //3
    //print key or keyinv
    //true for key
    //false for keyinv
    void printK(bool KEY = true) const;

    // 3
    //multiply the plain text with the key or the cyphered text with keyinv
    //if useKey is false use keyinv
    void matMUL(int**& res, int**& op1, bool isKey, int maxrows) const;


    void string_to_matrix_int(string &text, int maxrows, int**& mat) const;

    void matrix_int_to_string(int**& mat, int maxrows, string &text) const;



};

#endif // hillcypher_h
