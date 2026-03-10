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
#include <functional>
#include <array>
#include <bitset>
#include <stack>
#include <queue>
#include <tuple>
#include <fstream>

#include <typeindex>

#include <concepts>

#include "ReleaseUtility.h"
#include "LogUtility.h"
#include "WTGBResult.h"

#include "CoreType/Vector2Int.h"
#include "CoreType/Vector4.h"
#include "CoreType/Vector3.h"
#include "CoreType/Vector2.h"
#include "CoreType/Matrix4x4.h"
#include "CoreType/RectF.h"
#include "CoreType/RectInt.h"
#include "CoreType/Color.h"
#include "CoreType/Collection/HandlerCollection.h"
#include "CoreType/Handler.h"

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


#include "LibHeader/FileSystem.h"

#ifdef _DEBUG
#else
	// リリースモードで wassert 未定義エラーを消すために
	#define wassert(expression)
#endif

#endif //PCH_H

// ゲーム側の設定
