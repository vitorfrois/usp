# Teorema de Bayes
> "Probabilidade é uma opinião metódica e inferência de dados nada mais é do que a revisão de tal opinião com novas informações relevantes."

### Partição do espaço amostral

$B_1, B_2,...,B_n$ formam uma partição do espaço amostral se:
- $B_i \cap B_j = \empty$
- $\cup^n_{i=1}B_i=\Omega$
- $P(B_i) \ge 0$ | $i=1,...,n$

A partição também pode ser visualizada como as peças de um quebra cabeça.

Seja A um evento no espaço amostral, temos:
$A = \cup_n^{i=1}A\cap B_i$

### Teorema da Probabilidade Total
Baseado no corolário acima, segue

$P(A) = P( \cup_n^{i=1}A\cap B_i)$
$P(A) = \sum^n_{i=1} P(A\cap B_i)$

Pela aula de **Probabilidade Condicional**, sabemos que 
$P(A\cap B_i) = P(A | B_i)P(B_i)$ 
e portanto podemos reescrever a igualdade como

$P(A) = \sum^n_{i=1} P(A | B_i)P(B_i)$

Essa propriedade é muito útil pois permite reescrever probabilidades de um jeito mais fácil.

### Teorema de Bayes
Vamos demonstrar o teorema
$P(B_i | A) = \dfrac{P(A \cap B_i)}{P(A)}$

$P(B_i | A) = \dfrac
	{P(A | B_i)P(B_i)}
	{\sum^n_{j=1} P(A | B_j)P(B_j)}$

Os termos dessa equação são nomeados como

$\text{probabilidade a posteriori} = \dfrac
	{\text{verossimilhança}\times \text{priori}}
	{\text{evidência}}$
