# LoverBoy - Firmware

[![Plataforma: ESP32-S3](https://img.shields.io/badge/platform-ESP32--S3-blue.svg)](#-estrutura-do-código)
[![Framework: Arduino](https://img.shields.io/badge/framework-Arduino-00979D.svg)](#-compilar-e-gravar)

**Idioma:** [English](./README.md) | Português

O firmware em C++ do LoverBoy (`firmware/LoverBoy/`) é organizado por responsabilidade: um orquestrador central delega a gerenciadores especializados, e todo jogo herda um ciclo de vida comum de uma classe base abstrata.

[Arquitetura](#-arquitetura) · [Recursos](#-recursos) · [Estrutura do Código](#-estrutura-do-código) · [Compilar e Gravar](#-compilar-e-gravar) · [Adicionando um Jogo](#-adicionando-um-jogo) · [Voltar ao README](../README-pt.md)

---

## ▸ Arquitetura

`LoverBoyCore` é o orquestrador global de estado (Menu vs Jogo) e delega a gerenciadores especializados:

| Gerenciador | Responsabilidade |
|---|---|
| `InputManager` | Leitura centralizada de botões: detecção de borda de latência zero, qualificação de soltura contra cliques duplos, repetição automática (DAS/ARR) e bloqueio de vazamento entre telas |
| `MenuManager` | Splash screen, carrossel de jogos, configurações e HUD |
| `BatteryManager` | Leitura do ADC e cálculo do percentual da bateria (curva por partes) |
| `ConfigManager` | Persistência centralizada na NVS (configurações, mudo e recordes) |
| `SoundManager` | Fila de áudio e player de melodias não-bloqueante (máquina de estados em milissegundos) |
| `TextRenderer` | Desenho de texto UTF-8 com acentos sobre a fonte pixelada retrô |
| `Localization` | Seleção de idioma e busca de textos via `tr()` |

Novos jogos herdam da superclasse abstrata `Game`, que fornece a máquina de estados padrão e os métodos do padrão Template Method.

---

## ▸ Recursos

- **Jogos inclusos:** Crossy, Flappy, Frogger, Genius, Snake e Tetris a ~60 FPS.
- **Renderização por diferença (zero flicker):** Apenas os pixels que mudaram entre os quadros são apagados e redesenhados, eliminando cintilações no barramento do display.
- **Recordes persistentes:** Top 3 de cada jogo salvo na Flash (Preferences/NVS), com tela clássica estilo arcade para inserir 3 iniciais.
- **Tutoriais integrados:** Todo jogo tem uma tela de tutorial no carrossel de 3 opções do título (Jogar, Tutorial, Recordes), em inglês e português.
- **Menu de configurações:** Volume, brilho da tela, tema de cores (5 paletas), idioma e reset de recordes. O estado de mudo persiste entre reinicializações, evitando o buzzer alto na inicialização.
- **Interface multilíngue:** Inglês (padrão) e Português do Brasil. Todo texto da tela fica em uma única tabela (`i18n_strings.h`).
- **Áudio não-bloqueante:** Melodias e efeitos rodam em uma máquina de estados sem congelar a lógica dos jogos.

---

## ▸ Estrutura do Código

```text
firmware/
├── README.md                           # Documentação em Inglês
├── README-pt.md                        # Esta documentação (Português)
└── LoverBoy/
    ├── LoverBoy.ino                    # Ponto de entrada: inicializa o sistema e roda o loop
    └── src/
        ├── core/                       # Gerenciadores de hardware e núcleo do sistema
        │   ├── LoverBoyCore.h/.cpp     # Orquestrador global (Menu vs Jogo)
        │   ├── InputManager.h/.cpp     # Leitura de botões, debounce e auto-repeat
        │   ├── BatteryManager.h/.cpp   # ADC e cálculo do percentual da bateria
        │   ├── ConfigManager.h/.cpp    # Persistência centralizada de configurações na NVS
        │   ├── SoundManager.h/.cpp     # Fila de áudio e melodias não-bloqueante
        │   ├── pins.h                  # Mapeamento de pinos do ESP32-S3 e display
        │   └── audio_assets.h          # Biblioteca de frequências e vetores de melodias
        ├── games/                      # Motor de jogos e jogos implementados
        │   ├── Game.h/.cpp             # Classe base abstrata (ciclo de vida Template Method)
        │   ├── CrossyGame.h/.cpp
        │   ├── FlappyGame.h/.cpp
        │   ├── FroggerGame.h/.cpp
        │   ├── GeniusGame.h/.cpp
        │   ├── SnakeGame.h/.cpp
        │   └── TetrisGame.h/.cpp
        ├── ui/                         # Interface de usuário e renderização visual
        │   ├── MenuManager.h/.cpp      # Splash, carrossel de jogos, configurações e HUD
        │   ├── TextRenderer.h/.cpp     # Texto UTF-8 com acentos na fonte pixelada
        │   └── Utf8Text.h/.cpp         # Decodificação UTF-8 e decomposição de acentos
        └── localization/               # Internacionalização e traduções
            ├── Localization.h/.cpp     # Seleção de idioma e busca de textos (tr())
            └── i18n_strings.h          # Tabela única com todos os textos em todos os idiomas
```

As definições de pinos ficam em [`pins.h`](./LoverBoy/src/core/pins.h); o mapeamento correspondente na PCB está na [documentação da PCB](../pcb/README-pt.md#-pinagem--mapeamento-no-firmware).

---

## ▸ Compilar e Gravar

Todos os três métodos usam o FQBN da placa `esp32:esp32:lilygo_t_display_s3`.

### Linux Nativo (`arduino-cli`)

Ideal para computadores com Linux nativo:

```bash
# Compilar
arduino-cli compile --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy

# Gravar (ajuste -p com a porta serial da sua placa)
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy
```

### Windows Nativo (Arduino IDE)

Ideal para desenvolvedores no Windows que preferem uma interface gráfica:

1. **Suporte à placa:** Instale o suporte a placas **ESP32** pelo Gerenciador de Placas.
2. **Bibliotecas:** Instale a biblioteca **TFT_eSPI** de Bodmer.
3. **Configuração da tela:** Em `TFT_eSPI/User_Setup_Select.h`, descomente `#include <User_Setups/Setup206_LilyGo_T_Display_S3.h>`.
4. **Compilar e gravar:** Abra `firmware/LoverBoy/LoverBoy.ino`, selecione a placa **LilyGo T-Display-S3** e a porta `COMx` correspondente, e clique em **Carregar** (*Upload*).

### Terminal WSL (`build_and_upload.sh`)

Ideal para quem desenvolve dentro do terminal Linux do WSL no Windows. O script [`build_and_upload.sh`](../build_and_upload.sh) na raiz compila com o `arduino-cli` no WSL, prepara os binários e grava com o `esptool.exe` do Windows:

```bash
./build_and_upload.sh -p COM7
```

| Flag | Descrição | Padrão |
|---|---|---|
| `-p`, `--port <PORT>` | Porta serial no Windows | `COM7` |
| `-b`, `--baud <BAUD>` | Velocidade de gravação | `921600` |
| `-f`, `--fqbn <FQBN>` | Identificador da placa | `esp32:esp32:lilygo_t_display_s3` |
| `-d`, `--dir <DIR>` | Pasta do firmware | `firmware/LoverBoy` |
| `-c`, `--cli <PATH>` | Binário do `arduino-cli` no WSL | detectado automaticamente |
| `-e`, `--esptool <PATH>` | Caminho do `esptool.exe` no Windows | detectado automaticamente |
| `-h`, `--help` | Mostra a ajuda e sai | |

---

## ▸ Adicionando um Jogo

1. Crie `XxxGame.h/.cpp` em [`src/games/`](./LoverBoy/src/games/), herdando de `Game` e implementando seus métodos virtuais puros (`resetGame`, `updatePlaying`, `drawPlaying`, `handleInputPlaying`, `onResume`, `drawTutorialContent`).
2. Adicione um `case` em `LoverBoyCore::loadGame()`.
3. Adicione o nome em `gameNames` e incremente `GAME_COUNT` em [`MenuManager.h`](./LoverBoy/src/ui/MenuManager.h). Use um nome de uma única palavra.
4. Adicione os textos do tutorial para todos os idiomas em [`i18n_strings.h`](./LoverBoy/src/localization/i18n_strings.h).
