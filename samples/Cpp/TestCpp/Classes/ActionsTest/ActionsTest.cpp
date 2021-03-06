#include "ActionsTest.h"
#include "../testResource.h"
#include "cocos2d.h"

static std::function<Layer*()> createFunctions[] = {

    CL(ActionManual),
    CL(ActionMove),
    CL(ActionRotate),
    CL(ActionScale),
    CL(ActionSkew),
    CL(ActionRotationalSkew),
    CL(ActionRotationalSkewVSStandardSkew),
    CL(ActionSkewRotateScale),
    CL(ActionJump),
    CL(ActionCardinalSpline),
    CL(ActionCatmullRom),
    CL(ActionBezier),
    CL(ActionBlink),
    CL(ActionFade),
    CL(ActionTint),
    CL(ActionAnimate),
    CL(ActionSequence),
    CL(ActionSequence2),
	CL(ActionRemoveSelf),
    CL(ActionSpawn),
    CL(ActionReverse),
    CL(ActionDelayTime),
    CL(ActionRepeat),
    CL(ActionRepeatForever),
    CL(ActionRotateToRepeat),
    CL(ActionRotateJerk),
    CL(ActionCallFunction),
    CL(ActionCallFuncN),
    CL(ActionCallFuncND),
    CL(ActionCallFuncO),
    CL(ActionReverseSequence),
    CL(ActionReverseSequence2),
    CL(ActionOrbit),
    CL(ActionFollow),
    CL(ActionTargeted),
    CL(ActionMoveStacked),
    CL(ActionMoveJumpStacked),
    CL(ActionMoveBezierStacked),
    CL(ActionCardinalSplineStacked),
    CL(ActionCatmullRomStacked),
    CL(PauseResumeActions),
    CL(Issue1305),
    CL(Issue1305_2),
    CL(Issue1288),
    CL(Issue1288_2),
    CL(Issue1327),
    CL(Issue1398)
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
    pLayer->init();
    pLayer->autorelease();
    
    return pLayer;
}

void ActionsTestScene::runThisTest()
{
    sceneIdx = -1;
    addChild(nextAction());

    Director::getInstance()->replaceScene(this);
}


std::string ActionsDemo::title()
{
    return "ActionsTest";
}

std::string ActionsDemo::subtitle()
{
    return "";
}

void ActionsDemo::onEnter()
{
    BaseTest::onEnter();

    // Or you can create an sprite using a filename. only PNG is supported now. Probably TIFF too
    _grossini = Sprite::create(s_pPathGrossini);
    _grossini->retain();

    _tamara = Sprite::create(s_pPathSister1); 
    _tamara->retain();

    _kathia = Sprite::create(s_pPathSister2);
    _kathia->retain();

    addChild(_grossini, 1);
    addChild(_tamara, 2);
    addChild(_kathia, 3);

    _grossini->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/3));
    _tamara->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height*2/3));
    _kathia->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+VisibleRect::getVisibleRect().size.height/2)); 
}

void ActionsDemo::onExit()
{
    _grossini->release();
    _tamara->release();
    _kathia->release();

    BaseTest::onExit();
}

void ActionsDemo::restartCallback(Object* pSender)
{
    Scene* s = new ActionsTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionsDemo::nextCallback(Object* pSender)
{
    Scene* s = new ActionsTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionsDemo::backCallback(Object* pSender)
{
    Scene* s = new ActionsTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void ActionsDemo::centerSprites(unsigned int numberOfSprites)
{
    auto s = Director::getInstance()->getWinSize();

    if( numberOfSprites == 0 )
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setVisible(false);
    } 
    else if ( numberOfSprites == 1 ) 
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setPosition(Point(s.width/2, s.height/2));
    }
    else if( numberOfSprites == 2 ) 
    {        
        _kathia->setPosition( Point(s.width/3, s.height/2));
        _tamara->setPosition( Point(2*s.width/3, s.height/2));
        _grossini->setVisible(false);
    } 
    else if( numberOfSprites == 3 ) 
    {
        _grossini->setPosition( Point(s.width/2, s.height/2));
        _tamara->setPosition( Point(s.width/4, s.height/2));
        _kathia->setPosition( Point(3 * s.width/4, s.height/2));
    }
}

void ActionsDemo::alignSpritesLeft(unsigned int numberOfSprites)
{
    auto s = Director::getInstance()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        _tamara->setVisible(false);
        _kathia->setVisible(false);
        _grossini->setPosition(Point(60, s.height/2));
    } 
    else if( numberOfSprites == 2 ) 
    {        
        _kathia->setPosition( Point(60, s.height/3));
        _tamara->setPosition( Point(60, 2*s.height/3));
        _grossini->setVisible( false );
    } 
    else if( numberOfSprites == 3 ) 
    {
        _grossini->setPosition( Point(60, s.height/2));
        _tamara->setPosition( Point(60, 2*s.height/3));
        _kathia->setPosition( Point(60, s.height/3));
    }
}

//------------------------------------------------------------------
//
// ActionManual
//
//------------------------------------------------------------------
void ActionManual::onEnter()
{
    ActionsDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    _tamara->setScaleX( 2.5f);
    _tamara->setScaleY( -1.0f);
    _tamara->setPosition( Point(100,70) );
    _tamara->setOpacity( 128);

    _grossini->setRotation( 120);
    _grossini->setPosition( Point(s.width/2, s.height/2));
    _grossini->setColor( Color3B( 255,0,0));

    _kathia->setPosition( Point(s.width-100, s.height/2));
    _kathia->setColor( Color3B::BLUE);
}

std::string ActionManual::subtitle()
{
    return "Manual Transformation";
}

//------------------------------------------------------------------
//
//    ActionMove
//
//------------------------------------------------------------------
void ActionMove::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto s = Director::getInstance()->getWinSize();

    auto actionTo = MoveTo::create(2, Point(s.width-40, s.height-40));
    auto actionBy = MoveBy::create(2, Point(80,80));
    auto actionByBack = actionBy->reverse();

    _tamara->runAction( actionTo);
    _grossini->runAction( Sequence::create(actionBy, actionByBack, NULL));
    _kathia->runAction(MoveTo::create(1, Point(40,40)));
}

std::string ActionMove::subtitle()
{
    return "MoveTo / MoveBy";
}

//------------------------------------------------------------------
//
// ActionScale
//
//------------------------------------------------------------------
void ActionScale::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = ScaleTo::create(2.0f, 0.5f);
    auto actionBy = ScaleBy::create(2.0f, 1.0f, 10.0f);
    auto actionBy2 = ScaleBy::create(2.0f, 5.0f, 1.0f);

    _grossini->runAction( actionTo);
    _tamara->runAction( Sequence::create(actionBy, actionBy->reverse(), NULL));
    _kathia->runAction( Sequence::create(actionBy2, actionBy2->reverse(), NULL));
}

