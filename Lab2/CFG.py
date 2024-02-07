from ProductionRule import ProductionRule

class CFG:
    def __init__(self, rules: [ProductionRule], terminals, startSymbol):
        self.rules = rules
        self.terminals = terminals
        self.startSymbol = startSymbol
