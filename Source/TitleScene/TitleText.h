#include <wtgb.h>


/// <summary>
/// タイトルのテキスト表示
/// </summary>
class TitleText : public GameObject
{
public:
	TitleText(const EntityId _titleNeco);
	~TitleText();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	EntityId titleNeco_;    // タイトルネコ
	TextureHandle hImage_;  // タイトルテキストの画像

	Vector2 beginPosition_;  // 最初の地点
	Vector2 endPosition_;    // あげ切った地点
	Vector2 imageSize_;      // 画像サイズ
};
