# Computação de Alto Desempenho

Resumo baseado nos conteúdos da Prova 1 de 2022 e no exercício proposto em Sala

### Qual a diferença entre o problema de consistência de memória e o problema de coerência de cache?

A consistência de memória garante que as operações de escrita e leitura em disco sejam realizadas da forma correta, utilizando-se, por exemplo, de regiões críticas. Já a coerência de cache busca garantir que todos os processadores tenham acesso às mesmas informações na cache através de invalidação e sincronização propostos em protocolos como o MESI.

### Quais fatores impedem a escalabilidade de um algoritmo paralelo?

O principal fator que impede a escalabilidade é o overhead de comunicação, que adiciona um custo fixo à adição de novos processores. Esse custo fixo corresponde a unificação de informação e comunicação entre processadores. Assim, nem sempre a paralelização irá promover um speedup satisfatório.

### Por que a GPU não é uma SIMD pura?

Uma máquina SIMD pura possui uma única thread com múltiplos dados. A GPU possui múltiplos threads, e dessa forma, se configura comoo um misto de MIMD e SIMD.

### Compare a rede Ômega (Multiestágio) com crossbar e barramento em relação a desempenho e custos.

As redes de barramento são bem simples, apresentando um baixo custo de implementação, em troca de um desempenho lento, dado que apenas uma comunicação pode acontecer por vez. Já a Crossbar supera esse problema ligando direamente os nós da rede em pares. A principal desvantagem dessa abordagem é o alto custo envolvido. As redes Ômega representam um meio termo entre as vantagem e desvantagens apresentadas nas primeiras redes. As entradas são conectadas às saídas através de vários estágios, garantindo uma comunicação robusta e eficiente sem altos custos presentes na Crossbar.
