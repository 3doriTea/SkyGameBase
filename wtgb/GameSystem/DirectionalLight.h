#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// 平行光線を管理するシステム
	/// </summary>
	class DirectionalLight : public IGameSystem
	{
	public:
		DirectionalLight();
		~DirectionalLight();

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

		/// <summary>
		/// 光源の方向を取得する
		/// </summary>
		/// <returns>光源の方向</returns>
		Vector3 GetDirection() const { return direction_; }

		/// <summary>
		/// 光源の方向を設定する
		/// </summary>
		/// <param name="_direction">光源の方向</param>
		void SetDirection(const Vector3& _direction) { direction_ = _direction; }

		/// <summary>
		/// 光源の色を設定する
		/// </summary>
		/// <param name="_color">光源の色</param>
		void SetColor(const Color _color) { color_ = _color; }

		/// <summary>
		/// 光源の色を取得する
		/// </summary>
		/// <returns>光源の色</returns>
		Color GetColor() const { return color_; }

	private:
		Vector3 direction_;  // 平行光源の方向
		Color color_;        // 光源の色
	};
}
