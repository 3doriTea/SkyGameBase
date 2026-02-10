#include "GameComponent/GameObject.h"


template<typename ComponentT>
wtgb::ComponentOption<ComponentT>& wtgb::GameObjectBuilder::AddComponent()
{
	ComponentT& component{ target_.template AddComponent<ComponentT>() };
	return *(new ComponentOption<ComponentT>{ *this, &component });
}
