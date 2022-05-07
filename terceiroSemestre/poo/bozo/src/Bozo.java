public class Bozo {
    static public void main(String[] args){
        RolaDados dados = new RolaDados();
        Placar placar = new Placar();
        String sInput;
        for(int i = 0; i < 10; i++){
            sInput = "1";
            System.out.print("Pressione ENTER para iniciar a rodada. ");
            while(!sInput.equals("")){
                try{
                    sInput = EntradaTeclado.leString();
                }catch (Exception IOException){
                    System.out.println("Insira uma string! ");
                }
            }
            dados.rolar();
            System.out.println(dados.toString());
            for(int j = 0; j < 2; j++){
                System.out.print("Insira os dados a serem rolados separados por espaços: ");
                sInput = "";
                try{
                    sInput = EntradaTeclado.leString();
                }catch (Exception IOException){
                    System.out.println("Insira uma string! ");
                }
                dados.rolar(sInput);
                System.out.println(dados.toString());
            }
            System.out.println(placar.toString());
            int input = -1;
            System.out.print("Escolha uma posição: ");
            try{
                input = EntradaTeclado.leInt();
            }catch (Exception IOException){
                System.out.println("Insira um inteiro! ");
            }

            try{
                placar.add(input, dados.rolar(""));
            }catch(Exception IllegalArgumentException){
                System.out.println("Insira um valor válido! ");
            }

            System.out.print("\033[H\033[2J");
            System.out.flush();
            System.out.println("PONTUAÇÃO: " + placar.getScore());
            System.out.println(placar.toString());


        }
    }
}
