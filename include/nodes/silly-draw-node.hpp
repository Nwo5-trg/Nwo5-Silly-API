#pragma once

#include "../export.hpp"
#include <Geode/cocos/draw_nodes/CCDrawNode.h>

namespace nwo5::nodes {
    constexpr cocos2d::ccVertex2F toVert(cocos2d::CCPoint point) {
        return {point.x, point.y};
    }
    constexpr cocos2d::ccVertex2F toVert(float x, float y) {
        return {x, y};
    }

    namespace impl {
        static constexpr cocos2d::ccColor4F CLEAR_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
    }

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
        /// draw a line from start to end
        bool drawSegment(const cocos2d::CCPoint& start, const cocos2d::CCPoint& end, float thickness, const cocos2d::ccColor4F& color);
        /// draw a *straight* line from start to end
        /// this function is "faster" than drawSegment
        /// but should only be used if u arent connecting segments to eachother
        /// because itll look bad and leave a gap
        bool drawLine(const cocos2d::CCPoint& start, const cocos2d::CCPoint& end, float thickness, const cocos2d::ccColor4F& color);
        /// draw a dashed line from start to end
        /// @param segmentLength how long a dashed dot + empty space segment is
        /// @param segmentDotSize percentage of segmentLength the dot is (dashDotLength = segmentLength * segmentDotSize)
        bool drawDashedLine(const cocos2d::CCPoint& start, const cocos2d::CCPoint& end, float thickness, const cocos2d::ccColor4F& color, float segmentLength, float segmentDotSize = 0.5f);
        /// draw a line from points[0] to points[1], then points[1] to points[2], etc...
        /// @param points ptr to a c array of ccpoints
        /// @param size amount of points in c array
        /// @note does nothing if segments < 2
        bool drawSegments(const cocos2d::CCPoint* points, unsigned int size, float thickness, const cocos2d::ccColor4F& color);
        /// draw a line from points[0] to points[1], then points[1] to points[2], etc...
        /// @note does nothing if segments < 2
        bool drawSegments(std::span<const cocos2d::CCPoint> points, float thickness, const cocos2d::ccColor4F& color);

        /// draw a circle at center with radius radius
        /// @param segments how many triangle "slices" the circle is made up of
        /// @note does nothing if segments < 3
        bool drawCircle(const cocos2d::CCPoint& center, float radius, const cocos2d::ccColor4F& color, unsigned int segments, float outlineThickness = 0.0f, const cocos2d::ccColor4F& outlineColor = impl::CLEAR_COLOR);
        /// draw an ellipse at center with radius radius
        /// @param segments how many triangle "slices" the circle is made up of
        /// @note does nothing if segments < 3
        bool drawEllipse(const cocos2d::CCPoint& center, cocos2d::CCSize radius, const cocos2d::ccColor4F& color, unsigned int segments, float outlineThickness = 0.0f, const cocos2d::ccColor4F& outlineColor = impl::CLEAR_COLOR);

        /// draw a polygon with points points
        /// @param points ptr to a c array of ccpoints
        /// @param size amount of points in c array
        /// @note does nothing if segments
        /// @note border alignment not impl
        /// @note calls ccdrawnode::drawPolygon internally
        bool drawPolygon(const cocos2d::CCPoint* points, unsigned int size, const cocos2d::ccColor4F& color, float outlineThickness = 0.0f, const cocos2d::ccColor4F& outlineColor = impl::CLEAR_COLOR, cocos2d::BorderAlignment = {});
        /// draw a polygon with points points
        /// @note does nothing if segments
        /// @note border alignment not impl
        /// @note calls ccdrawnode::drawPolygon internally
        bool drawPolygon(std::span<const cocos2d::CCPoint> points, const cocos2d::ccColor4F& color, float outlineThickness = 0.0f, const cocos2d::ccColor4F& outlineColor = impl::CLEAR_COLOR, cocos2d::BorderAlignment = {});

        /// draw a square with radius radius
        bool drawDot(const cocos2d::CCPoint& center, float radius, const cocos2d::ccColor4F& color);

        /// draw a rect from rect
        /// @note border alignment not impl
        bool drawRect(const cocos2d::CCRect& rect, const cocos2d::ccColor4F& color, float outlineThickness = 0.0f, const cocos2d::ccColor4F& = impl::CLEAR_COLOR, cocos2d::BorderAlignment = {});
        /// draw a rect from start to end
        /// @note border alignment not impl
        bool drawRect(const cocos2d::CCPoint& start, const cocos2d::CCPoint& end, const cocos2d::ccColor4F& color, float outlineThickness = 0.0f, const cocos2d::ccColor4F& outlineColor = impl::CLEAR_COLOR, cocos2d::BorderAlignment = {});

        /// set tint color for everything drawn
        void setTint(const cocos2d::ccColor4F& color);
        const cocos2d::ccColor4F& getTint() const;

        /// set if tint color is used
        void setUseTint(bool tint);
        bool getUseTint() const;

        /// std::vector::reserve
        void reserve(unsigned int size);
        /// std::vector::reserve(m_nBufferCount + count)
        void reserveCount(unsigned int count);
        /// reserves space for triangles and updates buffercount/dirty accordingly
        /// @returns a ptr at the end of the buffer u can write ur triangles to
        Triangle* writeTriangles(unsigned int count);
        /// reserves space for vertices and updates buffercount/dirty accordingly
        /// @returns a ptr at the end of the buffer u can write ur vertices to
        Vertex* writeVertices(unsigned int count);

        static SillyDrawNode* create();
    };
}