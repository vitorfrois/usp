public class Ex3 {
    public static void main(String[] args){
        int n;
        try{
            n = EntradaTeclado.leInt();
        }catch(Exception IOException){
            System.out.println("Insira um inteiro");
            return;
        }
        for(int i = n; i > 0; i--){
            for(int j = 0; j < i; j++) System.out.print("*");
            System.out.print("\n");
        }
    }
}
