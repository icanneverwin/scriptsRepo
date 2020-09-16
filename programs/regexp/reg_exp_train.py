import re
from turtle import st


def re_match(string:str):
    match = re.search(r'[\s]{0}[АВЕКМНОРСТУХ]{1}\d\d\d[АВЕКМНОРСТУХ]{2}[1-9]{2,3}|[АВЕКМНОРСТУХ]{2}\d\d[1-9]{2,3}', rf'{string}')
    print(match[0] if match else 'Not found')


def car_number_rus(string:str):
    private_pattern = '[\s]{0}[АВЕКМНОРСТУХ]{1}\d\d\d[АВЕКМНОРСТУХ]{2}[1-9]{2,3}'
    taxi_pattern = '[АВЕКМНОРСТУХ]{2}\d\d[1-9]{2,3}'

    if re.fullmatch(rf'{private_pattern}', rf'{string}'):
        print('Private')
    elif re.fullmatch(rf'{taxi_pattern}', rf'{string}'):
        print('Taxi')
    else:
        print('Fail')


def find_words(string:str):
    
    #words_pattern = '[а-яА-Я]+' 
    words_pattern = '\w[\w-]*' 
    match = re.findall(rf'{words_pattern}', rf'{string}')

    print(match)
    return len(match)

def time_substr(string:str):
    
    pattern='(?:[0-1][0-9]|2[0-3])(?::[0-5][0-9]){1,2}' # match time HH:MM or HH:MM:SS
    match=re.findall(rf'{pattern}', rf'{string}')
    print(match)
    tbc='(TBC)'

    return re.sub(pattern, tbc, string, count=0)

    

if __name__== "__main__":
    #re_match(' С227НА777')
    #match = re.search(r'\b[АВЕКМНОРСТУХ]{1}\d\d\d[АВЕКМНОРСТУХ]{2}[1-9]{2,3}|\b[АВЕКМНОРСТУХ]{2}\d\d[1-9]{2,3}', r' С227НА777')
    #print(' С227НА777')
    #print(match[0] if match else 'Not found')

    car_number_rus('Т22В7477')

    test_str="""Он --- серо-буро-малиновая редиска!! 
    >>>:-> 
    А не кот. 
    www.kot.ru"""

    test='хех'


    print(find_words(test_str))

    test1_str="""Уважаемые! Если вы к 09:00 не вернёте 
    чемодан, то уже в 09:00:01 я за себя не отвечаю. 
    PS. С отношением 25:50 всё нормально!
    """

    print(time_substr(test1_str))