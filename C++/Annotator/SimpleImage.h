//===================================================================================
// Copyright (c) Microsoft Corporation.  All rights reserved.                        
//                                                                                   
// THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY                    
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT                       
// LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND                          
// FITNESS FOR A PARTICULAR PURPOSE.                                                 
//===================================================================================

#pragma once

#include "Image.h"
#include "DrawGeometryOperation.h"

using namespace Hilo::Direct2DHelpers;

class SimpleImage : public IImage
{
public:
    // Getters and setters
    HRESULT __stdcall GetDrawingRect(__out D2D1_RECT_F* rect) override;
    HRESULT __stdcall SetDrawingRect(__in const D2D1_RECT_F& rect) override;
    HRESULT __stdcall GetTransformedRect(D2D1_POINT_2F midPoint, __out D2D1_RECT_F* rect) override;
    HRESULT __stdcall GetImageInfo(__out ImageInfo* info) override;
    HRESULT __stdcall SetBoundingRect(__in const D2D1_RECT_F& rect) override;
    HRESULT __stdcall SetRenderingParameters(__in const RenderingParameters& drawingObjects) override;
    HRESULT __stdcall ContainsPoint(__in D2D1_POINT_2F point, __out bool* doesImageContainPoint) override;
    HRESULT __stdcall TranslateToAbsolutePoint(__in D2D1_POINT_2F point, __out D2D1_POINT_2F *translatedPoint) override;
    HRESULT __stdcall GetScale(__out float* scale) override;
    HRESULT __stdcall GetClipRect(__out D2D1_RECT_F* rect) override;

    // Rendering method
    HRESULT __stdcall Draw() override;
    HRESULT __stdcall Load() override;
    HRESULT __stdcall Save(__in IShellItem *saveAsItem = nullptr) override;

    // Resource management
    HRESULT __stdcall DiscardResources() override;

    // Image operations
    HRESULT __stdcall PushImageOperation(__in IImageOperation* imageOperation) override;
    HRESULT __stdcall CanUndo(__out bool* canUndo) override;
    HRESULT __stdcall CanRedo(__out bool* canRedo) override;
    HRESULT __stdcall UndoImageOperation() override;
    HRESULT __stdcall RedoImageOperation() override;

protected:
    // Constructor/destructor
    SimpleImage(ImageInfo imageInfo);
    virtual ~SimpleImage();

    // Interface support
    bool QueryInterfaceHelper(const IID &iid, void **object)
    {
        return CastHelper<IImage>::CastTo(iid, this, object);
    }

private:
    // Constant
    static const float ShadowDepth;

    // Image information
    ImageInfo m_imageInfo;
    ComPtr<ID2D1Bitmap> m_bitmap;
    ComPtr<IWICBitmap> m_wicBitmap;
    ComPtr<ID2D1RenderTarget> m_currentRenderTarget;

    // Image operations
    std::vector<ComPtr<IImageOperation>> m_imageOperations;
    std::stack<ComPtr<IImageOperation>> m_redoStack;

    D2D1_POINT_2F m_drawingPoint;
    D2D1_RECT_F m_drawingRect;
    D2D1_RECT_F m_originalDrawingRect;
    D2D1_RECT_F m_boundingRect;
    D2D1_RECT_F m_clipRect;
    bool m_isHorizontal;

    // Rendering parameters
    RenderingParameters m_renderingParameters;

    // Bitmap methods
    HRESULT LoadBitmapFromShellItem();

    // Rendering methods
    HRESULT DrawImage(const D2D1_RECT_F& drawingRect, const D2D1_RECT_F& imageRect, bool isSaving);
    void CalculateDrawingRect();
    void DrawShadow(const D2D1_RECT_F& bitmapRect);

    // Matrix helper functin
    D2D1::Matrix3x2F GetTransformationsReversed(D2D1_POINT_2F midPoint, int upTo = 0 /* 0 = all transformations */);
    D2D1::Matrix3x2F GetInverseTransformations(D2D1_POINT_2F midPoint);
    D2D1_RECT_F GetTransformedRect(D2D1_POINT_2F midPoint, const D2D1_RECT_F& rect);

    // Determines if this image is rotated
    static bool IsRotationOperation(IImageOperation* operation);
    inline static bool IsRotation(ImageOperationType operationType)
    {
        return (operationType == ImageOperationTypeRotateClockwise || operationType == ImageOperationTypeRotateCounterClockwise);
    }
    
    inline float GetCurrentImageScale()
    {
        // image portion actual size / image portion display size
        return Direct2DUtility::GetRectWidth(m_clipRect) / Direct2DUtility::GetRectWidth(m_drawingRect);
    }

    void RecalculateClipRect();
};
