# Word Speech Recognition with DP Matching

このパッケージは DP マッチングによる単語音声認識を行うソフトウェアです。

音声の音響特徴量ベクトルが記述された、正解データと未知（認識対象）データのマッチングを行います。

## 動作確認済みの環境

+ OS : Ubuntu 22.04.1 LTS
+ Compiler : GCC 11.3.0

## インストール

```
git clone https://github.com/nacky823/dp-matching-word-recognition.git
```

## 入力と出力

> **Warning**  
> + このパッケージでは、サンプルデータの提供を行わないため、予めサンプルデータを用意する必要があります。
> + 入力するサンプルデータは、単語の音声に音響分析が施され、15次のメルケプストラム特徴量を抽出したデータを想定しています。
> + サンプルデータに関する詳細な情報は、[以下](https://github.com/nacky823/dp-matching-word-recognition/tree/master#%E5%85%A5%E5%8A%9B)を参照してください。

### 入力
+ テキストファイル形式で **2 種類のファイルセット** を入力

    + DP マッチングを行う際の、**正解データ** のファイルセットと、**未知データ** のファイルセットの２種類

+ 入力するファイルセットの規則

    + **１つのファイルセット** には **100 個のテキストファイル** を含める
    + 各ファイルセットに含まれる **単語** は **全て同じ** 必要がある

+ 入力するテキストファイルの規則

    + 各ファイルには、**1 つの単語** を含める
    + 各ファイル名には、`1` から `100` までの **単語に対応した番号** を重複せず記述する
    + 各ファイル名には、正解データと未知データを区別する為の **番号** を割り振る
        ```
        sample[正解データと未知データを区別するための番号]_[単語に対応した番号].txt
        ```
        + ファイル名の例
            ```
            sample011_100.txt
            ```

+ 入力するテキストファイルの記述規則

    + １行目：拡張子 `.txt` を除いた、自身の **ファイル名**

    + ２行目：発音した **単語**

    + ３行目：４行目以降のデータの **フレーム数**（行数）

        + ４行目以降のデータでは、「１行」が「１フレーム」を意味する

    + ４行目以降：**音響特徴量ベクトル** のデータ

        + １行あたり **15 個** のデータを、半角スペース `" "` を区切りとして記述する

+ 入力するテキストファイルの記述例

    + `sample011_100.txt`
        ```
        sample011_100
        TANGO
        64
        0.859710 0.298871 -0.004965 ... -0.035384 
        0.995925 0.355393 0.187254 ... -0.002132 
        ...
        0.536624 0.023738 -0.203361 ... 0.064307 
        ```

### 出力
+ 未知データの **「ある単語」** と正解データの **100 単語** のマッチング結果を出力
    + 単語認識率（正解率）[%] を標準出力に出力

## 使用方法

### 入力データの準備

+ このパッケージでは、サンプルデータの提供を行わないため、予めサンプルデータを用意する必要があります。

1. このパッケージのルートディレクトリに移動
    + `git clone` を行ったディレクトリのパスが `/path/to/cloned_ws/` の場合、以下のコマンドを実行
        ```
        cd /path/to/cloned_ws/dp-matching-word-recognition/
        ```

1. サンプルデータのファイルを配置するための、階層構造を作成
    ```
    mkdir -p sample_data/{sample011,sample012,sample021,sample022}
    ```
    + 以下のような階層構造が作成される
        ```
        .
        ├── core
        └── sample_data
            ├── sample011
            ├── sample012
            ├── sample021
            └── sample022
        
        6 directories
        ```

1. 上記で作成した、`sample011` のような末端ディレクトリにそれぞれ、サンプルデータを配置する
    ```
    mv /path/to/sample_data_directory_1/* ./sample_data/sample011/
    mv /path/to/sample_data_directory_2/* ./sample_data/sample012/
    mv /path/to/sample_data_directory_3/* ./sample_data/sample021/
    mv /path/to/sample_data_directory_4/* ./sample_data/sample022/
    ```
    + 各末端ディレクトリ（ex. `sample011/`）には、複数のテキストファイルが含まれている必要がある
    + 各末端ディレクトリのテキストファイルの数は、 `common.hpp` の `20` 行目で一様に指定されている
        + テキストファイルの数を指定したい場合は、[以下のコード](https://github.com/nacky823/dp-matching-word-recognition/blob/bc8401fdeccceb54b851bb6e38a578098b4a015c/core/common.hpp#L20C1-L20C25) の `100` を指定したい数に編集する
            ```c++
            #define NUM_OF_FILES 100
            ```
    + これらのテキストファイルは、サンプルデータとして使用される

### 実行方法

1. （任意）[`common.hpp`](https://github.com/nacky823/dp-matching-word-recognition/blob/21ca44049b26923f9da6329d8207242a2023943c/core/common.hpp#L18C1-L19C54) の `18`, `19` 行目を編集
    + マッチングに使用する、正解と認識対象のファイルセットをそれぞれ指定
        ```c++
        #define CORRECT 11 // File number of the correct data
        #define UNKNOWN 12 // File number of the unknown data
        ```
        > **Note**
        > + 初期設定では正解ファイルセットが、`11` つまり `sample011` になっている。
        > + 初期設定では認識対象ファイルセットが、`12` つまり `sample012` になっている。
        > + 正解または認識対象ファイルセットを任意のものに指定

1. コンパイル
    1. このパッケージのディレクトリに移動
    1. [`dp-matching-word-recognition/core/`](https://github.com/nacky823/dp-matching-word-recognition/tree/master/core) ディレクトリに移動してコンパイル
        ```
        cd core/ && make
        ```

1. 実行
    ```
    ./do
    ```
    + 下記のように **単語認識率 [%]** が出力される
        ```
        
        !!! Did not match with the correct answer. !!!
        Correct file : sample011_020.txt
        Unknown file : sample012_062.txt
        Word distance is 0.603361
        
        
        The accuracy rate is 99% [%].
        ```
        + 不一致の単語がある場合、詳細情報を出力する
            + `Correct file : sample011_020.txt` は正解のファイル
            + `Unknown file : sample012_062.txt` は認識対象のファイル
            + `Word distance is 0.603361` は DP マッチングにおける単語間距離

### 斜め遷移の重み変更方法

累積距離を計算するための再帰方程式において、斜め遷移の重みを変更する手順は以下の通りです。

1. [`common.hpp`](https://github.com/nacky823/dp-matching-word-recognition/blob/cb6c0397860a4f31eb237090836015804eec90a5/core/common.hpp#L21C1-L21C17) の `21` 行目を編集
    + 重みの値を、任意の `double` 型の浮動小数点数に変更する
        ```c++
        #define WEIGHT 2
        ```
        > **Note**
        > + 初期設定では重みの値が `2` になっている。
        > + ex. $\sqrt{2}$ に変更する場合、以下の様に記述する。
        >     ```c++
        >     #define WEIGHT 1.414213562373
        >     ```

1. コンパイル & 実行
    + `core/` ディレクトリで以下のコマンドを実行
    ```
    make clean && make && ./do
    ```

## License

This project is licensed under the GNU General Public License (GPL) version 2.0. 
Please see the [`COPYING`](https://github.com/nacky823/dp-matching-word-recognition/blob/master/COPYING) file for more information.

© 2023 Yuki NAGAKI