#include "GameComponent/GameObject.h"

template<typename ComponentT>
wtgb::ComponentOption<ComponentT>& wtgb::GameObjectBuilder::AddComponent()
{
	ComponentT* pComponent{ pTarget_->template AddComponent<ComponentT>() };
	return *(new ComponentOption<ComponentT>{ *this, pComponent });
}
