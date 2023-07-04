# Assignment 2 - PDI
# 2023.04.21
# Vítor Amorim Fróis
# 12543440
# @undergrad-SCC0251

import numpy as np
from math import pi
import imageio
from matplotlib import pyplot as plt
from dataclasses import dataclass
import sys

IDEAL_LOW_PASS = 0
IDEAL_HIGH_PASS = 1
IDEAL_BAND_PASS = 2
LAPLACIAN_HIGH_PASS = 3
GAUSSIAN_HIGH_PASS = 4
BUTTERWORTH_LOW_PASS = 5
BUTTERWORTH_HIGH_PASS = 6
BUTTERWORTH_BAND_REJECT = 7
BUTTERWORTH_BAND_PASS = 8


def show_image(image: np.array):
    N, _ = image.shape
    plt.imshow(image, cmap="gray")
    plt.show()


@dataclass
class Filter:
    P: int
    Q: int
    input_image: np.array
    new_image: np.array
    expected_image: np.array
    pi_2 = np.power(pi, 2)
    k = (-4 * pi_2)
    np_filter: np.array
    image_min: int
    image_max: int

    @staticmethod
    def normalize(image: np.array):
        image_min = image.min()
        image_max = image.max()
        normalized = (((image - image_min) * 255) / (image_max - image_min))
        normalized = normalized.astype(np.uint8)
        return normalized

    @classmethod
    def read_input_image(cls, image_name: str):
        input_image = imageio.v3.imread(image_name)
        cls.image_min = np.min(input_image)
        cls.image_max = np.max(input_image)
        cls.P, cls.Q = input_image.shape
        cls.input_image = input_image

    @classmethod
    def read_expected_image(cls, image_name: str):
        cls.expected_image = imageio.v3.imread(image_name)

    @classmethod
    def apply_filter(cls):
        input_image_frequency = np.fft.fftshift(np.fft.fft2(cls.input_image))
        new_image_frequency = input_image_frequency * cls.np_filter
        new_image = np.fft.ifft2(np.fft.ifftshift(new_image_frequency)).real
        cls.new_image = cls.normalize(new_image)

    @staticmethod
    def diff_power(a, b, exponent=2):
        return (a - b)**exponent

    @classmethod
    def diff_sum_sqrt(cls, a, b):
        result = np.sqrt(cls.diff_power(a, cls.P / 2) + cls.diff_power(b, cls.Q / 2))
        return result

    @classmethod
    def get_filter(cls, f):
        np_filter = np.ones((cls.P, cls.Q), dtype=np.float32)
        for x in range(cls.P):
            for y in range(cls.Q):
                np_filter[x, y] = f(x, y)
        # show_image(np_filter)
        cls.np_filter = np_filter

    @classmethod
    def compute_rmse(cls):
        N, M = cls.expected_image.shape
        fsum = 0
        cls.new_image = cls.new_image.astype(np.int32)
        # show_image(cls.expected_image)
        # show_image(cls.new_image)
        for i in range(N):
            for j in range(M):
                difference = (cls.new_image[i, j] - cls.expected_image[i, j])
                fsum += np.power(difference, 2)
        rmse = np.sqrt((fsum / (N * M)))
        return rmse


@dataclass
class Ideal(Filter):
    D0: float = 1.0
    D1: float = 1.0

    @classmethod
    def read_pass_input(cls, parameters_list: list):
        cls.D0 = float(parameters_list[0])

    @classmethod
    def read_band_input(cls, parameters_list: list):
        cls.D0 = float(parameters_list[0])
        cls.D1 = float(parameters_list[1])

    @classmethod
    def lowpass_function(cls, a, b, D0=None):
        if D0 is None:
            D0 = cls.D0
        D = cls.diff_sum_sqrt(a, b)
        if D <= D0:
            return 1
        else:
            return 0

    @classmethod
    def highpass_function(cls, a, b, D0=None):
        if D0 is None:
            D0 = cls.D0
        D = cls.diff_sum_sqrt(a, b)
        if D <= D0:
            return 0
        else:
            return 1

    @classmethod
    def band_pass_function(cls, a, b):
        D = cls.highpass_function(a, b, cls.D1)
        D + cls.lowpass_function(a, b, cls.D0)
        return D


@dataclass
class Laplacian(Filter):

    @classmethod
    def laplacian_function(cls, a, b):
        result = cls.k * (cls.diff_power(a, cls.P / 2) + cls.diff_power(b, cls.Q / 2))
        return 1 - result


@dataclass
class Gaussian(Filter):
    omega_r: float
    omega_c: float
    omega_r2: float
    omega_c2: float

    @classmethod
    def read_pass_input(cls, parameters_list: list):
        cls.omega_r = int(parameters_list[0])
        cls.omega_c = int(parameters_list[1])
        cls.set_omega()

    @classmethod
    def set_omega(cls):
        cls.omega_r2 = 2 * cls.omega_r**2
        cls.omega_c2 = 2 * cls.omega_c**2

    @classmethod
    def gaussian_function(cls, a, b):
        first = cls.diff_power(a, cls.P / 2) / cls.omega_r2
        second = cls.diff_power(b, cls.Q / 2) / cls.omega_c2
        x = first + second
        return np.exp(-x)


