# Guia de Compilação e Gravação

Três formas de compilar o firmware e gravar a LILYGO T-Display-S3. Todas usam o FQBN da placa `esp32:esp32:lilygo_t_display_s3`.

[English](./BUILDING.md) · [Linux](#01-linux-nativo-arduino-cli) · [Windows](#02-windows-nativo-arduino-ide) · [WSL](#03-terminal-wsl-build_and_uploadsh) · [Voltar ao README](../README-pt.md)

---

## 01. Linux Nativo (`arduino-cli`)

Ideal para computadores com Linux nativo.

```bash
# Compilar
arduino-cli compile --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy

# Gravar (ajuste -p com a porta serial da sua placa)
arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:lilygo_t_display_s3 firmware/LoverBoy
```

---

## 02. Windows Nativo (Arduino IDE)

Ideal para desenvolvedores no Windows que preferem uma interface gráfica.

1. **Suporte à placa:** Instale o suporte a placas **ESP32** pelo Gerenciador de Placas.
2. **Bibliotecas:** Instale a biblioteca **TFT_eSPI** de Bodmer.
3. **Configuração da tela:** Em `TFT_eSPI/User_Setup_Select.h`, descomente `#include <User_Setups/Setup206_LilyGo_T_Display_S3.h>`.
4. **Compilar e gravar:** Abra `firmware/LoverBoy/LoverBoy.ino`, selecione a placa **LilyGo T-Display-S3** e a porta `COMx` correspondente, e clique em **Carregar** (*Upload*).

---

## 03. Terminal WSL (`build_and_upload.sh`)

Ideal para quem desenvolve dentro do terminal Linux do WSL no Windows. O script compila com o `arduino-cli` no WSL, prepara os binários e grava com o `esptool.exe` do Windows.

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
