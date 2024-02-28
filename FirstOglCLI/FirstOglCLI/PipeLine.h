#include "Transform.h"
#include "Rigidbody.h"
#ifndef __PipeLine__
#define __PipeLine__
class PipeLine
{
public:
	//��ɓ��������͂�����
	void Step()
	{
	}
	void AdaptForce(Transform& transform, Rigidbody& rigidbody, EVec3f& externalForce, EVec3f& externalTorque, float deltaTime)
	{
		if (rigidbody.type == 0)//�ړ����Ȃ����[�h�̏ꍇ�͑ł��؂�
			return;
		EVec3f accel = externalForce * (1 / rigidbody.mass);
		EMat3f inverseMoment = rigidbody.moment.inverse();
		EVec3f angleAccel = inverseMoment * externalTorque;
		transform.linearVelocity += deltaTime * accel;
		transform.rotateVelocity += angleAccel * deltaTime;
		//��]�̎���
		/*
		EVec3f angleAccel = EVec3f{ (0.57 / 2) * (0.57 / 2),(0.57 / 2) * (0.57 / 2),(0.57 / 2) * (0.57 / 2) } / (rigidbody.mass * (0.57/2) *(0.57/2));
		transform.rotateVelocity += angleAccel * deltaTime;
		*/

	}
	void DetectCollisions(std::vector<std::unique_ptr<PrimitiveObject>>& objects)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				CollisionCalc(objects[i],objects[j]);
			}
		}
	}

	void Integrate(std::vector<std::unique_ptr<PrimitiveObject>>& objects, float deltaTime) {
		for (auto& object : objects) {
			object->transform.position += object->transform.linearVelocity * deltaTime;
			//object->transform.rotation += object->transform.rotateVelocity * deltaTime;
		}
	}

	void CollisionCalc(std::unique_ptr<PrimitiveObject>& object1, std::unique_ptr<PrimitiveObject>& object2)
	{
		//���Ƌ��̓����蔻��
		if (object1->shapeType == 0 && object2->shapeType == 0)
		{
			auto x1 = object1->transform.position[0];
			auto y1 = object1->transform.position[1];
			auto z1 = object1->transform.position[2];
			auto x2 = object2->transform.position[0];
			auto y2 = object2->transform.position[1];
			auto z2 = object2->transform.position[2];
			//�_�E���L���X�g���Ď擾����
			auto ball1 = dynamic_cast<Ball*>(object1.get());
			auto ball2 = dynamic_cast<Ball*>(object2.get());
			auto r1 = ball1->R;
			auto r2 = ball2->R;
			auto distanceSquared = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
			// 2�̋��̔��a�̘a
			auto radiusSum = r1 + r2;
			// �����蔻��
			if (distanceSquared <= radiusSum * radiusSum) {//�Փ˂��Ă���Ȃ�
				//TODO�F��]���l������Ă��Ȃ�
				auto e = object1->rigidbody.e * object2->rigidbody.e;
				auto m1 = object1->rigidbody.mass;
				auto m2 = object2->rigidbody.mass;
				auto msum = m1 + m2;
				auto v1 = object1->transform.linearVelocity;
				auto v2 = object2->transform.linearVelocity;
				auto v1Next = v1 + m2 * (1 + e) * (v2 - v1) / msum;
				auto v2Next = v2 + m1 * (1 + e) * (v1 - v2) / msum;
				object1->transform.linearVelocity = v1Next;
				object2->transform.linearVelocity = v2Next;
			}
		}
		//���ƒ����̂̓����蔻��
		else if((object1->shapeType == 0 && object2->shapeType == 1)||(object1->shapeType == 1 && object2->shapeType == 0))
		{
			Ball* ball;
			Box* box;
			if (object1->shapeType == 0 && object2->shapeType == 1)
			{
				ball = dynamic_cast<Ball*>(object1.get());
				box = dynamic_cast<Box*>(object2.get());
			}
			else
			{
				ball = dynamic_cast<Ball*>(object2.get());
				box = dynamic_cast<Box*>(object1.get());
			}
			auto centerPos = ball->transform.position;
			auto R = ball->R;
			auto size = EVec3f{box->width,box->height,box->depth};
			auto box_position = box->transform.position;
			auto sqLength = 0.0;
			//AABB
			for (int i = 0; i < 3; i++) {
				auto point = centerPos[i];
				auto boxMin = box_position[i] - size[i]/2;
				auto boxMax = box_position[i] + size[i]/2;
				if (point < boxMin) {
					sqLength += (point - boxMin) * (point - boxMin);
				}
				if (point > boxMax) {
					sqLength += (point - boxMax) * (point - boxMax);
				}
			}
			//�����蔻��
			if (sqLength <= R * R){
				auto v = ball->transform.linearVelocity;
				ball->transform.linearVelocity *= -0.9;//�ړ������𔽓]�����邾��
			}
		}
	}
};
#endif