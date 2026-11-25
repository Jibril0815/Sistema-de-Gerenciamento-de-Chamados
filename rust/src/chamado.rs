#[derive(Debug, Clone, PartialEq, Eq)]

#[allow(non_camel_case_types)]

pub enum Status {
    AguardandoTriagem,
    Pendente,
    EmAtendimento,
    Concluido,
}//enumeração que representa os possíveis status de um chamado.

#[derive(Debug, Clone, PartialEq, Eq)]
#[allow(non_camel_case_types)]

pub enum Prioridade {
    Baixa,
    Media,
    Alta,
    Critica,
}//enumeração que representa os possíveis níveis de prioridade de um chamado.

#[derive(Debug, Clone, PartialEq, Eq)]
#[allow(non_camel_case_types)]

pub enum Categoria {
    Hardware,
    Software,
    Rede,
    Acesso,
    Outros,
}//enumeração que representa as possíveis categorias de um chamado.

#[derive(Debug, Clone)]

pub struct Chamado {
    pub id: u64,
    pub ordem_chegada: u64,
    pub solicitante: String,
    pub titulo: String,
    pub descricao: String,
    pub status: Status,
    pub prioridade: Prioridade,
    pub categoria: Categoria,
    pub historico: Vec<String>,
}

impl Chamado {

    pub fn new(
        id: u64,
        ordem_chegada: u64,
        solicitante: String,
        titulo: String,
        descricao: String,
        status: Status,
        prioridade: Prioridade,
        categoria: Categoria,
    ) -> Self {
        Chamado {
            id,
            ordem_chegada: id,
            solicitante: solicitante.to_string(),
            titulo: titulo.to_string(),
            descricao: descricao.to_string(),
            status,
            prioridade,
            categoria,
            historico: Vec::new(),
        }
    }

    pub fn status_nome(&self) -> String {
        match self.status {
            Status::AguardandoTriagem => "Aguardando Triagem",
            Status::Pendente => "Pendente",
            Status::EmAtendimento => "Em Atendimento",
            Status::Concluido => "Concluído",
        }.to_string()
    }

    pub fn prioridade_nome(&self) -> String {
        match self.prioridade {
            Prioridade::Baixa => "Baixa",
            Prioridade::Media => "Média",
            Prioridade::Alta => "Alta",
            Prioridade::Critica => "Crítica",
        }.to_string()
    }

    pub fn categoria_nome(&self) -> String {
        match self.categoria {
            Categoria::Hardware => "Hardware",
            Categoria::Software => "Software",
            Categoria::Rede => "Rede",
            Categoria::Acesso => "Acesso",
            Categoria::Outros => "Outros",
        }.to_string()
    }
}

// --- Implementação do trait Ord para o BinaryHeap ---

// O BinaryHeap do Rust precisa que o tipo implemente Ord (ordenação total).
// Como queremos que o chamado de MAIOR prioridade fique no topo,
// implementamos a comparação inversamente.

impl Ord for Chamado {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        // Primeiro compara por prioridade (maior vence)
        // Depois, em caso de empate, compara por ordem de chegada (menor número = chegou primeiro)
        match self.prioridade.cmp(&other.prioridade) {
            std::cmp::Ordering::Equal => self.ordem_chegada.cmp(&other.ordem_chegada),
            other_order => other_order,
        }
    }
}

// Implementação de PartialOrd (necessária para Ord)
impl PartialOrd for Chamado {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}