std::string ActionScale::subtitle()
{
    return "ScaleTo / ScaleBy";
}

//------------------------------------------------------------------
//
//    ActionSkew
//
//------------------------------------------------------------------
void ActionSkew::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = SkewTo::create(2, 37.2f, -37.2f);
    auto actionToBack = SkewTo::create(2, 0, 0);
    auto actionBy = SkewBy::create(2, 0.0f, -90.0f);
    auto actionBy2 = SkewBy::create(2, 45.0f, 45.0f);
    auto actionByBack = actionBy->reverse();

    _tamara->runAction(Sequence::create(actionTo, actionToBack, NULL));
    _grossini->runAction(Sequence::create(actionBy, actionByBack, NULL));

    _kathia->runAction(Sequence::create(actionBy2, actionBy2->reverse(), NULL));
}

string ActionSkew::subtitle()
{
    return "SkewTo / SkewBy";
}

// ActionRotationalSkew
void ActionRotationalSkew::onEnter()
{
    ActionsDemo::onEnter();

    this->centerSprites(3);

    auto actionTo = RotateTo::create(2, 37.2f, -37.2f);
    auto actionToBack = RotateTo::create(2, 0, 0);
    auto actionBy = RotateBy::create(2, 0.0f, -90.0f);
    auto actionBy2 = RotateBy::create(2, 45.0f, 45.0f);
    auto actionByBack = actionBy->reverse();

    _tamara->runAction( Sequence::create(actionTo, actionToBack, NULL) );
    _grossini->runAction( Sequence::create(actionBy, actionByBack, NULL) );

    _kathia->runAction( Sequence::create(actionBy2, actionBy2->reverse(), NULL) );
}

std::string ActionRotationalSkew::subtitle()
{
    return "RotationalSkewTo / RotationalSkewBy";
}



//ActionRotationalSkewVSStandardSkew
void ActionRotationalSkewVSStandardSkew::onEnter()
{
    ActionsDemo::onEnter();

    _tamara->removeFromParentAndCleanup(true);
    _grossini->removeFromParentAndCleanup(true);
    _kathia->removeFromParentAndCleanup(true);

    auto s = Director::getInstance()->getWinSize();

    Size boxSize(100.0f, 100.0f);

    auto box = LayerColor::create(Color4B(255,255,0,255));
    box->setAnchorPoint(Point(0.5,0.5));
    box->setContentSize( boxSize );
    box->ignoreAnchorPointForPosition(false);
    box->setPosition(Point(s.width/2, s.height - 100 - box->getContentSize().height/2));
    this->addChild(box);

    auto label = LabelTTF::create("Standard cocos2d Skew", "Marker Felt", 16);
    label->setPosition(Point(s.width/2, s.height - 100 + label->getContentSize().height));
    this->addChild(label);

    auto actionTo = SkewBy::create(2, 360, 0);
    auto actionToBack = SkewBy::create(2, -360, 0);

    box->runAction(Sequence::create(actionTo, actionToBack, NULL));

    box = LayerColor::create(Color4B(255,255,0,255));
    box->setAnchorPoint(Point(0.5,0.5));
    box->setContentSize(boxSize);
    box->ignoreAnchorPointForPosition(false);
    box->setPosition(Point(s.width/2, s.height - 250 - box->getContentSize().height/2));
    this->addChild(box);

    label = LabelTTF::create("Rotational Skew", "Marker Felt", 16);
    label->setPosition(Point(s.width/2, s.height - 250 + label->getContentSize().height/2));
    this->addChild(label);
    auto actionTo2 = RotateBy::create(2, 360, 0);
    auto actionToBack2 = RotateBy::create(2, -360, 0);
    box->runAction(Sequence::create(actionTo2, actionToBack2, NULL));
}
std::string ActionRotationalSkewVSStandardSkew::subtitle()
{
    return "Skew Comparison";
}

// ActionSkewRotateScale
void ActionSkewRotateScale::onEnter()
{
    ActionsDemo::onEnter();

    _tamara->removeFromParentAndCleanup(true);
    _grossini->removeFromParentAndCleanup(true);
    _kathia->removeFromParentAndCleanup(true);

    Size boxSize(100.0f, 100.0f);

    auto box = LayerColor::create(Color4B(255, 255, 0, 255));
    box->setAnchorPoint(Point(0, 0));
    box->setPosition(Point(190, 110));
    box->setContentSize(boxSize);

    static float markrside = 10.0f;
    auto uL = LayerColor::create(Color4B(255, 0, 0, 255));
    box->addChild(uL);
    uL->setContentSize(Size(markrside, markrside));
    uL->setPosition(Point(0.f, boxSize.height - markrside));
    uL->setAnchorPoint(Point(0, 0));

    auto uR = LayerColor::create(Color4B(0, 0, 255, 255));
    box->addChild(uR);
    uR->setContentSize(Size(markrside, markrside));
    uR->setPosition(Point(boxSize.width - markrside, boxSize.height - markrside));
    uR->setAnchorPoint(Point(0, 0));
    addChild(box);

    auto actionTo = SkewTo::create(2, 0.f, 2.f);
    auto rotateTo = RotateTo::create(2, 61.0f);
    auto actionScaleTo = ScaleTo::create(2, -0.44f, 0.47f);

    auto actionScaleToBack = ScaleTo::create(2, 1.0f, 1.0f);
    auto rotateToBack = RotateTo::create(2, 0);
    auto actionToBack = SkewTo::create(2, 0, 0);

    box->runAction(Sequence::create(actionTo, actionToBack, NULL));
    box->runAction(Sequence::create(rotateTo, rotateToBack, NULL));
    box->runAction(Sequence::create(actionScaleTo, actionScaleToBack, NULL));
}

string ActionSkewRotateScale::subtitle()
{
    return "Skew + Rotate + Scale";
}

//------------------------------------------------------------------
//
//    ActionRotate
//
//------------------------------------------------------------------
void ActionRotate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = RotateTo::create( 2, 45);
    auto actionTo2 = RotateTo::create( 2, -45);
    auto actionTo0 = RotateTo::create(2 , 0);
    _tamara->runAction( Sequence::create(actionTo, actionTo0, NULL));

    auto actionBy = RotateBy::create(2 ,  360);
    auto actionByBack = actionBy->reverse();
    _grossini->runAction( Sequence::create(actionBy, actionByBack, NULL));

    _kathia->runAction( Sequence::create(actionTo2, actionTo0->clone(), NULL));
}

