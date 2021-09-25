def dec2bin(n):
        s = ""
        x = 1

        half_n = n >> 1 # n >> 1 == n/2
        while x <= half_n:
                x = x << 1 # n << 1 == n*2

        while x >= 1:
                n -= x
                if n >= 0:
                        s = s + "1"
                else:
                        s = s + "0"
                        n += x
                x = x >> 1 # again x/2

        return s

sum = 0
for x in range(1,999999):
        s = str(x)
        if s == s[::-1]:
                s_b = dec2bin(int(s))
                if s_b == s_b[::-1]:
                        sum += x
                        print '%d = %s' % (x, s_b)
print 'Answer: %d' % (sum)
