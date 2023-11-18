/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonAPI.h"
#include "LessonX.h"
#include <math.h>
#include <mmsystem.h>
#include <windows.h>
#pragma comment(lib,"Winmm.lib")
////////////////////////////////////////////////////////////////////////////////
//
//����ٶ�
float g_fSpeedwanjiaLeft	=	0.f;
float g_fSpeedwanjiaRight	=	0.f;
float g_fSpeedwanjiaTop		=	0.f;
float g_fSpeedwanjiaBottom	=	0.f;
//��ͼ�ٶ�
float g_fSpeedMapLeft	=	0.f;
float g_fSpeedMapRight	=	0.f;
float g_fSpeedMapTop	=	0.f;
float g_fSpeedMapBottom	=	0.f;
//����ٶ�
float g_fSpeedskyLeft	=	0.f;
float g_fSpeedskyRight	=	0.f;
float g_fSpeedskyTop	=	0.f;
float g_fSpeedskyBottom	=	0.f;
//��Ļ�߽�ֵ
float g_fScreenLeft	    =	0.f;
float g_fScreenRight	=	0.f;
float g_fScreenTop	    =	0.f;
float g_fScreenBottom	=	0.f;
int	g_iGameState	=	0;               //��Ϸ״̬
int g_iguan1Count = 10;                  //����1������
int g_Scores = 0;                        //�÷�
int HP = 3;                              //Ѫ��
char *szNameguan2 = NULL;                //ָ�����2
int j = 0;                               //��������







// ��Ϸ״̬��0 -- ��Ϸ�����ȴ���ʼ״̬��1 -- ���¿ո����ʼ����ʼ����Ϸ��2 -- ��Ϸ������
//
void		GameInit();
void		GameRun( float fDeltaTime );
void		GameEnd();



void OngongjiColguan1(const char* szgongjiName,const char* szguan1Name);//���������1��ײ
void Createguan1();//�������1
void CreateMoreguan1(const char* szTarName);//����1�������¹���1
void Createguan2();//�������2
//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�


