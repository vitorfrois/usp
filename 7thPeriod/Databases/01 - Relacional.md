# Modelo Relacional
Os dados são relacionados como um conjunto de relações em tabelas bidimensional

Armazena os dados utilizando apenas duas estruturas sintáticas: valores e relações

Define como conjunto de dados podem ser manipulados em operacoes CRUD: Create, Remove, Update & Delete

### Domínio de Dados
Os valores sao indivisiveis, chamados atômicos. Um domínio de dados é um conjunto de valores atômicos.

Exemplo: nome de alunos

Em geral é designado pelo Tipo de Dados

Atributos podem ser Monovalorados (Idade) ou Multivalorados (Irmaos).

### Notação 

{ } - Usam-se chaves para indicar conjuntos – conjuntos não podem repetir
elementos, e n˜ao existe ordem entre os elementos.
( ) - Usam-se parˆenteses para indicar listas – listas assumem uma ordem
entre os elementos.
[ ] - Usam-se colchetes para indicar valores numa tupla – especialmente
para identificar um elemento num conjunto.
< > - Usam-se chaves angulares para indicar tuplas – valores que
respeitam a ordem da lista que define a tupla.

#### Nome do Esquema da Relação
Aluno
#### Esquema da relção 
Aluno(NUSP, Idade,...)
#### Estado da Relação
Aluno{NUSP, Idade,...}

## Chaves no Modelo Relacional
### Superchave
Um conjunto de atributos de uma relação T que identifique univocadamente cada tupla em qualquer extensão do esquema é chamada uma Superchave.

Suponha $Aluno(Nome, RG, EstadoRG, Idade, Curso, NUSP)$.
As superchaves poderão ser
$SCh_1(Aluno)=\{RG, EstadoRG, Curso\}$

$SCh_2(Aluno)=\{NUSP, Idade\}$

## Chave 
É uma superchave da qual não se pode retirar nenhum atributo e ainda preservar-se a propriedade de identificação unívoca na relação.

$Ch_2(Aluno)=\{NUSP\}$

São úteis para buscar tuplas na relação. A convenção é de grifar os atributos que fazem parte de chaves candidatas.

## Chave Estrangeira
Outro tipo de chave é a chave estrangeira. Ela não é chave nesta relação.

Ocorre na relação T1 referente a T2 quando um conjunto de atributos $C \subseteq T1$ que não necessariamente é chave em T1, é compatível com a chave primária $D = Ch_0(T2)$ de uma relação T2.

Suponha duas tabelas, uma de alunos e outra de disciplinas.
O atributo NUSP de alunos é uma chave estrangeira em Disciplina.NUSP_Monitor.
(exemplo do slide)

## Definição de Base de Dados Relacional
Uma base de dados relacional usualmente compreende diversas relações. O esquema de uma base de dados relacional é:
- um conjunto de esquemas de relações
- um conjunto de restrições de integridade
Uma base de dados relacional (ou uma instância de uma base de dados relacional) é:
- um conjunto de relvars $BD = \{T1, T2,...,Tn\}$
- e toda relavar deve sempre satisfazer ao seu esquema e ao conjunto de restrições correspondente. 

### Integridade
- A chave candidata deve ser única
- A chave primária de qualquer relação não pode ser nula.
- O valor de um atributo que é chave estrangeira deve existir também como o valor da chave primária em uma tupla na relação correspondente.

Para o último item, como no exemplo acima, a Disciplina.NUSP_Monitor só pode referenciar um NUSP que existe na relação Alunos.


