package org.example;
import com.sun.source.tree.Tree;

import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.util.Objects;
import java.util.TreeMap;

public class ContaPalavra{
    String nomeArquivo;
    InputStream inputStream = null;
    private HashMap<String, Integer> map = new HashMap<String, Integer>();
    public ContaPalavra() throws IOException {
        //Tenta ler o nome do arquivo
        System.out.println("O arquivo a ser lido deve estar na pasta resources. ");
        System.out.print("Insira o nome do arquivo: ");
        try{
            nomeArquivo = EntradaTeclado.leString();
        }catch(Exception IOException){
            System.out.println("Insira uma string!");
        }
        //Abre o arquivo para leitura
        ClassLoader classLoader = getClass().getClassLoader();
        File file = new File(Objects.requireNonNull(classLoader.getResource(nomeArquivo)).getFile());
        try {
            inputStream = new FileInputStream(file);
        } catch (FileNotFoundException e) {
            System.out.println("Arquivo não encontrado! ");
        }
    }

    //Adiciona uma nova string ao HashMap
    public void adicionar(String palavra){
        if(map.containsKey(palavra)){
            map.put(palavra, map.get(palavra) + 1);
        }else{
            map.put(palavra, 1);
        }
    }

    //Cria o mapa lendo as palavras do arquivo texto
    public void criaMapa() throws IOException {
        int data;
        //Lê as palavras e usa a função inserir para colocar no
        //HashMap
        do{
            String palavra = "";
            data = inputStream.read();
            do {
                if(data != 32)
                    palavra += (char) Character.toLowerCase((char) data);
                data = inputStream.read();
            }while(data > 64 && data < 123);
            this.adicionar(palavra);
        }while(data != -1);
    }

    //Imprime o HashMap
    public void imprimir(){
        TreeMap<String, Integer> ordenado = new TreeMap<>(map);
        for(Map.Entry<String, Integer> elemento : ordenado.entrySet()){
            System.out.println(elemento.getKey() + " (" + elemento.getValue() + ")");
        }
    }

    //Fecha o arquivo aberto para leitura
    public void fechar(){
        if (inputStream != null) {
            try {
                inputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

}

