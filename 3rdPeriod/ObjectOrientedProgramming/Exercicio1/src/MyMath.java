public class MyMath {

    public static Double sqrt(Double x){
        Double x0 = x/10, x1 = x0;
        do{
            x0 = x1;
            x1 = (x0 + (x/x0))/2.0;
        }while(MyMath.abs((x0-x1)) > 0.00000001);
        return x1;
    }

    static Double[] baskhara(Double delta, Double a, Double b){
        Double[] raizes = new Double[2];
        raizes[0] = (-b+MyMath.sqrt(delta))/(2*a);
        raizes[1] = (-b-MyMath.sqrt(delta))/(2*a);
        return raizes;
    }

    public static boolean isPrime(int num) {
        for (int i = 2; i<= num/i; i++) {
            if (num % i == 0) {
                return false;
            }
        }
        return num > 1;
    }

    public static Double abs(Double x){
        if(x < 0) return x * -1;
        else return x;
    }

    static Double funcao(Double x){
        return (x*x*x) - (x*x) - (13*x) + (8);
    }
    static Double derivadaFuncao(Double x){
        return (3*x*x) - (2*x) - (13);
    }

    static void bissecao(){
        Double a = 0.0, b = 0.0, c = 0.0;
        System.out.println("Insira o intervalo [a,b] para calculo da função x³-x²-13x+8 através da bisseção");
        try{
            System.out.print("a = ");
            a = EntradaTeclado.leDouble();
        }catch (Exception IOException){
            System.out.println("Insira um double");
        }
        try{
            System.out.print("b = ");
            b = EntradaTeclado.leDouble();
        }catch (Exception IOException){
            System.out.println("Insira um double");
        }

        if (funcao(a) * funcao(b) >= 0){
            System.out.println("f(a) * f(b) >= 0. Insira novos valores de a e b");
            return;
        }
		int iteracoes = 0;
        while ((b-a) >= 0.00000001){
            iteracoes++;
			c = (a+b)/2;

            if (funcao(c) == 0.0) break;
            else if (funcao(c) * funcao(a) < 0)  b = c;
            else a = c;
        }
        System.out.print("A raiz da função é " + c + ". Foram necessárias " + iteracoes + " iterações");
    }

    static void newtonRaphson(){
        Double x0 = 0.0;
        try{
            System.out.print("Insira o chute inicial para calcular as raízes de " +
                    "x³-x²-13x+8 através do método de Newton Raphson. \nx0 = ");
            x0 = EntradaTeclado.leDouble();
        }catch (Exception IOException){
            System.out.println("Insira um Double");
        }

        Double x1 = MyMath.funcao(x0);
        Double erro = MyMath.abs((x1 - x0));
		int iteracoes = 0;
        while(erro >= 0.00000001) {
            iteracoes++;
			x0 = x1;
            x1 = x0 - (MyMath.funcao(x0)/MyMath.derivadaFuncao(x0));
            erro = MyMath.abs((x1 - x0));
        }
        System.out.println("Valor da raiz: " + x1 + ". Foram necessárias " + iteracoes + " iteracoes");

    }

}
