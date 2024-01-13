# Esp32_Lora_4RL
Acionamento de 04 Relés com Esp32 e Rádio Lora Ebyte
### Obs: Não esquecer de conectar as antenas nas duas placas
# Hardware:
- O radio deve estar na mesma frequeência, endereço e canal.
- Normalmente já vem nesta configuração mas pode ser ajustado pelo programa RF_Setting.
- Foi usado um conversor de 12 V para 5V pois o Radio Ebyte tem melhor performance nesta tensão.
- Colocado um diodo na entrada da fonte para evitar danos caso haja inversão de polaridade.
- Os pinos M0, M1 e Aux foram conectados ao Esp32 porém este Sketch não está fazendo uso dos mesmos.
