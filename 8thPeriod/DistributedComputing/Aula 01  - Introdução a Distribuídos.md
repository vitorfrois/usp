[[SSC0904 - Sistemas Computacionais Distribuídos]]
Segunda-feira, 12 de agosto de 2024
# Distributed Systems
* Aula para falar sobre o conteúdo da disciplina: motivação.
* Qual o problema que estamos tentando resolver? Por que Sistemas Distribuídos?
* Relacionadas a muitos outras disciplinas
* O que são sistemas distribuídos? Não é tão fácil de definir
# What is a Distributed System?
* Coleção de entidades independentes que cooperam para resolver um problema que não pode ser resolvido individualmente. (textbook definition)
* Coleção de elementos computacionais autônomos que parecem a seus usuários como um único sistema coerente. (Tanenbaum)
* Componentes localizados numa rede de computadores se comunicam e coordenam ações apenas por meio de passagem de mensagem. Leva a:
	* Concorrência entre componentes
	* Falta de um relógio global
	* Falhas independentes de componente

* Definições acima não motivam a gente

# Intuição
* Não é exclusivo de computação
* Sistemas distribuídos em diferentes contextos
	* Produção
	* Manufatura
	* Gerencial
* Em oposição a sistema centralizado
* Exemplo que não é computacional:
	* Pedra-papel-tesoura (PPT)
	* Ordem de precedência circular
	* Imagine um (PPT) em que oponentes estão em salas diferentes
	* Como fazer se não vemos a mão um do outro?
	* Apenas se tiver uma forma de os dois se comunicarem
	* Cada um faz uma escolha e escreve num papel
	* Joga papel por cima do muro
	* Ambos chegam a conclusões separadamente (e.g. A wins)
	* Há riscos envolvidos:
	* E se o papel de um lado chegou antes de o outro ter enviado a mensagem? O outro pode escolher o papel que o fará vencer, enganando o outro lado
* O que mudou:
	* Versão original: ambos veem os movimentos ao mesmo tempo
	* Neste caso, há uma informação compartilhada visual
	* Este "mesmo tempo" não é exatamente instantâneo. Mas é muito rápido a ponto de não ser distinguível do imediato
	* Na nova versão, é necessária uma troca de mensagens, tendo de confiar na validade destas mensagem
	* Não temos uma visão simultânea das mesmas variáveis
	* Cada thread tem suas variáveis, e têm de se comunicar
* 2 componentes A e B têm acesso a uma memória compartilhada -> coisas ficam mais fáceis; conhecimento simultâneo do estado global do sistema (shared data).
* Coisas começam a ficar difíceis quando não se tem mais memória compartilhada entre A e B. Cada um deles tem uma memória local própria.
* Muitas coisas podem acontecer de forma que estas "cópias locais" possam divergir
	* E.g. Tem que dar um jeito de atualizar todas as cópias igualmente. Quase impossível fazer isso ao exato mesmo tempo (ainda mais precisando de comunicação, pois comunicação não é instantânea). Imagina se nesse meio tempo o sistema tiver de tomar uma decisão baseada no valor dessas variáveis.
	* Comunicação também pode ser corrompida e está sujeita a erros. Pode enviar e não chegar. A confirmação pode não chegar. Timeout e manda de novo (incrementou duas vezes).
* Muitos probleminhas surgem no meio do caminho.
# Algoritmo de PPT
* init -> Pa = input_a -> Pb = message_b
* init -> Pa = message_a -> Pb = input_b

# Formalizando
* Sistemas Distribuídos
	* Vários componentes que para funcionar precisam concordar a respeito de alguns valores. Mas eles têm apenas cópias locais, sem visão do estado global. Para isto, vão precisar se comunicar.
* Ideia de solução: cada entidade:
	1. Anota timestamp
	2. Anota valor
	3. Espera tempo T
	4. Envia mensagem
	5. Recebe mensagem da outra entidade
	6. Checa se timestamp < T, OK; Caso contrário, há um problema.
