fi = open('18.dat', 'r')
Tri=[]
for line in fi:
    Tri.append( map( int, line.split() ) )

ms=0 # maxsum
def sub( r, c, s ): # row, column, sum
    r+=1
    if r==len(Tri):
        global ms
        if s>ms: ms=s
        return
    for i in [0,1]: sub( r, c+i, s+Tri[r][c+i] )

sub( 0, 0, Tri[0][0] )
print ms
