public class Dado {
    int lastLado = -1, lados = 6;
    Random dado = new Random();

    public Dado(){

    }

    public Dado(int n){
        lados = n;
    }

    //if no value is passed, the function consider a
    //6 sided dice
    public int rolar(){
        int resultado = dado.getIntRand(lados) + 1;
        lastLado = resultado;
        return resultado;
    }

    public int getLado(){
        return lastLado;
    }

    public String toString(){
        String s = "";
        //dice structure
        //  a       b
        //  c   d   e
        //  f       g
        char a, b, c, d, e, f, g;
        a = b = c = d = e = f = g = ' ';

        if(lastLado == 1){
            a = b = c = e = f = g = ' ';
            d = '*';
        }else if(lastLado == 2){
            a = c = d = e = g = ' ';
            b = f = '*';
        }else if(lastLado == 3){
            a = c = e = g = ' ';
            b = f = d = '*';
        }else if(lastLado == 4){
            c = d = e = ' ';
            a = b = f = g = '*';
        }else if(lastLado == 5){
            c = e = ' ';
            a = b = d = f = g = '*';
        }else if(lastLado == 6){
            d = ' ';
            a = b = c = e = f = g = '*';
        }
        s =     "+-----+    \n" +
                "|" + a + "   "           + b + "|    \n" +
                "|" + c + " "   + d + " " + e + "|    \n" +
                "|" + f + "   "           + g + "|    \n" +
                "+-----+ ";
        return s;
    }

    public static void main(String[] args){
        Dado dice = new Dado();
        int valor;
        valor = dice.rolar();
        System.out.println(valor);
        valor = dice.rolar();
        System.out.println(valor);
        System.out.println(dice.toString());
        System.out.println(dice.getLado());
    }
}
