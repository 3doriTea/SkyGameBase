#pragma once

/*
* バディーズ・スカイ・コンバット再構築のために作られるゲームベース
* 決してゲームエンジン制作にのめり込んではいけない
* 作ったゲームをお客様に楽しんでもらうことが最終目標であり、その目標のためのベースが wtgb
* 読み方は ダブティージービー
* 由来は mtgb の m を 水平軸反転しただけ
*/

#include "Core/Game.h"
#include "Core/IGame.h"
#include "Core/IGameSystem.h"
#include "Core/GameScene.h"

#include "Core/GameObjectBuilder.h"

#include "GameComponent/GameObject.h"
#include "GameComponent/GameObjectProperty.h"
#include "GameComponent/Transform.h"
#include "GameComponent/ModelMesh.h"
#include "GameComponent/MeshRenderer.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/Camera.h"
#include "GameSystem/Input.h"
#include "GameSystem/SceneManager.h"

using wtgb::IGame;
using wtgb::IGameSystem;
using wtgb::GameSystemCollection;
using wtgb::GameScene;

using wtgb::GameObject;
using wtgb::GameObjectProperty;
using wtgb::ModelMesh;
using wtgb::MeshRenderer;

using namespace wtgb;
