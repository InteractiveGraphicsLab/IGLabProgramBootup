/*
�v���~�e�B�u��3D���f���Ɋւ���N���X���܂܂ꂽ�w�b�_�[�t�@�C��
*/
#include "OglForCLI.h"
#include "Transform.h"
#include "Rigidbody.h"

/*
enum color2
{
	green,
	brown,
	white,
};

void SetColr(color2 c)
{
	switch (c)
	{
	case green:
		glColor3f(0.180, 0.545, 0.341);
		break;
	case brown:
		glColor3f(0.545, 0.271, 0.075);
		break;
	case white:
		glColor3f(1.000, 0.980, 0.980);
		break;
	default:
		break;
	}
}
*/


/// <summary>
/// �v���~�e�B�u�I�u�W�F�N�g�̊��N���X
/// </summary>
class PrimitiveObject
{
public:
	Transform transform;
	Rigidbody rigidbody;
	int shapeType;
	//color2 c;
	void SetTransform(EVec3f position, EVec3f rotation, EVec3f linearVelocity, EVec3f rotateVelocity)
	{
		transform.position = position;
		transform.rotation = rotation;
		transform.linearVelocity = linearVelocity;
		transform.rotateVelocity = rotateVelocity;
	}

	/*
	void SetColor(color2 col)
	{
		c = col;
	}
	*/

	void SetPosition(float x,float y,float z)
	{
		EVec3f position = { x,y,z };
		transform.position = position;
	}

	/// <summary>
	/// rigidbody�̐ݒ�
	/// </summary>
	/// <param name="mass"></param>
	/// <param name="type">0�͕s���A1�Ȃ瓮��</param>
	void SetRigidbody(float mass,float e,int type)
	{
		rigidbody.mass = mass;
		rigidbody.e = e;
		rigidbody.type = type;
	}
	virtual void Draw() = 0;
	virtual bool IsHit(EVec3f& rayPos, EVec3f& rayDir) = 0;
	virtual ~PrimitiveObject() {
	}
};


/// <summary>
/// ���Ɋւ���N���X
/// </summary>
class Ball:public PrimitiveObject
{
private:
	const float M = 10; //����
	const int N = 50; //������
	const EVec3f firstPosition = {0,0,0};//���̂̒��S(�d�S�̈ʒu)
	const EVec3f firstRotation = {0,0,0};//�p��(���̏�Ԃ���̉�])
	const EVec3f firstLinearVelocity = {0,0,0};//�p��(���̏�Ԃ���̉�])
	const EVec3f firstRotateVelocity = {0,0,0};//�p��(���̏�Ԃ���̉�])
public:
	const float R = 0.57 / 2;
	Ball()
	{
		SetTransform(firstPosition,firstRotation,firstLinearVelocity,firstRotateVelocity);
		SetRigidbody(M,0.9,1);
		shapeType = 0;
		//SetColor(white);
	};

