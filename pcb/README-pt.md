# LoverBoy - PCB Customizada & Eletrônica

[![EDA: EasyEDA v6.5](https://img.shields.io/badge/EDA-EasyEDA%20v6.5-blue.svg)](source/)
[![Licença: CC BY-NC-SA 4.0](https://img.shields.io/badge/licen%C3%A7a-CC%20BY--NC--SA%204.0-lightgrey.svg)](../LICENSE)

[← LoverBoy](../README-pt.md) · **Idioma:** [English](README.md) | Português

Placa-mãe through-hole de camada única projetada no EasyEDA que integra a **LILYGO T-Display-S3**, 8 botões táteis estilo arcade (D-Pad, A, B, Start, Select), um buzzer passivo piezoelétrico, uma chave deslizante liga/desliga e um circuito de recarga LiPo USB-C TP4056 em uma única placa portátil.

> [!WARNING]
> **Errata da Revisão 1.0 de Hardware (Problemas Conhecidos):**
> Os arquivos atuais da placa `v1.0` nesta pasta possuem duas erratas de hardware conhecidas que serão corrigidas no **redesign da PCB v2.0**:
> 1. **Curto no Roteamento dos Botões ([Issue #7](https://github.com/paixonite/loverboy/issues/7)):** Um erro no traçado faz com que os botões fechem curto entre `3V3` e `GND` ao serem pressionados, em vez de passarem pelos resistores de `10kΩ` (`R1–R8`). Nas placas `v1.0` fabricadas, a correção consiste em cortar a trilha direta logo após cada botão e soldar a conexão passando pelo respectivo resistor.
> 2. **Desalinhamento do Footprint do TP4056 ([Issue #8](https://github.com/paixonite/loverboy/issues/8)):** A medida horizontal do módulo TP4056 ficou cerca de 2 mm menor do que o componente real, fazendo o módulo ultrapassar levemente a borda da placa e deslocando a tela em ~2 mm para a esquerda do centro na carcaça `v1.0` ([Issue #9](https://github.com/paixonite/loverboy/issues/9)).

> [!NOTE]
> **Nomenclatura dos Arquivos (`EspBoy`):** A Revisão 1.0 do hardware foi originalmente projetada e prototipada sob o nome provisório *EspBoy* antes do projeto receber o nome oficial **LoverBoy**. Todos os arquivos fonte, esquemáticos, BOM e Gerbers da `v1.0` mantêm o prefixo `EspBoy_*`; a futura versão `v2.0` passará a utilizar o prefixo `LoverBoy_*`.

## Layout da Placa & Esquemático

<p align="center">
  <img src="EspBoy_PCB_Layout.png" width="48%" alt="Layout da PCB LoverBoy" />
  <img src="EspBoy_Schematic.png" width="48%" alt="Esquemático LoverBoy" />
</p>

- **PDFs Vetoriais para Inspeção / Impressão:**
  - [`EspBoy_PCB_Layout.pdf`](EspBoy_PCB_Layout.pdf)
  - [`EspBoy_Schematic.pdf`](EspBoy_Schematic.pdf)

## Lista de Materiais (BOM)

A planilha completa está disponível em [`EspBoy_BOM.csv`](EspBoy_BOM.csv).

| Designador | Componente | Qtd | Footprint / Encapsulamento | Part Number | Código LCSC |
| :--- | :--- | :---: | :--- | :--- | :--- |
| `ESPBOY` | **LILYGO T-Display-S3** (ESP32-S3 + TFT 1.9") | 1 | Barramento THT Customizado | T-Display S3 | — |
| `UP, DOWN, LEFT, RIGHT, A, B, START, SELECT` | **Botão Tátil 12×12mm (Push Button)** | 8 | `KEY-TH_4P-L12.0-W12.0` | `TC-00121FS-080E` | `C4355204` |
| `R1–R8` | **Resistor Axial 10kΩ** | 8 | `RES-TH_BD2.2-L6.0-P10.00` | `10kΩ` (Axial 0.4) | `C9900020985` |
| `BUZZER` | **Buzzer Passivo Piezo** (Ø 22mm, passo 10mm) | 1 | `BUZ-TH_BD22.0-P10.00` | `2207-P10MM` | `C49246969` |
| `SWITCH` | **Chave Deslizante (Slide Switch)** | 1 | `SW-TH_SS12F44G4` | `SS12F44G5` | `C22435641` |
| `USB-C` | **Módulo Carregador TP4056 USB-C** | 1 | Módulo THT Customizado | TP4056 1S LiPo | — |
| *(Externo)* | **Bateria LiPo 3.7V** | 1 | Soldada nos pinos `BAT+`/`BAT-` do TP4056 | LiPo Recarregável 3.7V | — |

## Pinagem & Mapeamento no Firmware

Todas as trilhas da PCB correspondem diretamente às definições em [`firmware/LoverBoy/src/core/pins.h`](../firmware/LoverBoy/src/core/pins.h):

| Designador na PCB | Função | GPIO ESP32-S3 | Macro no Firmware (`pins.h`) | Observações |
| :--- | :--- | :---: | :--- | :--- |
| `UP` | D-Pad Cima | `GPIO 1` | `BTN_UP` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `RIGHT` | D-Pad Direita | `GPIO 2` | `BTN_RIGHT` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `DOWN` | D-Pad Baixo | `GPIO 3` | `BTN_DOWN` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `LEFT` | D-Pad Esquerda | `GPIO 43` | `BTN_LEFT` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `SELECT` | Botão Select | `GPIO 18` | `BTN_SELECT` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `START` | Botão Start | `GPIO 44` | `BTN_START` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `A` | Botão de Ação A | `GPIO 17` | `BTN_A` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `B` | Botão de Ação B | `GPIO 21` | `BTN_B` | Ativo em nível ALTO (pull-down de 10kΩ) |
| `BUZZER` | Áudio Buzzer Passivo | `GPIO 16` | `BUZZER_PIN` | Acionado via timer PWM LEDC |
| *(Interno)* | Habilitação de Bateria | `GPIO 15` | `POWER_ENABLE_PIN` | Latch interno de energia da T-Display-S3 |
| *(Interno)* | Leitura ADC da Bateria | `GPIO 4` | `BATTERY_SENSE_PIN` | Divisor de tensão interno no ADC |
| *(Interno)* | Backlight da Tela TFT | `GPIO 38` | `TFT_BL_PIN` | Controle PWM de brilho da tela ST7789 |

## Guia de Fabricação & Manufatura

A placa foi desenhada com larguras de trilha e espaçamentos generosos para permitir tanto a **fabricação local em laboratório/makerspace** quanto a encomenda em **fábricas comerciais de PCB**, utilizando exatamente os mesmos arquivos.

### Opção 1: Fabricação Local / Maker Space (Fresadora CNC ou Laser)

O protótipo `v1.0` foi confeccionado em uma **fresadora CNC**, e o traçado é igualmente compatível com **gravação a laser** (ablação de tinta/filme fotossensível + corrosão ou ablação direta do cobre):

- **Trilhas em Camada Única (Bottom Layer):** Todas as trilhas de cobre estão na face inferior da placa, dispensando o alinhamento de duas faces ou virar a placa na fresadora.
- **Trilhas e Espaçamentos Largos:** Projetada respeitando as tolerâncias físicas de isolamento por fresagem (≥ 0.4 mm de isolamento e trilhas largas), o que garante excelente definição tanto em fresas CNC quanto no feixe fino de máquinas a laser.
- **Componentes 100% Through-Hole (THT):** Todos os componentes da placa utilizam furos passantes, facilitando a soldagem manual em cobre nu (sem máscara de solda).
- **Sem Furos Metalizados (PTH):** Por ser estritamente de camada única, não é necessária metalização química de vias nem uso de rebites condutivos.

### Opção 2: Fábrica Comercial de PCB (JLCPCB / PCBWay / OSH Park)

Para encomendar placas industrializadas com máscara de solda, basta enviar o arquivo [`gerbers/Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip`](gerbers/Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip) diretamente na plataforma da fabricante com os parâmetros padrão:

| Parâmetro | Configuração Recomendada |
| :--- | :--- |
| **Material Base** | FR-4 |
| **Camadas (Layers)** | 1 ou 2 Camadas (2 camadas costuma ser o menor custo padrão) |
| **Espessura da PCB** | **1.6 mm** (dimensionada para o encaixe na [carcaça impressa em 3D](../case/README-pt.md)) |
| **Peso do Cobre** | 1 oz |
| **Acabamento Superficial** | HASL (com ou sem chumbo) ou ENIG |
| **Cor da Máscara de Solda** | Qualquer cor |

## Editando os Arquivos Fonte (EasyEDA)

Os arquivos editáveis do esquemático e layout estão na pasta [`source/`](source/):
- `source/SCH_EspBoy.json` — Arquivo do esquemático
- `source/PCB_EspBoy.json` — Arquivo do layout da PCB

### Como Abrir

1. Acesse o **[EasyEDA Standard](https://easyeda.com/editor)** (no navegador ou aplicativo desktop, criado na versão `v6.5.51`).
2. Vá no menu **File → Open → EasyEDA...**
3. Selecione `SCH_EspBoy.json` e `PCB_EspBoy.json` para visualizar, alterar trilhas ou exportar novos arquivos Gerber.

## Estrutura de Diretórios

```text
pcb/
├── README.md                                       # Documentação em Inglês
├── README-pt.md                                    # Esta documentação (Português)
├── EspBoy_BOM.csv                                  # Lista de Materiais (BOM) com códigos LCSC
├── EspBoy_PCB_Layout.pdf / .png                    # Exportações 2D do layout da placa
├── EspBoy_Schematic.pdf / .png                     # Exportações do esquemático elétrico
├── gerbers/
│   └── Gerber_EspBoy_PCB_EspBoy_2025-10-09.zip     # Pacote Gerber e furação Excellon pronto para fabricação
└── source/
    ├── PCB_EspBoy.json                             # Código-fonte do layout no EasyEDA Standard
    └── SCH_EspBoy.json                             # Código-fonte do esquemático no EasyEDA Standard
```