//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void GameMainLoop( float	fDeltaTime )
{
    switch( g_iGameState )
    {
    // ��ʼ����Ϸ�������һ���������
    case 1:
    {
        PlaySound("game/data/audio/GloriousMorning.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
        GameInit();
        g_iGameState	=	2; // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
    }
    break;

    // ��Ϸ�����У����������Ϸ�߼�
    case 2:
    {
        // TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
        if( HP>0&&j<3 )
        {
            GameRun( fDeltaTime );


        }
        else
        {
            // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
            g_iGameState	=	0;
            GameEnd();
        }
    }
    break;
    case 3:
    {
         Createguan2();
         g_iGameState = 2;
    }

    // ��Ϸ����/�ȴ����ո����ʼ
    case 0:
    default:
        break;
    };
}

//==============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void GameInit()
{
    dSetSpriteVisible("GameBegin",0);
    g_fScreenLeft	 = 	dGetScreenLeft();
    g_fScreenRight  = 	dGetScreenRight();
    g_fScreenTop 	 = 	dGetScreenTop();
    g_fScreenBottom = 	dGetScreenBottom();
    Createguan1();


}
//==============================================================================
//
// ÿ����Ϸ������
void GameRun( float fDeltaTime )
{

    float fPoswanjiaX,fPoswanjiaY;
    fPoswanjiaX = dGetSpritePositionX( "wanjia" );
    fPoswanjiaY = dGetSpritePositionY( "wanjia" );

    char *szName=NULL;
    for(int i = 0; i<10; i++)
        {
        szName = dMakeSpriteName("guan1",i);
        dSpriteMoveTo( szName, fPoswanjiaX, fPoswanjiaY,4, 1 );
    }

    if(g_Scores%10 == 0&&g_Scores>=20&&g_Scores<50)
    {
        g_iGameState = 3;
        g_Scores++;
    }
    else if(g_Scores%5 == 0&&g_Scores>50)
    {
        g_iGameState = 3;
        g_Scores++;
    }









}
//==============================================================================
//
// ������Ϸ����
void GameEnd()
{   if(j == 3)
    dSetSpriteVisible("youwin",1);
    else
    dSetSpriteVisible("GameOver",1);
    char *szName = NULL;
    for(int i=0;i<10;i++){
        szName = dMakeSpriteName("guan1",i);
        dDeleteSprite(szName);
        dDeleteSprite("wanjia");
    }
    dDeleteSprite("ball");


}

//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void OnMouseMove( const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    float fPoswanjiaX,fPoswanjiaY;
    fPoswanjiaX = dGetSpritePositionX( "wanjia" );
    fPoswanjiaY = dGetSpritePositionY( "wanjia" );
    double y,x;
    dSetSpritePosition("ball",fPoswanjiaX,fPoswanjiaY);
    dSetSpriteVisible("ball",1);

    if( 2 != g_iGameState )
		return;
    if(iMouseType == MOUSE_LEFT){
    float fSpeedX = 0.f;
    float fSpeedY = 0.f;
    x = (double)fMouseX - (double)fPoswanjiaX;
    y = (double)fMouseY - (double)fPoswanjiaY;
    float ftan = atan2( y,x );
    fSpeedX = dRotationToVectorX( ftan/3.14*180 )*30;
    fSpeedY = dRotationToVectorY( ftan/3.14*180 )*30;
    dSetSpriteLinearVelocity("ball",fSpeedX,fSpeedY);
    }

}
//==========================================================================
//
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
    if( KEY_SPACE == iKey && 0 == g_iGameState )
    {
        g_iGameState	=	1;
        dSetTextValue("score",g_Scores);
        dSetSpriteVisible("ball",0);
    }
    else if( 2 == g_iGameState)
    {
        switch(iKey)
        {
        case KEY_W:
            g_fSpeedwanjiaTop = -10.f;
            dAnimateSpritePlayAnimation( "wanjia", "a02jes5lge_Animation3", 0 );
            break;
        case KEY_A:
            g_fSpeedwanjiaLeft = -15.f;
            dAnimateSpritePlayAnimation( "wanjia", "a02jes5lge_Animation1", 0 );
            break;
        case KEY_S:
            g_fSpeedwanjiaBottom = 10.f;
            dAnimateSpritePlayAnimation( "wanjia", "a02jes5lge_Animation", 0 );
            break;
        case KEY_D:
            g_fSpeedwanjiaRight = 15.f;
            dAnimateSpritePlayAnimation( "wanjia", "a02jes5lge_Animation2", 0 );
            break;
        }
        switch(iKey)
        {
        case KEY_W:
            g_fSpeedMapTop = 10.f;
            g_fSpeedskyTop = 10.f;
            break;
        case KEY_A:
            g_fSpeedMapLeft = 15.f;
            g_fSpeedskyLeft = 15.f;
            break;
        case KEY_S:
            g_fSpeedMapBottom = -10.f;
            g_fSpeedskyBottom = -10.f;
            break;
        case KEY_D:
            g_fSpeedMapRight = -10.f;
            g_fSpeedskyRight = -10.f;
            break;
        }


    }
    dSetSpriteLinearVelocity("wanjia",g_fSpeedwanjiaLeft + g_fSpeedwanjiaRight, g_fSpeedwanjiaTop + g_fSpeedwanjiaBottom);
    dSetSpriteLinearVelocity("Map",g_fSpeedMapLeft + g_fSpeedMapRight, g_fSpeedMapTop + g_fSpeedMapBottom);
    dSetSpriteLinearVelocity("sky",g_fSpeedskyLeft + g_fSpeedskyRight, g_fSpeedskyTop + g_fSpeedskyBottom);

}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void OnKeyUp( const int iKey )
{
    switch(iKey)
    {
    case KEY_W:
        g_fSpeedwanjiaTop = 0.f;
        break;
    case KEY_A:
        g_fSpeedwanjiaLeft = 0.f;
        break;
    case KEY_S:
        g_fSpeedwanjiaBottom = 0.f;
        break;
    case KEY_D:
        g_fSpeedwanjiaRight = 0.f;
        break;

    default:
        break;
    }
    switch(iKey)
    {
    case KEY_W:
        g_fSpeedMapTop = 0.f;
        g_fSpeedskyTop = 0.f;
        break;
    case KEY_A:
        g_fSpeedMapLeft = 0.f;
        g_fSpeedskyLeft = 0.f;
        break;
    case KEY_S:
        g_fSpeedMapBottom = 0.f;
        g_fSpeedskyBottom = 0.f;
        break;
    case KEY_D:
        g_fSpeedMapRight = 0.f;
        g_fSpeedskyRight = 0.f;
        break;
    }
    dSetSpriteLinearVelocity("wanjia",g_fSpeedwanjiaLeft + g_fSpeedwanjiaRight, g_fSpeedwanjiaTop + g_fSpeedwanjiaBottom);
    dSetSpriteLinearVelocity("Map",g_fSpeedMapLeft + g_fSpeedMapRight, g_fSpeedMapTop + g_fSpeedMapBottom);
    dSetSpriteLinearVelocity("sky",g_fSpeedskyLeft + g_fSpeedskyRight, g_fSpeedskyTop + g_fSpeedskyBottom);

}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
void OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    if( 2 != g_iGameState )
		return;
    for(int i=0; i<10; i++)
    {
        if(strcmp("wanjia",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i))==0)
        {
            HP--;
            dDeleteSprite(szTarName);
            if(HP == 2)
            dDeleteSprite("xin1");
            if(HP == 1)
            dDeleteSprite("xin2");
            if(HP == 0)
                dDeleteSprite("xin3");
                return;

        }
        if(strcmp("wanjia",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan2",i))==0)
        {
            HP--;
            dDeleteSprite(szTarName);
            if(HP == 2)
            dDeleteSprite("xin1");
            if(HP == 1)
            dDeleteSprite("xin2");
            if(HP == 0)
                dDeleteSprite("xin3");
                return;

        }

        if(strcmp("gongji",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i))==0)
        {
            dDeleteSprite(szTarName);
            g_Scores++;
            dSetTextValue("score",g_Scores);
            CreateMoreguan1(szTarName);


        }
        if(strcmp("gongji",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan2",i))==0)
        {
            dDeleteSprite(szTarName);
            g_Scores++;
            dSetTextValue("score",g_Scores);

        }
        if(strcmp("ball",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i))==0)
        {
            dDeleteSprite(szTarName);
            g_Scores++;
            dSetTextValue("score",g_Scores);
            CreateMoreguan1(szTarName);
            dSetSpriteVisible("ball",0);
        }
        if(strcmp("ball",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan2",i))==0)
        {
            dDeleteSprite(szTarName);
            g_Scores++;
            dSetTextValue("score",g_Scores);
            dSetSpriteVisible("ball",0);
        }
        if(strcmp("zhu1",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i)) == 0)
        {
            dDeleteSprite(szTarName);
            dAnimateSpritePlayAnimation("zhu1","imageMoleRedAnimation",0);
            CreateMoreguan1(szTarName);


        }
        if(strcmp("zhu2",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i)) == 0)
        {
            dDeleteSprite(szTarName);
            dAnimateSpritePlayAnimation("zhu2","imageMoleLilacAnimation",0);
            CreateMoreguan1(szTarName);


        }
         if(strcmp("zhu3",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("guan1",i)) == 0)
        {
            dDeleteSprite(szTarName);
            dAnimateSpritePlayAnimation("zhu3","imageMoleGreenAnimation",0);
            CreateMoreguan1(szTarName);


        }





    }

    for(int m = 1;m<4;m++){
        if(strcmp("wanjia",szSrcName)==0&&strcmp(szTarName,dMakeSpriteName("garlic",m))==0)
        {
            dDeleteSprite(szTarName);
            j++;
            dSetTextValue("garlicNUM",j);

        }
    }

}
//===========================================================================
//
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}
void OngongjiColguan1(const char* szgongjiName,const char* szguan1Name)
{
    if(strstr(szguan1Name,"guan1")!= NULL)
    {
        dDeleteSprite(szguan1Name);


    }
}
void Createguan1()
{
    char *szName = NULL;
    int	iLoop = 0,iPosX = 0,iPosY = 0;
    for( iLoop = 0; iLoop < g_iguan1Count; iLoop++ )
    {
        szName	=	dMakeSpriteName( "guan1", iLoop );
        dCloneSprite( "guan1", szName );
        iPosX	=	dRandomRange( g_fScreenLeft, g_fScreenRight);//��������
        iPosY	=	dRandomRange( g_fScreenTop, g_fScreenBottom);
        dSetSpritePosition( szName, (float)iPosX, (float)iPosY );
    }


}
void CreateMoreguan1(const char* szTarName)
{

    int	iPosX = 0,iPosY = 0;

    dCloneSprite( "guan1", szTarName);
    iPosX	=	dRandomRange( g_fScreenLeft, g_fScreenRight );//��������
    iPosY	=	dRandomRange( g_fScreenTop, g_fScreenBottom );
    dSetSpritePosition( szTarName, (float)iPosX, (float)iPosY );
    dSetSpritePosition( "appear", (float)iPosX, (float)iPosY);
    dAnimateSpritePlayAnimation("appear","g777Animation",0);

}
void Createguan2(){

    int	iLoop = 0,iPosY = 0;
    for( iLoop = 0; iLoop < 6; iLoop++ )
    {
        szNameguan2	=	dMakeSpriteName( "guan2", iLoop );
        dCloneSprite( "guan2", szNameguan2 );
        iPosY	=	dRandomRange( g_fScreenTop, g_fScreenBottom );
        dSetSpritePosition( szNameguan2, g_fScreenLeft, (float)iPosY );
        dSetSpriteLinearVelocityX(szNameguan2,20);
    }

}

