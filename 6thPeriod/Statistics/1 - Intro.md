> # Introdução à Estatística

### Determinístico VS Probabilístico

Em um modelo **determinístico**, podemos deduzir o resultado de um experimento com certeza.

Já em um modelo **probabilístico**, esperamos que um padrão emerja após um grande número de experimentos. Não podemos determinar exatamente o valor da saída, mas a probabilidade de cada uma.

## Conceitos fundamentais

**Espaço amostral** $(\Omega)$: Conjunto de saídas do experimento

**Evento (A)**: Um elemento do espaço amostral

**Evento impossível:** $\varnothing$

**Evento certo:** $\Omega$

$A \cup B$: é o evento que ocorre se A ou B ocorrem

$A \cap B$: é o evento que ocorre somente se ambos ocorrerem

$\bar A$: ocorre se A não ocorre

**Eventos mutualmente exclusivos**: $A \cap B = \varnothing$

## Axiomas da Probabilidade

Uma função $P$ é denominada uma medida de probabilidade se satisfaz 

- $0 \leq P(A) \leq 1, \forall A \in \Omega$
- $P(\Omega) = 1$
- Se $A, B$ forem mutuamente exclusivos, então $P(A \cup B) = P(A) + P(B)$

#### Probabilidade da união de eventos

$P(A \cup B)=P(A)+P(B)-P(A \cap B)$

**Prova**

$$
A \cup B = (\bar A \cap B)\cup(A \cap \bar B)U(A\cap B)
\\ \text{Como os eventos são mutuamente exclusivos, podemos escrever}
\\ P(A \cup B) = P(\bar A \cap B) + P(A \cap \bar B) + P(A\cap B)
\\ \text{Também sabemos que } P(\bar A \cap B) = P(A) - P(A \cap B), \text{ logo}
\\ P(A \cup B) = [P(A) - P(A \cap B)] + [P(B) - P(A \cap B)] + P(A\cap B)
\\ \text{Finalmente: } P(A \cup B) = P(A) + P(B) - P(A \cap B)
$$

**Probabilidade condicional**

Lê se como a probabilidade de A ocorrer dado que B ocorreu

$P(A|B)=\dfrac{P(A\cap B)}{P(B)}$

**Eventos independentes**

A e B são eventos independentes se, e somente se $P(A \cap B) = P(A)P(B)$



