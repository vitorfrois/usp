from manim import *

class BarChartExample(Scene):
    def construct(self):
        pull_req = [396, 135, 119, 102, 52, 48, 171]
        bases = [
            "Binária",
            "Octal",
            "Decimal",
            "Hexa",
            "256",
            "n",
            "k"
        ]
        title = Tex("Tempo de ordenação por Radix Sort com bases variadas em vetor esparso").move_to(DOWN*3.2).scale(0.8)
        label_y = Tex("Tempo (ms)").move_to(UP*2.85 + LEFT*2.5).scale(0.6)
        label_x = Tex("Bases").move_to(RIGHT*4.25 + DOWN *1.8).scale(0.6)

        colors = ["#003f5c", "#58508d", "#bc5090", "#ff6361", "#ffa600"]
        bar = BarChart(
            pull_req,
            max_value=max(pull_req),
            bar_names=bases,
            bar_label_scale_val=0.3,
            # label_y_axis= True,
            bar_colors=colors
        )
        self.add(bar, label_y, label_x, title)