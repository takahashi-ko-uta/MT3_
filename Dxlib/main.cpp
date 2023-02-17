#include "DxLib.h"
#include "Vector3.h"
#include "Quaternion.h"
#include <vector>

//�֐��v���g�^�C�v�錾
void DrawAxis3D(const float length);

//���̕`��
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);
//�֐��v���g�^�C�v�錾
//int DrawCircle(Vector2 vec, int r, unsigned int color);

//�����̕`��
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int color);

int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DivColor, const unsigned int SpcColor, const int FillFlag);

//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,//�J�����̈ʒu
	const Vector3& cameraTarget,//�J�����̒����_
	const Vector3& cameraUp
);

//����_�̏W��
Vector3 splinePosition(const std::vector<Vector3>& points, size_t startIndex, float t);


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �E�B���h�E����
	const int WIN_WIDTH = 1024;
	// �E�B���h�E�c��
	const int WIN_HEIGHT = 576;
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);
	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(200, 200, 200);
	// DXlib�̏�����
	if (DxLib_Init() == -1)  return -1;
	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);
	SetUseZBuffer3D(TRUE);//Z�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);//Z�o�b�t�@�ւ̏������݂�L���ɂ���

	//�N���b�v��
	SetCameraNearFar(1.0f, 1000.0f);//�J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);//��ʂ̒��S���J�����̒��S�ɍ��킹��
	SetCameraPositionAndTargetAndUpVec(
		Vector3(-20.0f, 20.0f, -120.0f),
		//Vector3(0.0f,200.0f,0.0f),//�J�����̈ʒu
		Vector3(0.0f, 0.0f, 0.0f),//�J�����̒����_
		Vector3(0.0f, 1.0f, 0.0f)//�J�����̏�̌���
	);

	


	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
		Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
		Quaternion identity_ = Identity();
		Quaternion conj = Conjugate(q1);
		Quaternion inv = Inverse(q1);
		Quaternion normal = Normalize(q1);
		Quaternion mul1 = q1 * q2;
		Quaternion mul2 = q2 * q1;
		float norm = Norm(q1);

		// �`�揈��
		// ��ʃN���A
		ClearDrawScreen();  //��ʂ�����
		//DrawAxis3D(500.0f); //xyz���̕`��

		DrawFormatString(3, 10, GetColor(0, 0, 0), "p1(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", q1.x, q1.y, q1.z, q1.w);
		DrawFormatString(3, 30, GetColor(0, 0, 0), "p2(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", q2.x, q2.y, q2.z, q2.w);
		DrawFormatString(3, 50, GetColor(0, 0, 0), "identity(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", identity_.x, identity_.y, identity_.z, identity_.w);
		DrawFormatString(3, 70, GetColor(0, 0, 0), "conj(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", conj.x, conj.y, conj.z, conj.w);
		DrawFormatString(3, 90, GetColor(0, 0, 0), "inv(x:%.2f,y:%.2f,z:%.2f,w:%.2f)",inv.x, inv.y, inv.z, inv.w);
		DrawFormatString(3, 110, GetColor(0, 0, 0), "normal(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", normal.x, normal.y, normal.z, normal.w);
		DrawFormatString(3, 130, GetColor(0, 0, 0), "mul1(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", mul1.x, mul1.y, mul1.z, mul1.w);
		DrawFormatString(3, 150, GetColor(0, 0, 0), "mul2(x:%.2f,y:%.2f,z:%.2f,w:%.2f)", mul2.x, mul2.y, mul2.z, mul2.w);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();


	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

//xyz�̕`��
void DrawAxis3D(const float length)
{
	//���̐��̕`��
	DrawLine3D(VGet(-length, 0, 0), VGet(+length, 0, 0), GetColor(255, 0, 0));//x��
	DrawLine3D(VGet(0, -length, 0), VGet(0, +length, 0), GetColor(0, 255, 0));//y��
	DrawLine3D(VGet(0, 0, -length), VGet(0, 0, +length), GetColor(0, 0, 255));//z��

}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };//�\���� �������q���X�g

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);//DxLib�֐��̌Ăяo��
}
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r,
	const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };

	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
//�����̕`��
//DXLib=> int DrawLine3D(VECTOR Pos1, VECTOR Pos2, unsigned int color);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };//�\���� �������q���X�g
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };//�\���� �������q���X�g

	return DrawLine3D(p1, p2, color);
}
//�J�����̈ʒu�Ǝp���̐ݒ�
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,//�J�����̈ʒu
	const Vector3& cameraTarget,//�J�����̒����_
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
	//��Ԃ��ׂ��_�̐�
	size_t n = points.size() - 2;

	if (startIndex > n)return points[n];//Pn�̒l��Ԃ�
	if (startIndex < 1)return points[1];//P1�̒l��Ԃ�

	//p0~p3�̐���_���擾���� p1~p2���Ԃ���
	Vector3 p0 = points[startIndex - 1];
	Vector3 p1 = points[startIndex];
	Vector3 p2 = points[startIndex + 1];
	Vector3 p3 = points[startIndex + 2];
	//Catmull-Rom�̎��ɂ����
	Vector3 position = {
		2 * p1 + (-p0 + p2) * t +
		(2 * p0 - 5 * p1 + 4 * p2 - p3) * (t * t) +
		(-p0 + 3 * p1 - 3 * p2 + p3) * (t * t * t) };

	return position * 0.5f;
}