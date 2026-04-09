---
title: Fast IO
documentation_of: ../fast_io.hpp
---

# Fast IO

高速な入出力を行うための構造体です。標準入出力（`stdin` / `stdout`）およびファイル入出力に対応しています。
`fread` および `fwrite` を用いて、128KB のバッファを内部で確保・管理することで、標準の `cin` / `cout` よりも高速に入出力処理を行います。

## `FastRead`

高速に入力を読み取るための構造体です。

### 使い方
```cpp
#include "fast_io.hpp"

FastRead in;

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
- `FastRead()`: `stdin` から読み込むインスタンスを生成します。
- `FastRead(const filesystem::path& p)`: 指定したファイルパスから読み込むインスタンスを生成します。
- `FastRead(FILE *stream)`: 指定したファイルストリームから読み込むインスタンスを生成します。

### メソッド
- `template<unsigned_integral T> void operator () (T &x)`
- `template<signed_integral T> void operator () (T &x)`
- `void operator () (char &x)`
- `void operator () (string &x)`
- `template<class... Ts> void operator () (Ts&... xs)`: 可変長引数で複数の変数を一度に読み込みます。
- `template<class T> FastRead& operator >> (T &x)`

整数型、文字、文字列の読み込みに対応しています。空白文字（スペース、タブ、改行等）は読み飛ばされます。

## `FastWrite`

高速に出力を書き出すための構造体です。

### 使い方
```cpp
#include "fast_io.hpp"

FastWrite out;

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
- `FastWrite()`: `stdout` に書き出すインスタンスを生成します。
- `FastWrite(const filesystem::path& p)`: 指定したファイルパスに書き出すインスタンスを生成します。
- `FastWrite(FILE *stream)`: 指定したファイルストリームに書き出すインスタンスを生成します。

### メソッド
- `template<unsigned_integral T> void operator () (T x)`
- `template<signed_integral T> void operator () (T x)`
- `void operator () (char c)`
- `void operator () (string_view s)`
- `template <char End = '\n', char Sep = ' ', class T, class... Ts> void ln(T&& x, Ts&&... xs)`: 複数の値を文字 `Sep` で区切って出力し、最後に `End` を出力します。
- `template<class T> FastWrite& operator << (T x)`

整数型(`__uint128_t`を含む)、文字、文字列(`string_view`)の出力に対応しています。
出力バッファはデストラクタでフラッシュされます。
