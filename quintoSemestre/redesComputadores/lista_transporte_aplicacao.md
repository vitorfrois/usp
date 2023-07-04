## Lista de Transporte e Aplicação
#### Vítor Amorim Fróis
#### 12543440

1. Um sistema baseado em IPv4 não possui capacidade de diferenciar dados sensíveis a atraso, tais como streaming e não sensíveis, como transferência de arquivos. jä o IPv6 garante baixa latência nessas aplicações quando comparado ao IPv4.

2.
    a. Um Denial of Service (DoS) é um ataque que tem o objetivo de atingir um servidor. Em específico, o SynFlood é um DoS que explora uma fraqueza do protocolo TCP/IP. Pelo protocolo TCP/IP, antes de iniciar a transmissão de dados é necessário realizar o Handshake em 3 etapas, processo que consiste em:

    - O cliente requisita uma conexão enviando um SYN ao servidor.
    - O servidor confirma esta requisição mandando um SYN-ACK de volta ao cliente.
    - O cliente por sua vez responde um ACK e a conexão está estabelecida.

    Um cliente malicioso, pode implementar o protocolo TCP de forma incompleta para não enviar essa última mensagem ACK. O servidor irá esperar isso por um tempo, já que um simples congestionamento de rede pode ser a causa do ACK em falta. A resposta maliciosa pode ocupar recursos no servidor, até o ponto em que todos estejam ocupados - nesse caso, nenhuma nova conexão pode ser feita, resultando em negação de serviço.

    b. 

3. 
