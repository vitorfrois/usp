## Bicicletários na USP
$X_{ij}$: quantidade de alunos que vão do prédio $i$ ao bicicletário $j$
$y_i$: 1 se há bicicletário $j$ e 0 c.c.

A função objetiva 
$$Min (\alpha\sum \sum b_{ij}x_{ij} + \gamma \sum c_j y_j)$$ busca minimizar o custo de instalação dos bicicletários e a distância caminhada por cada aluno.

Deve haver um máximo de 4 bicicletários
$\sum_{j=1}^{9} y_j \le 4$
Os 9 bicicletários devem atender a demanda dos prédios
$\sum_{j=1}^{9} x_{ij} = d_i$
A capacidade dos bicicletários instalados
$\sum_{i=1}^{12} x_{ij} \le Cap_j y_j$ 
$j=1...9$
$x_{ij} \in \Z^+$
$y_j \in {0,1}$

## Transporte de Alimentos
Deve-se enviar alimentos de São Paulo e BH até cidades do Sul passando por Curitiba e Porto Alegre minimizando custos.
$x_{ij}$: quantidade de alimentos que vai de $i$(SP, BH) para $j$(C, PA)
$y_{jk}$: quantidade de alimentos que vai de $j$(C, PA) para $k$(IT, RC, JS)

Alimento que sai de {São Paulo, Belo Horizonte}
$x_{SP,C}+x_{SP, PA} \le 1000$: alimento vindo de SP
$x_{BH,C}+x_{BH, PA} \le 800$: alimento vindo de BH

Transbordo 
$x_{PA} = y_{PA}$
$x_{C} = y_{C}$

O alimento que sai de {Curitiba, Porto Alegre} e vai para {Itá, Rio do Campo, Jaraguá do Sul}
$y_{C,IT}+y_{PA, IT} \ge 300$: alimento indo para Itá
$y_{C,RC}+y_{PA, RC} \ge 800$: alimento indo para Rio do Campo
$y_{C,JS}+y_{PA, JS} \ge 700$: alimento indo para Jaraguá do Sul

Buscamos minimizar os custos de transporte de alimentos
$$Min( \sum \sum c_{ij}x_{ij} + \sum \sum c_{jk}y_{jk} + \sum p_j z_j + \sum W_j w_j)$$
