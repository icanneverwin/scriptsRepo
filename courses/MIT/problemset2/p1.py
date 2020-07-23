#def cardbalance(balance: int, annualInterestRate: int, monthlyPaymentRate: int, monthCount: int) -> int: 
def cardbalance(balance: int, annualInterestRate: int, monthlyPaymentRate: int) -> int: 
    '''
    balance:            user's current balance
    annualInterestRate: bank's annual rate
    monthlyPaymentRate: user's monthly payment
    # monthCount          month count 

    returns: user's balance value after monthCount
    '''

    monthlyInterestRate = annualInterestRate / 12

    for i in range(12):
        minMonthlyPayment = monthlyPaymentRate * balance
        # unpaid balance in the end of the month
        balance = round(balance - minMonthlyPayment, 2)
        
        balance = round(balance + (monthlyInterestRate * balance), 2)

        # print(f'Month {i} remaining banalce: {balance}')

    return round(balance, 2)


if __name__ == "__main__":
    print(cardbalance(42, 0.2, 0.04))
    print(cardbalance(484, 0.2, 0.04))