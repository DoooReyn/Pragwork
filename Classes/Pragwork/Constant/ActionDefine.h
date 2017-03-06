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
    FadeAwayBaseFrame,  //淡出
    FadeInBaseFrame,    //淡入
    OpacityInAction,    //渐现
    OpacityOutAction,   //渐隐
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
        case ActionCode::FadeAwayBaseFrame : {
            FadeOut     *a1 = FadeOut::create(.5f);
            Hide        *a2 = Hide::create();
            Sequence    *sq = Sequence::create(a1, a2, NULL);
            sq->setTag(ActionCode::FadeAwayBaseFrame);
            return sq;
        }
        case ActionCode::FadeInBaseFrame : {
            FadeIn      *a1 = FadeIn::create(.5f);
            Show        *a2 = Show::create();
            Sequence    *sq = Sequence::create(a1, a2, NULL);
            sq->setTag(ActionCode::FadeInBaseFrame);
            return sq;
        }
        case ActionCode::OpacityInAction : {
            FadeTo      *a1 = FadeTo::create(.3, 255);
            Sequence    *sq = Sequence::create(a1, NULL);
            sq->setTag(ActionCode::OpacityInAction);
            return sq;
        }
        case ActionCode::OpacityOutAction : {
            FadeTo      *a1 = FadeTo::create(.3f, 0);
            Sequence    *sq = Sequence::create(a1, NULL);
            sq->setTag(ActionCode::OpacityOutAction);
            return sq;
        }
        default:
            return NULL;
    }
}

#endif /* ActionDefine_h */
