# Álgebra Relacional

A álgebra relacional é composta por um conjunto de operadores utilizados para manipular relações como um todo.

Os operadores presentes podem ser divididos em 3 grupos:
1. Operadores sobre Conjuntos
2. Operadores Relacionais Unários
3. Operadores Relacionais Binários

Juntamente do operador renomear, representado por $\rho$.
$\rho((Aluno \cap Professor)/ Pessoa)$

## Operadores sobre Conjuntos
Quase todas os Operadores Relacionais sobre Conjuntos são binários. Para que duas relações possam ser operadas por um operadores sobre um conjunto é necessário que ambas sejam Compatíveis em Domínio.

Esperamos uma compatibilidade sintática, isto é, além dos dois conjuntos possuírem o mesmo número de atributos, cada par de atributos correspondentes tem o mesmo domínio.

$$
Aluno = (Nome, Idade, Curso)

Professor = (Nome, Idade, Depto)

Funcionario = (Nome, Depto, Idade)

Dom(nome): char(30),

Dom(idade): int,

Dom(Curso): char(12),

Dom(Depto): char(12)
$$

Professor é compatível com Aluno, mas não com Funcionário.

### Operadores Binários
#### União $T_1 \cup T_2$
Contém todas tuplas de T1 e todas tuplas de T2. Todas as tuplas que estão em ambas aparecem apenas uma vez.

#### Intersecção $T_1 \cap T_2$
Contém as tuplas que estão em T1 e T2.

#### Diferença $T_1 - T_2$ 
Contém tuplas que estão em T1 mas não em T2.

#### Complemento de uma relação $traco T$
Cardinalidade de um conjunto

#### Produto Cartesiano $T1 \times T2$
Não leva em conta a estrutura das relações. As tuplas são todas as combinações possíveis de valores de T1 com valores de T2.

### Operadores Unários
#### Operador de Selecão $\sigma_{(c)}T$
Aplicada sobre uma relação T, obtem o subconjunto das tuplas que satisfazem à condição c.
#### Projeção $\pi_{(<\textbf{lista de atributos}>)}T$
Seleciona colunas da relação.
