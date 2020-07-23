import math
from is_sorted import is_sorted
import random
#from matplotlib import pylab as plt
from matplotlib import pyplot as plt
import time

def recurPower(base, exp):
    '''
    base: int or float.
    exp: int >= 0
 
    returns: int or float, base^exp
    '''
    # Your code here
    if exp == 0:
        return 1
    elif exp == 1:
        return base
    else:
        return base*recurPower(base, exp - 1)


def gcdIter(a, b):
    '''
    a, b: positive integers
    
    returns: a positive integer, the greatest common divisor of a & b.
    '''
    # Your code here
    while a % b > 0:
        r = a % b 
        a = b
        b = r
    return b


def gcdRecur(a, b):
    '''
    a, b: positive integers
    
    returns: a positive integer, the greatest common divisor of a & b.
    '''
    # Your code here
    if b == 0:
        return a
    else:
        return gcdRecur(b, (a % b))


def fib(x):
    '''
    x: positive integer
    returns: Fibonacci of x
    '''
    if x == 0 or x == 1:
        return 1
    else:
        return fib(x-1) + fib(x-2)


def isPalindrome(s):
    '''
    s: string to validate
    returns: True if string is palindrome, False if not
    '''
    def toChars(s):
        s = s.lower()
        temp = ''
        for c in s:
            if c in 'abcdefghijklmnopqrstuvwxyz':
                temp = temp + c
        return temp
    
    def isPal(s):
        if len(s) <= 1:
            return True
        else:
            return s[0] == s[-1] and isPal(s[1:-1])
    
    return isPal(toChars(s))


def isIn(char, sortedStr):
    '''
    char: a single character
    sorderStr: an alphabetized string

    returns: True if char is in aStr, False otherwise
    '''

    lenstr = len(sortedStr)
    if lenstr == 0:
        return False
    elif lenstr == 1:
        if char == sortedStr:
            return True
        else:
            return False
    else:
        middle_char = int(lenstr / 2)
        if char == sortedStr[middle_char]:
            return True
        elif char < sortedStr[middle_char]:
            return isIn(char, sortedStr[0:middle_char])
        elif char > sortedStr[middle_char]:
            return isIn(char, sortedStr[middle_char:])



def polysum(n, s):
    '''
    n: int, number of sides
    s: side length

    returns: sum of the area and square of the perimeter of the regular polygon
    '''

    area = (0.25 * n * s**2) / math.tan(math.pi / n)
    P = n * s
    return round(area + P**2, 4)
    

def oddTuples(aTup):
    '''
    aTup: a tuple
    
    returns: tuple, every other element of aTup. 
    '''

    tupLen = len(aTup)
    newTuple = ()

    for i in range(tupLen):
        if i % 2 == 0:
            newTuple = newTuple + (aTup[i],)
        
    return newTuple
    


def how_many(aDict):
    '''
    aDict: A dictionary, where all the values are lists.

    returns: int, how many values are in the dictionary.
    '''
    # Your Code Here
    count = 0
    for key in aDict:
        count = count + len(aDict[key])
    return count


def biggest(aDict):
    '''
    aDict: A dictionary, where all the values are lists.

    returns: The key with the largest number of values associated with it
    '''
    # Your Code Here
    count = 0
    
    for key in aDict:
        if count < len(aDict[key]):
            count = len(aDict[key])
            temp_key = key
            
    return temp_key


def genPrimes():
    
    num = 2
    while True:
        for i in range(2, num):
            if num % i == 0:
                num += 1
                break
        else:
            yield num
            num += 1

#########################################################################
# search and sort algorithms
#########################################################################

# linear search: O(n)
def linear_search(L: list, e) -> bool:
    '''
    L: list in which search is performed
    e: element to be searched
    result: True or False
    '''
    found = False
    for i in range(len(L)):
        if e == L[i]:
            found = True
    return found


# linear search on sorted list: O(n)
def linear_search_sorted(L: list, e) -> bool:
    for i in range(len(L)):
        if L[i] == e:
            return True
        if L[i] > e:
            return False
    return False


# bisection search imp 1: O(nlog(n))

def bisect_search1(L: list, e) -> bool:
    if L == []:
        return False
    elif len(L) == 1:
        return L[0] == e
    else:
        half = len(L) // 2
        if L[half] > e:
            return bisect_search1(L[:half], e)
        else:
            return bisect_search1(L[half:], e)
    

