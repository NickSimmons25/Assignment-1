#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//splits a string into seperate letters and encrypts them using a key inputted into the function. Each letter is "rotated" (ie shifted a certain number of places forward in the alphabet) by a value equal to the inputted key. 

void rotationCipher(char inputText[], int rotationAmount) 
{
  FILE *output;
  output = fopen("output.txt", "w"); //defines for the program the file where the encrypted text will be printed. 
  char outputText[strlen(inputText) + 1]; //defines for the program an array which will store the encrypted text. 
  char letter = 0; //stores each individual letter as it is being shifted. 

  //this loop ensures that the encryption is performed on every letter in the string. 

  for(int x = 0; x < strlen(inputText) + 1; x++) 
  {
    letter = inputText[x]; //stores the letter currently being encrypted in the letter variable. 
    if(letter >= 65 && letter <= 90) //doesnt convert anything that isnt a capital letter).
    {
      letter = letter - 65; //converts the letter to a number between 0 and 25. 
      if(letter > rotationAmount) 
      {
          letter = letter - rotationAmount; //if subtracting the rotation amount from the letter's number value will not produce a negative number, then this decision is executed. 
      }
      else if(letter < rotationAmount) //if subtracting the rotation amount from the letter's number value will produce a negative number, then this decision is executed. 
      {
        letter = (26 - (rotationAmount - letter)); //the produced negative number is added to 26. This means that letters near the start of the alphabet will be converted to numbers near the end of the alphabet. 
      }
      else if(letter == rotationAmount) //in the special case that the letter is equal to the key, the encrypted letter will always equal 0. 
      {
        letter = 0;
      }
      letter = letter + 65; //converts the letter back into an ASCII code which represents a capital letter.
    }
    outputText[x] = letter; //assigns the letter to the outputText array to be sent to the output file. 
  }
  outputText[strlen(inputText)] = '\0'; //ends the output string manually with a null character. 
  fprintf(output, "encrypted text: %s\n", outputText); //prints the output string to the output file. 
}

//splits a string into seperate letters and decrypts them using a key inputted into the function. Each letter is "rotated" (ie shifted a certain number of places forward in the alphabet) backwards by a value equal to the key. 

void decryptRotationFull(char inputText[], int rotationAmount) 
{
  FILE *output;
  output = fopen("output.txt", "w"); //defines for the program the file where the encrypted text will be printed. 
  char outputText[strlen(inputText) + 1]; //defines for the program an array which will store the encrypted text. 
  char letter = 0; //stores each individual letter as it is being shifted. 
  //this loop ensures that the decryption is performed on every letter in the string. 
  for(int x = 0; x < strlen(inputText) + 1; x++) 
  {
    letter = inputText[x]; //stores the letter currently being encrypted in the letter variable. 
    if(letter >= 65 && letter <= 90) //stops space bars and other non letter characters from being decrypted. 
    {
      letter = letter - 64; //converts letter to a number between 1 and 26. 
      if(letter <= (26 - rotationAmount)) //if the letter's value is smaller than the total number of letters in the alphabet - the key, add the value of the key to the letter.  
        letter = letter + rotationAmount;
      else if(letter >= (26 - rotationAmount)) //if the letter's value is larger or equal to the total number of letters in the alphabet - the key, subtract (number of letters - key) from the value for letter. 
        letter = (letter - (26 - rotationAmount));
      letter = letter + 64; //converts the letter from a number between 1 and 26 back to its original ASCII code. 
    }
    outputText[x] = letter;
  }
  outputText[strlen(inputText)] = '\0'; //ends the output string manually with a null character. 
  fprintf(output, "decrypted text: %s\n", outputText); //prints the output string to the output file. 
}

char decryptRotation(int letter, int rotationAmount) //takes a single letter from a string encrytped using the rotation cipher, converts it to a number between 1 and 26 (representing the letters in the alphabet) and decrypts it using its key. Used in the rotation cipher without key function.  
{
  if(letter >= 65 && letter <= 90) //stops space bars and other non letter characters from being decrypted.
    {
      letter = letter - 64; //converts letter to a number between 1 and 26. 
      if(letter <= (26 - rotationAmount)) //if the letter's value is smaller than the total number of letters in the alphabet - the key, add the value of the key to the letter.  
        letter = letter + rotationAmount;
      else if(letter >= (26 - rotationAmount)) //if the letter's value is larger or equal to the total number of letters in the alphabet - the key, subtract (number of letters - key) from the value for letter. 
        letter = (letter - (26 - rotationAmount));
      letter = letter + 64; //converts the letter from a number between 1 and 26 back to its original ASCII code. 
    }
  return letter; //returns the decrypted letter. 
}

