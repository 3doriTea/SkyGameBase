#include "pch\pch.h"
#include "CallStackViewer.h"

#include <windows.h>
#include <dbghelp.h>
#include <iomanip>
#include <sstream>

std::string wtgb::GetStackTrace(const int _skipFrames)
{
	// 最大フレーム数
	static const int MAX_FRAMES = 64;
	// スタックポインタを格納する配列
	void* stack[MAX_FRAMES]{};

	// プロセスのハンドルを取得
	HANDLE hProcess{ GetCurrentProcess() };

	// 呼び出し履歴のポインタをキャプチャする
	// _skipFrames: スキップするフレーム数 (GetStackTrace関数自体をスキップするために 1 または 2 を指定)
	// frames: キャプチャされたフレーム数
	const USHORT frames
	{
		CaptureStackBackTrace(
			_skipFrames,
			MAX_FRAMES,
			stack,
			nullptr) // ハッシュ値不要
	};

	std::stringstream ss;

	// シンボル情報の初期化
	// NULL は検索パスにカレントディレクトリと環境変数 _NT_SYMBOL_PATH を使用
	// TRUE はシンボルパスの再帰的検索を有効にする
	if (!SymInitialize(hProcess, nullptr, TRUE))
	{
		ss << "SymInitialize failed (Error: " << GetLastError() << ")\n";
		return ss.str();
	}

	// SYMBOL_INFO構造体は可変長なので、バッファを確保
	static const size_t MAX_NAME_LENGTH = 1024;
	SYMBOL_INFO* pSymbol
	{
		reinterpret_cast<SYMBOL_INFO*>(calloc(
			sizeof(SYMBOL_INFO) + MAX_NAME_LENGTH * sizeof(char), 1))
	};

	if (pSymbol == nullptr)
	{
		ss << "Memory allocation for symbol failed\n";
		SymCleanup(hProcess);
		return ss.str();
	}

	pSymbol->MaxNameLen = MAX_NAME_LENGTH - 1;
	pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);

	ss << "--- Call Stack ---\n";

	for (USHORT i = 0; i < frames; ++i)
	{
		// 関数名とアドレスの取得 (SymFromAddr)
		if (SymFromAddr(hProcess, (DWORD64)stack[i], 0, pSymbol))
		{
			// ファイル名と行番号の取得 (SymGetLineFromAddr64)
			IMAGEHLP_LINE64 lineInfo{ sizeof(IMAGEHLP_LINE64) };
			DWORD dwDisplacement{}; // 行の開始からのオフセット

			if (SymGetLineFromAddr64(hProcess, (DWORD64)stack[i], &dwDisplacement, &lineInfo))
			{
				// ファイル名と行番号が取得できた場合
				ss << std::setw(3) << std::dec << frames - 1 - i << ": 0x"
					<< std::hex << std::setw(16) << std::setfill('0') << pSymbol->Address
					<< " in " << pSymbol->Name
					<< " (" << lineInfo.FileName << ":" << lineInfo.LineNumber << ")\n";
			}
			else
			{
				// 関数名のみ取得できた場合
				ss << std::setw(3) << std::dec << frames - 1 - i << ": 0x"
					<< std::hex << std::setw(16) << std::setfill('0') << pSymbol->Address
					<< " in " << pSymbol->Name << " (No line info)\n";
			}
		}
		else
		{
			// シンボル情報が取得できなかった場合（アドレスのみ）
			ss << std::setw(3) << std::dec << frames - 1 - i << ": 0x"
				<< std::hex << std::setw(16) << std::setfill('0') << (DWORD64)stack[i]
				<< " (Symbol not found)\n";
		}
	}

	ss << "--------------------\n";

	// クリーンアップ
	free(pSymbol);
	SymCleanup(hProcess);

	return ss.str();
}
