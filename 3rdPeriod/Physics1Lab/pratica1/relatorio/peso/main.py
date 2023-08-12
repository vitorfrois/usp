from manim import *

class SquareToCircle(Scene):
    def construct(self):
        R1 = Ellipse(3,1).move_to(UP*2)
        R2 = Ellipse(3,1).move_to(DOWN*2)
        # r1 = Ellipse(3,1).move_to(UP*2).scale(0.5)
        # r2 = Ellipse(3,1).move_to(DOWN*2).scale(0.5)
        L1 = Line(DOWN*2+2*LEFT, UP*2+2*LEFT)
        self.add(R1, R2, L1)