use crate::gerenciamento::Sistema;
use crate::chamado::{Status, Prioridade, Categoria};
use std::io::{self, Write};

fn ler_linha(prompt: &str) -> String {
    print!("{}", prompt);
    io::stdout().flush().unwrap();
    let mut entrada = String::new();
    io::stdin().read_line(&mut entrada).expect("Falha ao ler entrada");
    entrada.trim().to_string()
}

fn ler_numero_u64(prompt: &str) -> Option<u64> {
    let linha = ler_linha(prompt);
    linha.trim().parse::<u64>().ok()
}

fn ler_escolha_u32(prompt: &str, max: u32) -> Option<u32> {
    let linha = ler_linha(prompt);
    let valor: u32 = linha.trim().parse().ok()?;
    if valor <= max {
        Some(valor)
    } else {
        None
    }
}

pub fn interface_executar(sistema: &mut Sistema) {
    loop {
        println!(
            "\n=== GERENCIAMENTO DE CHAMADOS ===\n\
             1 Cadastrar\n\
             2 Listar aguardando triagem\n\
             3 Triar proximo\n\
             4 Listar pendentes (prioridade)\n\
             5 Iniciar proximo atendimento\n\
             6 Listar em atendimento\n\
             7 Concluir chamado\n\
             8 Consultar por ID\n\
             9 Historico\n\
             10 Alterar categoria\n\
             11 Alterar prioridade\n\
             12 Desfazer alteracao\n\
             13 Listar todos\n\
             0 Sair"
        );

        let opcao = match ler_escolha_u32("Opcao: ", 13) {
            Some(o) => o,
            None => {
                println!("Entrada invalida.");
                continue;
            }
        };

        if opcao == 0 {
            println!("Encerrando sistema...");
            break;
        }

        match opcao {
            1 => {
                let solicitante = ler_linha("Solicitante: ");
                let titulo = ler_linha("Titulo: ");
                let descricao = ler_linha("Descricao: ");

                if solicitante.is_empty() || titulo.is_empty() || descricao.is_empty() {
                    println!("Dados invalidos.");
                    continue;
                }

                let id = sistema.cadastrar(&solicitante, &titulo, &descricao);
                if id > 0 {
                    println!("Chamado cadastrado. ID: {}", id);
                } else {
                    println!("Falha ao cadastrar.");
                }
            }
            2 => {
                // Listar aguardando triagem
                sistema.listar_todos();
            }
            3 => {
                println!("Categoria (0 Hardware, 1 Software, 2 Rede, 3 Acesso, 4 Outros): ");
                let cat = match ler_escolha_u32("", 4) {
                    Some(c) => match c {
                        0 => Categoria::Hardware,
                        1 => Categoria::Software,
                        2 => Categoria::Rede,
                        3 => Categoria::Acesso,
                        _ => Categoria::Outros,
                    },
                    None => {
                        println!("Entrada invalida.");
                        continue;
                    }
                };

                println!("Prioridade (0 Baixa, 1 Media, 2 Alta, 3 Critica): ");
                let pri = match ler_escolha_u32("", 3) {
                    Some(p) => match p {
                        0 => Prioridade::Baixa,
                        1 => Prioridade::Media,
                        2 => Prioridade::Alta,
                        _ => Prioridade::Critica,
                    },
                    None => {
                        println!("Entrada invalida.");
                        continue;
                    }
                };

                match sistema.triar_proximo(cat, pri) {
                    Some(id) => println!("Chamado {} triado.", id),
                    None => println!("Nao foi possivel triar."),
                }
            }
            4 => {
                sistema.listar_todos();
            }
            5 => {
                match sistema.iniciar_atendimento() {
                    Some(id) => println!("Atendimento iniciado: {}", id),
                    None => println!("Nao ha chamados pendentes."),
                }
            }
            6 => {
                sistema.listar_todos();
            }
            7 => {
                match ler_numero_u64("ID: ") {
                    Some(id) => {
                        if sistema.concluir(id) {
                            println!("Chamado {} concluido.", id);
                        } else {
                            println!("Nao foi possivel concluir.");
                        }
                    }
                    None => println!("ID invalido."),
                }
            }
            8 => {
                match ler_numero_u64("ID: ") {
                    Some(id) => {
                        if let Some(c) = sistema.buscar(id) {
                            println!(
                                "\nID: {}\nStatus: {}\nCategoria: {}\nPrioridade: {}\n\
                                 Solicitante: {}\nTitulo: {}\nDescricao: {}",
                                c.id, c.status_nome(), c.categoria_nome(), c.prioridade_nome(),
                                c.solicitante, c.titulo, c.descricao
                            );
                        } else {
                            println!("Chamado nao encontrado.");
                        }
                    }
                    None => println!("ID invalido."),
                }
            }
            9 => {
                match ler_numero_u64("ID: ") {
                    Some(id) => {
                        if let Some(c) = sistema.buscar(id) {
                            println!("--- Historico do Chamado {} ---", id);
                            if c.historico.is_empty() {
                                println!("Sem historico.");
                            } else {
                                for (i, evento) in c.historico.iter().enumerate() {
                                    println!("{}. {}", i + 1, evento);
                                }
                            }
                        } else {
                            println!("Chamado nao encontrado.");
                        }
                    }
                    None => println!("ID invalido."),
                }
            }
            10 => {
                match ler_numero_u64("ID: ") {
                    Some(id) => {
                        println!("Nova categoria (0-4): ");
                        match ler_escolha_u32("", 4) {
                            Some(cat) => {
                                let categoria = match cat {
                                    0 => Categoria::Hardware,
                                    1 => Categoria::Software,
                                    2 => Categoria::Rede,
                                    3 => Categoria::Acesso,
                                    _ => Categoria::Outros,
                                };
                                if sistema.alterar_categoria(id, categoria) {
                                    println!("Categoria atualizada.");
                                } else {
                                    println!("Alteracao nao realizada.");
                                }
                            }
                            None => println!("Entrada invalida."),
                        }
                    }
                    None => println!("ID invalido."),
                }
            }
            11 => {
                match ler_numero_u64("ID: ") {
                    Some(id) => {
                        println!("Nova prioridade (0-3): ");
                        match ler_escolha_u32("", 3) {
                            Some(pri) => {
                                let prioridade = match pri {
                                    0 => Prioridade::Baixa,
                                    1 => Prioridade::Media,
                                    2 => Prioridade::Alta,
                                    _ => Prioridade::Critica,
                                };
                                if sistema.alterar_prioridade(id, prioridade) {
                                    println!("Prioridade atualizada.");
                                } else {
                                    println!("Alteracao nao realizada.");
                                }
                            }
                            None => println!("Entrada invalida."),
                        }
                    }
                    None => println!("ID invalido."),
                }
            }
            12 => {
                if sistema.desfazer() {
                    println!("Ultima alteracao desfeita.");
                } else {
                    println!("Nao ha alteracao reversivel.");
                }
            }
            13 => {
                sistema.listar_todos();
            }
            _ => println!("Opcao invalida!"),
        }
    }
}
