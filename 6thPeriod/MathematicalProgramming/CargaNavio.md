# Otimização de Carga do Navio

[Link para o enunciado](https://drive.google.com/file/d/1W7FlhBY0LBbGOyk8YP8ACwSC7ewgKLtu/view)

## Resolução

São oferecidos 3 tipos de cargas para organizar em 3 compartimentos.

O objetivo do exercício é **maximizar** o lucro. O lucro $L$ é a soma do lucro por tonelada de carga multiplicado pela respectiva quantidade de tonelagem para todas as cargas.

$$\text{Max}(L) \\ L= L_aT_a + L_bT_b + L_cT_c$$

A tonelagem total de cada carga será a soma da quantidade de carga por porão.

Carga a: $T_a = T_{ap} + T_{ac} + T_{ar}$

Carga b: $T_b = T_{bp} + T_{bc} + T_{br}$

Carga c: $T_c = T_{cp} + T_{cc} + T_{cr}$

Cada um dos valores acima deve ser positivo também.

$T_{ap}, T_{ac},...,  T_{cr} \ge 0$

Deve-se limitar a quantidade de $T$ para cada carga, portanto:

$T_a \le 7000$

$T_b \le 6500$

$T_a \le 4000$

Em cada porão - proa, centro e ré - deve haver quantidade máxima de volume e peso.

**Tonelagem máxima**

Proa: $T_p \le T_{ap} + T_{bp} + T_{cp}$ 

Centro: $T_c \le T_{ac} + T_{bc} + T_{cc}$

Ré: $T_r \le T_{ar} + T_{br} + T_{cr}$

**Volume máximo**

Considere $D_a$ o volume por tonelada da carga $a$.

Proa: $V_p \le D_aT_{ap} + D_bT_{bp} + D_cT_{cp}$ 

Centro: $V_c \le D_aT_{ac} + D_bT_{bc} + D_cT_{cc}$ 

Ré: $V_r \le D_aT_{ar} + D_bT_{br} + D_cT_{cr}$ 





