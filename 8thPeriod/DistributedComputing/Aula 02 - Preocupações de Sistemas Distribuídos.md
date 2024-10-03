Segunda-feira, 9 de setembro de 2024
[[SSC0904 - Sistemas Computacionais Distribuídos]]
<hr>

# Problemas
- Estudo de casos de problemas e soluções (geralmente cursos são assim)
- Começo da década de 90 começaram a juntar teoria sobre Sistemas Distribuídos
- Overlap com outros disciplinas
	- O que é próprio de sistemas distribuídos?
- Tenho um sistema, algoritmo para funcionar precisa de variáveis e seus valores, faz operações nessas variáveis. Se construa um sistema monolítico, mesmo que meu programa tenha várias threads, elas acessam as variáveis globais de ondem podem ler e escrever, da mesma memória. Quando opto por uma estrutura distribuídas, em que componentes rodam em plataformas computacionais separadas. Nesse arranjo, não temos variáveis globais para todos. Se 2 componente tem vars a e b, cada um deles têm suas cópias globais de a e b. Queremos mante-las atualizadas, mas esta atualização não tem como ser instantânea, pois estamos nos comunicando por uma rede, que tem um atraso de tempo que pode não ser desprezível.
- Jogo de FPS: você precisava avisar todo mundo da suas ações e posições, mas isso demora um tempo. Pode ser que para o outro jogador você ainda não abriu a porta, enquanto para você, você já abriu a porta. Se for mais rápido que o tempo de reação humana, ok, se não for, então nessa aplicação não tem como desprezar
- Sistemas fracamente acoplados (pesquisar)
- Interface com a disciplina de redes. Rodando em cima da rede, mas o foco não é a rede.
- Junta bits num frame e faz algum checksum para checar se não houve nenhuma alteração indevida. Bit de paridade é a forma mais simples de checagem.
- Envia frames de um lado para outro
- Camada a mais, camada de rede, onde ocorre roteamento nos roteadores. empacota o frame e vai passando de roteador em roteador.
- Queremos comunicar processo a processo, não apenas placa a placa. Então temos a camada de transporte, que comunica fim a fim, processo a processo. A camada de transporte tem ack, reordena os pacotes. Pede retransmissão se tiver problema.
- Em redes, ouvimos do tal de modelo OSI. O modelo OSI é um modelo de referência de arquitetura em camadas. Model o teórico. Existem outras camadas no OSI.
	- Camada de sessão. resolve problema dos de cima, em vez do dos debaixo. Caiu a conexão, cria outra conexão. Guardo o estado os se estava na sessão para poder continuar. Controle de diálogo (impressoras em rede, acabou o papel. ...)
	- Apresentação: preservação semântica. Manter o separador decimal, se é ASCII, se é UTF-8, ...
	- Aplicação em si
- Queremos que as coisas sejam transparentes. Não queremos que quem usa a aplicação tenha de saber ou se preocupar se o sistema é distribuído ou monolítico.
- Técnicas para quebrar uma tarefa em subtarefas que podem ser paralelizadas, tanto com threads numa mesma máquina com memória compartilhada, como com troca de mensagens numa rede distribuída, sem memória compartilhada e com comunicação que tem overhead.
- Sincronização é problema de computação concorrente
- Sistemas distribuídos: tolerância a falhas para garantir uma visão consistente dos estados do sistema.
# Comunicação
- Rede com componentes de uma aplicação distribuída
	- E.g: Micro-serviços que juntos compõe uma aplicação
	- E.g.Ou várias cópias de um banco de dados para balanceamento de carga, ou para tolerância a falhas
- Problema, não queremos que o fato de ser distribuído apareça, tem que ser tão simples de usar como se fosse monolítica
	- A rede pode mudar de topologia
	- As aplicações podem mudar de um lugar para outro
## Rede de canal único (Rede de Broadcast)
- Todos conectados no mesmo meio físico
- Internamente, um hub faz um curto em todos os cabos, replica todos os sinais
- Canal de broadcast
- Mensagem vai chegar em todo o mundo
- Cada placa de rede tem um endereço MAC
- Escrevemos o endereço MAC do destinatário
- Placas de rede educadas, não abre se não forem para elas, apesar de poder (modo promíscuo)
- Camada de rede não faz nada nessa topologia
## Caso da internet
- É complicada
- É uma WAN: conexão de diversas LAN's
- Socket é uma API que abre uma conexão de transporte
# Overlay network (pesquisar)
- Rede virtualmente ponto a ponto
- Não necessariamente ligando todos a todos
# Performance
- Tende a dar um problema de desempenho
- Avaliar eficiência da topologia overlay
	- Contagem de hops
	- Contagem de por quantos roteadores passaram
	- Tabelinha todos para todos
	- Critério: melhor média, melhor pior caso, etc.
- Links stress: quantos caminhos virtuais passam por um link físico
- Stretch factor (fator de esticamento): razão entre o custo de usar o overlay e o custo de usar a rede física.
	- Tenho o custo de comunicação de cada link. 
		- Delay
		- Taxa de erro
		- ...
	- O melhor é esticar o menos possível a rede