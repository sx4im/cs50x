text = input("Text: ")
l = 0
w = 1
s = 0

for char in text:
    if (char == ' '):
        w += 1
    elif (char == '.' or char == '?' or char == '!'):
        s += 1
    elif (char.isalpha()):
        l += 1
index = round(0.0588 * l / w * 100 - 0.296 * s / w * 100 - 15.8)

if (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print("Grade", index)
