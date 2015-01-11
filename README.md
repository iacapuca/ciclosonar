# CICLOSONAR
A Cycling Activism tool to measure the distance between a bicycle and a car.

O Ciclosnar é uma ferramenta para cicloativistas que tem interesse em aferir a distância com que os motoristas passam ao ultrapassar o ciclista e com isso fomentar políticas públicas ou produzir estudos.
# MARCO LEGAL:
É definida a distância conforme o Código Brasileiro de Trânsito
em seu artigo 201, como 1,5m o mínimo para ultrapassagem de um
ciclista pelo motorista. No artigo XXX é definido que deve-se
diminuir a velocidade ao ultrapassar os ciclistas para uma
compatível com a seguraça.

# OBJETIVOS:
O projeto Ciclossonar tem como objetivo medir a distância
que os motoristas passam ao ultrapassar os ciclistas e com
isso fomentar políticas públicas que reduzam acidentes e
estimulem um trânsito seguro e humano.

## OBJETIVOS ESPECÍFICOS:
1. - Medir a distância em cada ponto da bicicleta
2. - Medir a velocidade do ciclista
3. - Medir a velocidade relativa do motorista com o ciclista
4. - Medir a velocidade do motorista
5. - Medir o tamanho do veículo que realiza ultrapassagem
6. - Quantificar a quantidade de finos que o ciclista recebe:
* 6.1 - Ao passar em ruas mais ou menos movimentadas
* 6.2 - Por andar no canto ou mais ao centro da faixa
* 6.3 - Conforme seu sexo
* 6.4 - Conforme sua roupa e acessórios
* 6.5 - Conforme sua bicicleta
7. - Medir o que influencia mais da distância ou da velocidade
no conforto do ciclista ao pedalar, conforme sua experiência




# ETAPAS NECESSÀRIAS NO CÓDIGO DO ARDUÍNO
* 0.1  - Medir distância com sonar 1                        - OK
* 0.11 - Medir distância com sonar 2                        - OK
* 0.12 - Medir distância média                              - OK
* 0.2  - Gravar no Cartão SD                                - OK
* 0.21 - Bluetooth enviar dados para o celular              - OK
* 0.3  - Adicionar "botão do pânico"                        - OK - Tem erros de compilação que foram corrigidos em 0.31
* 0.31 - Buzzer ao apertar o botão                          - OK
* 0.4  - Medir velocidade da bicicleta                      -
* 0.5  - Receber dados do celular                           -
* 0.51 - Receber dados GPS do celular                       -
* 0.5  - Controle de falsos positivos                       - Talvez o controle e configurações pelo celular
* 0.52 - Receber configuração pelo celular                  -
* 0.51 - A bicicleta passa o carrou ou o contrário          - Talvez o controle e configurações pelo celular
* 0.61 - Colocar o buzzer para avisar sobre o funcionamento -
* 0.6  - Colocar o botão do pânico para ter mais funções    - Talvez o controle e configurações pelo celular
* 0.8  - Medir a velocidade dos carros                      - Talvez deixar para software externo
* 0.9  - Medir o comprimento dos carros                     - Talvez deixar para sofware externo
* 0.91 - Diferenciar se carro, moto ou caminhão             - Talvez deixar para software externo
* 1.0  - Lançar o protótipo
