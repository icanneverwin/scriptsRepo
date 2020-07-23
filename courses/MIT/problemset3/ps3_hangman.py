# Hangman game
#

# -----------------------------------
# Helper code
# You don't need to understand this helper code,
# but you will have to know how to use the functions
# (so be sure to read the docstrings!)

import random
import string

WORDLIST_FILENAME = "E:\work\code\MIT\problemset3\words.txt"

def loadWords():
    """
    Returns a list of valid words. Words are strings of lowercase letters.
    
    Depending on the size of the word list, this function may
    take a while to finish.
    """
    print("Loading word list from file...")
    # inFile: file
    inFile = open(WORDLIST_FILENAME, 'r')
    # line: string
    line = inFile.readline()
    # wordlist: list of strings
    wordlist = line.split()
    print("  ", len(wordlist), "words loaded.")
    return wordlist

def chooseWord(wordlist):
    """
    wordlist (list): list of words (strings)

    Returns a word from wordlist at random
    """
    return random.choice(wordlist)

# end of helper code
# -----------------------------------

# Load the list of words into the variable wordlist
# so that it can be accessed from anywhere in the program
wordlist = loadWords()

def isWordGuessed(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: boolean, True if all the letters of secretWord are in lettersGuessed;
      False otherwise
    '''

    lcLettersGuessed = []
    # lettersGuessed to lowercase
    for i in lettersGuessed:
      lcLettersGuessed.append(i.lower())

    for char in secretWord.lower():
      if char not in lcLettersGuessed:
        return False

    return True



def getGuessedWord(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters and underscores that represents
      what letters in secretWord have been guessed so far.
    '''

    lcLettersGuessed = []
    # lettersGuessed to lowercase
    for i in lettersGuessed:
      lcLettersGuessed.append(i.lower())

    vList = []
    for char in secretWord.lower():
      if char not in lcLettersGuessed:
        vList.append('_ ')
      else:
        vList.append(char)

    return ''.join(vList)


def getAvailableLetters(lettersGuessed):
    '''
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters that represents what letters have not
      yet been guessed.
    '''
    lcLettersGuessed = []
    # lettersGuessed to lowercase
    for i in lettersGuessed:
      lcLettersGuessed.append(i.lower())


    vList = []

    for char in string.ascii_lowercase:
      if char not in lettersGuessed:
        vList.append(char)
    
    return ''.join(vList)
    

def hangman(secretWord):
    '''
    secretWord: string, the secret word to guess.

    Starts up an interactive game of Hangman.

    * At the start of the game, let the user know how many 
      letters the secretWord contains.

    * Ask the user to supply one guess (i.e. letter) per round.

    * The user should receive feedback immediately after each guess 
      about whether their guess appears in the computers word.

    * After each round, you should also display to the user the 
      partially guessed word so far, as well as letters that the 
      user has not yet guessed.

    Follows the other limitations detailed in the problem write-up.
    '''
    print('Welcome to the game, Hangman!')
    print(f'I am thinking of a word that is {len(secretWord)} letters long')

    guess_count = 8
    lettersGuessed = []

    def isLetterGuessed(charGuessed, secretWord):
      if charGuessed.lower() in secretWord.lower():
        return True
      else:
        return False

    while guess_count > 0:
      print('-----------------------------------------------')
      print(f'You have {guess_count} guesses left.')
      print(f'Available letters: {getAvailableLetters(lettersGuessed)}')

      # get user input
      charGuessed = input('Please guess a letter: ')

      # if user already guessed that letter
      if charGuessed in lettersGuessed:
        print("Oops! You've already guessed that letter:", getGuessedWord(secretWord, lettersGuessed))

      # if user guessed and it's a new letter
      elif isLetterGuessed(charGuessed, secretWord):
        lettersGuessed.append(charGuessed)
        print('Good guess:', getGuessedWord(secretWord, lettersGuessed))
      # if user has not guessed
      else:
        print('Oops! That letter is not in my word:',  getGuessedWord(secretWord, lettersGuessed))
        guess_count -= 1
        if guess_count == 0:
          print('-----------------------------------------------')
          print(f'Sorry, you ran out of guesses. The word was {secretWord}.')



      # when the word has been guessed
      if isWordGuessed(secretWord, lettersGuessed):
        print('-----------------------------------------------')
        print('Congradulations, I won')
        break
      
      




if __name__ == "__main__":

  #secretWord = 'apple'
  #lettersGuessed = ['i', 'a', 'c', 'l', 'k', 'p', 'r', 's']
  #print(isWordGuessed(secretWord, lettersGuessed))
  #print(getGuessedWord(secretWord, lettersGuessed))
  #print(getAvailableLetters(lettersGuessed))
# When you've completed your hangman function, uncomment these two lines
# and run this file to test! (hint: you might want to pick your own
# secretWord while you're testing)

  secretWord = chooseWord(wordlist).lower()
  hangman(secretWord)