std::string ActionRotate::subtitle()
{
    return "RotateTo / RotateBy";
}

//------------------------------------------------------------------
//
// ActionJump
//
//------------------------------------------------------------------
void ActionJump::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto actionTo = JumpTo::create(2, Point(300,300), 50, 4);
    auto actionBy = JumpBy::create(2, Point(300,0), 50, 4);
    auto actionUp = JumpBy::create(2, Point(0,0), 80, 4);
    auto actionByBack = actionBy->reverse();

    _tamara->runAction( actionTo);
    _grossini->runAction( Sequence::create(actionBy, actionByBack, NULL));
    _kathia->runAction( RepeatForever::create(actionUp));
}
std::string ActionJump::subtitle()
{
    return "JumpTo / JumpBy";
}

//------------------------------------------------------------------
//
// ActionBezier
//
//------------------------------------------------------------------
void ActionBezier::onEnter()
{
    ActionsDemo::onEnter();

    auto s = Director::getInstance()->getWinSize();

    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Bezier curve, make it (0,0)
    //

    centerSprites(3);

    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(0, s.height/2);
    bezier.controlPoint_2 = Point(300, -s.height/2);
    bezier.endPosition = Point(300,100);

    auto bezierForward = BezierBy::create(3, bezier);
    auto bezierBack = bezierForward->reverse();
    auto rep = RepeatForever::create(Sequence::create( bezierForward, bezierBack, NULL));


    // sprite 2
    _tamara->setPosition(Point(80,160));
	ccBezierConfig bezier2;
    bezier2.controlPoint_1 = Point(100, s.height/2);
    bezier2.controlPoint_2 = Point(200, -s.height/2);
    bezier2.endPosition = Point(240,160);

    auto bezierTo1 = BezierTo::create(2, bezier2);    

    // sprite 3
    _kathia->setPosition(Point(400,160));
    auto bezierTo2 = BezierTo::create(2, bezier2);

    _grossini->runAction( rep);
    _tamara->runAction(bezierTo1);
    _kathia->runAction(bezierTo2);

}

std::string ActionBezier::subtitle()
{
    return "BezierBy / BezierTo";
}

//------------------------------------------------------------------
//
// ActionBlink
//
//------------------------------------------------------------------
void ActionBlink::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    auto action1 = Blink::create(2, 10);
    auto action2 = Blink::create(2, 5);

    _tamara->runAction( action1);
    _kathia->runAction(action2);
}

std::string  ActionBlink::subtitle()
{
    return "Blink";
}

//------------------------------------------------------------------
//
// ActionFade
//
//------------------------------------------------------------------
void ActionFade::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    _tamara->setOpacity( 0 );
    auto action1 = FadeIn::create(1.0f);
    auto action1Back = action1->reverse();

    auto action2 = FadeOut::create(1.0f);
    auto action2Back = action2->reverse();

    _tamara->runAction( Sequence::create( action1, action1Back, NULL));
    _kathia->runAction( Sequence::create( action2, action2Back, NULL));
}

std::string  ActionFade::subtitle()
{
    return "FadeIn / FadeOut";
}

//------------------------------------------------------------------
//
// ActionTint
//
//------------------------------------------------------------------

void ActionTint::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

    auto action1 = TintTo::create(2, 255, 0, 255);
    auto action2 = TintBy::create(2, -127, -255, -127);
    auto action2Back = action2->reverse();

    _tamara->runAction( action1);
    _kathia->runAction( Sequence::create( action2, action2Back, NULL));
}

std::string  ActionTint::subtitle()
{
    return "TintTo / TintBy";
}

//------------------------------------------------------------------
//
// ActionAnimate
//
//------------------------------------------------------------------
void ActionAnimate::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    //
    // Manual animation
    //
    Animation* animation = Animation::create();
    for( int i=1;i<15;i++)
    {
        char szName[100] = {0};
        sprintf(szName, "Images/grossini_dance_%02d.png", i);
        animation->addSpriteFrameWithFileName(szName);
    }
    // should last 2.8 seconds. And there are 14 frames.
    animation->setDelayPerUnit(2.8f / 14.0f);
    animation->setRestoreOriginalFrame(true);

    Animate* action = Animate::create(animation);
    _grossini->runAction(Sequence::create(action, action->reverse(), NULL));
    
    //
    // File animation
    //
    // With 2 loops and reverse
    AnimationCache *cache = AnimationCache::getInstance();
    cache->addAnimationsWithFile("animations/animations-2.plist");
    Animation *animation2 = cache->animationByName("dance_1");

    Animate* action2 = Animate::create(animation2);
    _tamara->runAction(Sequence::create(action2, action2->reverse(), NULL));

// TODO:
//     observer_ = [[NSNotificationCenter defaultCenter] addObserverForName:AnimationFrameDisplayedNotification object:nil queue:nil usingBlock:^(NSNotification* notification) {
// 
//         NSDictionary *userInfo = [notification userInfo);
//         NSLog(@"object %@ with data %@", [notification object), userInfo );
//     });


    //
    // File animation
    //
    // with 4 loops
    Animation *animation3 = animation2->clone();
    animation3->setLoops(4);


    Animate* action3 = Animate::create(animation3);
    _kathia->runAction(action3);
}

void ActionAnimate::onExit()
{
    ActionsDemo::onExit();
    //TODO:[[NSNotificationCenter defaultCenter] removeObserver:observer_);
}

std::string ActionAnimate::title()
{
    return "Animation";
}

std::string ActionAnimate::subtitle()
{
    return "Center: Manual animation. Border: using file format animation";
}

//------------------------------------------------------------------
//
//    ActionSequence
//
//------------------------------------------------------------------
void ActionSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto action = Sequence::create(
        MoveBy::create( 2, Point(240,0)),
        RotateBy::create( 2,  540),
        NULL);

    _grossini->runAction(action);
}

std::string ActionSequence::subtitle()
{
    return "Sequence: Move + Rotate";
}

//------------------------------------------------------------------
//
//    ActionSequence2
//
//------------------------------------------------------------------
void ActionSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    _grossini->setVisible(false);

    auto action = Sequence::create(
		Place::create(Point(200,200)),
		Show::create(),
		MoveBy::create(1, Point(100,0)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback1,this)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback2,this,_grossini)),
		CallFunc::create( CC_CALLBACK_0(ActionSequence2::callback3,this,_grossini,0xbebabeba)),
		NULL);

    _grossini->runAction(action);
}

void ActionSequence2::callback1()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 1 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionSequence2::callback2(Node* sender)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 2 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*2,s.height/2));

    addChild(label);
}

