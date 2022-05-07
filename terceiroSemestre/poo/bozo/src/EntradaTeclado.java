import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class EntradaTeclado {
    static InputStreamReader isr;
    static BufferedReader br;

    public EntradaTeclado() {
    }

    public static String leString() throws IOException {
        return br.readLine();
    }

    public static int leInt() throws IOException {
        String x = leString();
        return Integer.parseInt(x);
    }

    public static Double leDouble() throws IOException{
        String x = leString();
        return Double.parseDouble(x);
    }

    static {
        isr = new InputStreamReader(System.in);
        br = new BufferedReader(isr);
    }
}