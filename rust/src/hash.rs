use crate::chamado::Chamado;
use std::collections::HashMap;

// Tipo alias para facilitar o uso
type TabelaHash = HashMap<u64, Chamado>;

/// Cria uma nova tabela hash vazia
pub fn nova() -> TabelaHash {
    HashMap::new()
}

pub fn inserir(tabela: &mut TabelaHash, chamado: Chamado) -> bool {
    // Verifica se o ID já existe
    if tabela.contains_key(&chamado.id) {
        false // ID duplicado
    } else {
        // Insere o chamado. A chave é o ID (u64), o valor é a struct Chamado.
        tabela.insert(chamado.id, chamado);
        true
    }
}// Insere um chamado na tabela hash. Retorna true se inserido com sucesso,
// false se o ID já existir.

pub fn buscar(tabela: &TabelaHash, id: u64) -> Option<&Chamado> {
    tabela.get(&id)
}// Busca um chamado pelo ID. Retorna Some(&Chamado) se encontrado, None caso contrário.

pub fn remover(tabela: &mut TabelaHash, id: u64) -> Option<Chamado> {
    tabela.remove(&id)
}// Remove um chamado pelo ID. Retorna Some(Chamado) se removido, None caso contrário.

pub fn tamanho(tabela: &TabelaHash) -> usize {
    tabela.len()
}// Retorna o número de chamados na tabela hash.

pub fn existe(tabela: &TabelaHash, id: u64) -> bool {
    tabela.contains_key(&id)
}// Verifica se um chamado com o ID existe na tabela hash. Retorna true se existir, 
// false caso contrário.