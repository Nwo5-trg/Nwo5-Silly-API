#include <nodes/include.hpp>
#include <utils/include.hpp>

using namespace nwo5::utils::prelude;
using namespace geode::prelude;

namespace nwo5::nodes {
    CCGLProgram* getShaderPositionColorUColor() {
        auto cache = CCShaderCache::sharedShaderCache();

        auto program = cache->programForKey("shader-position-color-u-color"_spr);

        if (program) {
            return program;
        }

        program = new CCGLProgram;
        program->initWithVertexShaderByteArray( // stolen from cocos but createing tint
            "													\n\
            attribute vec4 a_position;							\n\
            attribute vec4 a_color;								\n\
            #ifdef GL_ES										\n\
            varying lowp vec4 v_fragmentColor;					\n\
            #else												\n\
            varying vec4 v_fragmentColor;						\n\
            #endif												\n\
                                                                \n\
            void main()											\n\
            {													\n\
                gl_Position = CC_MVPMatrix * a_position;		\n\
                v_fragmentColor = a_color;						\n\
            }													\n\
            "
            , 
            "													\n\
            #ifdef GL_ES										\n\
            precision lowp float;								\n\
            #endif												\n\
                                                                \n\
            varying vec4 v_fragmentColor;						\n\
            uniform vec4 u_tint;                                \n\
                                                                \n\
            void main()											\n\
            {													\n\
                vec4 col = v_fragmentColor * u_tint;            \n\
                gl_FragColor = vec4(col.rgb * col.a, col.a);	\n\
            }													\n\
            "
        );

        program->addAttribute("a_position", kCCVertexAttrib_Position);
        program->addAttribute("a_color", kCCVertexAttrib_Color);

        if (!program->link()) {
            log::error("silly draw node shader no link 3:");

            return nullptr;
        }

        program->updateUniforms();
        cache->addProgram(program, "shader-position-color-u-color"_spr);
        program->release();

        return program;
    }

