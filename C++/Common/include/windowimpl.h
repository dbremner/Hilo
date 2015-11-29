//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================

#pragma once

using namespace Hilo::WindowApiHelpers;

namespace Hilo 
{
    namespace WindowApiHelpers
    {
        //
        // The default implementation of an IWindow interface, representing
        // the interface to a single window.
        //
        class Window : public IWindow
        {
        public:
            // IWindow implementation
            HRESULT __stdcall Show(__in bool isVisible) override;
            HRESULT __stdcall RedrawWindow() override;
            HRESULT __stdcall RedrawWindow(__in bool eraseBackground) override;
            HRESULT __stdcall UpdateWindow() override;
            HRESULT __stdcall Close() override;
            HRESULT __stdcall GetTitle(__out std::wstring* title) override;
            HRESULT __stdcall SetTitle(__in const std::wstring& title) override;
            HRESULT __stdcall GetLargeIcon(__out HICON* icon) override;
            HRESULT __stdcall SetLargeIcon(__in HICON icon) override;
            HRESULT __stdcall GetSmallIcon(__out HICON* icon) override;
            HRESULT __stdcall SetSmallIcon(__in HICON icon) override;
            HRESULT __stdcall GetSize(__out unsigned int* pixelWidth, __out unsigned int* pixelHeight) override;
            HRESULT __stdcall SetSize(__in unsigned int pixelWidth, __in unsigned int pixelHeight) override;
            HRESULT __stdcall SetPosition(__in unsigned int posX, __in unsigned int posY) override;
            HRESULT __stdcall GetRect(__out RECT* rect) override;
            HRESULT __stdcall GetParentWindowRect(__out RECT* rect) override;
            HRESULT __stdcall SetRect(__in RECT rect) override;
            HRESULT __stdcall SetZOrder(__in Hilo::WindowApiHelpers::IWindow *windowInsertAfter) override;
            HRESULT __stdcall SetZOrder(__in ZOrderPlacement placement) override;
            HRESULT __stdcall GetWindowHandle(__out HWND* hWnd) override;
            HRESULT __stdcall GetParentWindowHandle(__out HWND* hWnd) override;
            HRESULT __stdcall SetWindowHandle(__in HWND hWnd) override;
            HRESULT __stdcall GetMessageHandler(__out IWindowMessageHandler** messageHandler) override;
            HRESULT __stdcall SetMessageHandler(__in IWindowMessageHandler* messageHandler) override;
            HRESULT __stdcall GetClientRect(__out RECT* clientRect) override;
            HRESULT __stdcall SetCapture() override;
            HRESULT __stdcall SetFocus() override;
            HRESULT __stdcall IsMouseCaptured(__out bool* isMouseCaptured) override;

        protected:
            Window();
            virtual ~Window();

            bool QueryInterfaceHelper(const IID &iid, void **object)
            {
                return CastHelper<IWindow>::CastTo(iid, this, object);
            }

        private:
            HWND m_hWnd;
            HICON m_smallIcon;
            HICON m_largeIcon;
            ComPtr<IWindowMessageHandler> m_messageHandler;
            std::wstring m_title;
        };
    }
}
