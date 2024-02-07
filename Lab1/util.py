def isNumber(s):
     
    # handle for negative values
    negative = False
    if(s[0] =='-'):
        negative = True
         
    if negative == True:
        s = s[1:]
     
    # try to convert the string to int
    try:
        n = float(s)
        return True
    # catch exception if cannot be converted
    except ValueError:
        return False