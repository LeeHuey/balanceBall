//
//  BalanceBallScene.cpp
//  balanceBall
//
//  Created by leexu on 14-5-9.
//
//

#include "BalanceBallScene.h"

#define FIX_POS(_pos, _min, _max) \
if (_pos < _min)        \
_pos = _min;        \
else if (_pos > _max)   \
_pos = _max;        \

USING_NS_CC;

CCScene* BalanceBall::scene()
{
    CCScene *scene = NULL;
    do
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        BalanceBall *layer = BalanceBall::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BalanceBall::init()
{
    bool bRet = false;
    do
    {
        //////////////////////////////
        // 1. super init first
        CC_BREAK_IF(! CCLayer::init());

        
        
        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        
        // add a "close" icon to exit the progress. it's an autorelease object
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(BalanceBall::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                    origin.y + pCloseItem->getContentSize().height/2));
        
        // create menu, it's an autorelease object
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        
        this->addChild(pMenu, 1);
        
        /////////////////////////////
        // 3. add your codes below...
        //a.设置背景
        // add "background" picture
        CCSprite* pSprite = CCSprite::create("bg.jpg");
        
        // position the sprite on the center of the screen
        pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        
        // add the sprite as a child to this layer
        this->addChild(pSprite, 0);
        
        //b.添加小丑
        CCSprite* pHeadLeft = CCSprite::create("head_left.png");
        pHeadLeft->setPosition(ccp(origin.x + pHeadLeft->getContentSize().width/2, origin.y + visibleSize.height - pHeadLeft->getContentSize().height/2));
        this->addChild(pHeadLeft);
        
        CCSprite* pHeadRight = CCSprite::create("head_right.png");
        pHeadRight->setPosition(ccp(origin.x + visibleSize.width - pHeadRight->getContentSize().width/2, origin.y + visibleSize.height - pHeadRight->getContentSize().height/2));
        this->addChild(pHeadRight);
        
        //c. add ball
        m_pBall = CCSprite::create("ball.png");
        m_pBall->setPosition(ccp(visibleSize.width/2, visibleSize.height + m_pBall->getContentSize().height/2));
        this->addChild(m_pBall);
        
        bRet = true;
    }while (0);
    
    return bRet;
}

void BalanceBall::onEnter()
{
    CCLayer::onEnter();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCActionInterval* actionTo = CCJumpTo::create(0.5, CCPointMake(visibleSize.width/2, 223), 50, 0);
    m_pBall->runAction(actionTo);
    
    setAccelerometerEnabled(true);
}

void BalanceBall::didAccelerate(CCAcceleration* pAccelerationValue)
{
    CCSize ballSize = m_pBall->getContentSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCPoint ptNow = m_pBall->getPosition();
    
    CCPoint ptTemp = CCDirector::sharedDirector()->convertToUI(ptNow);
    
    ptTemp.x += pAccelerationValue->x * 9.81f;
    
    CCPoint ptNext = CCDirector::sharedDirector()->convertToGL(ptTemp);
    FIX_POS(ptNext.x,(ballSize.width / 2.0), (visibleSize.width - ballSize.width / 2.0));
    FIX_POS(ptNext.y,(ballSize.height / 2.0), (visibleSize.height - ballSize.height / 2.0));
    m_pBall->setPosition(ptNext);
}

void BalanceBall::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
