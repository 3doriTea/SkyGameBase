
template<typename GameObjectT>
inline GameObjectT* wtgb::GameObject::FindGameObject(const EntityId _entityId)
{
	return dynamic_cast<GameObjectT*>(System().Get<CPGameObject>().Get(_entityId));
}
