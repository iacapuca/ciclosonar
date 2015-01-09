/*
PROGRAMA CICLOSSONAR
Versão 0.2
Pedro Luiz Santos e Daniel Valença
Data de modificacao: 2015.01.08
*/
 
/*
MARCO LEGAL:
É definida a distância conforme o Código Brasileiro de Trânsito
em seu artigo 201, como 1,5m o mínimo para ultrapassagem de um
ciclista pelo motorista. No artigo XXX é definido que deve-se
diminuir a velocidade ao ultrapassar os ciclistas para uma
compatível com a seguraça.
 
OBJETIVOS:
O projeto Ciclossonar tem como objetivo medir a distância
que os motoristas passam ao ultrapassar os ciclistas e com
isso fomentar políticas públicas que reduzam acidentes e
estimulem um trânsito seguro e humano.
 
OBJETIVOS ESPECÍFICOS:
1 - Medir a distância em cada ponto da bicicleta
2 - Medir a velocidade do ciclista
3 - Medir a velocidade relativa do motorista com o ciclista
4 - Medir a velocidade do motorista
5 - Medir o tamanho do veículo que realiza ultrapassagem
6 - Quantificar a quantidade de finos que o ciclista recebe:
6.1 - Ao passar em ruas mais ou menos movimentadas
6.2 - Por andar no canto ou mais ao centro da faixa
6.3 - Conforme seu sexo
6.4 - Conforme sua roupa e acessórios
6.5 - Conforme sua bicicleta
7 - Medir o que influencia mais da distância ou da velocidade
no conforto do ciclista ao pedalar, conforme sua experiência
 
*/
 
/*
ETAPAS NECESSÀRIAS NO CÓDIGO DO ARDUÍNO
0.1  - Medir distância com sonar 1                        - OK
0.11 - Medir distância com sonar 2                        - OK
0.12 - Medir distância média                              - OK
0.2  - Gravar no Cartão SD                                - OK
0.21 - Bluetooth enviar dados para o celular              - OK
0.3  - Adicionar "botão do pânico"                        - OK - Tem erros de compilação que foram corrigidos em 3.1
0.31 - Buzzer ao apertar o botão                          - OK
0.4  - Medir velocidade da bicicleta                      -
0.5  - Receber dados do celular                           -
0.51 - Receber dados GPS do celular                       -
0.52 - Receber configuração pelo celular                  -
0.5  - Controle de falsos positivos                       - Talvez o controle e configurações pelo celular
0.51 - A bicicleta passa o carrou ou o contrário          - Talvez o controle e configurações pelo celular
0.6  - Colocar o botão do pânico para ter mais funções    - Talvez o controle e configurações pelo celular
0.61 - Colocar o buzzer para avisar sobre o funcionamento -
0.8  - Medir a velocidade dos carros                      - Talvez deixar para software externo
0.9  - Medir o comprimento dos carros                     - Talvez deixar para sofware externo
0.91 - Diferenciar se carro, moto ou caminhão             - Talvez deixar para software externo
1.0  - Lançar o protótipo
*/
 
/* BIBLIOTECAS INCLUÍDAS */
#include <SD.h> // Biblioteca de leitura do cartão SD
#include <NewPing.h> // Biblioteca de ???
 
// DEFINIÇÕES
// DOS PINOS
//#define BLUETOOTH_TX_PIN 0 // Pino transmissão bluetooth
//#define BLUETOOTH_RX_PIN 1 // Pino transmissão bluetooth
#define BUZZER_PIN 3       // Pino do buzzer
#define USER_BUTTON_PIN 4  // Pino do botão do pânico
#define HALL_SENSOR_PIN 5  // Pino do sensor hall
#define SONAR1_TRIG_PIN 6  // Pino do trigger do sonar 1
#define SONAR1_ECHO_PIN 7  // Pino do echo do sonar 1
#define SONAR2_TRIG_PIN 8  // Pino do trigger do sonar 2
#define SONAR2_ECHO_PIN 9  // Pino do echo do sonar 2
#define SDCARD_PIN 10
// OUTRAS DEFINIÕES
#define MAX_DISTANCE 50   // Definição da distância máxima de medição dos Sonares
 
// CRIAÇÃO DOS SONARES
NewPing sonar1(SONAR1_TRIG_PIN, SONAR1_ECHO_PIN, MAX_DISTANCE);
NewPing sonar2(SONAR2_TRIG_PIN, SONAR2_ECHO_PIN, MAX_DISTANCE);
 
// VARIÁVEIS GLOBAIS
// Variaveis de configuração
File myFile;                          // Objeto do arquivo para salvar os dados
char nomeDoArquivo[] = "log.txt";     // Arquivo onde serão salvas os dados
const int distanciaSensores = 1;      // Distancia que foi instalado os sensores
const int frequenciaDeLeitura = 200;  // 200Hz
const float raioDaRoda = 700;         // Raio da roda onde está o sensor hall
//Variaveis de uso global
unsigned long tempoAtual;             // Contagem do tempo
unsigned long tempoInicial;           // Tempo inicial do Arduino
int contaRevolucoes;                  // Conta quantas revolucoes em um periodo de tempo
unsigned long tempoRevolucoes;
float velocidadeAtual;
 
// FUNÇÕES
void inicializaSD();
void imprimeSaida(unsigned long paraImpressao[], int totalVariaveis);
boolean verificaUltrapassagem();
float medeVelocidadeDoCiclista();
 
