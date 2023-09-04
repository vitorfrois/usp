# Introdução
## Aprendizado de Máquina
> "**Machine Learning**: the field of study that giver computer the ability to learn without being explicitly programmed"

Pode ser exemplificado como uma função $g$ que aproxima $f: X \rightarrow Y$ por meio de um conjunto de testes $(x_i, y_i)$

## Série Temporal
Uma **série temporal** é um conjunto de valores ordenados x tal que 

- $x = (x_1,x_2,...,x_n)$
- $x_i \in \mathbb{R} ,\forall i \in {1,2,...,n}$

Séries temporais podem ser multivariadas ou multidimensionais quando $x_i \in \mathbb{R} ^d$

### Estacionaridade
Descreve como os dados se comportam ao longo do tempo. O teste mais comum para verificação é o de Dickey-Fuller.
```
from statsmodels.tsa.stattools import adfuller
adfuller(time_series)
```

Para algumas aplicações é necessário "estacionarizar" a série. Esse processo pode ser feito via **diferenciação**, que carrega problemas com variância.

### Componentes (de uma Série Temporal)
**Tendência**: a tendência indica o crescimento ou descrescimento dos valores de uma série e pode ser local ou global. Pode ser aproximada linearmente pelo método dos mínimos quadrados.
**Sazonalidade**: é calculada por $\dfrac{\text{série temporal}}{tendência}$ e mostra como a série se repete ao longo do tempo.
**Residual**: $\text{série temporal} - (\text{tendência}\times \text{sazonalidade})$. É o erro da aproximação da série feita pela tendência.
**Ciclicidade**: sazonalidade de longo termo que não pode ser demonstrada.

### Média Móvel
Para um valor $x_n$, pega a média de todos valores entre $x_{n-i}$ até $x_{n+i}$
É outra maneira de estimar a **tendência** da série temporal



**Estacionaridade de tendência**: 
Falta de tendência indica estacionaridade
