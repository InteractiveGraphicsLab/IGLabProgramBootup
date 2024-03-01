/*
�v���~�e�B�u��3D���f���Ɋւ���N���X���܂܂ꂽ�w�b�_�[�t�@�C��
*/
#include "OglForCLI.h"
#include "Transform.h"
#include "Rigidbody.h"

const float PI = 3.1415;

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
	void SetTransform(EVec3f position,EVec3f linearVelocity, EVec3f rotateVelocity)
	{
		transform.position = position;
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
	/// �����x�N�g��(x,y,z)����]���Ƃ��āA�p�xtheta������]
	/// </summary>
	/*
	void SetQuaternion(float x,float y,float z,float theta)
	{
		transform.quaternion[0] = x * sinf(theta / 2);
		transform.quaternion[0] = y * sinf(theta / 2);
		transform.quaternion[0] = z * sinf(theta / 2);
		transform.quaternion[0] = cosf(theta / 2);
	}
	*/

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
	const EVec3f firstEuler = EVec3f{0,0,0};//�p��(���̏�Ԃ���̉�])
	const EVec3f firstLinearVelocity = {0,0,0};//�p��(���̏�Ԃ���̉�])
	const EVec3f firstRotateVelocity = {0,0,0};//�p��(���̏�Ԃ���̉�])
public:
	const float R = 0.57 / 2;
	Ball()
	{
		SetTransform(firstPosition,firstLinearVelocity,firstRotateVelocity);
		SetRigidbody(M,0.9,1);
		transform.euler = firstEuler;
		shapeType = 0;
		rigidbody.moment = EMat3f({{M*R*R*2/5,0,0},{0,M * R * R * 2 / 5,0},{0,0,M * R * R * 2 / 5}});
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
			glRotatef(transform.euler[2], 0.0f, 0.0f, 1.0f); // Z������̉�]
			glRotatef(transform.euler[1], 0.0f, 1.0f, 0.0f); // Y������̉�]
			glRotatef(transform.euler[0], 1.0f, 0.0f, 0.0f); // X������̉�]
			//glTranslatef(transform.position[0], transform.position[1], transform.position[2]); // �d�S�̈ʒu�Ɉړ�
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
class Box:public PrimitiveObject
{
	const float M = 2;
	const EVec3f firstPosition = { 0,0,0 };//���̂̒��S(�d�S�̈ʒu)
	const EVec3f firstRotation = EVec3f{ 0,0,0};//�p��(���̏�Ԃ���̉�])
	const EVec3f firstLinearVelocity = { 0,0,0 };//�p��(���̏�Ԃ���̉�])
	const EVec3f firstRotateVelocity = { 0,0,0 };//�p��(���̏�Ԃ���̉�])
public:
	const float width;
	const float height;
	const float depth;
	Box(float width,float height,float depth) : width(width), height(height), depth(depth)
	{
		SetTransform(firstPosition,firstLinearVelocity, firstRotateVelocity);
		transform.euler = firstRotation;
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
			/*
			//glTranslatef(transform.position[0], transform.position[1], transform.position[2]); // �d�S�̈ʒu�Ɉړ�
			auto q0 = transform.quaternion[0];
			auto q1 = transform.quaternion[1];
			auto q2 = transform.quaternion[2];
			auto q3 = transform.quaternion[3];
			float R0 = q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3;
			auto R1 = 2 * (q1 * q2 + q0 * q3);
			auto R2 = 2 * (q1 * q3 - q0 * q2);
			auto R3 = 0;
			auto R4 = 2 * (q1 * q2 - q0 * q3);
			auto R5 = q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3;
			auto R6 = 2 * (q2 * q3 + q0 * q1);
			auto R7 = 0;
			auto R8 = 2 * (q1 * q3 + q0 * q2);
			auto R9 = 2 * (q2 * q3 - q0 * q1);
			auto R10 = q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3;
			auto R11 = 0;
			auto R12 = 0;
			auto R13 = 0;
			auto R14 = 0;
			auto R15 = 1;
			float m[16] =
			{
				R0,R1,R2,R3,R4,R5,R6,R7,R8,R9,R10,R11,R12,R13,R14,R15
			};
			glMultMatrixf(m);//���݂̍s��ɔC�ӂ̍s�����Z����A16�p����^����A���Ԃɒ���
			*/
			glTranslatef(transform.position[0], transform.position[1], transform.position[2]); // �d�S�̈ʒu�Ɉړ�
			glRotatef(transform.euler[2], 0.0f, 0.0f, 1.0f); // Z������̉�]
			glRotatef(transform.euler[1], 0.0f, 1.0f, 0.0f); // Y������̉�]
			glRotatef(transform.euler[0], 1.0f, 0.0f, 0.0f); // X������̉�]
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