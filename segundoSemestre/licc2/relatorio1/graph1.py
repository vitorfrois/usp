from manim import *
import array as arr

from numpy import add

class sortingMethods(MovingCameraScene):
    def construct(self):
        self.camera.frame.save_state()

        ax = Axes(
            x_range=[0, 10000, 2000],
            y_range=[0, 250000, 50000],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 10000, 2000)},
            y_axis_config={"numbers_to_include": np.arange(0, 250000, 50000)},
            tips=False,
        )
        graphLabels = ax.get_axis_labels(
            x_label=Tex("Tamanho do vetor"), y_label=Tex("Tempo ($\mu$s)")
        )

        x_coordinates = [25, 100, 1000, 10000]
        
        bubble_x = insertion_x = merge_x = x_coordinates
        bubble_y = [28, 221, 7924, 337603]
        bubbleGraph = ax.get_line_graph(x_values=bubble_x, y_values=bubble_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        #bubbleLabel = ax.get_graph_label(bubbleGraph, "\int_a^b f'(x) dx = f(b)- f(a)")

        insertion_y = [28, 34, 2124, 77047]
        insertionGraph = ax.get_line_graph(x_values=insertion_x, y_values=insertion_y, line_color=RED, add_vertex_dots=True, vertex_dot_radius=0.05)

        merge_y = [27, 86, 657, 5824]
        mergeGraph = ax.get_line_graph(x_values=merge_x, y_values=merge_y, line_color=YELLOW, add_vertex_dots=True,  vertex_dot_radius=0.05)

        insertionLabel = Text('Insertion Sort', color=RED).scale(0.4).next_to(insertionGraph, UR);
        bubbleLabel = Text('Bubble Sort', color=BLUE).scale(0.4).next_to(insertionLabel, LEFT*10+UP*5);
        mergeLabel = Text('Merge Sort', color=YELLOW).scale(0.4).next_to(mergeGraph);

        plot = VGroup(bubbleGraph, insertionGraph, mergeGraph, ax)
        labels = VGroup(graphLabels, bubbleLabel, insertionLabel, mergeLabel)

        self.add(plot, labels)

        t1 = Tex('Aqui é apresentado o gráfico de tempo de processamento dos métodos bubble, insertion e merge de ordenação para tamanhos de vetor de 25, 100, 1000 e 10000. Entretanto, é difícil analisar a eficiência dos algoritmos com gráficos de pouca profundidade. Assim, vamos aumentar o número de pontos para 20, de 0 a 10000, com espaçamento igual.', color=WHITE).scale(0.6).move_to(UP+RIGHT);
        self.play(Write(t1), FadeOut(bubbleLabel),run_time=8.0)
        self.wait(6)
        self.play(FadeOut(t1), FadeIn(bubbleLabel))

        axExtraDetailed = Axes(
            x_range=[0, 10000, 1000],
            y_range=[0, 375000, 30000],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 10000, 2000)},
            y_axis_config={"numbers_to_include": np.arange(0, 375000, 30000)},
            tips=True
        )

        for x in range(0, 20):
            x_coordinates.insert(x, 500+(x*500))

        bubble_x = x_coordinates
        insertion_x = x_coordinates
        merge_x = x_coordinates        

        bubbleLabelDetailed = Text('Bubble Sort', color=BLUE).scale(0.4).next_to(insertionLabel, LEFT*20);
        bubble_y = [2265,3435,5991,10885,18413,25820,36851,49177,63161,78892,96625,118754,143977,166427,194194,220683,255760,308457,322840,365868]
        bubbleExtraDetailedGraph = axExtraDetailed.get_line_graph(x_values=bubble_x, y_values=bubble_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        #bubbleLabel = axExtraDetailed.get_graph_label(bubbleGraph, "\int_a^b f'(x) dx = f(b)- f(a)")

        insertion_y = [827,3482,2808,3413,5254,7150,9720,12808,15970,19863,23611,28625,35832,38949,43793,54673,59170,71217,71640,85263]
        insertionExtraDetailedGraph = axExtraDetailed.get_line_graph(x_values=insertion_x, y_values=insertion_y, line_color=RED, add_vertex_dots=True, vertex_dot_radius=0.05)
        insertionLabelExtraDetailed = Text('Insertion Sort', color=RED).scale(0.4).next_to(insertionExtraDetailedGraph, UR);

        merge_y = [377,645,1307,1975,1160,933,839,969,842,994,1083,1114,1301,1410,1502,1511,1665,1719,1877,1944]
        mergeExtraDetailedGraph = axExtraDetailed.get_line_graph(x_values=merge_x, y_values=merge_y, line_color=YELLOW, add_vertex_dots=True,  vertex_dot_radius=0.05)
        

        self.wait(2)

        #self.play(Restore(self.camera.frame))

        self.play(
            Transform(bubbleGraph, bubbleExtraDetailedGraph),
            Transform(insertionGraph, insertionExtraDetailedGraph),
            Transform(mergeGraph, mergeExtraDetailedGraph),
            Transform(bubbleLabel, bubbleLabelDetailed),
            Transform(insertionLabel, insertionLabelExtraDetailed),
            Transform(ax, axExtraDetailed)   
        )   

        t1 = Tex('A função do Bubble Sort estoura devido a pouca eficiência do algoritmo.', color=WHITE).scale(0.6).move_to(UP+RIGHT);
        t2 = Tex('Portanto, é possível considerar somente os valores menores que 100ms,', color=WHITE).scale(0.6).next_to(t1, DOWN);
        t3 = Tex('afim de preservar o detalhe em outras regioes do gráfico.', color=WHITE).scale(0.6).next_to(t2, DOWN);

        self.play(Write(t1))
        circle = Circle(color=PINK).scale(0.5).move_to(2.9*UP+RIGHT*4.5)     
        self.play(Create(circle))
        self.play(Write(t2))
        self.play(Write(t3))
        self.wait(1)
        self.play(FadeOut(t1), FadeOut(t2), FadeOut(t3))

        axDetailed = Axes(
            x_range=[0, 10000, 1000],
            y_range=[0, 100000, 10000],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 10000, 2000)},
            y_axis_config={"numbers_to_include": np.arange(0, 100000, 10000)},
            tips=False
        )
        
        bubbleGraphDetailed = axDetailed.get_line_graph(x_values=bubble_x, y_values=bubble_y, line_color=BLUE, add_vertex_dots=True, vertex_dot_radius=0.05)
        insertionGraphDetailed = axDetailed.get_line_graph(x_values=insertion_x, y_values=insertion_y, line_color=RED, add_vertex_dots=True, vertex_dot_radius=0.05)
        mergeGraphDetailed = axDetailed.get_line_graph(x_values=merge_x, y_values=merge_y, line_color=YELLOW, add_vertex_dots=True,  vertex_dot_radius=0.05)
        
        insertionLabelDetailed = Text('Insertion Sort', color=RED).scale(0.4).next_to(insertionGraphDetailed, UR);

        avisoBubble = Tex('O gráfico vai pro infinito :P', color=BLUE).scale(0.4).move_to(UP*3+RIGHT*2);
        lastBubble = Text('Bubble Sort', color=BLUE).scale(0.4).next_to(insertionLabel, LEFT*10+UP*5);

        self.play(
            FadeOut(circle),
            Transform(bubbleGraph, bubbleGraphDetailed),
            Transform(insertionGraph, insertionGraphDetailed),
            Transform(mergeGraph, mergeGraphDetailed),
            Transform(ax, axDetailed),
            Transform(bubbleLabel, lastBubble),
            Transform(insertionLabel, insertionLabelDetailed),
            Write(avisoBubble)
        ) 
        self.wait(5)