//this function takes some input text and applies each of the 25 possible keys to it, producing 25 different paragraphs of text decrypted using the rotation cipher. Each of these paragraphs are analysed individually. The text in each paragraph is broken into individual words, and each of these words is searched for in a document containing 10000 of the most common words in the english language. If the word matches a word in the dictionary, a counter (which is reset for every block of text rotated with a new key) is incremented. The block of text that produces the highest value for the incremented counter (i.e. contains the highest number of correct words) is then printed to the console. 

void rotationNoKey(char inputText[])
{
  int finalKey = 0; //defines a variable which will store the value of the correct key.
  char testArray[strlen(inputText)]; //defines an array which will store each of the 25 possible text combinations as these text combinations are broken into individual words and searched for in the dictionary.
  FILE *fr; //defines the file which will store the dictionary as fr.
  FILE *output; //defines a file where the decrypted text will be written. 
  fr = fopen("Smaller Dictionary.txt", "r"); //opens the dictionary for use in the program. 
  output = fopen("output.txt", "w"); //opens the file where the decrypted text will be written. 
  char testKey = 0; //defines a variable to store the current value of the test key. Will range from 0 - 25 throughout the program. 
  char testWord[30]; //defines a variable to store a word in the sentence as it is being searched for in the dictionary. 
  char finalArray[strlen(inputText)]; //defines a variable which will store the sentence with the highest number of words found in the dictionary file. This value is printed once the program is complete.
  int wordReset = 0; //variable used to reset the testWord variable once it is finished being searched for in the dictionary. 
  int elementOfArray = 0; //stores the value of the index of the current letter being assigned to the testWord array. 
  int elementOfWord = 0; //stores the value of the index of the current letter being assigned to the testWord array, but it is reset at the beginning of each iteration of the loop on line 108. 
  char dictionaryWord[30]; //variable which stores the value of a word from the dictionary as it is being tested against a word from the program. 
  int correctWords = 0; //variable which stores the total value of correct words each version of the output text produced. 
  int correctWordsFinal = 0; //variable which stores the largest value of correct words from a single piece of encoded text. 
    
  for(int x = 0; x < strlen(inputText); x++) //assigns the value of the inputted text to the array which is to be tested by the program and to the final array which will eventually be printed (if it is not replaced by a sentence which contains more words found in the dictionary).
  { 
    testArray[x] = inputText[x]; 
    finalArray[x] = inputText[x];
  }
  for(testKey = 0; testKey < 26; testKey++) //for loop which forces the entire program to repeat 25 times; once for each possible key. 
  {
    correctWords = 0; //resets the variable which stores the number of words found in the dictionary for each piece of text which was decrypted using one of the 25 keys. 
    elementOfArray = 0;
    for(int z = 0; z < strlen(inputText); z++) //decrypts the sentence stored in th test array using the current value of the key. 
      testArray[z] = decryptRotation(inputText[z], testKey);
    if(testArray[strlen(testArray) - 1] == '@') //fixes a bug in which the final value of the test array variable would be an @ symbol. Because it doesn't replace any of the text, the @ symbol is simply replaced with the null character. 
      testArray[strlen(testArray) - 1] = '\0';
    while(testArray[elementOfArray] != '\0') //this while loop splits each of the 25 different decrypted sentences into words and then searches for them in a dictionary. 
    {
      wordReset = 0; 
      while(testArray[elementOfArray] >= 65 && testArray[elementOfArray] <= 90) //produces a word from testArray and then stores it in testWord. The conditions of the initial while loop force it to stop assigning letters to testWord when an ASCII character that is not A - Z is detected. 
      {
        testWord[elementOfWord] = testArray[elementOfArray];
        elementOfArray++; //stores the current letter of the inputtext array that needs to be stored in the testWord array. 
        elementOfWord++; //elementOfWord is reset for each iteration of the loop on line 116, and elementOfArray is only reset for each iteration of the for loop on line 103. This stops the program from outputting the first word in the testArray sentence over and over again i.e. a new word is assigned to testWord for each iteration of the loop on line 116. 
      }
      elementOfArray++; //this makes sure that the next time the loop on line 116 is executed, the element of the testArray array being assigned to the testWord array is a capital letter.
      for(int q = 0; q < sizeof(testWord); q++) //removes all excess spaces in the testWord array which were left by the loop on line 119. 
      {
        if(testWord[q] == ' ')
          testWord[q] = '\0'; 
      } 
      if(testWord[0] != ' ') //stops a word made up of entirely blank space being searched for in the dictionary. Makes the program faster. 
      {
        while(fgets(dictionaryWord, sizeof(dictionaryWord) - 1, fr) != NULL) //loop which tests the word stored in testWord against every word in the smaller dictionary.txt file. Each word is stored in the array dictionaryWord, so that it may be tested against the word stored in testWord. 
        {
          for(int a = 0; a < sizeof(dictionaryWord); a++) //fixes a bug in which the final element of any word read from a file is a new line. This is done by replacing any new line character in the word with a null character. 
          {
            if(dictionaryWord[a] == '\n')
              dictionaryWord[a] = '\0';
          }
          if(strcmp(dictionaryWord, testWord) == 0) //if testWord and dictionaryWord are identical, increment the correctWords counter. 
          {
            correctWords++; 
          }
        }
        rewind(fr); //once the program is finished searching for every word in the dictionary, this line forces it to start from the very first word in the dictionary when it tests another word. 
        while(testWord[wordReset] != '\0') //resets the testWord array by replacing every element it contains with a space character. Some of these spaces are removed when the testWord array is assigned a new word on line 119, and then excess space is removed on line 126.
        {
          testWord[wordReset] = ' ';
          wordReset++;
        }
      }
    elementOfWord = 0; //resets the elementOfWord variable so that when testWord is given a new word, the new letters are added from the first element of the array.
    } 
  if(correctWords > correctWordsFinal) //if the current value of correctWords is larger than the previous largest value of correctWords (stored in correctWordsFinal), reset the value of correctWordsFinal to be the current correctWords value and reassign the final Array to be the current value of the test Array. 
  {
    correctWordsFinal = correctWords;
    for(int r = 0; r < strlen(finalArray); r++)
      finalArray[r] = testArray[r];
    finalKey = testKey;
  }
  }
  fprintf(output, "decrypted text: %s\n", finalArray); //writes the final decrypted text to the output file.  
  fprintf(output, "Key: %d\n", finalKey); //writes the correct key to the output file. 
}

