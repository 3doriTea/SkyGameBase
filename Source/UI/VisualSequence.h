#pragma once
#include <wtgb.h>


/// <summary>
/// UIを順番に表示させるシーケンス
/// </summary>
class VisualSequence : public GameObject
{
public:
	VisualSequence();
	inline ~VisualSequence() {}

	inline void Init() override {}
	inline void Update() override {}
	inline void Release() override {}

	VisualSequence& ClearSequence();
	VisualSequence& AddInSequence(const EntityId _visualEntity);

	/// <summary>
	/// 次のUIを表示する
	/// </summary>
	void ShowNext();
	/// <summary>
	/// <para>指定のインデクスを表示する</para>
	/// <para>現在のインデクスと同じ場合も更新がかかる</para>
	/// </summary>
	/// <param name="_index">インデクス</param>
	void ShowAt(const int _index);
private:
	std::vector<EntityId> visuals_;  // 表示内容のコレクション
	int currentIndex_;               // 表示内容のインデクス
	static int INVALID_INDEX_;       // 無効なインデクス
};