# bisection search imp 2: O(log(n))
def bisect_search2(L: list, e) -> bool:
    def bisect_search_helper(L: list, e, low, high):
        if high == low:
            return L[low] == e
        mid = (low + high) // 2
        if L[mid] == e:
            return True
        elif L[mid] > e:
            if low == mid: # nothing left to search
                return False
            else:
                return bisect_search_helper(L, e, low, mid - 1)
        else:
            return bisect_search_helper(L, e, mid + 1, high)

    if len(L) == 0:
        return False
    else:
        return bisect_search_helper(L, e, 0, len(L) - 1)


# bogo sort (monkey sort / stupid sort / etc.)
# base case O(n), worst - unbounded

def bogo_sort(L: list) -> list:
    while not is_sorted(L):
        random.shuffle(L)
        #print(L)
    #return L


# bubble sort : O(n^2)
def bubble_sort(L: list) -> list:
    swap = False
    while not swap:
        swap = True
        #print(L)
        for j in range( 1, len(L)):
            if L[j-1] > L[j]:
                swap = False
                #temp = L[j]
                #L[j] = L[j-1]
                #L[j-1] = temp
                L[j-1], L[j] = L[j], L[j-1]
    #return L


# selection sort (O(n^2))
def selection_sort(L: list) -> list:
    suffix = 0
    while suffix != len(L):
        for i in range(suffix, len(L)):
            if L[i] < L[suffix]:
                L[suffix], L[i] = L[i], L[suffix]
        suffix += 1
    
    #return L


# merge sort (1st rec lvl = O(n), 2nd rec lvl = O(n))
# overall complexity O(n*log(n))
def merge(left: list, right: list) -> list:
    result = []
    i, j = 0, 0

    while i< len(left) and j < len(right):
        if left[i] < right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    while (i < len(left)):
        result.append(left[i])
        i += 1
    while (j < len(right)):
        result.append(right[j])
        j += 1
    return result


def merge_sort(L:list):
    if len(L) < 2:
        return L[:]
    else:
        middle = len(L) // 2
        left = merge_sort(L[:middle])
        right = merge_sort(L[middle:])
        return merge(left, right)



if __name__ == "__main__":
    print(fib(3))
    print(isPalindrome('eve'))
    print(isPalindrome('Able was I, ere I saw Elbaa'))
    print(isIn('d', 'abdffhlmoopuvvx'))
    print(polysum(5, 3))
    #print(cardbalance(42, 0.2, 0.04))
    #print(cardbalance(484, 0.2, 0.04))
    #print(lowestPayment(3926, 0.2))
    print(oddTuples(('I', 'am', 'a', 'test', 'tuple')))

    animals = { 'a': ['aardvark'], 'b': ['baboon'], 'c': ['coati']}
    animals['d'] = ['donkey']
    animals['d'].append('dog')
    animals['d'].append('dingo')
    print(how_many(animals))
    print(biggest(animals))

    foo = genPrimes()
    foo.__next__()

    L1 = [1, 5, 3, 8, 4, 9, 6, 2]
    bogo_sort(L1)
    print(L1)

    L2 = [2, 7, 5, 9, 1, 3, 8, 4, 6]
    bubble_sort(L2)
    print(L2)

    L3 = [4, 2, 7, 1, 6, 9, 5, 8, 3]
    selection_sort(L3)
    print(L3)

    L4 = [8, 4, 1, 6, 5, 9, 2, 3, 7]
    print(merge_sort(L4))
    print(L4)

    mySample = []
    myLinear = []
    myQuad = []
    myCube = []
    myExp = []


    for i in range(30):
        mySample.append(i)
        myLinear.append(i)
        myQuad.append(i**2)
        myCube.append(i**3)
        myExp.append(1.5**i)
    

    plt.figure('lin')
    # plt.clf()
    plt.title('Linear')
    plt.xlabel('sample points')
    plt.ylabel('linear func')
    #plt.legend()
    plt.ylim(0, 1000)
    plt.plot(mySample, myLinear, 'b-', label='linear', linewidth=2.0)
    plt.show(block=False)
    #time.sleep(60)