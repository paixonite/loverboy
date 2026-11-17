# Guia de Arquitetura do Firmware

O firmware do LoverBoy (`firmware/LoverBoy/`) é organizado por responsabilidade: um orquestrador central delega a gerenciadores especializados, e todo jogo herda um ciclo de vida comum de uma classe base.

[English](./FIRMWARE.md) · [Arquitetura](#01-arquitetura) · [Recursos](#02-recursos) · [Estrutura do Código](#03-estrutura-do-código) · [Adicionando um Jogo](#04-adicionando-um-jogo) · [Voltar ao README](../README-pt.md)

---

## 01. Arquitetura

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

## 02. Recursos

- **Jogos inclusos:** Crossy, Flappy, Frogger, Genius, Snake e Tetris a ~60 FPS.
- **Renderização por diferença (zero flicker):** Apenas os pixels que mudaram entre os quadros são apagados e redesenhados, eliminando cintilações no barramento do display.
- **Recordes persistentes:** Top 3 de cada jogo salvo na Flash (Preferences/NVS), com tela clássica estilo arcade para inserir 3 iniciais.
- **Tutoriais integrados:** Todo jogo tem uma tela de tutorial no carrossel de 3 opções do título (Jogar, Tutorial, Recordes), em inglês e português.
- **Menu de configurações:** Volume, brilho da tela, tema de cores (5 paletas), idioma e reset de recordes. O estado de mudo persiste entre reinicializações, evitando o buzzer alto na inicialização.
- **Interface multilíngue:** Inglês (padrão) e Português do Brasil. Todo texto da tela fica em uma única tabela (`i18n_strings.h`).
- **Áudio não-bloqueante:** Melodias e efeitos rodam em uma máquina de estados sem congelar a lógica dos jogos.

---

## 03. Estrutura do Código

```text
firmware/LoverBoy/
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

As definições de pinos ficam em [`pins.h`](../firmware/LoverBoy/src/core/pins.h); o mapeamento correspondente na PCB está na [documentação da PCB](../pcb/README-pt.md#04-pinagem--mapeamento-no-firmware).

---

## 04. Adicionando um Jogo

1. Crie `XxxGame.h/.cpp` em `src/games/`, herdando de `Game` e implementando seus métodos virtuais puros (`resetGame`, `updatePlaying`, `drawPlaying`, `handleInputPlaying`, `onResume`, `drawTutorialContent`).
2. Adicione um `case` em `LoverBoyCore::loadGame()`.
3. Adicione o nome em `gameNames` e incremente `GAME_COUNT` em [`MenuManager.h`](../firmware/LoverBoy/src/ui/MenuManager.h). Use um nome de uma única palavra.
4. Adicione os textos do tutorial para todos os idiomas em `i18n_strings.h`.
