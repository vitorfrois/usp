public class ContatoJuridico() extends Contato{
    private String cnpj;
    private String razaoSocial;

    ContatoJuridico(String nome, String endereço, String email, 
        String cnpj, String razaoSocial){
        super(nome, endereço, email);
        this.cnpj = cnpj;
        this.razaoSocial = razaoSocial;
    }

    String toString(){
        super.toString();
        System.out.println("CNPJ: " + cnpj);
        System.out.println("Razão Social: " + razaoSocial);
    }
}