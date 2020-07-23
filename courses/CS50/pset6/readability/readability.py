from cs50 import get_string
import re

user_input = get_string("Text: ")
alpha_count = 0

for i in user_input:
    if i.isalpha():
        alpha_count += 1

#words_count = len(re.findall(r'\w+', user_input))
words_count = len(re.findall(" ", user_input))
words_count +=1
sentence_count = len(re.findall("\?|\.|\!", user_input))

print(f"alpha_count {alpha_count},words_count {words_count}, sentence_count {sentence_count}")


avg_letters = alpha_count / words_count * 100
avg_sentences = sentence_count / words_count * 100
index = round(0.0588 * avg_letters - 0.296 * avg_sentences - 15.8)

print(f"avg_letters {avg_letters},avg_sentences {avg_sentences}, index {index}")

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade ", index)

# 23.8875 7.4