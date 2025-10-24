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
#include "Core/GameScene.h"

#include "Core/GameObjectBuilder.h"

#include "GameComponent/GameObject.h"
#include "GameComponent/GameObjectProperty.h"
#include "GameComponent/Transform.h"

using wtgb::IGame;
using wtgb::GameSystemCollection;
using wtgb::GameScene;
using wtgb::GameObject;

using namespace wtgb;
