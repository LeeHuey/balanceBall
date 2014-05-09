//
//  BalanceBallScene.h
//  balanceBall
//
//  Created by leexu on 14-5-9.
//
//

#ifndef balanceBall_BalanceBallScene_h
#define balanceBall_BalanceBallScene_h

#include "cocos2d.h"

USING_NS_CC;

class BalanceBall : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void onEnter();
    
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(BalanceBall);
    
protected:
    CCSprite* m_pBall;
    double m_fLastTime;
    
    
};


#endif
