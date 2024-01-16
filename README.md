# Esp32_Lora_4RL
Acionamento de 04 Relés com Esp32 e Rádio Lora Ebyte
### Obs: Não esquecer de conectar as antenas nas duas placas
# Hardware:
- O radio deve estar na mesma frequência, endereço e canal.
- Normalmente já vem nesta configuração mas pode ser ajustado pelo programa RF_Setting.
- Foi usado um conversor de 12 V para 5V pois o Radio Ebyte tem melhor performance nesta tensão.
- Colocado um diodo na entrada da fonte para evitar danos caso haja inversão de polaridade.
- Os pinos M0, M1 e Aux foram conectados ao Esp32 porém este Sketch não está fazendo uso dos mesmos.
- Apesar das bobinas dos relés consumir baixa corrente ainda assim foi colocado o ULN 2003 como driver.
# Do skecth (Programa embarcado):
- As duas placas operam com o mesmo programa.
- Qualquer botão ( 1 a 4 ) clicado aciona o relé correspondente ( 1 a 4 ) e o relé remoto ( 1 a 4 ) via RF.
- Se o Botão 1 for apertado por mais de 10 segundos a placa entra no modo teste e  envia comandos sequencialmente a cada 2 segundos alternando os relés acionados.
- Qualquer click com menos de 5 segundos em qualquer dos 04 botões desarma o modo teste e volta na operação normal.
- Qualquer das placas pode transmitir ou receber (quando clica o botão a placa local transmite e a remota recebe e vice-versa).
- Foi usado a porta Serial 2 na comunicação com o Lora assim da para usar a Serial 0 para Debug no Monitor Serial da IDE.
- O código está bem comentado e fácil de acompanhar.
  

