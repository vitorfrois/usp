public class Senha {
//    private int numeroAleatorio;
    static int tentativas = 0;
	static int numeroAleatorio;
    public Senha(int n){
        Random rd = new Random();
        numeroAleatorio = rd.getIntRand(n);
    }

    public static void main(String[] args){
        System.out.print("Insira o máximo N: ");
        int n = 0;
        try{
            n = EntradaTeclado.leInt();
        }catch(Exception IOException){
            System.out.println("N deve ser um inteiro!");
        }
        Senha jogo = new Senha(n);
		int chute = -1;
        while(chute != numeroAleatorio){
            try{
				System.out.print("Insira um chute: ");
				chute = EntradaTeclado.leInt();
			}catch(Exception IOException){
				System.out.println("O chute deve ser um inteiro. ");
			}
			novaTentativa(chute);
        }

    }

    static void novaTentativa(int chute){
        tentativas++;
        if(chute < numeroAleatorio){
            System.out.println("O número que você procura é maior que " + chute);
        }else if(chute > numeroAleatorio){
            System.out.println("O número que você procura é menor que " + chute);
        }else if(chute == numeroAleatorio){
            System.out.println(chute + " é o número procurado! ");
            System.out.println("Foram necessárias " + tentativas + " tentativas.");
        }
    }



}
