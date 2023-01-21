#include "DxLib.h"
#include "Vector3.h"

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
	SetBackgroundColor(0, 0, 64);
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
		Vector3(0.0f, 200.0f, 0.0f),//�J�����̈ʒu
		Vector3(0.0f, 0.0f, 0.0f),//�J�����̒����_
		Vector3(0.0f, 0.0f, 1.0f)//�J�����̏�̌���
	);

	//���Ԍv���ɕK�v�ȃf�[�^
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	//��ԂŎg���f�[�^
	//start -> end��5[s]�Ŋ���������
	Vector3 p0(-100.0f, 0.0f, 0.0f);//�X�^�[�g�n�_
	Vector3 p1(-10.0f, 0.0f, 50.0f);//����_
	Vector3 p2(10.0f, 0.0f, -50.0f);//����_
	Vector3 p3(+100.0f, 0.0f, 0.0f);//�G���h�n�_
	float maxTime = 5.0f;
	float timeRate;

	//���̈ʒu
	Vector3 position;

	//���s�O�Ɂ@�J�E���^�l���擾
	startCount = GetNowHiPerformanceCount(); //long long int�^  64bit int

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{


		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//[R]�Ń��Z�b�g
		if (CheckHitKey(KEY_INPUT_R))
		{
			startCount = GetNowHiPerformanceCount();
		}
		//�o�ߎ���(elapsedTime[s])�̌v�Z
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float>(elapsedCount) / 1'000'000.0f;

		//�X�^�[�g�n�_�@�@:start
		//�G���h�n�_�@�@�@:end
		//�o�ߎ��ԁ@�@�@�@:elapsedTime[s]
		//�ړ������̗�(�o�ߎ���/�S�̎���):timeRate(%)

		timeRate = min(elapsedTime / maxTime, 1.0f);

		Vector3 a = lerp(p0, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, p3, timeRate);

		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);

		position = lerp(d, e, timeRate);

		//position = easeIn(start,end,timeRate);
		//position = easeOut(start,end,timeRate);
		//position = easeInOut(start,end,timeRate);

		//----------�`�揈��----------//
		// ��ʃN���A
		ClearDrawScreen();  //��ʂ�����
		DrawAxis3D(500.0f); //xyz���̕`��

		//���̕`��
		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p0, 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p1, 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p2, 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p3, 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);

		//
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%5.1f,%5.1f,%5.1f)", position.x, position.y, position.z);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f [s]", elapsedTime);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R] : Restart");

		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0(%6.1f,%6.1f,%6.1f)", p0.x, p0.y, p0.z);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1(%6.1f,%6.1f,%6.1f)", p1.x, p1.y, p1.z);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2(%6.1f,%6.1f,%6.1f)", p2.x, p2.y, p2.z);
		//DrawKeyOperation();//�L�[����̕`��

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
