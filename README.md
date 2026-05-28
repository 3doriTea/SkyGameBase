# はねねこボール - v1.1.2

本ゲームは C++ DirectX11 で制作した3Dゲームです。

[実演動画はこちら (OneDriveから共有)](https://jc21-my.sharepoint.com/:v:/g/personal/240343_jc-21_jp/IQDbNu6QCtRgTbJ0xSVoiaIHAbFs-TbK74dxwXnjmFmfAK8?e=15RTvi&nav=eyJyZWZlcnJhbEluZm8iOnsicmVmZXJyYWxBcHAiOiJTdHJlYW1XZWJBcHAiLCJyZWZlcnJhbFZpZXciOiJTaGFyZURpYWxvZy1MaW5rIiwicmVmZXJyYWxBcHBQbGF0Zm9ybSI6IldlYiIsInJlZmVycmFsTW9kZSI6InZpZXcifX0%3D)

## 開発環境

|||
|-|-|
|OS|Windows11|
|メモリ|32GB|
|IDE|Microsoft Visual Studio 2022 / 2026|
|言語|C++ 20 / HLSL (Shader Model 5.0) |
|ライブラリ| [FBX SDK](https://aps.autodesk.com/developer/overview/fbx-sdk) / [dr_libs](https://github.com/mackron/dr_libs) / [ImGui](https://github.com/ocornut/imgui) / [JSON for Modern C++ (Nlohmann-JSON)](https://github.com/nlohmann/json) |
||DirectX11|

## 開発期間

- プロジェクト始動 : 2025年9月29日
- プロジェクト終了 : 未定
- 期間 : 8ヶ月経過 (2026年5月24日現在)

## 実行方法

- exeファイルから実行する方法
  - Assets/ があるディレクトリで SkyGameBase.exe を実行
- Visual Studio から実行する方法
  - FBX SDK 2020.3.9 / 2020.3.7 を標準インストールまたは、  
    プロジェクトプロパティから FBX SDK へのパスを追加必要がある
  - F5キー または ローカルWindowsデバッガーボタン を押し実行

## 操作説明

- ゲーム起動後はマウスデバイスのみ使用
- ゲーム内に表示される黄色い円の内側をドラッグすることで操作
- プレイシーンに限り、黄色い円内外のドラック操作が異なる
  - 内側 → 操作ボールの指定方向への加速
  - 外側 → カメラの視点操作

## 注意事項

- ドラッグ中に画面外までカーソルを動かすと予期せぬ動作が起こるので  
  優しくゆっくり、画面内でつかんでください。
- プレイ中はスピーカーやイヤホン、ヘッドフォンなどで、音楽をお楽しみください。

![](SoundImage.png)

## ドキュメント

- [プロジェクト概要](docs/Document.md)  
  ディレクトリ構成やソースコードの分類の説明
- [コーディング規約](docs/CodingGuide.md)  
  ソースコードの書き方の説明
- [実装後の自己評価](docs/Reflections.md)  
  実装後に得られた効果の説明
- [アピールポイント](docs/SellingPoints.md)  
  制作時に苦戦した点と解決方法のまとめ

## VisualStudio のフィルター機能に関して

- フィルター機能は不使用、ディレクトリ構成でソースコードを分類

## 文字コードに関して

- 本プロジェクトは全てのテキストファイルで`UTF8` BOM無し を使用

□
