# Caso Discreto
Seja $X$ uma VA discreta, o m-ésimo momento estatístico é definido por 
$E[X^m]=\sum^\infty_{i=1}x_{i}^m P(X=x_{i})$
desde que a soma **convirja**
O **primeiro momento estatístico** é o valor esperado de $X$
$E[X]=\sum^\infty_{i=1}x_{i} P(X=x_{i})$

### Exemplo
Seja $X$ o valor da face em um lançamento de um dado. Determine $E[X]$
$$
E[X]=\sum^6_{i=1}i P(X=i) = 1 \frac{1}{6} + \dots + 6 \frac{1}{6}=\frac{7}{2}
$$
Ao simular esse experimento, obtemos o valor médio de 3,5. 
Podemos dizer que o primeiro momento é a média.
### Propriedades
$E[aX+b] = aE[X] + b$
## Variância
Seja $X$ uma variável aleatória discreta. O m-ésimo momento central é definido por 
$E[(X - E[X])^m]$
O **primeiro momento central** é igual a zero.
O **segundo momento central** é a variância.
$E[(X - E[X])^2]=E[X^2]-E[X]^2$

### Exemplo:
**Calcule o valor esperado e a variância do modelo de Poisson**
Distribuição de Poisson: $P(X=k)=\dfrac{e^{- \lambda} \lambda ^k}{k!}$
$E[x]=\lambda$
$V(x)=\lambda$

# Caso Contínuo
Seja $X$ uma VA discreta, o m-ésimo momento estatístico é definido por 
$E[X^m]=\int_{-\infty}^\infty x^m f(x) \, dx$
O **primeiro momento** é igual a 0
$E[(X - E[X])^1] = 0$
O segundo momento central é a variância
$$
E[(X - E[X])^2] = E[X^2] - E[X]^2
$$
$$
E[X^2] - E[X]^2 = \int_{-\infty}^\infty x^2 f(x) \, dx - (\int_{-\infty}^\infty x f(x) \, dx)^2
$$
