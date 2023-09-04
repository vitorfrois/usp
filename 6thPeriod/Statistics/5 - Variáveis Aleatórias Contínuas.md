## Função de distribuição de probabilidade
Uma VA $X$ é contínua se existir uma função de densidade probabilidade $f(x)$ tal que
- $f(x) \ge 0, \forall x \in \mathbb{R}$
- $\int^{\infty}_{-\infty} f(x)dx = 1$
- $a, b \in \mathbb{R}, -\infty<a<b<\infty$ 
- $P(a \le x \le b) = \int^{b}_{a} f(x)dx$

## Função de distribuição acumulada
Podemos ainda definir um função de distribuição acumulada de uma VA $X$ com função de distribuição de probabilidade $f(x)$ é definida:
$F(x) = P(X \le x) = \int^{x}_{-\infty} f(s)ds$
Veja ainda que 
$P(a \le x \le b) = \int^{b}_{a} f(x)dx = F(b) - F(a)$

A função de distribuição acumulada é muito útil para calcular a função de distribuição de probabilidade.
$f(x) = \dfrac{\partial F(x)}{\partial x}$
**Exemplo**:
$F(x) = 1-e^{-x}$ (em vermelho)
$f(x)=\dfrac{\partial}{\partial x}[1-e^{-x}]=e^{-x}$ (em azul)

```functionplot
---
title: Gráficos
xLabel: x
yLabel: y
bounds: [-2,5,-2,2]
disableZoom: true
grid: true
---
g(x)=E^-x
f(x)=1-E^(-x)
```


