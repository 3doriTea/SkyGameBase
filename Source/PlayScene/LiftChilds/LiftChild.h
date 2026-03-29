#pragma once
#include <wtgb.h>


/// <summary>
/// リフト追従オブジェクト
/// </summary>
class LiftChild : public GameObject
{
public:
	LiftChild(
		const EntityId _parentLift,
		const fs::path& _modelFile);
	~LiftChild();

	inline void Init() override;
	inline void Update() override;
	inline void Release() override;

	virtual ModelHandle OnGetModel() = 0;
	virtual void OnLoadParam(const json& _json) {}

protected:
	/// <summary>
	/// モデルをセットする
	/// </summary>
	/// <param name="_hModel">モデルのハンドル</param>
	void SetModel(const ModelHandle _hModel);

private:
	EntityId parentLift_;  // くっつく椅子
};
