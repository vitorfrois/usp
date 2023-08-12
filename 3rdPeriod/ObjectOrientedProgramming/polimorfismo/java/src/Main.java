public class Main {
    String listaOpcoes = 
        "Escolha uma opção: \n" +
        "0 -> Sair \n" +
        "1 -> Adicionar pessoa física\n" +
        "2 -> Remover \n" +
        "3 -> Consultar por nome \n" +
        "4 -> Consultar por CPF/CNPJ \n" +
        "5 -> Mostrar todos contatos. \n";

    String stringAdicionar = 
        "1 -> Pessoa física\n" +
        "2 -> Pessoa jurídica\n";

    public static void main(String[] args) {

        Contato[] agenda = new Contato[];
        int opcao = -1;
        while(opcao != 0){
            System.out.println(listaOpcoes);
            opcao = EntradaTeclado.leInt();
            if(opcao == 1){
            
            }else if(opcao == 2){

            }else if(opcao == 3){

            }else if(opcao == 4){

            }else if(opcao == 5){

            }else{
                System.out.println("Opção desconhecida. \n")
            }


        }
    }
}