    bool SillyDrawNode::init() {
        if (!CCDrawNode::init()) {
            return false;
        }

        setShaderProgram(getShaderPositionColorUColor());
        m_sBlendFunc = ccBlendFunc{GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
        m_bUseArea = false;

        return true;
    }
    void SillyDrawNode::draw() {
        if (!m_nBufferCount || m_useTint && !m_tintColor.a) {
            return;
        }

        CC_NODE_DRAW_SETUP();
        ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

        const auto tint = m_useTint ? m_tintColor : ccColor4F{1.0f, 1.0f, 1.0f, 1.0f};

        getShaderProgram()->setUniformLocationWith4f(
            getShaderProgram()->getUniformLocationForName("u_tint"),
            tint.r, tint.g, tint.b, tint.a
        );
    
        // render is inlined on some platforms i think so
        if (m_bDirty) {
            glBindBuffer(GL_ARRAY_BUFFER, m_uVbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(ccV2F_C4B_T2F) * m_uBufferCapacity, m_pBuffer, GL_STREAM_DRAW);

            m_bDirty = false;
        }

        #if CC_TEXTURE_ATLAS_USE_VAO
            ccGLBindVAO(m_uVao);
        #else
            ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
            glBindBuffer(GL_ARRAY_BUFFER, m_uVbo);

            glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), reinterpret_cast<GLvoid*>(offsetof(ccV2F_C4B_T2F, vertices)));
            glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ccV2F_C4B_T2F), reinterpret_cast<GLvoid*>(offsetof(ccV2F_C4B_T2F, colors)));
            glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ccV2F_C4B_T2F), reinterpret_cast<GLvoid*>(offsetof(ccV2F_C4B_T2F, texCoords)));
        #endif

        glDrawArrays(GL_TRIANGLES, 0, m_nBufferCount);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // doesnt seem to do anything but wtv
        CHECK_GL_ERROR_DEBUG();
    }

    bool SillyDrawNode::drawSegment(const CCPoint& start, const CCPoint& end, float thickness, const ccColor4F& color) {
        if (start == end || !color.a || !thickness) {
            return false;
        }
        
        auto ptr = writeTriangles(2 * 3);

        const auto n = ccpNormalize(ccpPerp(end - start));
        const auto t = ccpPerp(n);

        const auto nw = n * thickness;
        const auto tw = t * thickness;
        const auto v0 = toVert(end - (nw + tw));
        const auto v1 = toVert(end + (nw - tw));
        const auto v2 = toVert(end - nw);
        const auto v3 = toVert(end + nw);
        const auto v4 = toVert(start - nw);
        const auto v5 = toVert(start + nw);
        const auto v6 = toVert(start - (nw - tw));
        const auto v7 = toVert(start + (nw + tw));

        const auto col = color_cast<ccColor4B>(color);

        ptr[0] = {
            {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[1] = {
            {v3, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[2] = {
            {v3, col, {}}, {v4, col, {}}, {v2, col, {}}
        };
        ptr[3] = {
            {v3, col, {}}, {v4, col, {}}, {v5, col, {}}
        };
        ptr[4] = {
            {v6, col, {}}, {v4, col, {}}, {v5, col, {}}
        };
        ptr[5] = {
            {v6, col, {}}, {v7, col, {}}, {v5, col, {}}
        };

        return true;
    }
    bool SillyDrawNode::drawLine(const CCPoint& start, const CCPoint& end, float thickness, const ccColor4F& color) {
        if (start == end || !color.a || !thickness) {
            return false;
        }
        
        auto ptr = writeTriangles(2);

        const auto n = ccpNormalize(ccpPerp(ccpSub(end, start)));
        const auto nw = ccpMult(n, thickness);

        const auto v0 = toVert(start - nw);
        const auto v1 = toVert(start + nw);
        const auto v2 = toVert(end - nw);
        const auto v3 = toVert(end + nw);

        const auto col = color_cast<ccColor4B>(color);

        ptr[0] = {
            {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[1] = {
            {v3, col, {}}, {v1, col, {}}, {v2, col, {}}
        };

        return true;
    }
    bool SillyDrawNode::drawDashedLine(const CCPoint& start, const CCPoint& end, float thickness, const ccColor4F& color, float segmentLength, float segmentDotSize) {
        if (start == end || !color.a || !thickness || !segmentLength) {
            return false;
        }

        const auto length = start.getDistance(end);

        const unsigned int segments = std::ceil(length / segmentLength);
        auto ptr = writeTriangles(segments * 2);

        const auto dotSize = segmentLength * segmentDotSize;
        const auto col = color_cast<ccColor4B>(color);

        const auto dir = (end - start) / length;
        const auto n = ccpPerp(dir);
        const auto nw = n * thickness;

        size_t i = 0;
        for (int segment = 0; segment < segments; segment++) {
            const float dist = segment * segmentLength;

            const auto lineStart = start + dir * dist;
            const auto lineEnd = start + dir * std::min(dist + dotSize, length);

            const auto v0 = toVert(lineStart - nw);
            const auto v1 = toVert(lineStart + nw);
            const auto v2 = toVert(lineEnd - nw);
            const auto v3 = toVert(lineEnd + nw);

            ptr[i++] = {
                {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
            ptr[i++] = {
                {v3, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
        }

        return true;
    }
    bool SillyDrawNode::drawSegments(const CCPoint* points, unsigned int size, float thickness, const ccColor4F& color) {
        if (size < 2 || !color.a || !thickness) {
            return false;
        }

        for (size_t i = 0; i < size - 1; i++) {
            drawSegment(points[i], points[i + 1], thickness, color);
        }
        
        return true;
    }
    bool SillyDrawNode::drawSegments(std::span<const CCPoint> points, float thickness, const ccColor4F& color) {
        return drawSegments(points.data(), points.size(), thickness, color);
    }

    bool SillyDrawNode::drawCircle(const CCPoint& center, float radius, const ccColor4F& color, unsigned int segments, float outlineThickness, const ccColor4F& outlineColor) {
        return drawEllipse(center, {radius, radius}, color, segments, outlineThickness, outlineColor);
    }
    bool SillyDrawNode::drawEllipse(const CCPoint& center, CCSize radius, const ccColor4F& color, unsigned int segments, float outlineThickness, const ccColor4F& outlineColor) {
        if (segments < 3 || radius == CCSizeZero) {
            return false;
        }
        
        const auto fillTriangles = !color.a ? 0 : segments;
        const auto outlineTriangles = (!outlineThickness || !outlineColor.a) ? 0 : segments * 2;

        if (!fillTriangles && !outlineTriangles) {
            return false;
        }

        auto ptr = writeTriangles(fillTriangles + outlineTriangles);

        const auto fill = color_cast<ccColor4B>(color);
        const auto outline = color_cast<ccColor4B>(outlineColor);

        const Vertex centerVertex = {
            toVert(center), color_cast<ccColor4B>(fill), {}
        };

        const CCSize inner = radius - outlineThickness;
        // i love cocos operators :3
        const CCSize outer = radius - (-outlineThickness);

        ccVertex2F fillStart = {center.x + radius.width, center.y};
        ccVertex2F fillEnd;

        ccVertex2F innerStart = {center.x + inner.width, center.y};
        ccVertex2F innerEnd;
        ccVertex2F outerStart = {center.x + outer.width, center.y};
        ccVertex2F outerEnd;

        const float delta = (std::numbers::pi * 2) / segments;

        float angle = delta;
        size_t i = 0;
        for (int segment = 0; segment < segments; segment++) {
            const float ca = std::cos(angle);
            const float sa = std::sin(angle);

            if (fillTriangles) {
                fillEnd = {center.x + (radius.width * ca), center.y + (radius.height * sa)};

                ptr[i++] = {
                    centerVertex,{fillStart, fill, {}}, {fillEnd, fill, {}}
                };

                fillStart = fillEnd;
            }

            if (outlineTriangles) {
                innerEnd = {center.x + (inner.width * ca), center.y + (inner.height* sa)};
                outerEnd = {center.x + (outer.width * ca), center.y + (outer.height * sa)};

                ptr[i++] = {
                    {outerStart, outline, {}}, {innerStart, outline, {}}, {innerEnd, outline, {}}
                };
                ptr[i++] = {
                    {outerStart, outline, {}}, {innerEnd, outline, {}}, {outerEnd, outline, {}}
                };

                innerStart = innerEnd;
                outerStart = outerEnd;
            }

            angle += delta;
        }

        return true;
    }

    bool SillyDrawNode::drawPolygon(const CCPoint* points, unsigned int size, const ccColor4F& color, float outlineThickness, const ccColor4F& outlineColor, cocos2d::BorderAlignment) {
        return CCDrawNode::drawPolygon(const_cast<CCPoint*>(points), size, color, outlineThickness, outlineColor, {});
    }
    bool SillyDrawNode::drawPolygon(std::span<const CCPoint> points, const ccColor4F& color, float outlineThickness, const ccColor4F& outlineColor, cocos2d::BorderAlignment) {
        return CCDrawNode::drawPolygon(const_cast<CCPoint*>(points.data()), points.size(), color, outlineThickness, outlineColor, {});
    }

    bool SillyDrawNode::drawDot(const CCPoint& center, float radius, const ccColor4F& color) {
        if (!radius) {
            return false;
        }

        auto ptr = writeTriangles(2);

        const auto v0 = toVert(center - radius);
        const auto v1 = toVert(center.x + radius, center.y - radius);
        const auto v2 = toVert(center.x - radius, center.y + radius);
        const auto v3 = toVert(center - (-radius));

        const auto col = color_cast<ccColor4B>(color);

        ptr[0] = {
            {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[1] = {
            {v1, col, {}}, {v3, col, {}}, {v2, col, {}}
        };

        return true;
    }

    bool SillyDrawNode::drawRect(const CCRect& rect, const ccColor4F& color, float outlineThickness, const ccColor4F& outlineColor, cocos2d::BorderAlignment) {
        if (rect.size == CCSizeZero) {
            return false;
        }

        const auto fillTriangles = !color.a ? 0 : 2;
        const auto outlineTriangles = (!outlineThickness || !outlineColor.a) ? 0 : (2 * 4);

        if (!fillTriangles && !outlineTriangles) {
            return false;
        }

        auto ptr = writeTriangles(fillTriangles + outlineTriangles);

        const auto v0 = toVert(rect.origin);
        const auto v1 = toVert(rect.getMaxX(), rect.getMinY());
        const auto v2 = toVert(rect.getMinX(), rect.getMaxY());
        const auto v3 = toVert(rect.origin + rect.size);

        size_t i = 0;
        if (fillTriangles) {
            const auto col = color_cast<ccColor4B>(color);
            
            ptr[i++] = {
                {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
            ptr[i++] = {
                {v1, col, {}}, {v3, col, {}}, {v2, col, {}}
            };
        }
        
        if (outlineTriangles) {
            const auto outlineColor4b = color_cast<ccColor4B>(outlineColor);

            ptr[i++] = {
                {{v0.x - outlineThickness, v0.y - outlineThickness}, outlineColor4b, {}}, {{v1.x + outlineThickness, v1.y - outlineThickness}, outlineColor4b, {}}, {{v1.x + outlineThickness, v1.y + outlineThickness}, outlineColor4b, {}}
            };
            ptr[i++] = {
                {{v0.x - outlineThickness, v0.y - outlineThickness}, outlineColor4b, {}}, {{v1.x + outlineThickness, v1.y + outlineThickness}, outlineColor4b, {}}, {{v0.x - outlineThickness, v0.y + outlineThickness}, outlineColor4b, {}}
            };

            ptr[i++] = {
                {{v2.x - outlineThickness, v2.y - outlineThickness}, outlineColor4b, {}}, {{v3.x + outlineThickness, v3.y - outlineThickness}, outlineColor4b, {}}, {{v3.x + outlineThickness, v3.y + outlineThickness}, outlineColor4b, {}}
            };
            ptr[i++] = {
                {{v2.x - outlineThickness, v2.y - outlineThickness}, outlineColor4b, {}}, {{v3.x + outlineThickness, v3.y + outlineThickness}, outlineColor4b, {}}, {{v2.x - outlineThickness, v2.y + outlineThickness}, outlineColor4b, {}}
            };

            ptr[i++] = {
                {{v0.x - outlineThickness, v0.y - outlineThickness}, outlineColor4b, {}}, {{v0.x + outlineThickness, v0.y - outlineThickness}, outlineColor4b, {}}, {{v2.x + outlineThickness, v2.y + outlineThickness}, outlineColor4b, {}}
            };
            ptr[i++] = {
                {{v0.x - outlineThickness, v0.y - outlineThickness}, outlineColor4b, {}}, {{v2.x + outlineThickness, v2.y + outlineThickness}, outlineColor4b, {}}, {{v2.x - outlineThickness, v2.y + outlineThickness}, outlineColor4b, {}}
            };

            ptr[i++] = {
                {{v1.x - outlineThickness, v1.y - outlineThickness}, outlineColor4b, {}}, {{v1.x + outlineThickness, v1.y - outlineThickness}, outlineColor4b, {}}, {{v3.x + outlineThickness, v3.y + outlineThickness}, outlineColor4b, {}}
            };
            ptr[i++] = {
                {{v1.x - outlineThickness, v1.y - outlineThickness}, outlineColor4b, {}}, {{v3.x + outlineThickness, v3.y + outlineThickness}, outlineColor4b, {}}, {{v3.x - outlineThickness, v3.y + outlineThickness}, outlineColor4b, {}}
            };
        }

        return true;
    }
    bool SillyDrawNode::drawRect(const CCPoint& start, const CCPoint& end, const ccColor4F& color, float outlineThickness, const ccColor4F& outlineColor, cocos2d::BorderAlignment) {
        const CCPoint min{std::min(start.x, end.x), std::min(start.y, end.y)};
        const CCPoint max{std::max(start.x, end.x), std::max(start.y, end.y)};
        
        return drawRect({min, max - min}, color, outlineThickness, outlineColor);
    }

    void SillyDrawNode::setTint(const ccColor4F& color) {
        m_tintColor = color;

        m_bDirty = true;
    }
    const ccColor4F& SillyDrawNode::getTint() const {
        return m_tintColor;
    }

    void SillyDrawNode::setUseTint(bool tint) {
        m_useTint = tint;

        m_bDirty = true;
    }
    bool SillyDrawNode::getUseTint() const {
        return m_useTint;
    }

    void SillyDrawNode::reserve(unsigned int size) {
        if (size > m_uBufferCapacity) {
            m_uBufferCapacity += std::max(m_uBufferCapacity, size - m_nBufferCount);
            m_pBuffer = static_cast<ccV2F_C4B_T2F*>(
                realloc(m_pBuffer, m_uBufferCapacity * sizeof(ccV2F_C4B_T2F))
            );
        }
    }
    void SillyDrawNode::reserveCount(unsigned int count) {
        reserve(m_nBufferCount + count);
    }
    SillyDrawNode::Triangle* SillyDrawNode::writeTriangles(unsigned int count) {
        count *= 3;

        reserveCount(count);

        auto ptr = m_pBuffer + m_nBufferCount;

        m_nBufferCount += count;
        m_bDirty = true;

        return reinterpret_cast<Triangle*>(ptr);
    }
    SillyDrawNode::Vertex* SillyDrawNode::writeVertices(unsigned int count) {
        reserveCount(count);
        
        auto ptr = m_pBuffer + m_nBufferCount;

        m_nBufferCount += count;
        m_bDirty = true;

        return reinterpret_cast<Vertex*>(ptr);
    }

    SillyDrawNode* SillyDrawNode::create() {
        auto ret = new SillyDrawNode;

        if (!ret->init()) {
            delete ret;

            return nullptr;
        }

        ret->autorelease();

        return ret;
    }
}