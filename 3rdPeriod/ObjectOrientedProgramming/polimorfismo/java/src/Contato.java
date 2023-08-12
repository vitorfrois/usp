public class Contato {
    private String nome;
    private String endereço;
    private String email;
    
    Contato(String nome, String endereço, String email){
        this.nome = nome;
        this.endereço = endereço;
        this.email = email;
    }

    String toString(){
        System.out.println("Nome: " + nome);
        System.out.println("Endereço: " + endereço);
        System.out.println("email: " + email);
    }
    
}
