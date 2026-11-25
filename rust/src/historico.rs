use crate::chamado::Chamado;

/// Função para adicionar um evento ao histórico de um chamado.
pub fn adicionar(chamado: &mut Chamado, descricao: &str) {
    chamado.historico.push(descricao.to_string());
}