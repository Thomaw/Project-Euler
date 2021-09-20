import string
file=open("names.txt","r");
s=file.read();
m=""
for i in range(len(s)):
    if(s[i]!="\""):
        m+=s[i]

l=m.split(',')
l.sort()
dict={}
alpha=string.ascii_uppercase
for i in range(len(alpha)):
    dict[alpha[i]]=i+1

score=0
for i in range(len(l)):
    total=0
    for j in range(len(l[i])):
        total+=dict[l[i][j]]
    total=total*(i+1)
    score+=total
print score
