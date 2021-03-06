//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================

#pragma once

#include "WindowLayout.h"
#include "WindowApplicationImpl.h"

class AnnotatorApplication : public IUIApplication, public WindowApplication
{
protected:
    // Constructor/destructor
    AnnotatorApplication();
    ~AnnotatorApplication();

    // Messages
	virtual HRESULT OnCreate() override;
	virtual HRESULT OnClose() override;
	virtual HRESULT OnSize(unsigned int width, unsigned int height) override;
	virtual HRESULT OnKeyDown(unsigned int vKey) override;
	virtual HRESULT OnMouseWheel(D2D1_POINT_2F mousePosition, short delta, int keys) override;
	virtual HRESULT OnCommand(WPARAM wParam, LPARAM lParam) override;

    // Interface helper
    bool QueryInterfaceHelper(const IID &iid, void **object)
    {
        return CastHelper<IUIApplication>::CastTo(iid, this, object) ||
            WindowApplication::QueryInterfaceHelper(iid, object);
    }

    // IInitializeable implementation
    HRESULT __stdcall Initialize() override;

private:
    // Image editor window and handler
    ComPtr<Hilo::WindowApiHelpers::IWindow> m_imageEditorWindow;
    ComPtr<Hilo::WindowApiHelpers::IWindowMessageHandler> m_imageEditorHandler;
    ComPtr<IUICommandHandler> m_commandHandler;

    // Ribbon framework
    ComPtr<IUIFramework> m_ribbonFramework;

    // Methods
    UINT GetRibbonHeight();
    HRESULT InitializeRibbonFramework(Hilo::WindowApiHelpers::IWindow* window);
    HRESULT UpdateRenderWindowPosition(Hilo::WindowApiHelpers::IWindow* mainWindow, Hilo::WindowApiHelpers::IWindow* childWindow);
    bool RegisterFileAssociation();

    // IUIApplication implementation
	virtual HRESULT __stdcall OnCreateUICommand(unsigned int commandId, UI_COMMANDTYPE typeId, IUICommandHandler** commandHandler) override;
	virtual HRESULT __stdcall OnViewChanged(unsigned int viewId, UI_VIEWTYPE typeId, IUnknown* view, UI_VIEWVERB verb, int reasonCode) override;
	virtual HRESULT __stdcall OnDestroyUICommand(unsigned int commandId, UI_COMMANDTYPE typeId, IUICommandHandler* commandHandler) override;
};