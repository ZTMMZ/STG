#ifndef __ENEMY_PARAMS_H__
#define __ENEMY_PARAMS_H__

class EnemyParams{
public:
	//EnemyParams(int id);
	EnemyParams();
	int lifePoint;//敌人生命值
	int tag;//敌人Tag
	float createLocation[2];//敌人出现的初始位置坐标
	int enemyScore;//敌人掉落的分数

	int textureName;//敌人贴图文件编号
	int frameActionNum;//帧动画帧数

	float stayTime;//中间停留时间。[0]： bezierPointB[6]、bezierBTime的值无效化

	float bezierPointA[6];//确定贝塞尔曲线A的3个点坐标
	float bezierATime;//贝塞尔曲线A轨迹运动时间

	float bezierPointB[6];//确定贝塞尔曲线B的3个点坐标
	float bezierBTime;//贝塞尔曲线B轨迹运动时间

	
};
#endif // __ENEMY_PARAMS_H__
