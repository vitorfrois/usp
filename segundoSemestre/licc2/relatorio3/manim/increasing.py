from manim import *
import array as arr

from numpy import add
from numpy import genfromtxt
import numpy

#import CSV file

class functions(Scene):
    def construct(self):
        graphTitle = Tex("Métodos de ordenação").move_to(UP*3.5)
        data = genfromtxt('data.csv', delimiter=',', dtype=None)
        data[0] = data[0] * 0.01
        xmax = numpy.max(data[0])
        valuesArray = [data[1:]]
        ymax = numpy.max(valuesArray)
        ymax = np.floor(ymax/1000);
        ax = Axes(
            x_range=[numpy.min(data[0]), xmax, xmax/10],
            y_range=[0, ymax, ymax/10],
            x_length=7,
            y_length=5,
            x_axis_config={"numbers_to_include": data[0]},
            y_axis_config={"numbers_to_include": np.arange(0, ymax+0.001, ymax/10)},
            tips=False
        )

        graphLabels = ax.get_axis_labels(
            x_label=Tex("Tamanho do vetor $(\\times 10^3)$").scale(0.6), 
            y_label=Tex("Tempo (ms)").scale(0.6)
        )
        
        x_coordinates = data[0] 

        heap_y = data[1]/1000
        heapGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=heap_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        heapLabel = Text("Quick", color=BLUE).scale(0.4).move_to(heapGraph, UP)

        quick_y = data[2]/1000
        quickGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=quick_y, line_color=PINK, add_vertex_dots=True, vertex_dot_radius=0.05)
        quickLabel = Text('Heap', color=PINK).scale(0.4).next_to(quickGraph, UR)

        # bubble_y = data[4]
        # bubbleGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=bubble_y, line_color=YELLOW, add_vertex_dots=True,  vertex_dot_radius=0.05)
        # bubbleLabel = Text('Bubble', color=YELLOW).scale(0.4).next_to(bubbleGraph, DOWN)

        insertion_y = data[3]/1000
        insertionGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=insertion_y, line_color=GREEN_C, add_vertex_dots=True,  vertex_dot_radius=0.05)
        insertionLabel = Text('Insertion', color=GREEN_C).scale(0.4).next_to(insertionGraph, UR)

        merge_y = data[4]/1000
        mergeGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=merge_y, line_color=RED, add_vertex_dots=True,  vertex_dot_radius=0.05)
        mergeLabel = Text('Merge', color=RED).scale(0.4).next_to(mergeGraph, UR)

        # merge_y = data[6]
        # mergeGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=merge_y, line_color=MAROON_C, add_vertex_dots=True,  vertex_dot_radius=0.05)
        # mergeLabel = Text('Merge', color=MAROON_C).scale(0.4).next_to(heapLabel, DOWN)

        # bucket_y = data[7]
        # bucketGraph = ax.plot_line_graph(x_values=x_coordinates, y_values=bucket_y, line_color=TEAL, add_vertex_dots=True,  vertex_dot_radius=0.05)
        # bucketLabel = Text('Bucket', color=TEAL).scale(0.4).next_to(mergeLabel, DOWN)

        plot = VGroup(quickGraph, heapGraph, mergeGraph, insertionGraph, ax)
        labels = VGroup(quickLabel, heapLabel, mergeLabel, insertionLabel, graphLabels, graphTitle)

        self.add(plot, labels)
        