import os
import sys

dirs = ["ds", "graph", "math", "string", "tree", "other"]

def generate_md(src_path):
    base = os.path.splitext(src_path)[0]
    filename = os.path.basename(src_path)
    title = os.path.splitext(filename)[0].capitalize()
    md_path = base + ".md"

    doc_of = f"./{filename}"

    content = f"""---
title: {title}
documentation_of: {doc_of}
---

# {title}

## 概要
ここに概要を記述します。
（例: 0-indexed で管理し、区間は半開区間 `[l, r)` で指定します。）

## 使い方

```cpp
#include "{src_path}"

// 使用例
```

## メソッド

### `メソッド名`
ここにメソッドの説明を記述します。
- 制約:
- 計算量: $O()$
"""
    with open(md_path, "w", encoding="utf-8", newline='\n') as f:
        f.write(content)
    print(f"Generated {md_path}")

def main():
    for d in dirs:
        if not os.path.exists(d): continue
        for f in os.listdir(d):
            if f.endswith(".hpp") or f.endswith(".cpp"):
                src_path = os.path.join(d, f)
                base = os.path.splitext(src_path)[0]
                md_path = base + ".md"
                if not os.path.exists(md_path):
                    generate_md(src_path)

if __name__ == "__main__":
    main()
