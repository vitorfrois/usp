package org.example;
import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {

        ContaPalavra cp = new ContaPalavra();
        //Cria um mapa baseado no arquivo aberto
        cp.criaMapa();
        //Imprime o mapa
        cp.imprimir();
        //Fecha o arquivo
        cp.fechar();

    }
}