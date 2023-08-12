from manim import *

class sortingMethods(Scene):
    def construct(self):

        ax = Axes(
            x_range=[0, 10001, 2000],
            y_range=[0, 2401, 400],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 10001, 2000)},
            y_axis_config={"numbers_to_include": np.arange(0, 2401, 400)},
            tips=False,
        )
        graphLabels = ax.get_axis_labels(
            x_label=Tex("Tamanho do vetor"), y_label=Tex("Tempo ($\mu$s)")
        )

        #x_coordinates = [100, 1000, 10000, 100000]
        x_coordinates = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]

        insertion_x = merge_x = heap_x = quick_x = x_coordinates

        insertion_y = [96, 297, 738, 1141, 1761, 2555, 3439, 4411, 5653, 6892]
        insertionGraph = ax.get_line_graph(x_values=insertion_x, y_values=insertion_y, line_color=GREEN_C, add_vertex_dots=True, vertex_dot_radius=0.05)

        merge_y = [102, 186, 350, 510, 506, 629, 721, 833, 954, 1088]
        mergeGraph = ax.get_line_graph(x_values=merge_x, y_values=merge_y, line_color=PINK, add_vertex_dots=True, vertex_dot_radius=0.05)
        
        heap_y = [597, 1227, 1035, 931, 994, 1197, 1423, 1639, 1862, 2114]
        heapGraph = ax.get_line_graph(x_values=heap_x, y_values=heap_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        #heapLabel = ax.get_graph_label(heapGraph, "\int_a^b f'(x) dx = f(b)- f(a)")

        quick_y = [55, 116, 190, 266, 375, 406, 501, 585, 684, 745]
        quickGraph = ax.get_line_graph(x_values=quick_x, y_values=quick_y, line_color=RED, add_vertex_dots=True, vertex_dot_radius=0.05)

        insertionLabel = Text('Insertion Sort', color=GREEN_C).scale(0.4).next_to(heapGraph, UP);
        
        mergeLabel = Text('Merge Sort', color=PINK).scale(0.4).next_to(mergeGraph, UR);
        quickLabel = Text('Quick Sort', color=RED).scale(0.4).next_to(quickGraph, UR);
        heapLabel = Text('Heap Sort', color=BLUE).scale(0.4).next_to(heapGraph, UR);

        plot = VGroup(insertionGraph, mergeGraph, heapGraph, quickGraph, ax)
        labels = VGroup(graphLabels, insertionLabel, mergeLabel, heapLabel, quickLabel)

        self.add(plot, labels)
