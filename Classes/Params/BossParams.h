#ifndef __BOSS_PARAMS_H__
#define __BOSS_PARAMS_H__

class BossParams{
public:
	//BossParams(int id);
	BossParams();
	int lifePoint;//Boss����ֵ
	int tag;//BossTag
	float createLocation[2];//���˳��ֵĳ�ʼλ������
	int bossScore;//���˵���ķ���

	int textureName;//������ͼ�ļ����
	int frameActionNum;//֡����֡��


};
#endif // __BOSS_PARAMS_H__
