import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThrows;

import ssc103.bozo.dados.Placar;

public class PlacarTest {

    Placar placar = new Placar();

    @Test
    public void testGetScore() {
        placar.add(1, new int[] {1,1,1,1,1});
        assertEquals(5, placar.getScore());

        placar.add(2, new int[] {2,2,2,2,2});
        assertEquals(15, placar.getScore());

        placar.add(3, new int[] {3,3,3,3,3});
        assertEquals(30, placar.getScore());

        placar.add(4, new int[] {4,4,4,4,4});
        assertEquals(50, placar.getScore());

        placar.add(5, new int[] {5,5,5,5,5});
        assertEquals(75, placar.getScore()); //valor errado

        placar.add(6, new int[] {6,6,6,6,6});
        assertEquals(105, placar.getScore());

        placar.add(7, new int[] {6,6,6,5,5});
        assertEquals(120, placar.getScore());

        placar.add(8, new int[] {1,2,3,4,5});
        assertEquals(140, placar.getScore());

        placar.add(9, new int[] {6,6,6,6,5});
        assertEquals(170, placar.getScore());

        placar.add(10, new int[] {6,6,6,6,6});
        assertEquals(210, placar.getScore());

    }

    @Test
    public void testToString() {
        placar.add(1, new int[] {1,1,1,1,1});
        String saidaEsperada =
                "5      |   (7)    |   (4) \n" +
                "--------------------------\n" +
                "(2)    |   (8)    |   (5) \n" +
                "--------------------------\n" +
                "(3)    |   (9)    |   (6) \n" +
                "--------------------------\n" +
                "       |   (10)   |\n" +
                "       +----------+\n";
        assertEquals(saidaEsperada, placar.toString());
    }

    @Test
    public void testePosicaoOcupada(){
        Exception exception = assertThrows(IllegalArgumentException.class, ()-> placar.add(0, new int[] {1,2,3,4,5}));
        String mensagemEsperada = "Valor da posição ilegal";
        String mensagemRecebida = exception.getMessage();
        assertEquals(mensagemEsperada, mensagemRecebida);
    }

    @Test
    public void testePosicaoInvalida(){
        placar.add(9, new int[] {6,6,6,6,5});
        Exception exception = assertThrows(IllegalArgumentException.class, ()-> placar.add(9, new int[] {1,2,3,4,5}));
        String mensagemEsperada = "Posição ocupada no placar";
        String mensagemRecebida = exception.getMessage();
        assertEquals(mensagemEsperada, mensagemRecebida);
    }
}