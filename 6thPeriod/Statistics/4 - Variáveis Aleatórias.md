# Variáveis Aleatórias
Uma variável aleatória (VA) é uma **função** que mapeia o espaço amostral na reta real, sendo que cada elemento do espaço e mapeado em um valor real
### Exemplo
Suponha que lancemos duas moedas. O espaço amostral $\Omega$ associado ao experimento é dado por 
$\Omega = \{ CC, CR, RC, RR\}$
Uma possível VA associada ao experimento é definida por $X:$ número de caras.
$X(CC)=2$
$X(CR)=1$
$X(RC)=1$
$X(RR)=0$

### Notação 
$X, Y, Z, W:$ variáveis aleatórias
$x, y, z, w:$ valores das variáveis aleatórias

### Distribuição de Probabilidade 
### Exemplo
Duas bolas são retiradas sucessivamente, sem reposição, de uma caixa que contém 5 bolas vermelhas e 4 pretas. Seja a variável aleatória $X$: "número de bolas vermelhas retiradas no experimento". Determine a distribuição de probabilidade de $X$.

$X:\{0,1,2\}$

Vamos começar escrevendo as probabilidades de $X$ de acordo com as retiradas de 2 bolas seguidas.

| Saídas | $X$ | $P(X=x_i)$ |
|--------|---|--------|
| (V, P) | $1$ | $\dfrac{5}{9}$$\dfrac{4}{8}$      |
| (P, V) | $1$ | $\dfrac{4}{9}$$\dfrac{5}{8}$      |
| (V, V) | $2$ | $\dfrac{5}{9}$$\dfrac{4}{8}$      |
| (P, P) | $0$ | $\dfrac{4}{9}$$\dfrac{3}{8}$      |

Agora podemos escrever a distribuição de probabilidade

| $X$          | $0$                            | $1$                            | $2$                            |
|------------|------------------------------|------------------------------|------------------------------|
| $P(X=x_i)$ | $\dfrac{12}{72}$ | $\dfrac{40}{72}$ | $\dfrac{20}{72}$ |

Observamos também que a soma das probabilidades resulta em 1.
