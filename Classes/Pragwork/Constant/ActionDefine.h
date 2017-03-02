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

enum class ActionCode : unsigned int {
    None,
    EnterBaseFrame,
    ExitBaseFrame,
};

static Action* getActionByCode(ActionCode code) {
    switch (code) {
        case ActionCode::EnterBaseFrame : {
            ScaleTo     *a1 = ScaleTo::create(.3f, 1.12f);
            DelayTime   *a2 = DelayTime::create(.05f);
            ScaleTo     *a3 = ScaleTo::create(.1f, 1.f);
            Sequence    *sq = Sequence::create(a1, a2, a3, NULL);
            sq->setTag(ActionTag::EnterBaseFrame);
            return sq;
        }
        case ActionCode::ExitBaseFrame : {
            ScaleTo     *a1 = ScaleTo::create(.1f, 1.12f);
            DelayTime   *a2 = DelayTime::create(.05f);
            ScaleTo     *a3 = ScaleTo::create(.3f, .5f);
            RemoveSelf  *a4 = RemoveSelf::create();
            Sequence    *sq = Sequence::create(a1, a2, a3, a4, NULL);
            sq->setTag(ActionTag::ExitBaseFrame);
            return sq;
        }
        default:
            return NULL;
    }
}

#endif /* ActionDefine_h */
