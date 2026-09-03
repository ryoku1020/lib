---
title: Fast IO
documentation_of: ../fast-io.hpp
---

# Fast IO

高速な入出力を行うための構造体です。標準入出力（`stdin` / `stdout`）およびファイル入出力に対応しています。
`fread` および `fwrite` を用いて、128KB のバッファを内部で確保・管理することで、標準の `cin` / `cout` よりも高速に入出力処理を行います。

## `fast_read`

高速に入力を読み取るための構造体です。

### 使い方

```cpp
#include "fast-io.hpp"

fast_read in;

int n;
long long m;
in(n, m); // 複数同時に読み込み

string s;
in(s);

// operator >> も利用可能
int k;
in >> k;
```

### コンストラクタ

- `fast_read()`: `stdin` から読み込むインスタンスを生成します。
- `fast_read(const filesystem::path& p)`: 指定したファイルパスから読み込むインスタンスを生成します。
- `fast_read(FILE *stream)`: 指定したファイルストリームから読み込むインスタンスを生成します。

### メソッド

- `template<unsigned_integral T> void operator () (T &x)`
- `template<signed_integral T> void operator () (T &x)`
- `void operator () (char &x)`
- `void operator () (string &x)`
- `template<class... Ts> void operator () (Ts&... xs)`: 可変長引数で複数の変数を一度に読み込みます。
- `template<class T> fast_read& operator >> (T &x)`

整数型、文字、文字列の読み込みに対応しています。空白文字（スペース、タブ、改行等）は読み飛ばされます。

## `fast_write`

高速に出力を書き出すための構造体です。

### 使い方

```cpp
#include "fast-io.hpp"

fast_write out;

int n = 10;
long long m = 20;
out(n);
out(' ');
out(m);
out('\n');

// lnメソッドを使うと、スペース区切り・改行付きで簡単に出力できます
out.ln(n, m, 30); // "10 20 30\n" が出力される

// operator << も利用可能
out << "Hello, World!" << '\n';
```

### コンストラクタ

- `fast_write()`: `stdout` に書き出すインスタンスを生成します。
- `fast_write(const filesystem::path& p)`: 指定したファイルパスに書き出すインスタンスを生成します。
- `fast_write(FILE *stream)`: 指定したファイルストリームに書き出すインスタンスを生成します。

### メソッド

- `template<unsigned_integral T> void operator () (T x)`
- `template<signed_integral T> void operator () (T x)`
- `void operator () (char c)`
- `void operator () (string_view s)`
- `template <char End = '\n', char Sep = ' ', class T, class... Ts> void ln(T&& x, Ts&&... xs)`: 複数の値を文字 `Sep` で区切って出力し、最後に `End` を出力します。
- `template<class T> fast_write& operator << (T x)`

整数型(`__uint128_t`を含む)、文字、文字列(`string_view`)の出力に対応しています。
出力バッファはデストラクタでフラッシュされます。

## 境界・注意

- 入力は空白区切りの整数・文字・文字列を想定しています。`fast_read` には EOF 判定や入力失敗を返す API がないため、呼び出し回数分の正しいトークンが存在する必要があります。
- 整数は読み込み先の型で表現できる範囲に収めてください。範囲外の値や、符号なし整数に対する負数は扱えません。
- 文字列は空白を含まない 1 トークンを読みます。行全体を読む `getline` 相当の機能はありません。
- `fast_read(string&)` はトークンの途中で内部バッファを読み足しません。非常に長い文字列やバッファ境界をまたぐ文字列には使わず、その可能性がある入力には標準のストリームを使ってください。
- 浮動小数点数の入出力には対応していません。
- パス版コンストラクタはファイルを開けることを前提とし、失敗を通知しません。
- `fast_read` / `fast_write` はコピーできません。渡す必要がある場合は参照を使います。
- `FILE*` またはパスから構築したインスタンスはデストラクタでファイルを閉じます。`stdin` / `stdout` は閉じません。
- `fast_write` はデストラクタでバッファをフラッシュします。途中で別の出力 API と混在させる場合、出力順は保証されないため避けてください。

## 計算量

長さ `L` のトークンを 1 個読み書きする時間は `O(L)`、追加領域はインスタンスごとに `O(BUF_SIZE)` です。整数型では桁数が型のビット幅で抑えられるため、通常は 1 回あたり `O(1)` とみなせます。

一連の入出力全体では、読み飛ばした空白も含む入出力バイト数を `B` として時間 `O(B)` です。バッファ容量 `BUF_SIZE = 2^17` は入力サイズによらず一定です。

## 使用例

標準入力から読み、標準出力へ答えを出します。

```cpp
#include "fast-io.hpp"

fast_read in;
fast_write out;

int n;
in(n);

long long sum=0;
rep(i,n){
    long long x;
    in(x);
    sum+=x;
}

out.ln(sum);
```
