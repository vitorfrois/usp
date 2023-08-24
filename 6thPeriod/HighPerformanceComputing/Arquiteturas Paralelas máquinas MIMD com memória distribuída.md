## MIMD com memória distribuída
A coerência de cache existe somente em máquinas com memória compartilhada.
MIMD: Multiple Instruction, Multiple Data
- Existem diferentes computadores (ou nós)
- Interconectados por uma rede de conexão.

Cluster são formados por CPUs multicore.
- Threads que executam em um mesmo nó podem compartilhar memória

A rede de interconexão afeta a granulação do paralelismo
O projeto de algortimo deve maximizar concorrência e minmizar sobrecarregar comunicação.
**Escalabilidade absoluta**: há possibilidade de máquinas com vários nós
**Escalabilidade incremental**: novos nós podem ser adicionados.

**Middleware** são ferramentas para gerenciamento de escalonamento e balanceamento de carga. Caso um processo requira um ou mais processadores, ele faz uma análise sobre o número e tempo de processamento, por exemplo.