	bool IsHit(EVec3f& rayPos, EVec3f& rayDir)
	{
		float D = GetD(rayPos,rayDir);
		if (D >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	float GetD(EVec3f& rayPos, EVec3f& rayDir)
	{
		//���ʎ�
		//����ray��t�������ɂ��āA�����������݂��邩�ǂ���
		//rayDir�͑傫��1
		float D = powf(rayDir.dot(rayPos - transform.position), 2) - powf((rayPos - transform.position).norm(), 2) + powf(R, 2);
		return D;
	}

	float GetHitDist(EVec3f& rayPos, EVec3f& rayDir)
	{
		float t = -(rayDir.dot(rayPos - transform.position)) + powf(GetD(rayPos, rayDir),0.5f);
		return t;
	}

	void Draw() override
	{
		//�F
		glColor3f(1.000, 0.980, 0.980);
		glPushMatrix(); // ���݂̕ϊ��s���ۑ�
		{
			glTranslatef(transform.position[0], transform.position[1], transform.position[2]); // �d�S�̈ʒu�Ɉړ�
			/*//��]
			if (transform.rotation.norm() > 0.001) {
				EMat3f R;
				R = Eigen::AngleAxisf(transform.rotation.norm(),transform.rotation.normalized());
				float A[16];
				A[0] = R(0, 0); A[4] = R(0, 1); A[8] = R(0, 2); A[12] = 0;
				A[1] = R(1, 0); A[5] = R(1, 1); A[9] = R(1, 2); A[13] = 0;
				A[2] = R(2, 0); A[6] = R(2, 1); A[10] = R(2, 2); A[14] = 0;
				A[3] = 0; A[7] = 0; A[11] = 0; A[15] = 1;
				glMultMatrixf(A);
			}
			*/
		}
		glBegin(GL_TRIANGLES);
		for (int t = 0; t < N; t++)
		{
			for (int p = 0; p < N; p++)
			{
				float t1 = t / (float)N * 2 * 3.141592;
				float t2 = (t + 1) / (float)N * 2 * 3.141592;
				float p1 = (p / (float)N - 0.5f) * 3.141592;
				float p2 = ((p + 1) / (float)N - 0.5f) * 3.141592;
				glNormal3d(cos(p1) * cos(t1), cos(p1) * sin(t1), sin(p1));
				glVertex3d(R * cos(p1) * cos(t1), R * cos(p1) * sin(t1), R * sin(p1));
				glVertex3d(R * cos(p2) * cos(t1), R * cos(p2) * sin(t1), R * sin(p2));
				glVertex3d(R * cos(p2) * cos(t2), R * cos(p2) * sin(t2), R * sin(p2));
				glVertex3d(R * cos(p1) * cos(t1), R * cos(p1) * sin(t1), R * sin(p1));
				glVertex3d(R * cos(p1) * cos(t2), R * cos(p1) * sin(t2), R * sin(p1));
				glVertex3d(R * cos(p2) * cos(t2), R * cos(p2) * sin(t2), R * sin(p2));
			}
		}
		glEnd();
		glPopMatrix(); // �ϊ��s������ɖ߂�
	};
};

/// <summary>
/// �����̃N���X
/// </summary>
class Floor:public PrimitiveObject
{
	const float M = 2;
	const EVec3f firstPosition = { 0,0,0 };//���̂̒��S(�d�S�̈ʒu)
	const EVec3f firstRotation = { 0,0,0 };//�p��(���̏�Ԃ���̉�])
	const EVec3f firstLinearVelocity = { 0,0,0 };//�p��(���̏�Ԃ���̉�])
	const EVec3f firstRotateVelocity = { 0,0,0 };//�p��(���̏�Ԃ���̉�])
public:
	const float width;
	const float height;
	const float depth;
	Floor(float width,float height,float depth) : width(width), height(height), depth(depth)
	{
		SetTransform(firstPosition, firstRotation, firstLinearVelocity, firstRotateVelocity);
		SetRigidbody(M,0.9,0);
		shapeType = 1;
		//SetColor(brown);
	}
	bool IsHit(EVec3f& rayPos,EVec3f& rayDir) override
	{
		return false;
	}
	void Draw() override
	{
		glColor3f(0.180, 0.545, 0.341);
		glPushMatrix(); // ���݂̕ϊ��s���ۑ�
		{
			glTranslatef(transform.position[0], transform.position[1], transform.position[2]); // �d�S�̈ʒu�Ɉړ�
		}
		glEnable(GL_NORMALIZE);
		//����
		glBegin(GL_QUADS); //�l�p�`���쐬
		glNormal3f(0.0, -1.0, 0.0); //�@���x�N�g����ݒ�
		glVertex3f(-width / 2,- height/2, -depth / 2);
		glVertex3f(width / 2,- height/2, -depth / 2);
		glVertex3f(width / 2, -height/2, depth / 2);
		glVertex3f(-width / 2, -height/2, depth / 2);
		glEnd();
		//���
		glBegin(GL_QUADS);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width / 2, height/2, -depth / 2);
		glVertex3f(width / 2, height/2,-depth / 2);
		glVertex3f(width / 2, height/2, depth / 2);
		glVertex3f(-width / 2, height/2, depth / 2);
		glEnd();
		//�E
		glBegin(GL_QUADS);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(width / 2, -height/2, -depth / 2);
		glVertex3f(width / 2, -height/2, depth / 2);
		glVertex3f(width / 2, height/2, depth / 2);
		glVertex3f(width / 2, height/2, -depth / 2);
		glEnd();
		//��
		glBegin(GL_QUADS);
		glNormal3f(-1.0, 0.0, 0.0);
		glVertex3f(-width / 2, -height/2, -depth / 2);
		glVertex3f(-width / 2, -height/2, depth / 2);
		glVertex3f(-width / 2, height/2, depth / 2);
		glVertex3f(-width / 2, height/2, -depth / 2);
		glEnd();
		//����
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, -1.0);
		glVertex3f(-width / 2, -height/2, -depth / 2);
		glVertex3f(width / 2, -height/2, -depth / 2);
		glVertex3f(width / 2, height/2, -depth / 2);
		glVertex3f(-width / 2, height/2, -depth / 2);
		glEnd();
		//��
		glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(-width / 2, -height/2, depth / 2);
		glVertex3f(width / 2, -height/2, depth / 2);
		glVertex3f(width / 2, height/2, depth / 2);
		glVertex3f(-width / 2, height/2, depth / 2);
		glEnd();
		glDisable(GL_NORMALIZE);
		glPopMatrix();
	}
};