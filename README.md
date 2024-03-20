# mkworldmap

## 使い方
### 書式
```console
mkworldmap OPTIONS
```

### コマンドライン引数

| ショート名 | ロング名 | 説明 | デフォルト値 |
|:-|:-|:-|:-:|
| `-p` | `--projection` | 投影法名 | 必須  |
| `-t` | `--texture` | テクスチャファイル名 | デフォルト |
| `-w` | `--width` | 出力画像の幅 | 768 |
| `-s` | `--standard-longitude` | 標準経線 | 150 |
| `-o` | `--output` | 出力画像パス | `world-map.jpg` |
| | `--south-up` | 南を上にする | 北が上 |
| | `--standard-latitude` | 標準緯線（正積円筒） | 0 |
| | `--max-latitude` | 緯線の範囲（メルカトル、心射円筒） | 80 |

投影法名は以下のいずれかです。

| 値 | 説明 |
|:-:|:-|
| `equirectangular` | 正距円筒図法 |
| `cylindrical-equal-area` | 正積円筒図法 |
| `mercator` | メルカトル図法 |
| `miller` | ミラー図法 |
| `central-cylindrical` | 心射円筒図法 |
| `sinusoidal` | サンソン図法 |
| `mollweide` | モルワイデ図法 |
| `azimuthal-equidistant` | 正距方位図法 |
| `aitoff` | エイトフ図法 |
| `orthographic` | 正射図法 |
| `orthographic-aitoff` | 正射エイトフ図法 |
| `lambert-azimuthal-equal-area` | ランベルト正積方位図法 |
| `hammer` | ハンメル図法 |
| `gall-stereographic` | ゴール平射図法 |
| `eckert-1` | エケルト第一図法 |
| `eckert-2` | エケルト第二図法 |
| `eckert-3` | エケルト第三図法 |
| `eckert-4` | エケルト第四図法 |
| `eckert-5` | エケルト第五図法 |
| `eckert-6` | エケルト第六図法 |

経度と緯度の範囲は次の通りです。

| | 最小値 | 最大値 |
|:-:|:-:|:-:|
| 経度 | -180 | 180 |
| 緯度 | -90 | 90 |
