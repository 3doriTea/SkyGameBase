template<typename ComponentT>
wtgb::GameObjectBuilder& wtgb::ComponentSetter<ComponentT>::EndSetter()
{
	builder_.target_.template GetComponent<ComponentT>().Init(*builder_.target_.pCachedSystem_);

	delete pOption_;

	GameObjectBuilder& builder{ builder_ };
	delete this;  // NOTE: これ以降メンバにアクセスしてはいけない
	return builder;
}
