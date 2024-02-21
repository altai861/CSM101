global x
x = 5
def foo():
    y = 10
    print(x + y)

def bar():
    x = 7
    foo()

bar()
print(x)