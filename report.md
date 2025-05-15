# 新增功能
## 反方向判断
原游戏中只要输入和当前运动方向相反的方向就会导致游戏结束。


## 移除不必要的变量和参数
- update(delta)


## 修改
- snake
    传入窗口
    处理鼠标
    新增dir变量
    offset snake
    单位长度

    float offset_x_;
	float offset_y_;

    允许蛇头穿过自身

    删除不必要的变量
- snake node


game
存储多个screen


game_screen:
- state: pause


context结构，保存上下文

游戏画面的切换应该由game来切换


实时存储得分

- 重写hitSelf碰撞判断，避免过于敏感。
