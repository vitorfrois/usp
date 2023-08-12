#!/usr/bin/env python

import numpy as np
import imageio
from matplotlib import pyplot as plt
import sys

NO_ENHANCEMENT = 0
SINGLE_IMAGE_HIST = 1
JOINT_HIST = 2
GAMMA_CORRECTION = 3
NUMBER_IMAGES = 4
NUMBER_LEVELS = 256
TESTS_FOLDER = 'test_cases/'

image = np.floor(np.random.random((30, 30)) * 10)
ones = np.ones((30, 30))


def gamma_correction(image: np.array, gamma: float):
    print('corrigindo gamma')
    new_image = np.ceil(255 * np.power(image / 255.0, 1.0 / gamma))
    return new_image


def histogram(image: np.array, no_levels):
    hist = np.zeros(no_levels).astype(int)

    for level in range(no_levels):
        no_pixel_i = np.sum(image == level)

        hist[level] = no_pixel_i

    return hist


def histogram_equalization_function(image: np.array, no_levels):
    hist = histogram(image, no_levels)

    cumulative_hist = np.zeros(no_levels).astype(int)

    cumulative_hist[0] = hist[0]
    for level in range(1, no_levels):
        cumulative_hist[level] = hist[level] + cumulative_hist[level - 1]

    transfer_function = np.zeros(no_levels)
    N, M = image.shape

    for level in range(no_levels):
        s = ((no_levels - 1) / float(M * N)) * cumulative_hist[level]

        transfer_function[level] = s

    return transfer_function


def apply_equalization(image: np.array, no_levels, transfer_function: np.array):
    N, M = image.shape
    equalized_image = np.zeros((N, M))

    for level in range(no_levels):
        equalized_image[np.where(image == level)] = transfer_function[level]

    return equalized_image


def show_image(image: np.array):
    N, _ = image.shape
    plt.imshow(image, cmap="gray", vmin=0, vmax=N)
    plt.show()


def super_resolution(image_list):
    image_N, image_M = image_list[0].shape
    hd_image = np.zeros((image_N*2, image_M*2))
    for x in range(0, image_N, 1):
        for y in range(0, image_M, 1):
            hd_image[2*x, 2*y] = image_list[0][x, y]
            hd_image[2*x, 2*y + 1] = image_list[1][x, y]
            hd_image[2*x + 1, 2*y] = image_list[2][x, y]
            hd_image[2*x + 1, 2*y + 1] = image_list[3][x, y]
    return hd_image


def compute_rmse(my_image, reference_image):
    N, M = my_image.shape
    sum = 0
    for i in range(N):
        for j in range(M):
            difference = my_image[i, j] - reference_image[i, j]
            sum += np.power(difference, 2)
    rmse = np.sqrt((sum / (N * M)))
    return rmse


def process_images(image_list, enhancement_method, gamma):
    if enhancement_method == NO_ENHANCEMENT:
        return image_list
    elif enhancement_method == SINGLE_IMAGE_HIST:
        for i in range(NUMBER_IMAGES):
            transfer_function = histogram_equalization_function(image_list[i], NUMBER_LEVELS)
            image_list[i] = apply_equalization(image_list[i], NUMBER_LEVELS, transfer_function)
    elif enhancement_method == JOINT_HIST:
        sum_N, sum_M = image_list[0].shape
        final_transfer_function = np.zeros((sum_N, sum_M))
        for i in range(NUMBER_IMAGES):
            transfer_function = histogram_equalization_function(image_list[i], NUMBER_LEVELS)
            final_transfer_function += transfer_function
        for i in range(NUMBER_IMAGES):
            image_list[i] = apply_equalization(image_list[i], NUMBER_LEVELS, transfer_function)
    elif enhancement_method == GAMMA_CORRECTION:
        for i in range(NUMBER_IMAGES):
            image_list[i] = gamma_correction(image_list[i], gamma)

    return image_list


if __name__ == '__main__':
    png = '.png'
    stdin_input = sys.stdin.read()
    lines = stdin_input.split('\n')
    low_res_image_name = lines[0]
    hd_image_name = lines[1]
    enhancement_method = int(lines[2])
    gamma = float(lines[3])

    image_list = []
    for i in range(NUMBER_IMAGES):
        image_name = f'{TESTS_FOLDER}{low_res_image_name}{i}{png}'
        image_list.append(imageio.v3.imread(image_name))

    hd_image = imageio.v3.imread(TESTS_FOLDER + hd_image_name)

    enhanced_image_list = process_images(image_list, enhancement_method, gamma)

    my_hd_image = super_resolution(enhanced_image_list)

    rmse = compute_rmse(my_hd_image, hd_image)

    print('%.4f' % rmse)
