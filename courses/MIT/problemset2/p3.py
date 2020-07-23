def lowestPaymentBis(balance: int, annualInterestRate: int) -> float:
    lower_val = round(balance / 12, 2)
    upper_val = round((balance * (1 + annualInterestRate / 12)**12) / 12, 2)
    epsilon = 0.05
    monthlyInterestRate = annualInterestRate / 12
    # print(f'lower: {lower_val}, upper: {upper_val}')

    def cardbalance(balance: int, monthlyInterestRate: int, minMonthlyPayment: int) -> int: 
        for i in range(12):

            # unpaid balance in the end of the month
            balance = round(balance - minMonthlyPayment, 2)

            balance = round(balance + (monthlyInterestRate * balance), 2)
            # print(f'Month {i} remaining banalce: {balance}')

        return round(balance, 2)
    

    # go through bisect search
    midMonthlyPayment = (upper_val + lower_val) / 2
    while True:
        if -epsilon <= cardbalance(balance, monthlyInterestRate, midMonthlyPayment) <= epsilon:
            minMonthlyPayment = round(midMonthlyPayment, 2)
            break
        elif cardbalance(balance, monthlyInterestRate, midMonthlyPayment) < -epsilon:
            # minMonthlyPayment is too low
            upper_val = midMonthlyPayment
            midMonthlyPayment = (upper_val + lower_val) / 2
            #print(f'balance > epsilon, midMonthlyPayment: {midMonthlyPayment}')

        elif cardbalance(balance, monthlyInterestRate, midMonthlyPayment) > epsilon:
            # minMonthlyPayment is too high
            lower_val = midMonthlyPayment
            midMonthlyPayment = (upper_val + lower_val) / 2
            #print(f'balance < epsilon, midMonthlyPayment: {midMonthlyPayment}')

    return round(minMonthlyPayment, 2)



if __name__ == "__main__":
    #print(lowestPaymentBis(320000, 0.2))
    print(lowestPaymentBis(999999, 0.18))