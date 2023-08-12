import java.io.IOException;

public class Ex2 {
    public static void main(String[] args){
        Double a = 0.0, b = 0.0, c = 0.0;
        try{
            a = EntradaTeclado.leDouble();
        }catch(Exception IOException) {
            System.out.println("Insira um número inteiro!");
        }
        try{
            b = EntradaTeclado.leDouble();
        }catch(Exception IOException) {
            System.out.println("Insira um número inteiro!");
        }
        try{
            c = EntradaTeclado.leDouble();
        }catch(Exception IOException){
            System.out.println("Insira um número inteiro!");
        }

        Double delta = (b*b) - (4*a*c);
        if(delta < 0) {
            System.out.println("Delta negativo");
            return;
        }
        Double[] raizes = MyMath.baskhara(delta, a, b);
        System.out.printf("Raízes são " + raizes[0] + " e " + raizes[1]);
    }



}
