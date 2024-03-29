# Arduino UNO R4 もどき
![](weather.png)
## 買ったもの

- [これ(WeActStudio RA4M1)](https://ja.aliexpress.com/item/1005006103872563.html)の3.3V版
- 基板作った
    - LCDとI2C(J8)とUART(J7)とRTC電池(BT1)とSPIフラッシュ(U1)は使えた
    - 他にHX711とつなぐコネクタがある
    - Analog入力も後で試す

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
- SSD1306を使っている[128x32 OLED LCD](https://ja.aliexpress.com/item/32850288143.html)に表示する
- [ここ](https://101010.fun/iot/arduino-oled-display.html)を参考にした
- u8g2ライブラリをインストールする
- GND-＞GND:VCC-＞VCC:100->SCK:101->SDA につなぐ（J4につなぐ）
- OLED.ino を書き込む

## 温湿気圧・CO2濃度計
BME280とMH-Z19をつないで温度・湿度・気圧と二酸化炭素濃度を表示する  
5V電源がないので外部から持ってくる（GNDに注意！！）
- インストールするライブラリ
    - u8g2
    - SparkFun BME280
    - Mzh19 by Eduard
- ピン配は以下の図を参照
- weather.inoを書き込む

![](pin.png)

## 時計
RTC電池を使って時計を動かす（純正のR4 Minimaには電池繋げません）  
電池ホルターは[これ](https://ja.aliexpress.com/item/4000528748796.html)
- 電池ホルダーBT1にCR1220を入れる
- RTC_AutomaticExample.inoを書き込む
- [バッテリバックアップを使うとき](https://docs.arduino.cc/tutorials/uno-r4-wifi/vrtc-off/)を参考に改変している
- 内蔵クロックを使うと時計の精度がとっても悪いので[外部のオシレータを使う方法](https://me-yoh.com/arduino-uno-r4-rtc-fix)
    - VBATTを使うと外部のオシレータを発振出来ていません

## SPIフラッシュアクセス

[これ](https://ja.aliexpress.com/item/32326265518.html)
- ライブラリは[Arduino-W25Q64](https://github.com/Tamakichi/Arduino-W25Q64)
- READMEに従って手動でライブラリをインストール
- U1につなぐ
- 繋いでいるのはW25Q32だけど使えるらしい
- Arduino-W25Q64.inoを書き込む