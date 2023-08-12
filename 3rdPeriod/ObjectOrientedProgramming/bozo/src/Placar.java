public class Placar {
    int[] placarArray;

    public Placar(){
        placarArray = new int[10];
        for(int i = 0; i < 10; i++)
            placarArray[i] = -1;
    }

    public void add(int posicao, int[] dados){
        if(posicao > 10 || posicao < 0 || placarArray[posicao-1] != -1){
            throw new IllegalArgumentException();
        }
        placarArray[posicao-1] = 0;
        if(posicao <= 6){
            int count = 0;
            for(int i = 0; i < dados.length; i++){
                if(dados[i] == posicao){
                    count++;
                }
//
            }
            placarArray[posicao-1] = count * (posicao);
        }else{
            int[] count = new int[6];
            for(int i = 0; i < dados.length; i++)
                count[i] = 0;

            for(int i = 0; i < dados.length; i++){
                count[dados[i]-1]++;
//                System.out.println(dados[i]);
            }
            for(int i = 0; i < 6; i++)
                System.out.println(count[i]);

            //full hand
            if(posicao == 7){
                for(int i = 0; i < 6; i++)
                    if(count[i] >= 3)
                        placarArray[6] = 20;
            }
            //sequencia
            if(posicao == 8){
                int zeroCount = 0;
                for(int i = 0; i < 6; i++)
                    if(count[i] == 0) zeroCount++;
                if(zeroCount == 1 && (count[0] == 0 || count[5] == 0))
                    placarArray[7] = 30;
            }
            //quadra
            if(posicao == 9){
                for(int i = 0; i < 6; i++)
                    if(count[i] >= 4)
                        placarArray[8] = 40;
            }
            //quina
            if(posicao == 10){
                for(int i = 0; i < 6; i++)
                    if(count[i] >= 5)
                        placarArray[9] = 50;
            }
        }
    }

    public int getScore(){
        int score = 0;
        for(int i = 0; i < 10; i++){
            if(placarArray[i] != -1)
                score += placarArray[i];
        }
        return score;
    }

    public String toString(){
        String placar;
        String[] placarStringArray = new String[10];
        for(int i = 0; i < 10; i++){
            if(placarArray[i] != -1)
                placarStringArray[i] = " " + Integer.toString(placarArray[i]) + " ";
            else
                placarStringArray[i] = "(" + Integer.toString(i + 1) + ")";
        }
        placar = String.format(
                 "  %3s  |   %3s   |  %3s \n" +
                 " -------------------------\n" +
                 "  %3s  |   %3s   |  %3s \n" +
                 " -------------------------\n" +
                 "  %3s  |   %3s   |  %3s \n" +
                 " -------------------------\n" +
                 "       |   %3s   |\n"        +
                 "       +----------+\n",
                 placarStringArray[0],
                 placarStringArray[6],
                 placarStringArray[3],
                 placarStringArray[1],
                 placarStringArray[7],
                 placarStringArray[4],
                 placarStringArray[2],
                 placarStringArray[8],
                 placarStringArray[5],
                 placarStringArray[9]
                );
        return placar;

    }
}
