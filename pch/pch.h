// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef PCH_H
#define PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"

#include <string>
#include <cstdint>
#include <cassert>
#include <vector>
#include <map>
#include <format>
#include <string_view>

#include <concepts>

#include "ReleaseUtility.h"
#include "LogUtility.h"
#include "WTGBResult.h"

#include "CoreType/CoreType.h"

#endif //PCH_H