void ActionSequence2::callback3(Node* sender, long data)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 3 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*3,s.height/2));

    addChild(label);
}

std::string ActionSequence2::subtitle()
{
    return "Sequence of InstantActions";
}

//------------------------------------------------------------------
//
// ActionCallFuncN
//
//------------------------------------------------------------------
void ActionCallFuncN::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        MoveBy::create(2.0f, Point(150,0)),
        CallFuncN::create( CC_CALLBACK_1(ActionCallFuncN::callback, this)),
        NULL);

    _grossini->runAction(action);
}

std::string ActionCallFuncN::title()
{
    return "CallFuncN";
}

std::string ActionCallFuncN::subtitle()
{
    return "Grossini should jump after moving";
}

void ActionCallFuncN::callback(Node* sender )
{
    auto a = JumpBy::create(5, Point(0,0), 100, 5);
    sender->runAction(a);
}
//------------------------------------------------------------------
//
// ActionCallFuncND
// CallFuncND is no longer needed. It can simulated with std::bind()
//
//------------------------------------------------------------------
void ActionCallFuncND::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        MoveBy::create(2.0f, Point(200,0)),
        CallFuncN::create( CC_CALLBACK_1(ActionCallFuncND::doRemoveFromParentAndCleanup, this, true)),
        NULL);

    _grossini->runAction(action);
}

std::string ActionCallFuncND::title()
{
    return "CallFuncND + auto remove";
}

std::string ActionCallFuncND::subtitle()
{
    return "simulates CallFuncND with std::bind()";
}

void ActionCallFuncND::doRemoveFromParentAndCleanup(Node* pSender, bool cleanup)
{
    _grossini->removeFromParentAndCleanup(cleanup);
}

//------------------------------------------------------------------
//
// ActionCallFuncO
// CallFuncO is no longer needed. It can simulated with std::bind()
//
//------------------------------------------------------------------
void ActionCallFuncO::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        MoveBy::create(2.0f, Point(200,0)),
        CallFunc::create( CC_CALLBACK_0(ActionCallFuncO::callback, this, _grossini, true)),
        NULL);
    _grossini->runAction(action);
}

std::string ActionCallFuncO::title()
{
    return "CallFuncO + autoremove";
}

std::string ActionCallFuncO::subtitle()
{
    return "simulates CallFuncO with std::bind()";
}

void ActionCallFuncO::callback(Node* node, bool cleanup)
{
    node->removeFromParentAndCleanup(cleanup);
}

//------------------------------------------------------------------
//
//    ActionCallFunction
//
//------------------------------------------------------------------
void ActionCallFunction::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);


	auto action1 = Sequence::create(
                        MoveBy::create(2, Point(200,0)),
                        CallFunc::create( std::bind(&ActionCallFunction::callback1, this) ),
                        CallFunc::create(
                             // lambda
                             [&](){
                                 auto s = Director::getInstance()->getWinSize();
                                 auto label = LabelTTF::create("called:lambda callback", "Marker Felt", 16);
                                 label->setPosition(Point( s.width/4*1,s.height/2-40));
                                 this->addChild(label);
                             }  ),
                        NULL);

    auto action2 = Sequence::create(
                        ScaleBy::create(2 ,  2),
                        FadeOut::create(2),
                        CallFunc::create( std::bind(&ActionCallFunction::callback2, this, _tamara) ),
                        NULL);

    auto action3 = Sequence::create(
                        RotateBy::create(3 , 360),
                        FadeOut::create(2),
                        CallFunc::create( std::bind(&ActionCallFunction::callback3, this, _kathia, 42) ),
                        NULL);

    _grossini->runAction(action1);
    _tamara->runAction(action2);
    _kathia->runAction(action3);
}


void ActionCallFunction::callback1()
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 1 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*1,s.height/2));

    addChild(label);
}

void ActionCallFunction::callback2(Node* sender)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 2 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*2,s.height/2));

    addChild(label);

	CCLOG("sender is: %p", sender);
}

void ActionCallFunction::callback3(Node* sender, long data)
{
    auto s = Director::getInstance()->getWinSize();
    auto label = LabelTTF::create("callback 3 called", "Marker Felt", 16);
    label->setPosition(Point( s.width/4*3,s.height/2));
    addChild(label);

	CCLOG("target is: %p, data is: %ld", sender, data);
}

std::string ActionCallFunction::subtitle()
{
    return "Callbacks: CallFunc with std::function()";
}
//------------------------------------------------------------------
//
// ActionSpawn
//
//------------------------------------------------------------------

void ActionSpawn::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto action = Spawn::create(
        JumpBy::create(2, Point(300,0), 50, 4),
        RotateBy::create( 2,  720),
        NULL);

    _grossini->runAction(action);
}

std::string ActionSpawn::subtitle()
{
    return "Spawn: Jump + Rotate";
}


//------------------------------------------------------------------
//
// ActionRepeatForever
//
//------------------------------------------------------------------
void ActionRepeatForever::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);

    auto action = Sequence::create(
        DelayTime::create(1),
        CallFunc::create( std::bind( &ActionRepeatForever::repeatForever, this, _grossini) ),
        NULL);

    _grossini->runAction(action);
}

void ActionRepeatForever::repeatForever(Node* pSender)
{
    auto repeat = RepeatForever::create( RotateBy::create(1.0f, 360) );

    pSender->runAction(repeat);
}

std::string ActionRepeatForever::subtitle()
{
    return "CallFuncN + RepeatForever";
}


//------------------------------------------------------------------
//
// ActionRotateToRepeat
//
//------------------------------------------------------------------
void ActionRotateToRepeat::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

	auto act1 = RotateTo::create(1, 90);
	auto act2 = RotateTo::create(1, 0);
	auto seq = Sequence::create(act1, act2, NULL);
	auto rep1 = RepeatForever::create(seq);
	auto rep2 = Repeat::create( seq->clone(), 10);

    _tamara->runAction(rep1);
    _kathia->runAction(rep2);
}

std::string ActionRotateToRepeat ::subtitle()
{
    return "Repeat/RepeatForever + RotateTo";
}


//------------------------------------------------------------------
//
// ActionRotateJerk
//
//------------------------------------------------------------------
void ActionRotateJerk::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(2);

	auto seq = Sequence::create(
        RotateTo::create(0.5f, -20),
        RotateTo::create(0.5f, 20),
        NULL);

	auto rep1 = Repeat::create(seq, 10);
	auto rep2 = RepeatForever::create( seq->clone() );

    _tamara->runAction(rep1);
    _kathia->runAction(rep2);
}

