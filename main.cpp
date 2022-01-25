#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

class Usuario{
  private:
      string nome;
      int cpf;
      int creditos;

  public:

      Usuario( string nome, int cpf){
        this->nome = nome;
        this->cpf = cpf;
        this->creditos = 10;
      };


      string getNome(){
        return this->nome;
      };
      

      void setNome(string nome){
        if(!nome.empty() && nome!=""){
          this->nome=nome;
        } else {
          cout << "Nome Inválido!" << endl;
        }
      };


      int getCPF(){
        return this->cpf;
      };
      

      int getCreditos(){
        return this->creditos;
      };


      bool adicionarCreditos(int novoCredito){
        if(novoCredito > 0){
          this->creditos+= novoCredito;
          cout << this->creditos;
          return true;  
        }else {
          return false;
        }
      };


      bool removerCreditos(int rCredito){
        if(this->creditos - rCredito >= 0){
          this->creditos-= rCredito;
          return true;  
        }else {
          return false;
        }
      };

      // postfix
      void operator ++(int){  
        this->creditos+= 1;
      };

      // prefix
      void operator ++(){  
        this->creditos+= 1;
      };

      // postfix
      void operator --(int){  
       if(this->creditos > 0){
          this->creditos-= 1;
        }else {
          cout << "Operação inválida! Créditos insuficiente." << endl;
        }
      };

      // prefix
      void operator --(){  
        if(this->creditos > 0){
          this->creditos-= 1;
        }else {
          cout << "Operação inválida! Créditos insuficiente." << endl;
        }
      };
};


class Cadastro{
  private:
    map<int, Usuario> usuarios;

  public:

    void adicionarUsuario(Usuario usuario){
      if(usuarios.count(usuario.getCPF())==0){
        usuarios.insert(make_pair(usuario.getCPF(),usuario));
        cout << "Usuario cadastrado com sucesso\n";
      }else {
          cout << "Operação inválida! Usuário já cadastrado com esse CPF." << endl;
        }
    }


    vector<Usuario> getUsuarios(){
      vector<Usuario> retorno;
      for (auto it = usuarios.begin(); it != usuarios.end(); it++){
           retorno.push_back(it->second);
      }
      return retorno;  
    }


    Usuario* getUsuarioPorCPF(int cpf){
      map<int,Usuario>::iterator it = usuarios.find(cpf);
        if(it != usuarios.end()){
         return &it->second;
        }else{
          cout <<"Não existe um usuário com este CPF\n"; 
         }
      Usuario nulo= Usuario("",0);
      return &nulo;
    }


    vector<Usuario> getUsuariosPorNome(string n){
      vector<Usuario> retorno;
      for (auto it = usuarios.begin(); it != usuarios.end(); it++){
        if(n == it->second.getNome()){
           retorno.push_back(it->second);
           cout << "cpf: " << it->second.getCPF() << " créditos: "<< it->second.getCreditos() << endl;
        }
      }
      return retorno;  
    } 


    void delUsuarioPorCPF(int cpfDel){
      usuarios.erase(cpfDel);
    } 


    vector<Usuario> getUsuariosOrdenado(){
      vector<Usuario> retornoCred = getUsuarios();
      sort(
        retornoCred.begin(),
        retornoCred.end(),
        [] (Usuario usuario1, Usuario usuario2){
          return usuario1.getCreditos() < usuario2.getCreditos();
        } 
      );
      for(auto it=retornoCred.begin(); it!=retornoCred.end(); it++){
        cout << "nome " << it->getNome() <<" cpf: " << it->getCPF() << " créditos: "<< it->getCreditos() << endl;
      }
      return retornoCred;
    }
};


int main(int argc,char *argv[]) {
  
  int opcao=0;
  Cadastro cadastro;
  string nomeAux;
  int cpfAux;
  int creditosAux;
  
  while(opcao!=8){
    cout << "\n\nSelecione uma das opções a seguir:\n";
    cout << "[1] Cadastrar Usuário\n";
    cout << "[2] Verificar Usuários por Nome\n";
    cout << "[3] Verificar Usuário por CPF\n";
    cout << "[4] Remover Usuário por CPF\n";
    cout << "[5] Listar Usuários ordenados por créditos\n";
    cout << "[6] Adicionar crédito por CPF\n";
    cout << "[7] Remover crédito por CPF\n";
    cout << "[8] Finalizar\n";

    cin >> opcao;
    nomeAux = "";
    cpfAux = 0;
    creditosAux=0;

    switch(opcao){
      case 1: 
        cout <<"Digite o nome do usuário: ";
        cin >> nomeAux;
        cout <<"\nDigite o CPF do usuário: ";
        cin >> cpfAux;
        cadastro.adicionarUsuario(Usuario(nomeAux,cpfAux));
      break;

      case 2: 
        cout <<"Digite o nome do usuário: ";
        cin >> nomeAux;
        cadastro.getUsuariosPorNome(nomeAux);
      break;

      case 3: 
        cout <<"Digite o CPF do usuário: ";
        cin >> cpfAux;
        cout << (*cadastro.getUsuarioPorCPF(cpfAux)).getNome();
      break;

      case 4: 
        cout <<"Digite o CPF do usuário a ser removido: ";
        cin >> cpfAux;
        cadastro.delUsuarioPorCPF(cpfAux);
      break;

      case 5:
        cadastro.getUsuariosOrdenado();
      break;

      case 6: 
        cout <<"Digite o CPF do usuário a ser adicionado créditos: ";
        cin >> cpfAux;
        cout <<"\nDigite o valor: ";
        cin >> creditosAux;
        (*cadastro.getUsuarioPorCPF(cpfAux)).adicionarCreditos(creditosAux);
      break;

      case 7: 
        cout <<"Digite o CPF do usuário a remover créditos: ";
        cin >> cpfAux;
        cout <<"\nDigite o valor: ";
        cin >> creditosAux;
        (*cadastro.getUsuarioPorCPF(cpfAux)).removerCreditos(creditosAux);
      break;

      case 8:
        cout << "\nOperação finalizada\n";
      break;

      default:
        cout << "\nOpção inválida!\n";
      break;
    }
  }

  return 0;
} 