from manim import *
import array as arr

from numpy import add

class functions(Scene):
    def construct(self):

        ax = Axes(
            x_range=[100, 1000, 100],
            y_range=[0, 40, 10],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 1000, 100)},
            y_axis_config={"numbers_to_include": np.arange(0, 40, 10)},
            tips=False,
        )
        graphLabels = ax.get_axis_labels(
            x_label=Tex("Tamanho do vetor"), y_label=Tex("Tempo ($\mu$s)")
        )
        
        x_coordinates = []
        for x in range(0, 10):
            x_coordinates.insert(x, 100+(x*100))

        bubble_x = x_coordinates
        insertion_x = x_coordinates
        merge_x = x_coordinates        

        bubble_y = [1,2,2,2,3,4,4,5,5,6]
        bubbleGraph = ax.get_line_graph(x_values=bubble_x, y_values=bubble_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        bubbleLabel = Text('Bubble Sort', color=BLUE).scale(0.4).next_to(bubbleGraph, UR);

        insertion_y = [4,5,7,9,12,13,15,19,26,29]
        insertionGraph = ax.get_line_graph(x_values=insertion_x, y_values=insertion_y, line_color=RED, add_vertex_dots=True, vertex_dot_radius=0.05)
        insertionLabel = Text('Insertion Sort', color=RED).scale(0.4).next_to(insertionGraph, UR);

        merge_y = [25,42,70,126,111,49,58,70,75,86]
        mergeGraph = ax.get_line_graph(x_values=merge_x, y_values=merge_y, line_color=YELLOW, add_vertex_dots=True,  vertex_dot_radius=0.05)
        mergeLabel = Text('Merge Sort', color=YELLOW).scale(0.4).next_to(mergeGraph, UR);

        plot = VGroup(bubbleGraph, insertionGraph, ax)
        labels = VGroup(bubbleLabel, insertionLabel, graphLabels)

        self.add(plot, labels)
        