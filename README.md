# はねねこボール - v1.0.1

## 開発環境

|||
|-|-|
|OSとメモリ|Windows11 (メモリ 32GB)|
|IDE|Microsoft Visual Studio 2022 / 2026|
|開発言語とバージョン|C++ 20 / HLSL (Shader Model 5.0) |
|ライブラリ| [FBX SDK](https://aps.autodesk.com/developer/overview/fbx-sdk) / [dr_libs](https://github.com/mackron/dr_libs) / [ImGui](https://github.com/ocornut/imgui) / [JSON for Modern C++ (Nlohmann-JSON)](https://github.com/nlohmann/json) |
||DirectX11|

## 操作説明

- ゲーム起動後はマウスデバイスのみ使用
- ゲーム内に表示される黄色い円の内側をドラッグすることで操作
- プレイシーンに限り、黄色い円内外のドラック操作が異なる
	- 内側 → 操作ボールの指定方向への加速
	- 外側 → カメラの視点操作

## ドキュメント

- [プロジェクト概要](docs/Document.md)  
  ディレクトリ構成やソースコードの分類を説明します。
- [コーディング規約](docs/CodingGuide.md)  
  ソースコードの書き方を明記します。

## アピールポイント

- 別途記述
