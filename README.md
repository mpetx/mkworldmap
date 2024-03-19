# mkworldmap

## 使い方

### コマンドライン引数
#### 一般引数
| ショート名 | ロング名 | 説明 | デフォルト値 |
|:-:|:-:|:-|:-:|
| `-p` | `--projection` | 投影法名 |  |
| `-t` | `--texture` | テクスチャファイル名 | デフォルトテクスチャ |
| `-w` | `--width` | 出力画像の幅 | 1024 |
| `-s` | `--standard-longitude` | 標準経線（-180～180） | 150 |
| `-o` | `--option` | 出力画像パス | `world-map.jpg` |
| | `--south-up` | 南上北下にする | `F` |

#### `equirectangular`
`equirectangular`は正距円筒図法です。

追加のコマンドライン引数はありません。

#### `cylindrical-equal-area`
`cylindrical-equal-area`は正積円筒図法です。ランベルト正積円筒図法やゴール・ピーターズ図法を含みます。

| オプション | 説明 | デフォルト値 |
|:-:|:-|:-:|
| `--standard-latitude` | 標準緯線（-90～90） | 0 |
