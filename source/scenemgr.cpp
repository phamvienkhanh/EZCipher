#include "scenemgr.h"

SceneMgr* SceneMgr::s_instance = nullptr;

SceneMgr* SceneMgr::Inst()
{
    if(!s_instance)
        s_instance = new SceneMgr();
    
    return s_instance;
}

void SceneMgr::setScene(QtNodes::FlowScene* scene)
{
    m_scene = scene;
}

QtNodes::FlowScene* SceneMgr::getScene()
{
    return m_scene;
}

SceneMgr::SceneMgr()
{

}
