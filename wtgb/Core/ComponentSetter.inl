template<typename ComponentT>
wtgb::GameObjectBuilder& wtgb::ComponentSetter<ComponentT>::EndSetter()
{
	builder_.target_.template GetComponent<ComponentT>().Init(nullptr);

	delete pOption_;

	GameObjectBuilder& builder{ builder_ };
	delete this;
	return builder;
}
