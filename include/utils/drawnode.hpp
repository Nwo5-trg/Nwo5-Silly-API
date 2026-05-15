#pragma once

#include "../export.hpp"
#include <Geode/cocos/draw_nodes/CCDrawNode.h>

namespace nwo5::utils {
    constexpr cocos2d::ccVertex2F toVert(cocos2d::CCPoint pPoint) {
        return {pPoint.x, pPoint.y};
    }
    constexpr cocos2d::ccVertex2F toVert(float pX, float pY) {
        return {pX, pY};
    }

    constexpr cocos2d::ccColor4F CLEAR_COLOR{0.0f, 0.0f, 0.0f, 0.0f};

    /// fuck cocos
    SILLY_API_DLL cocos2d::CCGLProgram* getShaderPositionColorUColor();
    
    /// drawnode wrapper !! (this is unfinished and mainly just for better editor trail/trigger indicators, ill eventually js rewrite drawnode)
    /// - sets blendfunc to {GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA} by default (and switches shader too)
    /// - rewriten versions of most draw functions
    /// - drawing ellipses
    /// - color tinting (off by default)
    class SILLY_API_DLL SillyDrawNode : public cocos2d::CCDrawNode {
    protected:
        cocos2d::ccColor4F m_tintColor{1.0f, 1.0f, 1.0f, 1.0f};
        bool m_useTint = false;

        using Vertex = cocos2d::ccV2F_C4B_T2F;
        using Triangle = cocos2d::ccV2F_C4B_T2F_Triangle;
        
        virtual bool init();
        virtual void draw();
        
    public:
        /// draw a line from pStart to pEnd
        bool drawSegment(const cocos2d::CCPoint& pStart, const cocos2d::CCPoint& pEnd, float pThickness, const cocos2d::ccColor4F& pColor);
        /// draw a *straight* line from pStart to pEnd
        /// this function is "faster" than drawSegment
        /// but should only be used if u arent connecting segments to eachother
        /// because itll look bad and leave a gap
        bool drawLine(const cocos2d::CCPoint& pStart, const cocos2d::CCPoint& pEnd, float pThickness, const cocos2d::ccColor4F& pColor);
        /// draw a dashed line from pStart to pEnd
        /// @param pSegmentLength how long a dashed dot + empty space segment is
        /// @param pSegmentDotSize percentage of segmentLength the dot is (dashDotLength = pSegmentLength * pSegmentDotSize)
        bool drawDashedLine(const cocos2d::CCPoint& pStart, const cocos2d::CCPoint& pEnd, float pThickness, const cocos2d::ccColor4F& pColor, float pSegmentLength, float pSegmentDotSize = 0.5f);
        /// draw a line from pPoints[0] to pPoints[1], then pPoints[1] to pPoints[2], etc...
        /// @param pPoints ptr to a c array of ccpoints
        /// @param pSize amount of points in c array
        /// @note does nothing if pSegments < 2
        bool drawSegments(const cocos2d::CCPoint* pPoints, unsigned int pSize, float pThickness, const cocos2d::ccColor4F& pColor);
        /// draw a line from pPoints[0] to pPoints[1], then pPoints[1] to pPoints[2], etc...
        /// @note does nothing if segments < 2
        bool drawSegments(std::span<const cocos2d::CCPoint> pPoints, float pThickness, const cocos2d::ccColor4F& pColor);

        /// draw a circle at pCenter with radius pRadius
        /// @param pSegments how many triangle "slices" the circle is made up of
        /// @note does nothing if segments < 3
        bool drawCircle(const cocos2d::CCPoint& pCenter, float pRadius, const cocos2d::ccColor4F& pColor, unsigned int pSegments, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& pOutlineColor = CLEAR_COLOR);
        /// draw an ellipse at pCenter with radius pRadius
        /// @param pSegments how many triangle "slices" the circle is made up of
        /// @note does nothing if segments < 3
        bool drawEllipse(const cocos2d::CCPoint& pCenter, cocos2d::CCSize pRadius, const cocos2d::ccColor4F& pColor, unsigned int pSegments, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& pOutlineColor = CLEAR_COLOR);

        /// draw a polygon with points pPoints
        /// @param pPoints ptr to a c array of ccpoints
        /// @param pSize amount of points in c array
        /// @note does nothing if segments
        /// @note border alignment not impl
        /// @note calls ccdrawnode::drawPolygon internally
        bool drawPolygon(const cocos2d::CCPoint* pPoints, unsigned int pSize, const cocos2d::ccColor4F& pColor, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& pOutlineColor = CLEAR_COLOR, cocos2d::BorderAlignment = {});
        /// draw a polygon with points pPoints
        /// @note does nothing if segments
        /// @note border alignment not impl
        /// @note calls ccdrawnode::drawPolygon internally
        bool drawPolygon(std::span<const cocos2d::CCPoint> pPoints, const cocos2d::ccColor4F& pColor, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& pOutlineColor = CLEAR_COLOR, cocos2d::BorderAlignment = {});

        /// draw a square with radius pRadius
        bool drawDot(const cocos2d::CCPoint& pCenter, float pRadius, const cocos2d::ccColor4F& pColor);

        /// draw a rect from pRect
        /// @note border alignment not impl
        bool drawRect(const cocos2d::CCRect& pRect, const cocos2d::ccColor4F& pColor, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& = CLEAR_COLOR, cocos2d::BorderAlignment = {});
        /// draw a rect from pStart to pEnd
        /// @note border alignment not impl
        bool drawRect(const cocos2d::CCPoint& pStart, const cocos2d::CCPoint& pEnd, const cocos2d::ccColor4F& pColor, float pOutlineThickness = 0.0f, const cocos2d::ccColor4F& = CLEAR_COLOR, cocos2d::BorderAlignment = {});

        /// set tint color for everything drawn
        void setTint(const cocos2d::ccColor4F& pColor);
        const cocos2d::ccColor4F& getTint() const;

        /// set if tint color is used
        void setUseTint(bool pTint);
        bool useTint() const;

        /// std::vector::reserve
        void reserve(unsigned int pSize);
        /// std::vector::reserve(m_nBufferCount + pCount)
        void reserveCount(unsigned int pCount);
        /// reserves space for triangles and updates buffercount/dirty accordingly
        /// @returns a ptr at the end of the buffer u can write ur triangles to
        Triangle* writeTriangles(unsigned int pCount);
        /// reserves space for vertices and updates buffercount/dirty accordingly
        /// @returns a ptr at the end of the buffer u can write ur vertices to
        Vertex* writeVertices(unsigned int pCount);

        static SillyDrawNode* create();
    };
}