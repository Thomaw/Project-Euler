import string
def triangle(n):
    return (n*(n+1)/2)

def isTriangle(x):
    i=1
    while(True):
        k=triangle(i)
        if(k==x):
            return True
        if(k>x):
            return False
        i+=1

alpha={} #The Dictionary which holds the values for the alphabets
alphabet=string.ascii_uppercase 
for i in range(len(alphabet)):
    alpha[alphabet[i]]=i+1

#Format the input from the file so that it fits nicely in a list
f=open("words.txt","r")
s=f.read()
m=""
for i in range(len(s)):
    if(s[i]!='\"'):
        m+=s[i]
l=m.split(',');

#Calculate the number of triangle words
n=0
for i in l:
    m=list(i)
    total=0
    for j in m:
        total+=alpha[j]
    if(isTriangle(total)):
        n+=1
print n
