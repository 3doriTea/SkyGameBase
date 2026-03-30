#pragma once

/// <summary>
/// ミニキャラの種類
/// </summary>
using MiniCharaType = uint32_t;

/// <summary>
/// ミニキャラの種類
/// </summary>
enum MiniCharaType_ : MiniCharaType
{
	MiniCharaType_T,         // メイン
	MiniCharaType_Base3,     // ベース
	MiniCharaType_Tubar,     // チューバ
	MiniCharaType_Monkitty,  // ドラム
	MiniCharaType_Glocken,   // グロッケン
	MiniCharaType_Max,       // ミニキャラの種類の最大数
};
