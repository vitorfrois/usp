public class Ex6 {
    public static void main(String[] args){
        Double n = 0.0;
        Double menor = Double.POSITIVE_INFINITY, maior = Double.NEGATIVE_INFINITY;
        do{
            try {
                n = EntradaTeclado.leDouble();
            }catch(Exception IOException){
                System.out.println("Insira um número de ponto flutuante!");
            }
            if(n != 0){
                if(n < menor) menor = n;
                if(n > maior) maior = n;
            }
        }while(n != 0);
        System.out.print("O maior é " + maior + " e o menor é " + menor);
    }
}
