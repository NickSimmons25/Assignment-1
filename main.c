#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Cipher.h>
#include "mode.h"


int main() 
{
  FILE *input;
  FILE *output;  
  input = fopen("Input.txt", "r"); //opens the input file under the name input. 
  output = fopen("output.txt", "w"); //opens the output file under the name output. 
  char inputText[1000]; //defines an array which stores the text inputted into the program. 
  char spareInput[1000]; //defines an array which is assigned text from the input file which is not going to be used in the program. It only exists to move the fscanf pointer further down the input page. 
  char substitutionKey[100]; //defines an array which stores the substitution key. 
  int rotationKey = 0; //defines an array which stores the rotation key. 
  int mode = MODE; //defines an array which stores the value of the definition from the mode.h header file. 
  fgets(spareInput, 1000, input); //skips the first line of inputText.
  fgets(inputText, 1000, input); //reads the value of the input text from input.txt.
  inputText[strcspn(inputText, "\n")] = 0; //removes the newline character which is automatically added to the end of each string read using fgets. 
  fgets(spareInput, 1000, input); //skips the third line of inputText.
  //this loop converts all lower case text into upper case so that it may be understood by the encryption/decryption functions. 
  for(int x = 0; x < strlen(inputText) + 1; x++) 
    inputText[x] = caseConverter(inputText[x]);
  if(mode == 0) //executes the rotation encryption function if the user inputs mode 0 in the header file. 
  {
    fscanf(input, "%d", &rotationKey); //reads the rotation key. 
    rotationCipher(inputText, rotationKey);
  }
  else if(mode == 1) //executes the rotation decryption function (with key) if the user inputs mode 1 in the header file.
  {
    fscanf(input, "%d", &rotationKey); //reads the rotation key. 
    decryptRotationFull(inputText, rotationKey);
  }
  else if(mode == 2) //executes the rotation decryption function (without key) if the user inputs mode 2 in the header file.
  {
    rotationNoKey(inputText);
  }
  else if(mode == 3) //executes the substitution encryption function if the user inputs mode 3 in the header file.
  {
    fgets(substitutionKey, 100, input); //reads the substitution key. 
    substitutionKey[strcspn(substitutionKey, "\n")] = 0; //removes the fgets newline character from the end of the key. 
    encryptSubCipher(inputText, substitutionKey);
  }
  else if(mode == 4) //executes the substitution decryption function if the user inputs mode 4 in the header file.
  {
    fgets(substitutionKey, 100, input); //reads the substitution key.
    substitutionKey[strcspn(substitutionKey, "\n")] = 0; //removes the fgets newline character from the end of the key. 
    decryptSubCipher(inputText, substitutionKey);
  }
  else //outputs an error message if the user inputs a key that isnt listed in the mode file. 
    fprintf(output, "Unknown mode, check mode.h for a list of correct values for mode.");
}
