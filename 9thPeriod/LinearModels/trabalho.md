---
title: Modelos Lineares em Grafos
---

## Introdução 

Aprendizado de Máquina em Grafos é uma tarefa difícil. Na era do aprendizado profundo, modelos de redes convolucionais foram adaptados para grafos. 
O trabalho Heat Kernel Convolutional Graph Networks define o modelo 
$$
Y = \text{softmax}(e^{(-\tilde{L}t)}\mathbf{X}\mathbf{W})
$$
onde $W$ são os pesos aprendidos, $L$ é a matriz laplaciana, e $X$ é a matriz de features.

A ideia do método é propagar as features aos vizinhos de acordo com a difusão (representada pelo Heat/Difusion Kernel) sobre os nós do grafo.
O artigo é uma adaptação do Simple Graph Convolutions (SGC), que utiliza a própria matriz de adjacência para essa comparação.

Dessa forma, podemos realizar uma análise espectral do efeito de $e^{(-\tilde{L}t)}$ (difusão ao longo do tempo $t$) sobre a matriz de features.

## Análise Espectral

A seção 3.5 do artigo Heat Kernel Graph Convolutions apresenta uma análise espectral da difusão sobre as features. Os tópicos discutidos são

- Revisão de Análise Espectral: transformada de Fourier em grafos
- Heat Kernel: difusão por um ponto de vista espectral
- Efeito de diferentes kernels sobre as features
- Influência das altas frequências

Tem cerca de uma página com conteúdo denso e acho que conseguimos obter um relatório legal a partir disso. 

![](HKGN.png)

## Referências

- [Heat Kernel Graph Convolutions](https://openreview.net/forum?id=yBJihVXahXc)
- [Simplifying Graph Convolutions](https://arxiv.org/abs/1902.07153)