* Para isso funcionar, os dois relógios têm de estar sincronizados, o que é impossível
* Imperfeições físicas impossíveis de serem eliminadas
* Trocar mensagem de tempos em tempos para sincronizar, mas recaímos no mesmo problema de concordar sobre um valor global por troca de mensagens.
# Formulação mais intuitiva
* Existe um problema de distribuição
* Sistema com esse problema é um Sistema Distribuído
* Problema de distribuição em um sistema: seus componentes não têm o conhecimento simultâneo de algum estado global e precisam se coordenar para inferir este estado global se comunicando através de um canal não-idea (ideal: mensagens instantâneas e corretas, de forma a ter uma visão global consistente).
* Também referidos como sistemas fracamente acoplados
* Não há um relógio global
# Hoje
* Tudo pensamos da perspectiva de redes
* Problemas então atuais
* Definição: sabe que está usando SD quando algum computador em algum outro lugar caiu e você não consegue terminar o seu serviço
* Recorrente
* Década de 90: indústria identificou, nomeou e passou a estudar sistemas computacionais distribuídos
* Outra maneira a se referir: sistemas fracamente acoplados
* Delay inevitável para se comunicarem
# Outro exemplo
* Futebol de robôs. 2 modalidades:
	* Centralizada: campo, câmera, sistema de IA, sistema toma uma decisão centralizada passada para os robozinhos
	* Descentralizada: sem câmera que vê e toma decisões, cada robozinho tem sua própria câmera e têm de tomar decisões baseada em sua própria visão, mas com expectativas sobre o que os outros farão de forma autônoma, se comunicando ("Eu vou chutar, você não, espera aí)
# Por quê?
* Se é difícil, porque não fazer um sistema centralizado e monolítico
* Primeiro, porque você quer isso. Quer que seu sistema esteja disponível em lugares diferentes, acessada por diversos usuários
* E.g.: jogos multiplayer -> jogos de tempo real, como FPS. Centralizado, teriam que todos vir a sua casa. Se quiser que diferentes jogadores na rede, terá que ser distribuído.
* Níveis diferentes de distribuição: servidor decide por todos. Chegada na mesma ordem (problema). Problema de lag se tiver que fazer todos os cálculos centralizados a todo momento. Como é feito: jogo é uma simulação de tempo real. Em vez de cada jogador com apenas um programa que desenha na tela o que servidor manda, cada programa de jogo é uma simulação. No meio do caminho podem ocorrem coisas estranhas. É preciso de quando em quando, todos sincronizarem, mas não a todo momento. Simulação tem nomes: pode ser conservativa (toda hora); outra mais arriscada, cada um com sua simulação. De tempos em tempos, sincroniza alguns estados, especialmente os mais importantes, não todos. Se conflitos houverem, tomar decisões.
* 2 tipos de decisão:
	* Rollback: volta e faz de novo
	* Arbitrária: escolhe um resultado
# Why?
* Shared resources
* Scalability: capacity elasticity, load balancing
* Cost: supercomputer vs. parallel computation
* Dependability: availability, fault tolerance
* Design approach: SOA (Service-oriented architecture), microservices

* Leilão online é uma questão judicial. Problema distribuído.
## Escalabilidade
* Elasticidade de Capacidade:
* Escala e desescala de forma dinâmica, com balanço de carga para obter o mesmo desempenho, pagando apenas pelo que usa.
* Manter réplicas de bancos de dados não é uma tarefa simples
* Por vezes: algoritmo do avestruz, se não for crítico (Facebook). Se for crítico (bancário), tem que tratar.
## Confiabilidade
* Um servidor só: dá problema nele, dá problema em tudo
* Backups que replicam para dar confiabilidade, redundância, mesmo sem balanço de carga, mesmo que as requisições vão para um só
* Leva ao conceito de tolerância a falha
## Custo de computação
* Alternativa mais fácil: comprar um supercomputador
* Muito bons, mas muito caros, porque são processadores com tecnologias muito especiais
* Em vez disso, compra muitos computadores normais, quebra o problema em pedaço, de forma a usar o paralelismo para ter um speedup
* Se der problema em um, troca
* Se quiser aumentar, compre mais máquinas
## Maneira de pensar
* Pensa numa aplicação, pensa numa aplicação Web
* Micro-serviços independentes
# Quais o principais problemas?
## 1. Concorrência
* Componentes executam independentemente e precisam sincronizar por comunicação
* Não podem escrever ao mesmo tempo em um arquivo
* Região crítica -> pede um lock
* E se forem dois processos em computadores separados, precisam se comunicar sobre o lock. Enquanto a comunicação não acontece, há um risco de dois processos obterem acesso ao lock. Problemas de Deadlock.
## 2. Falhas independentes
* Se um componente não responde, não se sabe muito bem o que aconteceu
## 3. Abstração da rede
* Quero editar meus arquivos compartilhado de forma transparente
* Quero usar minha aplicação do mesmo jeito, estando distribuído ou não

# Enfim, transparência (3 acima)
* Quero que mude daqui para trás, não para o usuário
* Não dever ser afetados por:
	* Localização
	* Relocação
	* Migração
	* Acesso
	* Replicação
	* Concorrência
# Relendo definições iniciais
* Coleção de entidades independentes que cooperam para resolver um problema que não pode ser resolvido individualmente. (textbook definition)
* Coleção de elementos computacionais autônomos que parecem a seus usuários com um único sistema coerente. (Tanenbaum) ((Transparência))
* Componentes localizados numa rede de computadores se comunicam e coordenam ações apenas por meio de passagem de mensagem. Leva a:
	* Concorrência entre componentes
	* Falta de um relógio global
	* Falhas independentes de componente (não sei porque o componente falhou, porque é preciso que ele diga o que deu errado, mas ele já não está conseguindo se )