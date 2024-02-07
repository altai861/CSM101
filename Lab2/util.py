from CFG import CFG
from ProductionRule import ProductionRule
from CFG import CFG
import random
import math

def initializeCFG(grammar: CFG):
    grammar.rules = [ProductionRule('S', ["aSa", "bSb", "cSc", "dSd", "a", "b", "c", "d"]),
         ProductionRule('V', ["aSa", "bSb", "cSc", "dSd", "a", "b", "c", "d"])]

    grammar.terminals = ["a", "b", "c", "d"]
    grammar.startSymbol = 'S'

def findRule(grammar: CFG, symbol):
    for rule in grammar.rules:
        if rule.head == symbol:
            return rule
    return None


def getRandomElement(ruleBody):
    return random.choice(ruleBody)

def generatePalindrome(grammar: CFG, symbol):
    if symbol in grammar.terminals:
        return symbol
    else:
        rule = findRule(grammar, symbol)
        randomProduction = getRandomElement(rule.body)
        generatedString = ""
        for char in randomProduction:
            generatedString += generatePalindrome(grammar, char)
        return generatedString
    


# ----------------- Next Part

"""
def check_string(grammar, symbol, string):
    if symbol in grammar.terminals:
        # If the symbol is a terminal, check if it matches the corresponding character in the string
        return len(string) == 1 and string[0] == symbol

    for rule in grammar.rules:
        if rule.head == symbol:
            for production in rule.body:
                print(production)
                if len(string) >= len(production):
                    is_match = True
                    for prod_symbol, prod_char in zip(production, string):
                        print(prod_symbol, prod_char)
                        if not check_string(grammar, prod_symbol, prod_char):
                            is_match = False
                            break
                    if is_match:
                        return True

    return False
"""


def checkString(grammar: CFG, string):
    if len(string) == 1:
        return string in grammar.terminals
    if len(string) == 0:
        return True
    first = string[0]
    last = string[-1]
    if first != last:
        return False
    
    for rule in grammar.rules:
        for singleProd in rule.body:
            if singleProd[0] == first and singleProd[-1] == last:
                return checkString(grammar, string[1:-1])
    return False



# Didn't work
def parseString(grammar: CFG, str, symbol):
    if len(str) == 0:
        return True
    if symbol in grammar.terminals:
        return str[0] == symbol and parseString(grammar, str[1:], symbol)
    else:
        rule = findRule(grammar, symbol)
        for production in rule.body:
            if parseString(grammar, str, production[0]):
                return True
        return False
    
def testParser(grammar: CFG, numTests):
    print("Testing Parser with Random Palindrome: ")
    for i in range(1, numTests + 1):
        testPalindrome = generatePalindrome(grammar, grammar.startSymbol)
        print("Test ", i, ": Palindrome - ", testPalindrome)

        if checkString(grammar, testPalindrome):
            print("  Parser Result: Valid ")
        else:
            print("  Parser Result: Invalid ")

