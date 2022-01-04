from logging import log
from math import log10
from manim import *
import array as arr

from numpy import add

class functions(Scene):
    def construct(self):

        ax = Axes(
            x_range=[1, 1000, 100],
            y_range=[0, 15000, 1000],
            x_length=9,
            y_length=6,
            x_axis_config={"numbers_to_include": np.arange(0, 1000, 100)},
            y_axis_config={"numbers_to_include": np.arange(0, 15001, 3000)},
            tips=False,
        )
        graphLabels = ax.get_axis_labels(
            x_label=Tex("x"), y_label=Tex("y")
        )
        
        logGraph = ax.get_graph(lambda x: 4*x*log10(x), color=ORANGE)
        quadraticGraph = ax.get_graph(lambda x: x*log10(x), color=PURPLE)

        logGraphLabel = MathTex('4xlogx', color=ORANGE).scale(0.8).next_to(logGraph, UR)
        quadraticLabel = MathTex('xlogx', color=PURPLE).scale(0.8).next_to(quadraticGraph, UR)

        plot = VGroup(logGraph, quadraticGraph, ax)
        labels = VGroup(logGraphLabel, quadraticLabel, graphLabels)

        self.add(plot, labels)



