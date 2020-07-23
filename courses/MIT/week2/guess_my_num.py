low = 0
high = 100

print(f'Please think of a number between {low} and {high}!')

main_flag = True
usr_input_flag = True

def calc_half(low_num, high_num):
    return int((high_num - low_num) / 2)

# initial guess
guess = calc_half(low, high)

while main_flag:
    
    print(f'Is your secret number {guess}?')

    while True:
        usr_input = input("Enter 'h' to indicate the guess is too high. Enter 'l' to indicate the guess is too low. Enter 'c' to indicate I guessed correctly. ")
        if usr_input == 'h' or usr_input == 'l' or usr_input == 'c':
            break
        else:
            print('Sorry, I did not understand your input.')
            print('Is your secret number', guess, '?')
    if usr_input == 'c':
        print('Game over. Your secret number was:', guess)
        main_flag = False
    elif usr_input == 'h':
        high = guess
        guess = low + calc_half(low, high)
    elif usr_input == 'l':
        low = guess
        guess = low + calc_half(low, high)
