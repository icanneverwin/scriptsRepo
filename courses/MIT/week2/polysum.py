import math
def polysum(n, s):
    '''
    n: int, number of sides
    s: side length

    returns: sum of the area and square of the perimeter of the regular polygon
    '''

    area = (0.25 * n * s**2) / math.tan(math.pi / n)
    P = n * s
    return round(area + P**2, 4)