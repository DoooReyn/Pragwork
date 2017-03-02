//
//  ActionDefine.h
//  Pragwork
//
//  Created by Reyn-Mac on 2017/2/27.
//
//

#ifndef ActionDefine_h
#define ActionDefine_h

USING_NS_CC;

//动画编号
enum ActionCode : unsigned int {
    None,               //无
    EnterBaseFrame,     //BaseFrame 进入
    ExitBaseFrame,      //BaseFrame 退出
};

//根据动画变化获得对应动画
static Action* getActionByCode(ActionCode code) {
    switch (code) {
        case ActionCode::EnterBaseFrame : {
            ScaleTo     *a1 = ScaleTo::create(.3f, 1.12f);
            DelayTime   *a2 = DelayTime::create(.05f);
            ScaleTo     *a3 = ScaleTo::create(.1f, 1.f);
            Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
            sq->setTag(ActionCode::EnterBaseFrame);
            return sq;
        }
        case ActionCode::ExitBaseFrame : {
            ScaleTo     *a1 = ScaleTo::create(.1f, 1.12f);
            DelayTime   *a2 = DelayTime::create(.05f);
            ScaleTo     *a3 = ScaleTo::create(.3f, .5f);
            RemoveSelf  *a4 = RemoveSelf::create();
            Sequence    *sq = Sequence::create(a1, a2, a3, a4, NULL);
            sq->setTag(ActionCode::ExitBaseFrame);
            return sq;
        }
        default:
            return NULL;
    }
}

#endif /* ActionDefine_h */
