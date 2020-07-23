max_str = ''
s = 'nxxhwdkdohrvy'
temp_str = s[0]
len_str = len(s)


for i in range(1, len_str):
    #print(f'i = {i}, s[i] = {s[i]}, temp_str = {temp_str}, max_str = {max_str}')
    if s[i-1] <= s[i]:
        temp_str = temp_str + s[i]
    else:
        if len(temp_str) > len(max_str):
            max_str = temp_str
        temp_str = s[i]

if len(temp_str) > len(max_str):
    max_str = temp_str

print('Longest substring in alphabetical order is:', max_str)