import sys

sys.set_int_max_str_digits(0)

def factorial(n):
    result = 1
    for i in range(1, n + 1):
        result *= i
    return result

def print_usage():
    print('Usage: factorial.py N, where N is the number you want to get the factorial of.\n', file=sys.stderr)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)
    try:
        n = int(sys.argv[1])
    except ValueError:
        print_usage()
        sys.exit(1)
    result = factorial(n)
    print(f'factorial({n}) = {result}')
