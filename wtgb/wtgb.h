#pragma once

/*
* バディーズ・スカイ・コンバット再構築のために作られるゲームベース
* 決してゲームエンジン制作にのめり込んではいけない
* 作ったゲームをお客様に楽しんでもらうことが最終目標であり、その目標のためのベースが wtgb
* 読み方は ダブティージービー
* 由来は mtgb の m を 水平軸反転しただけ
*/

// 便利系
#include "WTGBAssert.h"
#include "Utility/Mathf.h"
#include "Utility/Ease.h"
#include "Utility/JsonUtility.h"
#include "Core/Entity.h"
#include "CoreType/ExtJson/Vector3.h"
#include "CoreType/ExtJson/Vector2Int.h"

// インタフェース系
#include "Core/IGame.h"
#include "Core/IGameSystem.h"

// コンポーネントプール
#include "GameSystem/CPCollider.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/CPGameObjectProperty.h"
#include "GameSystem/CPMeshRenderer.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPRigidBody.h"
#include "GameSystem/CPTransform.h"

// 他コア系
#include "Core/GameSystemCollection.h"
#include "Core/GameScene.h"
#include "Core/Game.h"

// コンポーネント
#include "GameComponent/GameObject.h"
#include "GameComponent/GameObjectProperty.h"
#include "GameComponent/Transform.h"
#include "GameComponent/ModelMesh.h"
#include "GameComponent/MeshRenderer.h"
#include "GameComponent/Collider.h"
#include "GameComponent/RigidBody.h"

// 他システム
#include "GameSystem/GameTime.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Camera.h"
#include "GameSystem/Input.h"
#include "GameSystem/Cursor.h"
#include "GameSystem/SceneManager.h"
#include "GameSystem/ResourceSystem.h"
#include "GameSystem/Canvas.h"
#include "GameSystem/Canvas/CanvasContext.h"
#include "GameSystem/Canvas/LayoutConfig.h"
#include "GameSystem/Audio.h"
#include "GameSystem/Direct3D.h"

// ビルダー
#include "Core/GameObjectBuilder.h"

// エイリアス
using wtgb::IGame;
using wtgb::IGameSystem;
using wtgb::GameSystemCollection;
using wtgb::GameScene;
using wtgb::GameObject;
using wtgb::GameObjectProperty;
using wtgb::ModelMesh;
using wtgb::MeshRenderer;

using namespace wtgb;
