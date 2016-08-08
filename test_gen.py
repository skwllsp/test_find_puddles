import sys

def main():
    n = int(sys.argv[1])
    m = int(sys.argv[2])
    v = 1
    for i in xrange(n):
        row = []
        for j in xrange(m):
            row.append(v)
            v += 1
        s = ' '.join(map(str, row))
        print s
        
if __name__ == "__main__":
    main()
