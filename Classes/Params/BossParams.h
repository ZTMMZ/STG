#ifndef __BOSS_PARAMS_H__
#define __BOSS_PARAMS_H__

class BossParams{
public:
	//BossParams(int id);
	BossParams();
	int lifePoint;//Boss生命值
	int tag;//BossTag
	float createLocation[2];//敌人出现的初始位置坐标
	int bossScore;//敌人掉落的分数

	int textureName;//敌人贴图文件编号
	int frameActionNum;//帧动画帧数


};
#endif // __BOSS_PARAMS_H__