std::string ActionRotateJerk::subtitle()
{
    return "RepeatForever / Repeat + Rotate";
}

//------------------------------------------------------------------
//
// ActionReverse
//
//------------------------------------------------------------------
void ActionReverse::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto jump = JumpBy::create(2, Point(300,0), 50, 4);
    auto action = Sequence::create( jump, jump->reverse(), NULL);

    _grossini->runAction(action);
}

std::string ActionReverse::subtitle()
{
    return "Reverse an action";
}


//------------------------------------------------------------------
//
// ActionDelayTime
//
//------------------------------------------------------------------
void ActionDelayTime::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto move = MoveBy::create(1, Point(150,0));
    auto action = Sequence::create( move, DelayTime::create(2), move, NULL);

    _grossini->runAction(action);
}

std::string ActionDelayTime::subtitle()
{
    return "DelayTime: m + delay + m";
}


//------------------------------------------------------------------
//
// ActionReverseSequence
//
//------------------------------------------------------------------
void ActionReverseSequence::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(1);

    auto move1 = MoveBy::create(1, Point(250,0));
    auto move2 = MoveBy::create(1, Point(0,50));
    auto seq = Sequence::create( move1, move2, move1->reverse(), NULL);
    auto action = Sequence::create( seq, seq->reverse(), NULL);

    _grossini->runAction(action);
}

std::string ActionReverseSequence::subtitle()
{
    return "Reverse a sequence";
}


//------------------------------------------------------------------
//
// ActionReverseSequence2
//
//------------------------------------------------------------------
void ActionReverseSequence2::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    // Test:
    //   Sequence should work both with IntervalAction and InstantActions
	auto move1 = MoveBy::create(1, Point(250,0));
	auto move2 = MoveBy::create(1, Point(0,50));
	auto tog1 = ToggleVisibility::create();
	auto tog2 = ToggleVisibility::create();
	auto seq = Sequence::create( move1, tog1, move2, tog2, move1->reverse(), NULL);
	auto action = Repeat::create(Sequence::create( seq, seq->reverse(), NULL), 3);


    // Test:
    //   Also test that the reverse of Hide is Show, and vice-versa
    _kathia->runAction(action);

	auto move_tamara = MoveBy::create(1, Point(100,0));
	auto move_tamara2 = MoveBy::create(1, Point(50,0));
	auto hide = Hide::create();
	auto seq_tamara = Sequence::create( move_tamara, hide, move_tamara2, NULL);
	auto seq_back = seq_tamara->reverse();
    _tamara->runAction( Sequence::create( seq_tamara, seq_back, NULL));
}
std::string ActionReverseSequence2::subtitle()
{
    return "Reverse sequence 2";
}

//------------------------------------------------------------------
//
// ActionRepeat
//
//------------------------------------------------------------------
void ActionRepeat::onEnter()
{
    ActionsDemo::onEnter();

    alignSpritesLeft(2);


    auto a1 = MoveBy::create(1, Point(150,0));
    auto action1 = Repeat::create(
        Sequence::create( Place::create(Point(60,60)), a1, NULL) , 
        3); 
    auto  action2 = RepeatForever::create(
        Sequence::create(a1->clone(), a1->reverse(), NULL)
        );

    _kathia->runAction(action1);
    _tamara->runAction(action2);
}

std::string ActionRepeat::subtitle()
{
    return "Repeat / RepeatForever actions";
}

//------------------------------------------------------------------
//
// ActionOrbit
//
//------------------------------------------------------------------
void ActionOrbit::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(3);

    auto orbit1 = OrbitCamera::create(2,1, 0, 0, 180, 0, 0);
    auto  action1 = Sequence::create(
        orbit1,
        orbit1->reverse(),
        NULL);

    auto orbit2 = OrbitCamera::create(2,1, 0, 0, 180, -45, 0);
    auto  action2 = Sequence::create(
        orbit2,
        orbit2->reverse(),
        NULL);

    auto orbit3 = OrbitCamera::create(2,1, 0, 0, 180, 90, 0);
    auto  action3 = Sequence::create(
        orbit3,
        orbit3->reverse(),
        NULL);

    _kathia->runAction(RepeatForever::create(action1));
    _tamara->runAction(RepeatForever::create(action2));
    _grossini->runAction(RepeatForever::create(action3));

    auto move = MoveBy::create(3, Point(100,-100));
    auto move_back = move->reverse();
    auto  seq = Sequence::create(move, move_back, NULL);
    auto  rfe = RepeatForever::create(seq);
    _kathia->runAction(rfe);
    _tamara->runAction(rfe->clone() );
    _grossini->runAction( rfe->clone() );
}

std::string ActionOrbit::subtitle()
{
    return "OrbitCamera action";
}

//------------------------------------------------------------------
//
// ActionFollow
//
//------------------------------------------------------------------
void ActionFollow::onEnter()
{
    ActionsDemo::onEnter();

    centerSprites(1);
    auto s = Director::getInstance()->getWinSize();

    _grossini->setPosition(Point(-200, s.height / 2));
    auto move      = MoveBy::create(2, Point(s.width * 3, 0));
    auto move_back = move->reverse();
    auto seq       = Sequence::create(move, move_back, NULL);
    auto rep               = RepeatForever::create(seq);

    _grossini->runAction(rep);

    this->runAction(Follow::create(_grossini, Rect(0, 0, s.width * 2 - 100, s.height)));
}

void ActionFollow::draw()
{
    auto winSize = Director::getInstance()->getWinSize();
    
	float x = winSize.width*2 - 100;
	float y = winSize.height;
    
	Point vertices[] = { Point(5,5), Point(x-5,5), Point(x-5,y-5), Point(5,y-5) };
	ccDrawPoly(vertices, 4, true);
}

std::string ActionFollow::subtitle()
{
    return "Follow action";
}

void ActionTargeted::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(2);


    auto jump1 = JumpBy::create(2,Point::ZERO,100,3);
    auto jump2 = jump1->clone();
    auto rot1 =  RotateBy::create(1, 360);
    auto rot2 = rot1->clone();

    auto t1 = TargetedAction::create(_kathia, jump2);
    auto t2 = TargetedAction::create(_kathia, rot2);

    auto seq = Sequence::create(jump1, t1, rot1, t2, NULL);
    auto always = RepeatForever::create(seq);

    _tamara->runAction(always);
}

std::string ActionTargeted::title()
{
    return "ActionTargeted";
}

std::string ActionTargeted::subtitle()
{
    return "Action that runs on another target. Useful for sequences";
}

//#pragma mark - ActionStacked

