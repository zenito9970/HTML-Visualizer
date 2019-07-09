# HTML Visualizer for C++

C++でアルゴリズム等の実装を可視化するためのライブラリです．  
可視化結果はHTMLファイルで出力されるため，環境を問わず見ることができます．

基本的な考え方は [colun/gvc](https://github.com/colun/gvc) を参考にしています．


## プログラムでの使い方

`HtmlVisualizer::Vis` クラスのインスタンスのコンストラクタでファイルへの書き込みを開始し，デストラクタで終了します．
なので，関数等に渡す際は参照やポインタを渡す必要があります．  
また，描画領域のサイズは 800x800 です．

### `HtmlVisualizer::Vis` クラスのメソッド

#### `void rect(double x, double y, double w, double h, Color bg = {0, 0, 0}, bool border = false)`

座標 ( `x`, `y` ) を左上の点として，幅 `w` で高さ `h` の長方形を描きます．  
デフォルトでは背景色を黒，枠線なしで描きます．  
引数: `bg` で背景色を， `border` で枠線の有無を指定できます．

#### `void circle(double x, double y, double radius, Color bg = {0, 0, 0})`

座標 ( `x`, `y` ) を中心の点として，半径 `radius` の円を描きます．  
デフォルトでは背景色を黒，枠線なしで描きます．  
引数: `bg` で背景色を指定できます．

### `void line(double x1, double y1, double x2, double y2, double width = 1 , Color color = {0, 0, 0})`

座標 ( `x1`, `y1` ) と座標 ( `x2`, `y2` ) を結ぶ直線を描きます．  
デフォルトでは黒い線を太さ1pxで描きます．

#### `void new_page()`

描画対象を次のページに切り替えます．

### `HtmlVisualizer::Color` 構造体

色を表すクラスです．
描画命令の引数として使用します．  
`int r` ， `int g` ， `int b` の3つのフィールドを持ちます．  
各フィールドは0から255までの値で表されます．

#### `namespace Palette`

`Color` 構造体のプリセットが用意されています．以下の9色です．

1. `Palette::Black`
1. `Palette::White`
1. `Palette::Gray`
1. `Palette::Purple`
1. `Palette::Blue`
1. `Palette::Green`
1. `Palette::Yellow`
1. `Palette::Orange`
1. `Palette::Red`


## HTMLファイルの使い方

生成されたHTMLファイルをブラウザで開きます．  
`canvas` 要素に可視化結果が描画されています．  
`next` ボタンで次のページに， `prev` ボタンで前のページにそれぞれ移動できます．


## Example

`example` ディレクトリは，このライブラリを用いた可視化のサンプルコード集です．

1. `example-bfs.cpp`
   - グリッド上での幅優先探索の様子を可視化したものです．
1. `example-2opt.cpp`
   - 巡回セールスマン問題の近似解法の一つである2-opt法の様子を可視化したものです．

