# コーディング規約

この規約は `*.cpp`, `*.h` ファイルに適用される  
また、この規約は `.editorconfig`ファイルで可能な限り設定する

## ソースコードの編集設定

|||
|-|-|
|文字コード|`UTF8` (BOM無し)|
|改行コード|`CRLF` (Windows環境)|
|インデント|`Tab` 文字|

## 前提

### メタ構文の説明

意味のない言葉として以下を使う

- `hoge`
- `fuga`
- `piyo`
- `foo`
- `bar`
- `baz`

## 命名規則

### ケース名の説明

#### ロワーキャメル

`hogeFuga`

始め小文字で単語の区切り目だけ大文字にする

#### アッパーキャメル

`HogeFuga`

始めも大文字で単語の区切り目も大文字にする

#### コンスタントケース

`HOGE_FUGA`

全て大文字で単語に区切り目にアンダースコア`_`を入れる

### 変数関係

#### 仮引数

関数の側で宣言する引数

`int _hogeFuga`
`const int _fooBar`


ロワーキャメル + 頭にアンダースコア`_`を付ける

### クラス関係

#### クラス名

`class HogeFuga`

アッパーキャメル

#### クラス名 (抽象クラス/インタフェース)

`class IHogeFuga`

アッパーキャメル + 頭にインタフェースの頭文字`I`を付ける

#### メンバ関数

`void HogeFuga()`

アッパーキャメル

#### メンバ変数

`int hogeFuga_`

ロワーキャメル + 末尾にアンダースコア`_`を付ける

#### メンバ変数 定数

`const int FOO_BAR`

コンスタントケース

### プリプロセッサ

#### マクロ名

`#define HOGE_FUGA`
`#define FOO_BAR 0`

コンスタントケース

### マクロの仮引数

`#define HOGE_FUGA(fooBar)`

ロワーキャメル

## 構文

### 変数初期化

`int hogeFuga{ 12345 };`

暗黙的に narrowing(情報量を少なくする型変換)を禁止すべく、初期化子リストを使用する

✅ `HogeFuga hogeFuga{ 12345 };`</br>
❌ `HogeFuga hogeFuga(12345);`</br>
❌ `HogeFuga hogeFuga = { 12345 };`</br>
❌ `HogeFuga hogeFuga = 12345;`

ただし、指定初期化子を使う場合は、1つの値のときのみ代入演算子`=`を使う

```cpp
const Hoge HOGE
{
  hoo = 0,
  bar = "",
  fuga
  {
    hoo = 20,
    bar = "ABC",
  },
};
```

DirectXの HOGEFUGA_DESC 系で見やすくなる効果を期待

### 波括弧の位置

Allman / BSD Style
```cpp
if (hogeFuga)
{
}

if (fooBar)
{
}
else
{
}
```

波括弧を改行し、行頭に置く

### インデント文字

タブ

```
{
	{
	}
}
```

全部の.h/.cppファイルでタブ文字

## 略称

- 略称は誰が読んでも分かる、共通認識を持った言葉にだけ使う
- わからない場合は説明のコメントを残す

以下共通認識を持つ略称

|略称|正式名称|
|-|-|
|init|initialize|

## コンポーネントの実装

セッターの有無にかかわらず、必ずメンバ変数の初期化を行う

□