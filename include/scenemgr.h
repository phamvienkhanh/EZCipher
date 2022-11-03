#ifndef _INC_SCENE_MGR_H_
#define _INC_SCENE_MGR_H_

#include "precompile.h"

class SceneMgr
{

public:
    static SceneMgr* Inst();

    void setScene(QtNodes::FlowScene* scene);
    QtNodes::FlowScene* getScene();

private:
    static SceneMgr* s_instance;
    SceneMgr();

    QtNodes::FlowScene* m_scene = nullptr;
};

#endif