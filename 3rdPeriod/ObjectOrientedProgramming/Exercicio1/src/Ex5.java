public class Ex5 {
    public static void main(String[] args){
        int n;
        try {
            n = EntradaTeclado.leInt();
        }catch(Exception IOException) {
            System.out.println("Insira um número inteiro");
            return;
        }
        int original = n;
        while(!MyMath.isPrime(n)) n--;
        System.out.print("O primo mais próximo de " + original + " é " + n);
    }
}
