## Vítor Amorim Fróis - 12543440
### a)
**Variáveis de decisão:** $x, y$ -> quantidade de poções do tipo $A$ e do tipo $B$ respectivamente
**Função objetiva:** $f(x, y) = (12A+8B)$ Buscamos  $Max(f)$
**Restrições:** 
- $2x+4y \le 32$
- $10x+5y \le 100$
- $6y \le 36$

**Domínio das variáveis:**
$x,y \in N^+$

### b)
Desenhamos as restrições através de inequações no plano.
![[Pasted image 20230920112316.png]]
Calculamos o vetor gradiente da função objetiva e encontramos a reta perpendicular a esse vetor.
![[Pasted image 20230920112358.png]]
A partir disso podemos encontrar o ponto pertencente ao espaço fornecido pelas **restrições** e gradiente que fornece o maior valor para a **função objetiva.**
![[Pasted image 20230920112157.png]]
Encontramos então o ponto $A = (8, 4)$ tal que $f(A)=128$
### c)
Caso houvesse apenas $24g$ de farinha, a reta azul ficaria exatamente na intersecção das retas. Assim, a solução continuaria igual.
![[Pasted image 20230920113046.png]]
### d)
Quando a poção $A$ cura 4 e a poção $B$ cura 12, obtemos uma nova função objetiva.
$f(A, B) = 4A+12B$ e, portanto, novo gradiente e reta perpendicular.
![[Pasted image 20230920113349.png]]
Ao aproximar a reta dos vértices das inequações, encontramos a solução ótima no ponto $B = (4, 6)$ tal que $f(B)=88$
![[Pasted image 20230920114212.png]]

