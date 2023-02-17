#include "DxLib.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <vector>

//関数プロトタイプ宣言
void DrawAxis3D(const float length);

//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);
//関数プロトタイプ宣言
//int DrawCircle(Vector2 vec, int r, unsigned int color);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int color);

int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DivColor, const unsigned int SpcColor, const int FillFlag);

//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,//カメラの位置
	const Vector3& cameraTarget,//カメラの注視点
	const Vector3& cameraUp
);

//制御点の集合
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウィンドウ横幅
	const int WIN_WIDTH = 1024;
	// ウィンドウ縦幅
	const int WIN_HEIGHT = 576;
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	// 画面の背景色を設定する
	SetBackgroundColor(200, 200, 200);
	// DXlibの初期化
	if (DxLib_Init() == -1)  return -1;
	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);//Zバッファを有効にする
	SetWriteZBuffer3D(TRUE);//Zバッファへの書き込みを有効にする

	//クリップ面
	SetCameraNearFar(1.0f, 1000.0f);//カメラの有効範囲を設定
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);//画面の中心をカメラの中心に合わせる
	SetCameraPositionAndTargetAndUpVec(
		Vector3(-20.0f, 20.0f, -120.0f),
		//Vector3(0.0f,200.0f,0.0f),//カメラの位置
		Vector3(0.0f, 0.0f, 0.0f),//カメラの注視点
		Vector3(0.0f, 1.0f, 0.0f)//カメラの上の向き
	);

	


	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		Quaternion rot0 = MakeAxisAngle({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rot1 = MakeAxisAngle({ 0.71f,0.0f,0.71f }, 3.141592f);

		rot0 = Normalize(rot0);
		rot1 = Normalize(rot1);
		Quaternion interpolate0 = Slerp(rot0, rot1, 0.0f);
		Quaternion interpolate1 = Slerp(rot0, rot1, 0.3f);
		Quaternion interpolate2 = Slerp(rot0, rot1, 0.5f);
		Quaternion interpolate3 = Slerp(rot0, rot1, 0.7f);
		Quaternion interpolate4 = Slerp(rot0, rot1, 1.0f);

		// 描画処理
		// 画面クリア
		ClearDrawScreen();  //画面を消去
		//DrawAxis3D(500.0f); //xyz軸の描画

		DrawFormatString(3, 10, GetColor(0, 0, 0), "0:(x:%.2f,y:%.2f,z:%.2f.w:%.2f)", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
		DrawFormatString(3, 30, GetColor(0, 0, 0), "1:(x:%.2f,y:%.2f,z:%.2f.w:%.2f)", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
		DrawFormatString(3, 50, GetColor(0, 0, 0), "2:(x:%.2f,y:%.2f,z:%.2f.w:%.2f)", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
		DrawFormatString(3, 70, GetColor(0, 0, 0), "3:(x:%.2f,y:%.2f,z:%.2f.w:%.2f)", interpolate3.x, interpolate3.y, interpolate3.z, interpolate3.w);
		DrawFormatString(3, 90, GetColor(0, 0, 0), "4:(x:%.2f,y:%.2f,z:%.2f.w:%.2f)", interpolate4.x, interpolate4.y, interpolate4.z, interpolate4.w);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();


	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//xyzの描画
void DrawAxis3D(const float length)
{
	//軸の線の描画
	DrawLine3D(VGet(-length, 0, 0), VGet(+length, 0, 0), GetColor(255, 0, 0));//x軸
	DrawLine3D(VGet(0, -length, 0), VGet(0, +length, 0), GetColor(0, 255, 0));//y軸
	DrawLine3D(VGet(0, 0, -length), VGet(0, 0, +length), GetColor(0, 0, 255));//z軸

}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };//構造体 初期化子リスト

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);//DxLib関数の呼び出し
}
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };

	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
//線分の描画
//DXLib=> int DrawLine3D(VECTOR Pos1, VECTOR Pos2, unsigned int color);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };//構造体 初期化子リスト
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };//構造体 初期化子リスト

	return DrawLine3D(p1, p2, color);
}
//カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,//カメラの位置
	const Vector3& cameraTarget,//カメラの注視点
	const Vector3& cameraUp
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t)
{
	//補間すべき点の数
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];//Pnの値を返す
	if (startIndex < 1)return points[1];//P1の値を返す

	//p0~p3の制御点を取得する p1~p2を補間する
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];
	//Catmull-Romの式による補間
	Vector3 position = {
		2 * p1 + (-p0 + p2) * t +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) +
		(-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t) };

	return position * 0.5f;
}