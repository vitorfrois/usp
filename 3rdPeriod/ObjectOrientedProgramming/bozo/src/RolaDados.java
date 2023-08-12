public class RolaDados {
    int numDados = 5;

    Dado[] dadoArray = createDiceArray(numDados);
    public RolaDados(int n){
        numDados = n;
        //create n dices
    }

    public RolaDados(){
        //create n dices
    }

    public Dado[] createDiceArray(int n){
        dadoArray = new Dado[n];
        for(int i = 0; i < numDados; i++){
            dadoArray[i] = new Dado();
            try {
                Thread.sleep(5);
            } catch (InterruptedException ex) {
                System.out.println("Erro! ");
            }
            //waits 5ms to create each dice
        }
        return dadoArray;
    }

    public int[] rolar(){
        int[] resultArray = new int[numDados];
        for(int i = 0; i < numDados; i++)
            resultArray[i] = dadoArray[i].rolar();

        return resultArray;
    }

    public int[] rolar(boolean[] quais){
        int[] resultArray = new int[numDados];
        for(int i = 0; i < numDados; i++){
            resultArray[i] = dadoArray[i].getLado();
            if(quais[i])
                resultArray[i] = dadoArray[i].rolar();
        }
        return resultArray;
    }

    public int[] rolar(String s){
        int[] diceArray = {};
        try{
            diceArray = rolar(atoi(s));
        }catch (Exception IllegalArgumentException){
            System.out.println("Insira um valor entre 1 e 5");
        }
        return diceArray;
    }

    public boolean[] atoi(String s){
        int stringSize = s.length();
        String stringNumber;
        boolean[] quais = new boolean[numDados];
        for(int i = 0; i < numDados; i++)
            quais[i] = false;
        int number;
        int i = 0;
        while(i < stringSize) {
//            stringNumber = "";
            if (s.charAt(i) != ' ') {
                number = Character.getNumericValue(s.charAt(i));
                if(number < 0 || number > numDados){
                    throw new IllegalArgumentException();
                }
                quais[number - 1] = true;
            }
            i++;
        }
        return quais;
    }


    public String toString(){
        String retorno = "";
        for(int i = 0; i < numDados; i++){
            retorno += (i+1) + "          ";
        }
        retorno += "\n";
        //dice structure
        //  0       1
        //  2   3   4
        //  5       6
        char[][] DNAMatrix = new char[8][numDados];
        //Dice Number Arrangement MATRIX
        //[position][diceNumber]
        for(int i = 0; i < numDados; i++)
            for(int j = 0; j < 8; j++)
                DNAMatrix[j][i] = ' ';
//
        for(int i = 0; i < numDados; i++){
            if(dadoArray[i].getLado() == 1){
                DNAMatrix[3][i] = '*';
            }else if(dadoArray[i].getLado() == 2){
                DNAMatrix[1][i] = '*';
                DNAMatrix[5][i] = '*';
            }else if(dadoArray[i].getLado() == 3){
                DNAMatrix[1][i] = '*';
                DNAMatrix[3][i] = '*';
                DNAMatrix[5][i] = '*';
            }else if(dadoArray[i].getLado() == 4){
                DNAMatrix[0][i] = '*';
                DNAMatrix[1][i] = '*';
                DNAMatrix[5][i] = '*';
                DNAMatrix[6][i] = '*';
            }else if(dadoArray[i].getLado() == 5){
                DNAMatrix[0][i] = '*';
                DNAMatrix[1][i] = '*';
                DNAMatrix[3][i] = '*';
                DNAMatrix[5][i] = '*';
                DNAMatrix[6][i] = '*';
            }else if(dadoArray[i].getLado() == 6){
                DNAMatrix[0][i] = '*';
                DNAMatrix[1][i] = '*';
                DNAMatrix[2][i] = '*';
                DNAMatrix[4][i] = '*';
                DNAMatrix[5][i] = '*';
                DNAMatrix[6][i] = '*';
            }
        }
        for(int i = 0; i < numDados; i++){
            retorno += "+-----+   ";
        }
        retorno += "\n";

        for(int i = 0; i < numDados; i++){
            retorno += String.format("|%s   %s|   ",
                    DNAMatrix[0][i],
                    DNAMatrix[1][i]);
        }
        retorno += "\n";

        for(int i = 0; i < numDados; i++){
            retorno += String.format("|%s %s %s|   ",
                    DNAMatrix[2][i],
                    DNAMatrix[3][i],
                    DNAMatrix[4][i]);
        }
        retorno += "\n";

        for(int i = 0; i < numDados; i++){
            retorno += String.format("|%s   %s|   ",
                    DNAMatrix[5][i],
                    DNAMatrix[6][i]);
        }

        retorno += "\n";

        for(int i = 0; i < numDados; i++){
            retorno += "+-----+   ";
        }
        retorno += "\n";
        return retorno;
    }

    public static void main(String args[]){
        RolaDados dados = new RolaDados();
        Placar placar = new Placar();
        int input = -1;
        while(input != 0){
            dados.rolar();
            System.out.println(dados.toString());
            try{
                input = EntradaTeclado.leInt();
            }catch (Exception IOException){
                System.out.println("Insira um inteiro! ");
            }
            placar.add(input, dados.rolar(""));
            System.out.println("pontuação = " + placar.getScore());
        }

    }
}
