#include "SubApp.h"
//Hello my name is Tony
SubApp::SubApp()
	: m_AppID(AppID::InvalidApp)
{}

SubApp::SubApp(AppID p_AppID)
	: m_AppID(p_AppID)
{}

AppID SubApp::GetAppID() const
{
	return m_AppID;
}