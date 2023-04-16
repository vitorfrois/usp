import numpy as np
from math import pi
import scipy

class Filter:
    P: int
    Q: int
    pi_2 = np.power(pi, 2)
    def __init__(image):
        self.P, self.Q = image.shape
        f = np.zeros((self.P, self.Q), dtype=np.float32)

    def apply_filter(f, image):
        new_image = np.zeros_like(image)
        for x in image:
            for y in x:
                new_image[x, y] = f(image[x], image[y])

    def diff_power(a, b, expoent=2):
        return np.power(a - b, expoent)

    def diff_sum_sqrt(a, b):
        result = np.sqrt(diff_power(a, self.P/2) + diff_power(b, self.Q/2))
        return result

class Ideal(Filter):
    D0: float = 1.0
    D1: float = 1.0

    def lowpass_function(a, b, r = self.D0):
        D = self.diff_sum_sqrt(a, b)
        if D <= r:
            return 1
        else:
            return 0

    def highpass_function(a, b, r = self.D0):
        D = self.diff_sum_sqrt(a, b)
        if D <= r:
            return 0
        else:
            return 1

    def band_pass_function(a, b):
        D = self.highpass_function(a, b, D1)
        D + self.lowpass_function(a, b, D0)
        if D <= r:
            return 0
        else:
            return 1

  
class Laplacian(Filter):
    k = (-4 * pi_2)

    def function(a, b):
        result = self.k * (self.diff_power(a, self.P/2) + self.diff_power(b, self.Q/2))
        return result


class Gaussian(Filter):
    omega_r2: float = 1.0
    omega_c2: float = 1.0
    
    def set_omega(r, c):
        omega_r2 = np.power(r, 2)
        omega_c2 = np.power(c, 2)

    def function(a, b):
        first = (self.diff_power(a, self.P/2)/omega_r2)
        second = (self.diff_power(b, self.Q/2)/omega_c2)
        x = first+second
        return np.exp(-x)


class Butterworth(Filter):
    D0: float = 1.0
    D1: float = 1.0
    n0: float = 1.0
    D1: float = 1.0

    def set_var(D0, n):
        self.D0 = D0
        self.n = n

    def function(a, b):
        den = (1 + np.power((self.diff_sum_sqrt(a, b)/self.D0), 2 * self.n0))
        return 1/den


def main():
    f = np.array([0, 2, 3, 4])
    print(FFT(f))

main()