void ActionStacked::onEnter()
{
    ActionsDemo::onEnter();
        
    this->centerSprites(0);
    
    this->setTouchEnabled(true);
    
    auto s = Director::getInstance()->getWinSize();
    this->addNewSpriteWithCoords(Point(s.width/2, s.height/2));
}

void ActionStacked::addNewSpriteWithCoords(Point p)
{
    int idx = CCRANDOM_0_1() * 1400 / 100;
    int x = (idx%5) * 85;
    int y = (idx/5) * 121;
    
    
    Sprite *sprite = Sprite::create("Images/grossini_dance_atlas.png", Rect(x,y,85,121));
    
    sprite->setPosition(p);
    this->addChild(sprite);
    
    this->runActionsInSprite(sprite);
}

void ActionStacked::runActionsInSprite(Sprite *sprite)
{
    // override me
}

void ActionStacked::ccTouchesEnded(Set* touches, Event* event)
{
    for ( auto &item: *touches ) {

        const Touch *touch = static_cast<Touch*>(item);

        Point location = touch->getLocation();
        addNewSpriteWithCoords( location );
    }
}

std::string ActionStacked::title()
{
    return "Override me";
}

std::string ActionStacked::subtitle()
{
    return "Tap screen";
}

//#pragma mark - ActionMoveStacked


void ActionMoveStacked::runActionsInSprite(Sprite *sprite)
{
    sprite->runAction(
        RepeatForever::create(
                Sequence::create(
                MoveBy::create(0.05f, Point(10,10)),
                MoveBy::create(0.05f, Point(-10,-10)),
       NULL)));
    
    MoveBy* action = MoveBy::create(2.0f, Point(400,0));
    MoveBy* action_back = action->reverse();
    
    sprite->runAction(
      RepeatForever::create(
        Sequence::create(action, action_back, NULL)
      ));
}


std::string ActionMoveStacked::title()
{
    return "Stacked MoveBy/To actions";
}

//#pragma mark - ActionMoveJumpStacked

void ActionMoveJumpStacked::runActionsInSprite(Sprite *sprite)
{
    sprite->runAction(
          RepeatForever::create(
            Sequence::create(
             MoveBy::create(0.05f, Point(10,2)),
             MoveBy::create(0.05f, Point(-10,-2)),
             NULL)));
    
    auto jump = JumpBy::create(2.0f, Point(400,0), 100, 5);
    auto jump_back = jump->reverse();
    
    sprite->runAction(
      RepeatForever::create(
          Sequence::create(jump, jump_back, NULL)
          ));
}

std::string ActionMoveJumpStacked::title()
{
    return "tacked Move + Jump actions";
}

//#pragma mark - ActionMoveBezierStacked

void ActionMoveBezierStacked::runActionsInSprite(Sprite *sprite)
{
    auto s = Director::getInstance()->getWinSize();
    
    // sprite 1
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(0, s.height/2);
    bezier.controlPoint_2 = Point(300, -s.height/2);
    bezier.endPosition = Point(300,100);
    
    BezierBy* bezierForward = BezierBy::create(3, bezier);
    BezierBy* bezierBack = bezierForward->reverse();
    auto seq = Sequence::create(bezierForward, bezierBack, NULL);
    RepeatForever* rep = RepeatForever::create(seq);
    sprite->runAction(rep);
    
    sprite->runAction(
     RepeatForever::create(
      Sequence::create(
       MoveBy::create(0.05f, Point(10,0)),
       MoveBy::create(0.05f, Point(-10,0)),
       NULL)));
}

std::string ActionMoveBezierStacked::title()
{
    return "Stacked Move + Bezier actions";
}


//#pragma mark - ActionCatmullRomStacked

void ActionCatmullRomStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    _tamara->setPosition(Point(50,50));
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Point(0,0));
    array->addControlPoint(Point(80,80));
    array->addControlPoint(Point(s.width-80,80));
    array->addControlPoint(Point(s.width-80,s.height-80));
    array->addControlPoint(Point(80,s.height-80));
    array->addControlPoint(Point(80,80));
    array->addControlPoint(Point(s.width/2, s.height/2));
    
    auto action = CatmullRomBy::create(3, array);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, NULL);
    
    _tamara->runAction(seq);
    
    
    _tamara->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Point(10,0)),
                MoveBy::create(0.05f, Point(-10,0)),
                NULL)));
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //
    
    auto array2 = PointArray::create(20);
    
    array2->addControlPoint(Point(s.width/2, 30));
    array2->addControlPoint(Point(s.width-80,30));
    array2->addControlPoint(Point(s.width-80,s.height-80));
    array2->addControlPoint(Point(s.width/2,s.height-80));
    array2->addControlPoint(Point(s.width/2, 30));
    
    auto action2 = CatmullRomTo::create(3, array2);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, NULL);
    
    _kathia->runAction(seq2);
    
    _kathia->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Point(10,0)),
                MoveBy::create(0.05f, Point(-10,0)),
                NULL)));
    
    
    array->retain();
    _array1 = array;
    array2->retain();
    _array2 = array2;
}

ActionCatmullRomStacked::~ActionCatmullRomStacked()
{
    CC_SAFE_RELEASE(_array1);
    CC_SAFE_RELEASE(_array2);
}

void ActionCatmullRomStacked::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCatmullRom(_array1,50);
    kmGLPopMatrix();
    
    ccDrawCatmullRom(_array2,50);
}

std::string ActionCatmullRomStacked::title()
{
    return "Stacked MoveBy + CatmullRom actions";
}

std::string ActionCatmullRomStacked::subtitle()
{
    return "MoveBy + CatmullRom at the same time in the same sprite";
}


//#pragma mark - ActionCardinalSplineStacked

void ActionCardinalSplineStacked::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Point(0, 0));
    array->addControlPoint(Point(s.width/2-30,0));
    array->addControlPoint(Point(s.width/2-30,s.height-80));
    array->addControlPoint(Point(0, s.height-80));
    array->addControlPoint(Point(0, 0));
    
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //

    auto action = CardinalSplineBy::create(3, array, 0);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, NULL);
    
    _tamara->setPosition(Point(50,50));
    _tamara->runAction(seq);
    
    _tamara->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Point(10,0)),
                MoveBy::create(0.05f, Point(-10,0)),
                NULL)));
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    auto *action2 = CardinalSplineBy::create(3, array, 1);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, NULL);
    
    _kathia->setPosition(Point(s.width/2,50));
    
    _kathia->runAction(seq2);
    
    _kathia->runAction(
        RepeatForever::create(
            Sequence::create(
                MoveBy::create(0.05f, Point(10,0)),
                MoveBy::create(0.05f, Point(-10,0)),
                NULL)));
    
    array->retain();
    _array = array;
}

