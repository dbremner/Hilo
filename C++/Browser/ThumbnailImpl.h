//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================


#pragma once

#include "AsyncLoader\AsyncLoaderInterfaces.h"
#include "ThumbnailControl.h"

using namespace Hilo::AsyncLoader;

class Thumbnail : public IThumbnail, public Hilo::AsyncLoader::IAsyncLoaderItem
{
public:
    // Setters and Getters
    virtual HRESULT __stdcall SetRenderingParameters(__in const RenderingParameters& drawingObjects) override;
    virtual HRESULT __stdcall SetParentWindow(__in Hilo::WindowApiHelpers::IChildNotificationHandler* parentWindowMessageHandler) override;
    virtual HRESULT __stdcall SetDefaultBitmap(__in ID2D1Bitmap* bitmap) override;
    virtual HRESULT __stdcall GetRect(__out D2D1_RECT_F* rect) override;
    virtual HRESULT __stdcall SetRect(__in D2D1_RECT_F rect) override;
    virtual HRESULT __stdcall GetThumbnail(__out ID2D1Bitmap** bitmap) override;
    virtual HRESULT __stdcall SetThumbnail(__in ID2D1Bitmap* newBitmap) override;
    virtual HRESULT __stdcall SetThumbnailIfNull(__in ID2D1Bitmap* newBitmap) override;
    virtual HRESULT __stdcall GetThumbnailInfo(__out ThumbnailInfo* thumbnailInfo) override;
    virtual HRESULT __stdcall SetIsFullImage(__in bool isFullImage) override;
    virtual HRESULT __stdcall GetSelectionState(__out ThumbnailSelectionState* selectionState) override;
    virtual HRESULT __stdcall SetSelectionState(__in ThumbnailSelectionState selectionState) override;
    virtual HRESULT __stdcall SetOpacity(float opacity) override;
    virtual HRESULT __stdcall SetFontSize(float size) override;

    // Rendering methods
    virtual HRESULT __stdcall Draw() override;
    
    // Resource management methods
    virtual HRESULT __stdcall ReleaseThumbnail() override;
    virtual HRESULT __stdcall ReleaseFullImage() override;
    virtual HRESULT __stdcall DiscardResources() override;

    // Asynchronous loader methods
    virtual HRESULT __stdcall EnableAsyncLoading(bool enable) override;

protected:
    // Asynchronous loader support
    CRITICAL_SECTION* m_criticalSection;
    bool m_asyncLoadingEnabled;
    int m_location;
    ComPtr<IAsyncLoaderItemCache> m_asyncLoaderItemCache;

    // Constructor/Destructor
    Thumbnail(ThumbnailInfo thumbnailInfo);
    virtual ~Thumbnail();

    // Query interface helper
    bool QueryInterfaceHelper(const IID &iid, void **object)
    {
        return CastHelper<IThumbnail>::CastTo(iid, this, object) ||
            CastHelper<Hilo::AsyncLoader::IAsyncLoaderItem>::CastTo(iid, this, object);
    }

    // Thumbnail information
    ThumbnailInfo m_thumbnailInfo;
    D2D1_RECT_F m_rect;
    DWRITE_TEXT_RANGE m_textRange;
    float m_fontSize;
    float m_opacity;
    ThumbnailSelectionState m_selectionState;
    bool m_isFullImage;

    // Rendering objects
    RenderingParameters m_renderingParameters;
    ComPtr<Hilo::WindowApiHelpers::IChildNotificationHandler> m_parentWindowMessageHandler;
    ComPtr<ID2D1Bitmap> m_defaultBitmap;
    ComPtr<IDWriteFactory> m_dWriteFactory;
    ComPtr<ID2D1Bitmap> m_thumbnailBitmap;
    ComPtr<ID2D1Bitmap> m_fullBitmap;
    ComPtr<IDWriteTextLayout> m_textLayout;

    // IAsyncLoaderItem implementation
    virtual HRESULT __stdcall SetCriticalSection(CRITICAL_SECTION* _cs) override;
    virtual HRESULT __stdcall SetMemoryManager(IAsyncLoaderMemoryManager* _p) override;
    virtual HRESULT __stdcall SetLocation(int location) override;
    virtual HRESULT __stdcall GetLocation(int* location) override;
    virtual HRESULT __stdcall LoadResource(unsigned int size, IUnknown** resource) override;
    virtual HRESULT __stdcall SetResource(IUnknown* resource) override;
    virtual HRESULT __stdcall RenderResource() override;
    virtual HRESULT __stdcall Load(LoadPage loadPage, LoadSize loadSize) override;
    virtual HRESULT __stdcall Unload(LoadSize loadSize) override;
    virtual HRESULT __stdcall Shutdown() override;
};
