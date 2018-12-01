#ifndef __ENEMY_PARAMS_H__
#define __ENEMY_PARAMS_H__

class EnemyParams{
public:
	//EnemyParams(int id);
	EnemyParams();
	int lifePoint;//��������ֵ
	int tag;//����Tag
	float createLocation[2];//���˳��ֵĳ�ʼλ������
	int enemyScore;//���˵���ķ���

	int textureName;//������ͼ�ļ����
	int frameActionNum;//֡����֡��

	float stayTime;//�м�ͣ��ʱ�䡣[0]�� bezierPointB[6]��bezierBTime��ֵ��Ч��

	float bezierPointA[6];//ȷ������������A��3��������
	float bezierATime;//����������A�켣�˶�ʱ��

	float bezierPointB[6];//ȷ������������B��3��������
	float bezierBTime;//����������B�켣�˶�ʱ��

	
};
#endif // __ENEMY_PARAMS_H__
