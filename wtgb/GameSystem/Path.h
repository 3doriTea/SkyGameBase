#pragma once
#include "pch/pch.h"
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// ファイルパスシステム
	/// </summary>
	class Path : public IGameSystem
	{
	public:
		/// <summary>
		/// 現在のディレクトリを指す
		/// </summary>
		class Current
		{
			friend Path;  // パスシステムからはアクセスできるようにするs
		private:
			Current(const fs::path& _currentPath);
			~Current() {}

		private:
			fs::path currentPath_;  // カレントパス

		public:
			/// <summary>
			/// 現在のディレクトリを取得する
			/// </summary>
			static fs::path Directory();

			/// <summary>
			/// ファイルが存在するかチェックする
			/// </summary>
			/// <param name="_path">チェックするファイルのパス</param>
			/// <returns>存在する true / false</returns>
			static bool Exists(const fs::path& _path);

		private:
			static Current* pInstance_;  // シングルトン用唯一のインスタンス
		};

	public:
		Path();
		~Path();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::DoNotUpdate; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override {};
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;
	};
}
