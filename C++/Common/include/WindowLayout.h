//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================


#pragma once

#include "WindowLayoutInterface.h"
#include <vector>

using namespace Hilo::WindowApiHelpers;

//
// The default implementation for the window layout interface
// 
class WindowLayout : public IWindowLayout
{
public:
    // Getters and setters
    HRESULT __stdcall SetMainWindow(__in_opt IWindow* mainWindow) override;
    HRESULT __stdcall GetMainWindow(__out IWindow** mainWindow) override;

    HRESULT __stdcall InsertChildWindow(IWindow* childWindow, __out unsigned int* index) override;
    HRESULT __stdcall GetChildWindowCount(__out unsigned int* count) override;
    HRESULT __stdcall GetChildWindow(__in unsigned int index, __out IWindow** childWindow) override;

    HRESULT __stdcall GetChildWindowLayoutHeight(__in unsigned int index, __out unsigned int* height) override;
    HRESULT __stdcall SetChildWindowLayoutHeight(__in unsigned int index, __in unsigned int height) override;

    // Methods
    HRESULT __stdcall SwitchDisplayMode(__in bool mode) override;
    HRESULT __stdcall UpdateLayout() override;
    HRESULT __stdcall Finalize() override;

protected:
    // Constructor
    WindowLayout();

    // Destructor
    virtual ~WindowLayout();

    bool QueryInterfaceHelper(const IID &iid, void **object)
    {
        return CastHelper<IWindowLayout>::CastTo(iid, this, object);
    }

    HRESULT __stdcall Initialize();

private:
    bool m_isSlideShow;
    unsigned int m_carouselPaneHeight;

    // Main and child windows
    ComPtr<IWindow> m_applicationWindow;
    std::vector<ComPtr<IWindow> > m_childWindows;
};
