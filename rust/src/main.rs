mod chamado;
mod fila;
mod pilha;
mod heap;
mod hash;
mod historico;
mod gerenciamento;
mod interface;

fn main() {
    let mut sistema = gerenciamento::Sistema::novo();
    interface::interface_executar(&mut sistema);
}
