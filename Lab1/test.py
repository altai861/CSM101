import unittest
from main import interpret

class TestInterpreter(unittest.TestCase):
    def test_addition(self):
        self.assertEqual(interpret("3 + 5"), 8)
    
    def test_subtraction(self):
        self.assertEqual(interpret("7 - 2"), 5)

    def test_complex_expression(self):
        self.assertEqual(interpret("2 * ( 4 + 3 )"), 14)
        self.assertAlmostEqual(interpret("10 * 0.7 + 3 / ( 6 + 9 / 5 ) + 7"), 14.384615, 4)

if __name__ == "__main__":
    unittest.main()
