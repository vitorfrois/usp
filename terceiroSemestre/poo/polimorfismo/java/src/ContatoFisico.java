public class ContatoFisico() extends Contato{
    private String dataNascimento;
    private String estadoCivil;
    private String cpf;
    
    ContatoFisico(String nome, String endereço, String email, 
        String dataNascimento, String estadoCivil, String cpf){
        super(nome, endereço, email);
        this.dataNascimento = dataNascimento;
        this.estadoCivil = estadoCivil;
        this.cpf = cpf;
    }

    String toString(){
        super.toString();
        System.out.println("Data de nascimento: " + dataNascimento);
        System.out.println("Estado civil: " + estadoCivil);
        System.out.println("CPF: " + cpf);
    }
}