## Lista de Transporte e Aplicação
#### Vítor Amorim Fróis - 12543440

### Links Importantes

[IPv6](https://www.gta.ufrj.br/grad/00_2/ipv6/text4.htm)

[Aula de Controle de Congestionamento (Jó)](https://www.youtube.com/watch?v=O7npnZXvTKw)



#### Resoluções

1. Um sistema baseado em IPv4 não possui capacidade de diferenciar dados sensíveis a atraso, tais como streaming e não sensíveis, como transferência de arquivos. Já o IPv6 garante baixa latência nessas aplicações quando comparado ao IPv4.

2.
    a. Um Denial of Service (DoS) é um ataque que tem o objetivo de atingir um servidor. Em específico, o SynFlood é um DoS que explora uma fraqueza do protocolo TCP/IP. Pelo protocolo TCP/IP, antes de iniciar a transmissão de dados é necessário realizar o Handshake em 3 etapas, processo que consiste em:

    - O cliente requisita uma conexão enviando um SYN ao servidor.
    - O servidor confirma esta requisição mandando um SYN-ACK de volta ao cliente.
    - O cliente por sua vez responde um ACK e a conexão está estabelecida.

    Um cliente malicioso, pode implementar o protocolo TCP de forma incompleta para não enviar essa última mensagem ACK. O servidor irá esperar isso por um tempo, já que um simples congestionamento de rede pode ser a causa do ACK em falta. A resposta maliciosa pode ocupar recursos no servidor, até o ponto em que todos estejam ocupados - nesse caso, nenhuma nova conexão pode ser feita, resultando em negação de serviço.

    b. 

3. 


4. Uma característica do User Datagram Protocol (UDP) é ser simples, isto é: não há estado de conexão nem no transmissor nem no receptor. Assim, todo Datagrama enviado por esse protocolo deve fornecer o endereçamento de destino.

5. O handshaking de uma conexão TCP se dá quando um cliente quer contatar um servidor e ocorre através dos seguintes passos:
    
    - O cliente requisita uma conexão enviando um SYN ao servidor.
    - O servidor confirma a requisição com um SYN-ACK.
    - O cliente por sua vez responde um ACK e a conexão está estabelecida

![texto](handshake.png)

6. 
    a. Os mecanismos de controle de fluxo e controle de congestionamento no protocolo são diferentes. 

    Quando os bytes chegam, são colocados em um buffer. O controle de fluxo existe para impedir que o buffer de recepção dos dados sature. Esse processo é gerenciado por uma técnica chamada Janela Deslizante.

    Já o controle de congestionamento visa impedir emissores enviando fluxo de dados acima da capacidade de tratamento da rede. 
    
    b. O controle de congestionamento no protocolo TCP é utilizado para previnir fluxo de rede acima do suportado. Quando há esgotamento da temporização de recebimento de ACK ou pela presença de ACKs duplicados, é identificado um congestionamento de rede. Para lidar com o fluxo anormal, é utilizada a janela de congestionamento, que limita-o via ACKs. Se um congestionamento for detectado, o sistema aciona a diminuição multiplicativa para diminuir a quantidade de dados recebida. Caso contrário, é utilizada recuperação aditiva para aumentar o fluxo de forma gradual até um certo limiar.

    

7. 