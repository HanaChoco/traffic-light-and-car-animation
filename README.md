# Traffic Light and Car Animation


信号機と車の3DCGアニメーション  


**Version:** 1.0.0
**Creation Date:** 2023年2月  
**Programming Language:** C++   
**Library:** OpenGL  



## Demo

https://github.com/user-attachments/assets/030ad03e-a640-4bf8-ad1a-4fa22828f196



## Overview

### Usage
- **右クリックk:** 歩行者側の信号の色が変化  
- **左クリック:** 信号に応じて車が進む  




### Point
- 車側ではなく歩行者側の信号を描画し、車と信号が同時に見えるように  
- 車の挙動を細かく設定:  
  - 横断歩道側の信号が赤のとき、車側は青のため走行を継続  
  - 横断歩道側の信号が青のとき、車側が赤なので、車は停止線付近で速度を落として停止線手前で停止  
  - 信号から離れていたり、停止線を超えている場合、車は信号が変わっても走行を続ける



## Planned Updates

- **全体的な改善**
  - コードをより綺麗にまとめる
  - 車や建物の描画を改良

- **機能の追加**
  - よりリアルな挙動を実装([押ボタン式信号機](https://www.police.pref.osaka.lg.jp/kotsu/kisei/5642.html)のような)
