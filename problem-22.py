"""
Using names.txt (right click and 'Save Link/Target As...'), a 46K text
file containing over five-thousand first names, begin by sorting it
into alphabetical order. Then working out the alphabetical value for
each name, multiply this value by its alphabetical position in the
list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN,
which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the
list. So, COLIN would obtain a score of 938 53 = 49714.

What is the total of all the name scores in the file?
"""

"""
A quick way to read the whole file is suggested at
http://stackoverflow.com/questions/7409780/reading-entire-file-in-python
"""
with open('names.txt', 'r') as content_file:
    raw = content_file.read()

L = []
for i in raw.split(','):
    L.append(i.split('"')[1])

score_of_char = lambda x: ord(x) - ord('A') + 1



L.sort()
j = 0
total = 0
for i in L:
    j += 1                      # j'th name
    score = 0
    for c in i:
        score += score_of_char(c)
    total += j * score
print total
