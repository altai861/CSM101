x = 2
def foo(y):
    x += y

def foo():
    x *= 2

foo(3)
foo()
print(x)