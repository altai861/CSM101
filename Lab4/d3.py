x = 5
def foo():
    print(x)

def bar():
    x = 10
    foo()

bar()