ActionCardinalSplineStacked::~ActionCardinalSplineStacked()
{
    CC_SAFE_RELEASE(_array);
}

void ActionCardinalSplineStacked::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCardinalSpline(_array, 0, 100);
    kmGLPopMatrix();
    
    auto s = Director::getInstance()->getWinSize();
    
    kmGLPushMatrix();
    kmGLTranslatef(s.width/2, 50, 0);
    ccDrawCardinalSpline(_array, 1, 100);
    kmGLPopMatrix();
}

std::string ActionCardinalSplineStacked::title()
{
    return "Stacked MoveBy + CardinalSpline actions";
}

std::string ActionCardinalSplineStacked::subtitle()
{
    return "CCMoveBy + CardinalSplineBy/To at the same time";
}

// Issue1305
void Issue1305::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    _spriteTmp = Sprite::create("Images/grossini.png");
    /* c++ can't support block, so we use CallFuncN instead.
    [spriteTmp_ runAction:[CallBlockN actionWithBlock:^(Node* node) {
        NSLog(@"This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
    }] );
    */

    _spriteTmp->runAction(CallFunc::create(std::bind(&Issue1305::log, this, _spriteTmp)));
    _spriteTmp->retain();

    scheduleOnce(schedule_selector(Issue1305::addSprite), 2);
}

void Issue1305::log(Node* pSender)
{
    CCLog("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE");
}

void Issue1305::onExit()
{
    _spriteTmp->stopAllActions();
    _spriteTmp->release();
    ActionsDemo::onExit();
}

void Issue1305::addSprite(float dt)
{
    _spriteTmp->setPosition(Point(250,250));
    addChild(_spriteTmp);
}

std::string Issue1305::title()
{
    return "Issue 1305";
}

std::string Issue1305::subtitle()
{
    return "In two seconds you should see a message on the console. NOT BEFORE.";
}

void Issue1305_2::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    auto spr = Sprite::create("Images/grossini.png");
    spr->setPosition(Point(200,200));
    addChild(spr);

    auto act1 = MoveBy::create(2 ,Point(0, 100));
    /* c++ can't support block, so we use CallFuncN instead.
    id act2 = [CallBlock actionWithBlock:^{
        NSLog(@"1st block");
    });
    id act3 = [MoveBy create:2, Point(0, -100));
    id act4 = [CallBlock actionWithBlock:^{
        NSLog(@"2nd block");
    });
    id act5 = [MoveBy create:2, Point(100, -100));
    id act6 = [CallBlock actionWithBlock:^{
        NSLog(@"3rd block");
    });
    id act7 = [MoveBy create:2, Point(-100, 0));
    id act8 = [CallBlock actionWithBlock:^{
        NSLog(@"4th block");
    });
    */

    auto act2 = CallFunc::create( std::bind( &Issue1305_2::printLog1, this));
    auto act3 = MoveBy::create(2, Point(0, -100));
    auto act4 = CallFunc::create( std::bind( &Issue1305_2::printLog2, this));
    auto act5 = MoveBy::create(2, Point(100, -100));
    auto act6 = CallFunc::create( std::bind( &Issue1305_2::printLog3, this));
    auto act7 = MoveBy::create(2, Point(-100, 0));
    auto act8 = CallFunc::create( std::bind( &Issue1305_2::printLog4, this));

    auto actF = Sequence::create(act1, act2, act3, act4, act5, act6, act7, act8, NULL);

    //    [spr runAction:actF);
    Director::getInstance()->getActionManager()->addAction(actF ,spr, false);

}

void Issue1305_2::printLog1()
{
    CCLog("1st block");
}

void Issue1305_2::printLog2()
{
    CCLog("2nd block");
}

void Issue1305_2::printLog3()
{
    CCLog("3rd block");
}

void Issue1305_2::printLog4()
{
    CCLog("4th block");
}

std::string Issue1305_2::title()
{
    return "Issue 1305 #2";
}

std::string Issue1305_2::subtitle()
{
    return "See console. You should only see one message for each block";
}

void Issue1288::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    Sprite *spr = Sprite::create("Images/grossini.png");
    spr->setPosition(Point(100, 100));
    addChild(spr);

    MoveBy* act1 = MoveBy::create(0.5, Point(100, 0));
    MoveBy* act2 = act1->reverse();
    auto act3 = Sequence::create(act1, act2, NULL);
    Repeat* act4 = Repeat::create(act3, 2);

    spr->runAction(act4);
}

std::string Issue1288::title()
{
    return "Issue 1288";
}

std::string Issue1288::subtitle()
{
    return "Sprite should end at the position where it started.";
}

void Issue1288_2::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    auto spr = Sprite::create("Images/grossini.png");
    spr->setPosition(Point(100, 100));
    addChild(spr);

    auto act1 = MoveBy::create(0.5, Point(100, 0));
    spr->runAction(Repeat::create(act1, 1));
}

std::string Issue1288_2::title()
{
    return "Issue 1288 #2";
}

std::string Issue1288_2::subtitle()
{
    return "Sprite should move 100 pixels, and stay there";
}


void Issue1327::onEnter()
{
    ActionsDemo::onEnter();
    centerSprites(0);

    auto spr = Sprite::create("Images/grossini.png");
    spr->setPosition(Point(100, 100));
    addChild(spr);

    auto act1 = CallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    auto act2 = RotateBy::create(0.25, 45);
    auto act3 = CallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    auto act4 = RotateBy::create(0.25, 45);
    auto act5 = CallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    auto act6 = RotateBy::create(0.25, 45);
    auto act7 = CallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));
    auto act8 = RotateBy::create(0.25, 45);
    auto act9 = CallFunc::create( std::bind(&Issue1327::logSprRotation, this, spr));

    auto actF = Sequence::create(act1, act2, act3, act4, act5, act6, act7, act8, act9, NULL);
    spr->runAction(actF);
}

std::string Issue1327::title()
{
    return "Issue 1327";
}

std::string Issue1327::subtitle()
{
    return "See console: You should see: 0, 45, 90, 135, 180";
}

void Issue1327::logSprRotation(Sprite* pSender)
{
    CCLog("%f", pSender->getRotation());
}

//Issue1398
void Issue1398::incrementInteger()
{
    _testInteger++;
    CCLog("incremented to %d", _testInteger);
}

void Issue1398::onEnter()
{
    ActionsDemo::onEnter();
    this->centerSprites(0);

    _testInteger = 0;
    CCLog("testInt = %d", _testInteger);

    this->runAction(
        Sequence::create(
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"1")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"2")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"3")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"4")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"5")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"6")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"7")),
			CallFunc::create( std::bind(&Issue1398::incrementIntegerCallback, this, (void*)"8")),
            NULL));
}

