# Arduino UNO R4 もどき

## 買ったもの

- [これ(WeActStudio RA4M1)](https://ja.aliexpress.com/item/1005006103872563.html)の3.3V版
- 基板作っているところ

## Arduino化

- [Arduino公式のダウンロードページ](https://github.com/arduino/ArduinoCore-renesas/tree/main/bootloaders/UNO_R4)からファームウェア(dfu_minima.hex)をダウンロード
- [Renesas公式のダウンロードページ](https://www.renesas.com/us/en/software-tool/renesas-flash-programmer-programming-gui)からFlash Programmerをダウンロードしてインストール
    - ユーサー登録が必要だった
- [ここ](https://community.element14.com/products/arduino/b/blog/posts/arduino-uno-r4-minima-troubleshooting-unknown-usb-device)のReflash the Bootloader以降に従ってファームウェアを書き込む
    - USBでつなぐ
    - MDボタンを押しながらリセットを押してからはなす（そのあとでMDボタンをはなす）×2回？
        - UARTが生えてくるので番号を覚えておく
    - Flash Programmer起動
        - Connect Settings tabでUARTを選ぶ
        - dfu_minima.hexを読み込む
        - 新しいプロジェクトを作ってセーブ
        - Startを押す (書き込む)
- Example Blinkで確認
    - LED_BUILTINはこのボードにはついていない
    - LED_BUILTINをLED_TXに変更すると動いた（3か所）
- 他にも[サンプルがある](https://github.com/arduino/ArduinoCore-renesas/tree/main/libraries)

## OLED 表示
- [これ](https://ja.aliexpress.com/item/32850288143.html)に表示する
- [ここ](https://101010.fun/iot/arduino-oled-display.html)を参考にした
- u8g2ライブラリをインストールする
- GND-＞GND:VCC-＞VCC:100->SCK:101->SDA につなぐ
- OLED.ino を書き込む