//This function encrypts strings using the substitution cipher. It first splits the string into individual characters. It then takes a character, tests whether or not it is a capital letter and if it is, it is replaced with the corresponding letter found in the cipherkey. 

void encryptSubCipher(char inputText[], char cipherKey[])
{
  FILE *output;
  output = fopen("output.txt", "w"); //defines for the program the file where the encrypted text will be printed. 
  char outputText[strlen(inputText) + 1]; //defines for the program an array which will store the encrypted text. 
  char letter = 0; //stores each individual letter as it is being shifted. 
  //this loop ensures that the decryption is performed on every letter in the string.
  for(int x = 0; x < strlen(inputText) + 1; x++) 
  {
    letter = inputText[x];
    if(letter >= 65 && letter <= 90) //stops anything that isnt a capital letter from being encrypted. 
    {
      letter = letter - 65; //converts the letter to a number between 0 and 25. 
      letter = cipherKey[letter]; //because the key is arranged such that the first letter in the key replaces A, the second replaces B... etc, the value of the input letter corresponds to the index in cipherKey of the letter it will be replaced with during encryption. 
    }
    outputText[x] = letter; //assigns the encrypted letter to the output text array. 
  }
  outputText[strlen(inputText)] = '\0'; //ends the output string manually with a null character. 
  fprintf(output, "encrypted text: %s\n", outputText); //prints the output string to the output file. 
}

//This function decrypts strings using the substitution cipher. It first splits the string into individual characters. It then takes a character, tests whether or not it is a capital letter and if it is, the substitution cipher key is used to determine what the letter was before it was encrypted. 

void decryptSubCipher(char inputText[], char cipherKey[])
{
  FILE *output;
  output = fopen("output.txt", "w"); //defines for the program the file where the decrypted text will be printed. 
  char outputText[strlen(inputText) + 1]; //defines for the program an array which will store the decrypted text. 
  char letter = 0; //stores each individual letter as it is being decrypted. 
  //this loop ensures that the decryption is performed on every letter in the string.
  for(int x = 0; x < strlen(inputText) + 1; x++) 
  {
    char letter = inputText[x];
    int index = 0;
    if(letter >= 65 && letter <= 90) //only decrypt the character if its ascii value lies between 65 and 90. 
    {
      //this for loop uses the formatting of the key to find the original letter. It finds the index of the encrypted letter, which will correspond to the ascii value of the original letter. Once this index value is found, it is stored in the variable index. 
      for(int i = 0; i < 26; i++) 
      {
        if(letter == cipherKey[i])
        {
          index = i;
          break;
        }
      }
      letter = index + 65; //the index is then converted into an ascii value between 65 and 90.      
    }
    outputText[x] = letter; //assigns the decrypted letter to the output text. 
  }
  outputText[strlen(inputText)] = '\0'; //ends the output string manually with a null character. 
  fprintf(output, "decrypted text: %s\n", outputText); //prints the output string to the output file. 
}


//this function converts singular characters from lower case to upper case. 

char caseConverter(char letter)
{
  if(letter >= 97 && letter <= 122) //doesnt convert anything with an ASCII value that doesnt correspond to a lower case letter. 
  {
    letter = letter - 32; //there is always a difference of 32 between the ASCII values of identical upper and lower case letters. 
  }
  return letter; 
}


