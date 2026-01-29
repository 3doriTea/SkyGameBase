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

	void ShowNext();
	void ShowAt(const int _index);
private:
	std::vector<EntityId> visuals_;  // 表示内容のコレクション
	int currentIndex_;               // 表示内容のインデクス
};
