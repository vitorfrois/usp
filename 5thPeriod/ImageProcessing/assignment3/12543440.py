# Assignment 3 - PDI
# 2023.04.21
# Vítor Amorim Fróis
# 12543440
# @undergrad-SCC0251

import numpy as np
np.seterr(divide='ignore', invalid='ignore')
import imageio
import sys
from scipy.ndimage import convolve

PI_OVER_2 = np.pi / 2
HUMAN = 1
NO_HUMAN = 0
NO_CLASSIFICATION = 2


def gradient_denominator(g_x, g_y):
    return np.sqrt(g_x**2 + g_y**2).sum()


class Image:
    classification: int
    image: np.array
    rgb_image: np.array
    descriptor: np.array

    x_sobel = np.array([[-1, -2, -1],
                        [0, 0, 0],
                        [1, 2, 1]])

    y_sobel = np.array([[-1, 0, 1],
                        [-2, 0, 2],
                        [-1, 0, 1]])

    def __init__(self, image_path: str, classification: int = NO_CLASSIFICATION):
        rgb_image = imageio.v3.imread(image_path)
        self.P, self.Q, _ = rgb_image.shape
        self.rgb_image = rgb_image
        self.classification = classification
        self.compute_descriptor()

    def get_image(self):
        return self.image

    def get_class(self):
        return self.classification

    def get_descriptor(self):
        return self.descriptor

    def apply_luminance(self):
        R_channel = self.rgb_image[:,:,0]
        G_channel = self.rgb_image[:,:,1]
        B_channel = self.rgb_image[:,:,2]
        self.image = np.floor(
            (0.299 * R_channel) +
            (0.587 * G_channel) +
            (0.114 * B_channel))

    def compute_gradients(self):
        g_x = convolve(self.image, self.x_sobel)
        g_y = convolve(self.image, self.y_sobel)
        return g_x, g_y

    def compute_magnitude(self, g_x, g_y):
        den = gradient_denominator(g_x, g_y)
        magnitude_matrix = np.sqrt(g_x**2 + g_y**2)/den
        return magnitude_matrix

    def compute_angles(self, g_x, g_y):
        phi_matrix = np.arctan(g_y/g_x)
        phi_matrix += PI_OVER_2
        phi_matrix = np.degrees(phi_matrix)
        return phi_matrix

    def compute_bins(self, phi_matrix: np.array):
        # bins_matrix = (phi_matrix/20) - 1
        bins_matrix = np.digitize(phi_matrix, np.arange(0, 180, 20)) - 1
        return bins_matrix

    def compute_descriptor(self):
        self.apply_luminance()
        g_x, g_y = self.compute_gradients()
        magnitude_matrix = self.compute_magnitude(g_x, g_y)
        phi_matrix = self.compute_angles(g_x, g_y)
        bins_matrix = self.compute_bins(phi_matrix)
        descriptor_array = np.zeros(9)
        for x in range(self.P):
            for y in range(self.Q):
                bin_number = bins_matrix[x, y]
                try:
                    descriptor_array[int(bin_number)] += magnitude_matrix[x, y]
                except ValueError:
                    pass

        self.descriptor = descriptor_array


class KNN:
    train_set: list[Image] = []

    def __init__(self, n_classes: int, nn: int):
        self.n_classes = n_classes
        self.nn = nn

    def euclidean_distance(self, image1, image2):
        descriptor1 = image1.get_descriptor()
        descriptor2 = image2.get_descriptor()
        d = np.sqrt(((descriptor1-descriptor2)**2).sum())
        return d

    def add_train_image(self, train_image: Image):
        self.train_set.append(train_image)

    def test(self, test_image):
        test_list: list[(float, int)] = []
        for elem in self.train_set:
            distance = self.euclidean_distance(elem, test_image)
            image_class = elem.classification
            test_tuple = (distance, image_class)
            test_list.append(test_tuple)
        test_list.sort()
        knn_class_list = [x[1] for x in test_list[:self.nn]]
        test_image_predicted_class = max(set(knn_class_list), key=knn_class_list.count)
        return test_image_predicted_class


def main():
    stdin_input = sys.stdin.read()
    lines = stdin_input.split('\n')
    knn = KNN(2, 3)
    predictions = []
    for image_path in lines[0].split(' '):
        image = Image(image_path, NO_HUMAN)
        knn.add_train_image(image)
    for image_path in lines[1].split(' '):
        image = Image(image_path, HUMAN)
        knn.add_train_image(image)
    for image_path in lines[2].split(' '):
        image = Image(image_path)
        predictions.append(knn.test(image))

    print(*predictions, ' \n')


main()


