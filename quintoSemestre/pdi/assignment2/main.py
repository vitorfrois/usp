import numpy as np
from math import pi
import imageio

IDEAL_LOW_PASS = 0
IDEAL_HIGH_PASS = 1
IDEAL_BAND_PASS = 2
LAPLACIAN_HIGH_PASS = 3
GAUSSIAN_HIGH_PASS = 4
BUTTERWORTH_LOW_PASS = 5
BUTTERWORTH_HIGH_PASS = 6
BUTTERWORTH_BAND_REJECT = 7
BUTTERWORTH_BAND_PASS = 8

class Filter:
    P: int
    Q: int
    input_image: np.array
    new_image: np.array
    expected_image: np.array
    pi_2 = np.power(pi, 2)
    k = (-4 * pi_2)


    def read_input_image(self, image_name: str):
        self.input_image = imageio.v3.imread(image_name)
        self.P, self.Q = self.input_image.shape
        f = np.zeros((self.P, self.Q), dtype=np.float32)

    def read_expected_image(self, image_name: str):
        self.expected_image = imageio.v3.imread(image_name)

    def apply_filter(self, f):
        new_image = np.zeros_like(self.input_image)
        for x in self.input_image:
            for y in x:
                new_image[x, y] = f(self.input_image[x], self.input_image[y])
        self.new_image = new_image

    def diff_power(self, a, b, exponent=2):
        return np.power(a - b, exponent)

    def diff_sum_sqrt(self, a, b):
        result = np.sqrt(self.diff_power(a, self.P / 2) + self.diff_power(b, self.Q / 2))
        return result

    def compute_rmse(self):
        N, M = self.expected_image.shape
        fsum = 0
        for i in range(N):
            for j in range(M):
                difference = self.new_image[i, j] - self.expected_image[i, j]
                fsum += np.power(difference, 2)
        rmse = np.sqrt((fsum / (N * M)))
        return rmse

class Ideal(Filter):
    D0: float = 1.0
    D1: float = 1.0

    def read_pass_input(self, parameters_list: list):
        self.D0 = parameters_list[0]

    def read_band_input(self, parameters_list: list):
        self.D0 = parameters_list[0]
        self.D1 = parameters_list[1]

    def lowpass_function(self, a, b, r = D0):
        D = self.diff_sum_sqrt(a, b)
        if D <= r:
            return 1
        else:
            return 0

    def highpass_function(self, a, b, r = D0):
        D = self.diff_sum_sqrt(a, b)
        if D <= r:
            return 0
        else:
            return 1

    def band_pass_function(self, a, b):
        D = self.highpass_function(a, b, self.D1)
        D + self.lowpass_function(a, b, self.D0)
        return D

  
class Laplacian(Filter):

    def function(self, a, b):
        result = self.k * (self.diff_power(a, self.P/2) + self.diff_power(b, self.Q/2))
        return result


class Gaussian(Filter):
    omega_r2: float = 1.0
    omega_c2: float = 1.0

    def read_pass_input(self, parameters_list: list):
        self.omega_r2 = parameters_list[0]
        self.omega_c2 = parameters_list[1]
        self.set_omega()

    def set_omega(self):
        self.omega_r2 = np.power(self.omega_r2, 2)
        self.omega_c2 = np.power(self.omega_c2, 2)

    def function(self, a, b):
        first = (self.diff_power(a, self.P/2)/self.omega_r2)
        second = (self.diff_power(b, self.Q/2)/self.omega_c2)
        x = first+second
        return np.exp(-x)


class Butterworth(Filter):
    D0: float
    D1: float
    n0: float
    n1: float

    def __init__(self):
        self.n = None

    def read_pass_input(self, parameters_list: list):
        self.D0 = parameters_list[0]
        self.n0 = parameters_list[1]

    def read_band_input(self, parameters_list: list):
        self.D0 = parameters_list[0]
        self.D1 = parameters_list[1]
        self.n0 = parameters_list[2]
        self.n1 = parameters_list[3]

    def set_var(self, D0, n):
        self.D0 = D0
        self.n = n

    def low_pass(self, a, b, d = D0, n = n0):
        den = (1 + np.power((self.diff_sum_sqrt(a, b)/d), 2 * n))
        return 1/den

    def high_pass(self, a, b, d = D0, n = n0):
        return 1 - self.low_pass(a, b, d, n)

    def band_pass_function(self, a, b, d0=D0, n0=n0, d1=D1, n1=n1):
        D = self.high_pass(a, b, d0, n0)
        D + self.low_pass(a, b, d1, n1)
        return D

    def band_reject_function(self, a, b, d0=D0, n0=n0, d1=D1, n1=n1):
        return 1 - self.band_pass_function(a, b, d0, n0, d1, n1)


def main():
    png = '.png'
    file_name = input()
    with open(file_name) as input_file:
        lines = input_file.read().split('\n')
        filters = lines[3]
        if filters == IDEAL_LOW_PASS:
            image_filter = Ideal()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.lowpass_function)
            rmse = image_filter.compute_rmse()
        elif filters == IDEAL_HIGH_PASS:
            image_filter = Ideal()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.highpass_function)
            rmse = image_filter.compute_rmse()
        elif filters == IDEAL_BAND_PASS:
            image_filter = Ideal()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.band_pass_function)
            rmse = image_filter.compute_rmse()
        elif filters == LAPLACIAN_HIGH_PASS:
            image_filter = Laplacian()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.apply_filter(image_filter.function)
            rmse = image_filter.compute_rmse()
        elif filters == GAUSSIAN_HIGH_PASS:
            image_filter = Gaussian()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.function)
            rmse = image_filter.compute_rmse()
        elif filters == BUTTERWORTH_LOW_PASS:
            image_filter = Butterworth()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.low_pass)
            rmse = image_filter.compute_rmse()
        elif filters == BUTTERWORTH_HIGH_PASS:
            image_filter = Butterworth()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.high_pass)
            rmse = image_filter.compute_rmse()
        elif filters == BUTTERWORTH_BAND_REJECT:
            image_filter = Butterworth()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.band_pass_function)
            rmse = image_filter.compute_rmse()
        elif filters == BUTTERWORTH_BAND_PASS:
            image_filter = Butterworth()
            image_filter.read_input_image(lines[0])
            image_filter.read_expected_image(lines[1])
            image_filter.read_pass_input(lines[2:])
            image_filter.apply_filter(image_filter.band_reject_function)
            rmse = image_filter.compute_rmse()

    print('%.4f' % rmse)


main()