@dataclass
class Butterworth(Filter):
    D0: int
    D1: int
    n0: float
    n1: float

    @classmethod
    def read_pass_input(cls, parameters_list: list):
        cls.D0 = int(parameters_list[0])
        cls.n0 = float(parameters_list[1])

    @classmethod
    def read_band_input(cls, parameters_list: list):
        cls.D0 = int(parameters_list[0])
        cls.n0 = float(parameters_list[1])
        cls.D1 = int(parameters_list[2])
        cls.n1 = float(parameters_list[3])

    @classmethod
    def low_pass_function(cls, a, b, d=None, n=None):
        if d is None:
            d = cls.D0
        if n is None:
            n = cls.n0
        den = (1 + (cls.diff_sum_sqrt(a, b) / d) ** (2 * n))
        return 1 / den

    @classmethod
    def high_pass_function(cls, a, b, d=None, n=None):
        if d is None:
            d = cls.D0
        if n is None:
            n = cls.n0
        return 1 - cls.low_pass_function(a, b, d, n)

    @classmethod
    def band_pass_function(cls, a, b, d0=None, n0=None, d1=None, n1=None):
        if d0 is None:
            d0 = cls.D0
        if n0 is None:
            n0 = cls.n0
        if d1 is None:
            d1 = cls.D1
        if n1 is None:
            n1 = cls.n1
        D = cls.high_pass_function(a, b, d0, n0)
        D + cls.low_pass_function(a, b, d1, n1)
        return cls.normalize(D)

    @classmethod
    def band_reject_function(cls, a, b, d0=None, n0=None, d1=None, n1=None):
        if d0 is None:
            d0 = cls.D0
        if n0 is None:
            n0 = cls.n0
        if d1 is None:
            d1 = cls.D1
        if n1 is None:
            n1 = cls.n1
        return 1 - cls.band_pass_function(a, b, d0, n0, d1, n1)


def main():
    stdin_input = sys.stdin.read()
    lines = stdin_input.split('\n')
    filters = int(lines[2])
    if filters == IDEAL_LOW_PASS:
        Ideal.read_input_image(lines[0])
        Ideal.read_expected_image(lines[1])
        Ideal.read_pass_input(lines[3:])
        Ideal.get_filter(Ideal.lowpass_function)
        Ideal.apply_filter()
        rmse = Ideal.compute_rmse()
    elif filters == IDEAL_HIGH_PASS:
        Ideal.read_input_image(lines[0])
        Ideal.read_expected_image(lines[1])
        Ideal.read_pass_input(lines[3:])
        Ideal.get_filter(Ideal.highpass_function)
        Ideal.apply_filter()
        rmse = Ideal.compute_rmse()
    elif filters == IDEAL_BAND_PASS:
        Ideal.read_input_image(lines[0])
        Ideal.read_expected_image(lines[1])
        Ideal.read_band_input(lines[3:])
        Ideal.get_filter(Ideal.band_pass_function)
        Ideal.apply_filter()
        rmse = Ideal.compute_rmse()
    elif filters == LAPLACIAN_HIGH_PASS:
        Laplacian.read_input_image(lines[0])
        Laplacian.read_expected_image(lines[1])
        Laplacian.get_filter(Laplacian.laplacian_function)
        Laplacian.apply_filter()
        rmse = Laplacian.compute_rmse()
    elif filters == GAUSSIAN_HIGH_PASS:
        Gaussian.read_input_image(lines[0])
        Gaussian.read_expected_image(lines[1])
        Gaussian.read_pass_input(lines[3:])
        Gaussian.get_filter(Gaussian.gaussian_function)
        Gaussian.apply_filter()
        rmse = Gaussian.compute_rmse()
    elif filters == BUTTERWORTH_LOW_PASS:
        Butterworth.read_input_image(lines[0])
        Butterworth.read_expected_image(lines[1])
        Butterworth.read_pass_input(lines[3:])
        Butterworth.get_filter(Butterworth.low_pass_function)
        Butterworth.apply_filter()
        rmse = Butterworth.compute_rmse()
    elif filters == BUTTERWORTH_HIGH_PASS:
        Butterworth.read_input_image(lines[0])
        Butterworth.read_expected_image(lines[1])
        Butterworth.read_pass_input(lines[3:])
        Butterworth.get_filter(Butterworth.high_pass_function)
        Butterworth.apply_filter()
        rmse = Butterworth.compute_rmse()
    elif filters == BUTTERWORTH_BAND_REJECT:
        Butterworth.read_input_image(lines[0])
        Butterworth.read_expected_image(lines[1])
        Butterworth.read_band_input(lines[3:])
        Butterworth.get_filter(Butterworth.band_reject_function)
        Butterworth.apply_filter()
        rmse = Butterworth.compute_rmse()
    elif filters == BUTTERWORTH_BAND_PASS:
        Butterworth.read_input_image(lines[0])
        Butterworth.read_expected_image(lines[1])
        Butterworth.read_band_input(lines[3:])
        Butterworth.get_filter(Butterworth.band_pass_function)
        Butterworth.apply_filter()
        rmse = Butterworth.compute_rmse()

    print('%.4f' % rmse)


main()
