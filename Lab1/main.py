from util import isNumber

def interpret(expression):
    tokens = tokenize(expression)
    print(tokens)
    num_stack = []
    op_stack = []

    for i in range(len(tokens)):
        token = tokens[i]
        print(i, token)

    for token in tokens:
        if isNumber(token):
            num_stack.append(float(token))
        elif token in {'+', '-', '*', '/'}:
            while op_stack and precedence(op_stack[-1]) >= precedence(token):
                print(op_stack[-1], precedence(op_stack[-1]))
                apply_operator(num_stack, op_stack)
            op_stack.append(token)
        elif token == '(':
            op_stack.append(token)
        elif token == ')':
            while op_stack and op_stack[-1] != '(':
                apply_operator(num_stack, op_stack)
            op_stack.pop()
        print(num_stack)
        print(op_stack)
        print(" ")

    while op_stack:
        apply_operator(num_stack, op_stack)

    return num_stack[0]

def apply_operator(num_stack, op_stack):
    operator = op_stack.pop()
    operand2 = num_stack.pop()
    operand1 = num_stack.pop()

    if operator == '+':
        num_stack.append(operand1 + operand2)
    elif operator == '-':
        num_stack.append(operand1 - operand2)
    elif operator == '*':
        num_stack.append(operand1 * operand2)
    elif operator == '/':
        num_stack.append(operand1 / operand2)

def precedence(operator):
    if operator in {'+', '-'}:
        return 1
    elif operator in {'*', '/'}:
        return 2
    return 0

def tokenize(expression):
    """
    operators = set('+-*/()')
    replacement = ''.join([' ' + char + ' ' if char in operators else char for char in expression])
    print(replacement.split())
    return replacement.split()
    """
    return expression.split()

def main():
    expression = input("Enter an arithmetic expression: ")
    result = interpret(expression)
    print("Result:", result)

if __name__ == "__main__":
    main()
