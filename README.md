# test_ams_as5048a
Test code for reading angle value from ams AS5048A sensor using Arduino.

## 概要
このリポジトリは、AMS社の回転角センサー"AS5048A"から出力される角度値を、AruduinoとのSPI通信にて取得するための最小限のコードを公開しています。

## 動作環境
- Sensor board
    - AMS AS5048A-EK-AB: https://www.digikey.jp/ja/products/detail/ams/AS5048A-TS-EK-AB/3188612
- Arduino board
    - Raspberry Pi Pico: https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html
- macOS 12.6
- Arduino IDE 1.8.19 + Visual Studio Code + Arduino Plugin
- Board library
    - Raspberry Pi Pico/RP2040 by Earle F. Phillhower, III v2.6.2


## 回路
回転角センサーとRaspberry Pi Picoとの間は、次の表に示すように接続した。

| AS5048A-EK-AB Pin No. | Name    | <->        | Raspberry Pi Pico Pin No. | Name          |
| --------------------- | ------- | ---------- | ------------------------- | ------------- |
| 1                     | 5V      | --         | 40                        | VBUS          |
| 2                     | 3.3V    |            |                           |               |
| 3                     | PWM     |            |                           |               |
| 4                     | SDA/CSn | --         | 22                        | GP17 SPI0 CSn |
| 5                     | SCL/SCK | -(200ohm)- | 24                        | GP18 SPI0 SCK |
| 6                     | A1/MOSI | --         | 25                        | GP19 SPI0 TX  |
| 7                     | A2/MISO | --         | 21                        | GP16 SPI0 RX  |
| 8                     | GND     | --         | 38                        | GND           |

手元の環境ではSCKのリンギングがやや大きかったため、ダンピング抵抗として200Ωを介してArduinoと接続した。

## 実行
test_anglesenor.inoをコンパイルし、生成されたバイナリーファイルをArduinoに書き込んでください。
Arduinoをmacへ接続した際に認識されたusbポートをシリアルターミナルソフトや、screenコマンドで接続すると次のような現在角度値が出力される。1回転を14bitで表現する。（センサーの生値そのまま）  
検出用マグネットを回転させるとangleの値が変化する。

```text
{angle:9723}
{angle:9722}
{angle:9720}
{angle:9723}
{angle:9723}
{angle:9724}
{angle:9723}
{angle:9723}
```

## リファレンス
- AS5048 Datasheet: https://ams.com/documents/20143/36005/AS5048_DS000298_4-00.pdf
