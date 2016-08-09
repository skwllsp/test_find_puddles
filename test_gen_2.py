import sys

def main():
    n = int(sys.argv[1])
    m = int(sys.argv[2])
    v = 1
    top = n*m+2
    row_i = 1
    for i in xrange(n):
        col_i = 1
        row = []
        for j in xrange(m):
            if row_i == 1 or row_i == n or col_i == 1 or col_i == m:
                row.append(top)
            else:
                row.append(v)
                v += 1

            col_i += 1
        row_i += 1
        s = ' '.join(map(str, row))
        print s
        
if __name__ == "__main__":
    main()
