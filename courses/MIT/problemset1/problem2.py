s_string = 'bob'
s = 'azcbobobegghaklbbobobb'
count = 0
s_len = len(s_string)
lens = len(s)


for i in range(lens):
    if lens - i < s_len:
        break
    if s[i:i+s_len] == s_string:
        count += 1

print('Number of times bob occurs is:', count)