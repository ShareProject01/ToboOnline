# ToboOnline

Unreal Engine 5で制作している、2人以上の対戦を想定したオンライン・アリーナシューターです。
ロビーでプレイヤーを受け入れ、プレイ人数を同期しながらアリーナへ遷移し、武器・弾薬・体力・チーム・勝敗を扱う一連のゲームフローを実装しています。
Epic Online System を利用し実装していましたが、ポートフォリオ用に該当箇所をすべて外しています。
(テストプレイ時にEpicアカウントが必要になってしまうためです)

## Project Overview

- **ジャンル**: Multiplayer arena shooter
- **エンジン**: Unreal Engine 5.8
- **対象環境**: Windows
- **プレイ構成**: ロビー、対戦アリーナ、リザルト画面
- **ネットワーク**: Unreal EngineのReplicationとIP Net Driverを利用
- **実装方式**: Blueprintを中心に、一部のゲーム基盤をC++で実装

## Game

- ToboOnline_Release\Windows このフォルダの「ToboOnline.exe」を実行するとプレイすることができます。
- ※ ローカルサーバーを立てて実行します。外部IPを指定しなければ外部にアクセスは発生しません。

### Lobby Flow

- ロビー画面で参加プレイヤーを表示
- プレイヤー番号と総プレイヤー数の表示
- ロビーからアリーナへのレベル遷移
- 複数回のロビー遷移を想定したUI初期化と状態更新

### Arena Shooter

- 一人称視点のキャラクター操作
- 移動とカメラ操作
- 2種類の武器
- 発射処理
- ダメージ、体力、撃破、リスポーン

### Multiplayer State

- PlayerController、PlayerState、GameStateを分けた状態管理
- プレイヤー番号、総人数、タイマー、チーム情報、スコアの同期
- UIへのRepNotifyイベント通知
- ロビー、ゲーム中、結果画面で異なるUIを表示


## Technology

| Category | Used technology |
| --- | --- |
| Engine | Unreal Engine 5.8 |
| Gameplay | C++, Blueprint |
| UI | UMG / Widget Blueprint |
| Input | Enhanced Input |
| Networking | Replication, GameMode, GameState, PlayerState, PlayerController |

## Architecture

```text
GameMode
  ├─ サーバー権限のゲーム進行
  ├─ プレイヤー参加・退出処理
  └─ マップ遷移

GameState
  ├─ 全体で共有する人数・タイマー・結果
  └─ RepNotifyによるクライアント通知

PlayerController
  ├─ ローカル入力
  ├─ UI生成と更新
  └─ プレイヤー固有の表示情報

PlayerState
  ├─ プレイヤー番号
  ├─ チーム情報
  └─ スコア・参加状態
```

## Controls

| Action | Key |
| --- | --- |
| Move | `W` / `A` / `S` / `D` |
| Camera rotation | Arrow keys |
| Fire | Project input mapping |
| Weapon switch | Project input mapping |

入力はEnhanced Inputを利用し、アクションとマッピングを分離しています。これにより、キーボード以外の入力デバイスにも拡張しやすい構成にしています。

## Directory Guide

```text
Content/Variant_Shooter/
├─ Blueprints/       キャラクター、GameMode、GameState、武器、AI
├─ UI/               ロビー、HUD、弾薬、体力、結果画面
├─ Input/            Enhanced Inputのアクションとマッピング
├─ Anims/            一人称・三人称の武器アニメーション
├─ Maps/             ロビー、遷移、アリーナ
└─ Materials/        武器・エフェクト・環境用マテリアル

Source/ToboOnline/
├─ Public/           C++ヘッダ
└─ Private/          C++実装
```

## How to Open

1. Unreal Engine 5.8をインストールします。
2. `ToboOnline.uproject` をUnreal Editorで開きます。
3. C++プロジェクトとして必要なモジュールをビルドします。
4. `Variant_Shooter/LobbyMap` または `Variant_Shooter/Lvl_ArenaShooter` を開きます。
5. PIEの複数プレイヤー設定を利用して、ロビーからアリーナへの遷移を確認します。

## Portfolio Highlights

このプロジェクトでは、次のような実装経験を示せます。

- ネットワークゲームにおけるサーバー権限とクライアント表示の分離
- ReplicationとRepNotifyを利用したゲーム状態の同期
- ロビーからゲーム、結果画面までの状態遷移設計
- BlueprintとC++の責務分担
- Enhanced Inputを利用した入力設計

## Current Status

現在は、対戦の基本フロー、武器・AI・UI・ネットワーク状態同期を検証している段階です。
今後は、UIデザインの統一、3Dモデルの変更、マッチメイキング、接続エラー時の表示、Epic Online Systemとの連携などの対応を行う予定です。


## Other

こちらのREADME.mdはAI(ChatGPT)に作成してもらいました。