void Issue1398::incrementIntegerCallback(void* data)
{
    this->incrementInteger();
    CCLog("%s", (char*)data);
}

std::string Issue1398::subtitle()
{
    return "See console: You should see an 8";
}

std::string Issue1398::title()
{
    return "Issue 1398";
}

/** ActionCatmullRom
 */
void ActionCatmullRom::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    //
    // sprite 1 (By)
    //
    // startPosition can be any coordinate, but since the movement
    // is relative to the Catmull Rom curve, it is better to start with (0,0).
    //
    
    _tamara->setPosition(Point(50, 50));
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Point(0, 0));
    array->addControlPoint(Point(80, 80));
    array->addControlPoint(Point(s.width - 80, 80));
    array->addControlPoint(Point(s.width - 80, s.height - 80));
    array->addControlPoint(Point(80, s.height - 80));
    array->addControlPoint(Point(80, 80));
    array->addControlPoint(Point(s.width / 2, s.height / 2));
    
    auto action = CatmullRomBy::create(3, array);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, NULL);
    
    _tamara->runAction(seq);
    
    
    //
    // sprite 2 (To)
    //
    // The startPosition is not important here, because it uses a "To" action.
    // The initial position will be the 1st point of the Catmull Rom path
    //    
    
    auto array2 = PointArray::create(20);
    
    array2->addControlPoint(Point(s.width / 2, 30));
    array2->addControlPoint(Point(s.width  -80, 30));
    array2->addControlPoint(Point(s.width - 80, s.height - 80));
    array2->addControlPoint(Point(s.width / 2, s.height - 80));
    array2->addControlPoint(Point(s.width / 2, 30));
    
    auto action2 = CatmullRomTo::create(3, array2);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, NULL);
    
    _kathia->runAction(seq2);
    
    _array1 = array;
    _array1->retain();
    _array2 = array2;
    _array2->retain();
}

ActionCatmullRom::~ActionCatmullRom()
{
    _array1->release();
    _array2->release();
}

void ActionCatmullRom::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCatmullRom(_array1, 50);
    kmGLPopMatrix();
    
    ccDrawCatmullRom(_array2,50);
}

string ActionCatmullRom::title()
{
    return "CatmullRomBy / CatmullRomTo";
}

string ActionCatmullRom::subtitle()
{
    return "Catmull Rom spline paths. Testing reverse too";
}

/** ActionCardinalSpline
 */
void ActionCardinalSpline::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(2);
    
    auto s = Director::getInstance()->getWinSize();
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Point(0, 0));
    array->addControlPoint(Point(s.width/2-30, 0));
    array->addControlPoint(Point(s.width/2-30, s.height-80));
    array->addControlPoint(Point(0, s.height-80));
    array->addControlPoint(Point(0, 0));
    
    //
    // sprite 1 (By)
    //
    // Spline with no tension (tension==0)
    //
    
    auto action = CardinalSplineBy::create(3, array, 0);
    auto reverse = action->reverse();
    
    auto seq = Sequence::create(action, reverse, NULL);
    
    _tamara->setPosition(Point(50, 50));
    _tamara->runAction(seq);
    
    //
    // sprite 2 (By)
    //
    // Spline with high tension (tension==1)
    //
    
    CardinalSplineBy *action2 = CardinalSplineBy::create(3, array, 1);
    auto reverse2 = action2->reverse();
    
    auto seq2 = Sequence::create(action2, reverse2, NULL);
    
    _kathia->setPosition(Point(s.width/2, 50));
    _kathia->runAction(seq2);
    
    _array = array;
    array->retain();
}

ActionCardinalSpline::~ActionCardinalSpline()
{
    _array->release();
}

void ActionCardinalSpline::draw()
{
    ActionsDemo::draw();
    
    // move to 50,50 since the "by" path will start at 50,50
    kmGLPushMatrix();
    kmGLTranslatef(50, 50, 0);
    ccDrawCardinalSpline(_array, 0, 100);
    kmGLPopMatrix();
    
    auto s = Director::getInstance()->getWinSize();
    
    kmGLPushMatrix();
    kmGLTranslatef(s.width/2, 50, 0);
    ccDrawCardinalSpline(_array, 1, 100);
    kmGLPopMatrix();
}

string ActionCardinalSpline::title()
{
    return "CardinalSplineBy / CardinalSplineTo";
}

string ActionCardinalSpline::subtitle()
{
    return "Cardinal Spline paths. Testing different tensions for one array";
}

/** PauseResumeActions
 */

PauseResumeActions::PauseResumeActions()
: _pausedTargets(NULL)
{

}

PauseResumeActions::~PauseResumeActions()
{
    CC_SAFE_RELEASE(_pausedTargets);
}

void PauseResumeActions::onEnter()
{
    ActionsDemo::onEnter();
    
    this->centerSprites(3);
    
    _tamara->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    _grossini->runAction(RepeatForever::create(RotateBy::create(3, -360)));
    _kathia->runAction(RepeatForever::create(RotateBy::create(3, 360)));
    
    this->schedule(schedule_selector(PauseResumeActions::pause), 3, false, 0);
    this->schedule(schedule_selector(PauseResumeActions::resume), 5, false, 0);
}

string PauseResumeActions::title()
{
    return "PauseResumeActions";
}

string PauseResumeActions::subtitle()
{
    return "All actions pause at 3s and resume at 5s";
}

void PauseResumeActions::pause(float dt)
{
    CCLog("Pausing");
    Director *director = Director::getInstance();

    CC_SAFE_RELEASE(_pausedTargets);
    _pausedTargets = director->getActionManager()->pauseAllRunningActions();
    CC_SAFE_RETAIN(_pausedTargets);
}

void PauseResumeActions::resume(float dt)
{
    CCLog("Resuming");
    Director *director = Director::getInstance();
    director->getActionManager()->resumeTargets(_pausedTargets);
}

//------------------------------------------------------------------
//
//    ActionRemoveSelf
//
//------------------------------------------------------------------
void ActionRemoveSelf::onEnter()
{
	ActionsDemo::onEnter();

	alignSpritesLeft(1);

	auto action = Sequence::create(
		MoveBy::create( 2, Point(240,0)),
		RotateBy::create( 2,  540),
		ScaleTo::create(1,0.1f),
		RemoveSelf::create(),
		NULL);

	_grossini->runAction(action);
}

std::string ActionRemoveSelf::subtitle()
{
	return "Sequence: Move + Rotate + Scale + RemoveSelf";
}
