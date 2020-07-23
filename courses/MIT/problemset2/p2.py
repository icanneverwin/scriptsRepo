def lowestPayment(balance: int, annualInterestRate: int) -> int:
    '''
    balance:            user's current balance
    annualInterestRate: bank's annual rate

    returns: lowest payment required to pay off all debt in inder 1 year
    '''
    monthlyInterestRate = annualInterestRate / 12


    def cardbalance(balance: int, monthlyInterestRate: int, minMonthlyPayment: int) -> int: 
        for i in range(12):

            # unpaid balance in the end of the month
            balance = round(balance - minMonthlyPayment, 2)

            balance = round(balance + (monthlyInterestRate * balance), 2)
            # print(f'Month {i} remaining balance: {balance}')

        return round(balance, 2)
    
    # assume min minMonthlyPayment = 10
    minMonthlyPayment = 10
    while True:
        if cardbalance(balance, monthlyInterestRate, minMonthlyPayment) >= 0:
            minMonthlyPayment += 10
        else:
            break

    return minMonthlyPayment


if __name__ == "__main__":
    print(lowestPayment(3926, 0.2))