// CONFIGURAÇÃO DO ARDUÍNO
void setup(){
 
  tempoInicial = millis();
  tempoRevolucoes = millis();
  velocidadeAtual = 0;
 
  // Razão de transmissão dos dados Seriais
  Serial.begin(9600);
 
  // Configura as portas
  pinMode(BUZZER_PIN, OUTPUT);     // Inicializa a porta do buzzer
  pinMode(USER_BUTTON_PIN, INPUT); // Inicializa a porta do botão do pânico
  pinMode(HALL_SENSOR_PIN, INPUT); // Inicializa a porta do sensor Hall
  pinMode(SDCARD_PIN, OUTPUT);   // Inicicaliza a porta do SD CARD
 
  inicializaSD(nomeDoArquivo);  
}
 
// ROTINA DE LOOP
void loop(){
 
  int distanciaSonar1 = sonar1.ping_cm();
  int distanciaSonar2 = sonar2.ping_cm();  
  boolean botaoPanico = !digitalRead(USER_BUTTON_PIN);
  boolean revolucao = digitalRead(HALL_SENSOR_PIN);
  if (revolucao) {
    velocidadeAtual = medeVelocidadeDoCiclista();
  }
  tempoAtual = millis() - tempoInicial; // Acrescenta um ao tempo
 
  // O tempo de ativação dos sonares serve para:
  // - definir quem está ultrapassando quem
  // - reduzir a quantidade de falsos positivos
  // - definir velocidade do carro
  // - definir comprimento do carro
  unsigned long tempoAtivacaoSonar1 = 0;
  unsigned long tempoAtivacaoSonar2 = 0;
  if (distanciaSonar1 > 0) {
    tempoAtivacaoSonar1 = tempoAtual;
  }
  if (distanciaSonar2 > 0) {
    tempoAtivacaoSonar2 = tempoAtual;
  }
 
  // Verifica se o carro ultrapassou o ciclista ou o inverso  
  boolean dadoValido = true;
 
  if (dadoValido || botaoPanico) {
    if (botaoPanico) {
      digitalWrite(BUZZER_PIN, HIGH);
    } else {
      digitalWrite(BUZZER_PIN, LOW);
    }
    const int totalVariaveis = 7;
    unsigned long paraImpressao[totalVariaveis] = {
                                                   botaoPanico,
                                                   tempoAtual/1000,
                                                   distanciaSonar1,
                                                   distanciaSonar2,
                                                   tempoAtivacaoSonar1/1000,
                                                   tempoAtivacaoSonar2/1000,
                                                   velocidadeAtual
                                                   };
 
    if (distanciaSonar1 > 0 || distanciaSonar2 > 0) {
      imprimeSaida(paraImpressao, totalVariaveis);    
    }
  }
}
 
// Verfica se a bicicleta ultrapassou o carro ou o oposto
// Verifica erros de falsos positivos esporádicos
boolean verificaUltrapassagem () {
  // Sensores distanciados de 1m
  // Um carro que está a 20m/s (72km/h)
  // Passa pelos dois sensores em 1/20s
  // Dez leituras nesse tempo, talvez seja suficiente - leituras a 1/200 s
 
}
 
float medeVelocidadeDoCiclista() {  
  float velocidade;
  contaRevolucoes++;
  Serial.println(contaRevolucoes);
  if (millis() - tempoRevolucoes < 2000.0) {
    if (contaRevolucoes > 20) {
      tempoRevolucoes = millis();
      contaRevolucoes = 0;
      Serial.println((millis() - tempoRevolucoes)*contaRevolucoes*raioDaRoda*2*3.1415/60);
      return (millis() - tempoRevolucoes)*contaRevolucoes*raioDaRoda*2*3.1415/60;
    } else {
      return velocidadeAtual;
    }
  } else {
    return 0;
  }
}
 
//FUNÇÃO IMPRIME TODAS AS SAÍDAS DO PROGRAMA NO SD E NO SERIAL
void imprimeSaida(unsigned long paraImpressao[], int totalVariaveis) {
  // Abre arquivos para impressão
  //myFile = SD.open(nomeDoArquivo, FILE_WRITE);
  for (int i = 0; i < totalVariaveis; i++) {
    //myFile.print(paraImpressao[i]);
    //myFile.print(",");
    Serial.print(paraImpressao[i]);
    if (i < totalVariaveis - 1) {
      Serial.print(",");
    }
   }
   // Adiciona nova linha
   //myFile.println("");
   Serial.println("");
   // Fecha o arquivo para impressão
   //myFile.close();
}
 
void inicializaSD(char arquivo[]) {
  // Rotina de inicialização do cartão SD
  Serial.println("Inicializando o cartao SD");
  if (!SD.begin(10)){
    Serial.println("A inicializacao falhou");
    return;    // Se falha, sai da rotina de configuração
  } else {
    Serial.println("Cartao SD Inicializado");
    if (SD.exists(arquivo)) {
      Serial.print("O arquivo ");
      Serial.print(arquivo);
      Serial.print("existe");
    } else {
    Serial.print("O arquivo ");
    Serial.print(arquivo);
    Serial.print("não existe");
    }
  Serial.print("Criando arquivo ");
  Serial.println(arquivo); // Não deveria criar apenas se inexistente?
  myFile = SD.open(arquivo, FILE_WRITE);
  myFile.close();  
  }
}