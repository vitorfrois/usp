public class Ex1 {
    public static void main(String[] args) throws Exception {
        Double x = EntradaTeclado.leDouble();
        Double x1 = MyMath.sqrt(x);
        System.out.print("Raiz quadrada de " + x + " é " + x1);
    }
}
