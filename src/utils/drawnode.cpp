#include <utils/include.hpp>

using namespace geode::prelude;

namespace nwo5::utils {
    CCGLProgram* getShaderPositionColorUColor() {
        auto cache = CCShaderCache::sharedShaderCache();

        auto program = cache->programForKey("shader-position-color-u-color"_spr);

        if (program) {
            return program;
        }

        program = new cocos2d::CCGLProgram;
        program->initWithVertexShaderByteArray( // stolen from cocos but createing tint
            "														\n\
            attribute vec4 a_position;								\n\
            attribute vec4 a_color;									\n\
            #ifdef GL_ES											\n\
            varying lowp vec4 v_fragmentColor;						\n\
            #else													\n\
            varying vec4 v_fragmentColor;							\n\
            #endif													\n\
                                                                    \n\
            void main()												\n\
            {														\n\
                gl_Position = CC_MVPMatrix * a_position;			\n\
                v_fragmentColor = a_color;							\n\
            }														\n\
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

    void SillyDrawNode::createSegment(CCPoint pStart, CCPoint pEnd, float pThickness, const ccColor4F& pColor) {
        if (pStart == pEnd || !pColor.a || !pThickness) {
            return;
        }
        
        auto ptr = writeTriangles(2 * 3);

        const auto n = ccpNormalize(ccpPerp(pEnd - pStart));
        const auto t = ccpPerp(n);

        const auto nw = n * pThickness;
        const auto tw = t * pThickness;
        const auto v0 = toVert(pEnd - (nw + tw));
        const auto v1 = toVert(pEnd + (nw - tw));
        const auto v2 = toVert(pEnd - nw);
        const auto v3 = toVert(pEnd + nw);
        const auto v4 = toVert(pStart - nw);
        const auto v5 = toVert(pStart + nw);
        const auto v6 = toVert(pStart - (nw - tw));
        const auto v7 = toVert(pStart + (nw + tw));

        const auto col = color_cast<ccColor4B>(pColor);

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
    }
    void SillyDrawNode::createLine(CCPoint pStart, CCPoint pEnd, float pThickness, const ccColor4F& pColor) {
        if (pStart == pEnd || !pColor.a || !pThickness) {
            return;
        }
        
        auto ptr = writeTriangles(2);

        const auto n = ccpNormalize(ccpPerp(ccpSub(pEnd, pStart)));
        const auto nw = ccpMult(n, pThickness);

        const auto v0 = toVert(pStart - nw);
        const auto v1 = toVert(pStart + nw);
        const auto v2 = toVert(pEnd - nw);
        const auto v3 = toVert(pEnd + nw);

        const auto col = color_cast<ccColor4B>(pColor);

        ptr[0] = {
            {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[1] = {
            {v3, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
    }
    void SillyDrawNode::createDashedLine(CCPoint pStart, CCPoint pEnd, float pThickness, const ccColor4F& pColor, float pSegmentLength, float pSegmentDotSize) {
        if (pStart == pEnd || !pColor.a || !pThickness || !pSegmentLength) {
            return;
        }

        const auto length = pStart.getDistance(pEnd);

        const unsigned int segments = std::ceil(length / pSegmentLength);
        auto ptr = writeTriangles(segments * 2);

        const auto dotSize = pSegmentLength * pSegmentDotSize;
        const auto col = color_cast<ccColor4B>(pColor);

        const auto dir = (pEnd - pStart) / length;
        const auto n = ccpPerp(dir);
        const auto nw = n * pThickness;

        size_t i = 0;
        for (int segment = 0; segment < segments; segment++) {
            const float dist = segment * pSegmentLength;

            auto start = pStart + dir * dist;
            auto end = pStart + dir * std::min(dist + dotSize, length);

            const auto v0 = toVert(start - nw);
            const auto v1 = toVert(start + nw);
            const auto v2 = toVert(end - nw);
            const auto v3 = toVert(end + nw);

            ptr[i++] = {
                {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
            ptr[i++] = {
                {v3, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
        }
    }
    void SillyDrawNode::createSegments(const CCPoint* pPoints, unsigned int pSize, float pThickness, const ccColor4F& pColor) {
        if (pSize < 2 || !pColor.a || !pThickness) {
            return;
        }

        for (size_t i = 0; i < pSize - 1; i++) {
            createSegment(pPoints[i], pPoints[i + 1], pThickness, pColor);
        }
    }
    void SillyDrawNode::createSegments(std::span<const CCPoint> pPoints, float pThickness, const ccColor4F& pColor) {
        createSegments(pPoints.data(), pPoints.size(), pThickness, pColor);
    }

    void SillyDrawNode::createCircle(CCPoint pCenter, float pRadius, const ccColor4F& pColor, unsigned int pSegments, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        createEllipse(pCenter, {pRadius, pRadius}, pColor, pSegments, pOutlineThickness, pOutlineColor);
    }
    void SillyDrawNode::createEllipse(CCPoint pCenter, CCSize pRadius, const ccColor4F& pColor, unsigned int pSegments, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        if (pSegments < 3 || pRadius == CCSizeZero) {
            return;
        }
        
        const auto fillTriangles = !pColor.a ? 0 : pSegments;
        const auto outlineTriangles = (!pOutlineThickness || !pOutlineColor.a) ? 0 : pSegments * 2;

        if (!fillTriangles && !outlineTriangles) {
            return;
        }

        auto ptr = writeTriangles(fillTriangles + outlineTriangles);

        const auto fill = color_cast<ccColor4B>(pColor);
        const auto outline = color_cast<ccColor4B>(pOutlineColor);

        const Vertex centerVertex = {
            toVert(pCenter), color_cast<ccColor4B>(fill), {}
        };

        pOutlineThickness /= 2;

        const CCSize inner = pRadius - pOutlineThickness;
        // i love cocos operators :3
        const CCSize outer = pRadius - (-pOutlineThickness);

        ccVertex2F fillStart = {pCenter.x + pRadius.width, pCenter.y};
        ccVertex2F fillEnd;

        ccVertex2F innerStart = {pCenter.x + inner.width, pCenter.y};
        ccVertex2F innerEnd;
        ccVertex2F outerStart = {pCenter.x + outer.width, pCenter.y};
        ccVertex2F outerEnd;

        const float delta = (std::numbers::pi * 2) / pSegments;

        float angle = delta;
        size_t i = 0;
        for (int segment = 0; segment < pSegments; segment++) {
            const float ca = std::cos(angle);
            const float sa = std::sin(angle);

            if (fillTriangles) {
                fillEnd = {pCenter.x + (pRadius.width * ca), pCenter.y + (pRadius.height * sa)};

                ptr[i++] = {
                    centerVertex,{fillStart, fill, {}}, {fillEnd, fill, {}}
                };

                fillStart = fillEnd;
            }

            if (outlineTriangles) {
                innerEnd = {pCenter.x + (inner.width * ca), pCenter.y + (inner.height* sa)};
                outerEnd = {pCenter.x + (outer.width * ca), pCenter.y + (outer.height * sa)};

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
    }

    void SillyDrawNode::createPolygon(const CCPoint* pPoints, unsigned int pSize, const ccColor4F& pColor, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        drawPolygon(const_cast<CCPoint*>(pPoints), pSize, pColor, pOutlineThickness, pOutlineColor);
    }
    void SillyDrawNode::createPolygon(std::span<const CCPoint> pPoints, const ccColor4F& pColor, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        createPolygon(pPoints.data(), pPoints.size(), pColor, pOutlineThickness, pOutlineColor);
    }

    void SillyDrawNode::createDot(cocos2d::CCPoint pCenter, float pRadius, const cocos2d::ccColor4F& pColor) {
        if (!pRadius) {
            return;
        }

        auto ptr = writeTriangles(2);

        pRadius /= 2;

        const auto v0 = toVert(pCenter - pRadius);
        const auto v1 = toVert(pCenter.x + pRadius, pCenter.y - pRadius);
        const auto v2 = toVert(pCenter.x - pRadius, pCenter.y + pRadius);
        const auto v3 = toVert(pCenter - (-pRadius));

        const auto col = color_cast<ccColor4B>(pColor);

        ptr[0] = {
            {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
        };
        ptr[1] = {
            {v1, col, {}}, {v3, col, {}}, {v2, col, {}}
        };
    }

    void SillyDrawNode::createRect(CCRect pRect, const ccColor4F& pColor, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        if (pRect.size == CCSizeZero) {
            return;
        }

        const auto fillTriangles = !pColor.a ? 0 : 3;
        const auto outlineTriangles = (!pOutlineThickness || !pOutlineColor.a) ? 0 : (2 * 3);

        auto ptr = writeTriangles(fillTriangles + outlineTriangles);

        const auto v0 = toVert(pRect.origin);
        const auto v1 = toVert(pRect.getMaxX(), pRect.getMinY());
        const auto v2 = toVert(pRect.getMinX(), pRect.getMaxY());
        const auto v3 = toVert(pRect.origin + pRect.size);

        size_t i = 0;
        if (fillTriangles) {
            const auto col = color_cast<ccColor4B>(pColor);
            
            ptr[i++] = {
                {v0, col, {}}, {v1, col, {}}, {v2, col, {}}
            };
            ptr[i++] = {
                {v1, col, {}}, {v3, col, {}}, {v2, col, {}}
            };
        }
        
        if (outlineTriangles) {
            const auto outlineColor = color_cast<ccColor4B>(pOutlineColor);

            ptr[i++] = {
                {v0, outlineColor, {}}, {v1, outlineColor, {}}, {{v1.x, v1.y + pOutlineThickness}, outlineColor, {}}
            };
            ptr[i++] = {
                {v0, outlineColor, {}}, {{v1.x, v1.y + pOutlineThickness}, outlineColor, {}}, {{v0.x, v0.y + pOutlineThickness}, outlineColor, {}}
            };

            ptr[i++] = {
                {{v2.x, v2.y - pOutlineThickness}, outlineColor, {}}, {{v3.x, v3.y - pOutlineThickness}, outlineColor, {}}, {v3, outlineColor, {}}
            };
            ptr[i++] = {
                {{v2.x, v2.y - pOutlineThickness}, outlineColor, {}}, {v3, outlineColor, {}}, {v2, outlineColor, {}}
            };

            ptr[i++] = {
                {{v0.x, v0.y + pOutlineThickness}, outlineColor, {}}, {{v0.x + pOutlineThickness, v0.y + pOutlineThickness}, outlineColor, {}}, {{v2.x + pOutlineThickness, v2.y - pOutlineThickness}, outlineColor, {}}
            };
            ptr[i++] = {
                {{v0.x, v0.y + pOutlineThickness}, outlineColor, {}}, {{v2.x + pOutlineThickness, v2.y - pOutlineThickness}, outlineColor, {}}, {{v2.x, v2.y - pOutlineThickness}, outlineColor, {}}
            };

            ptr[i++] = {
                {{v1.x - pOutlineThickness, v1.y + pOutlineThickness}, outlineColor, {}}, {{v1.x, v1.y + pOutlineThickness}, outlineColor, {}}, {{v3.x, v3.y - pOutlineThickness}, outlineColor, {}}
            };
            ptr[i++] = {
                {{v1.x - pOutlineThickness, v1.y + pOutlineThickness}, outlineColor, {}}, {{v3.x, v3.y - pOutlineThickness}, outlineColor, {}}, {{v3.x - pOutlineThickness, v3.y - pOutlineThickness}, outlineColor, {}}
            };
        }
    }
    void SillyDrawNode::createRect(CCPoint pStart, CCPoint pEnd, const ccColor4F& pColor, float pOutlineThickness, const ccColor4F& pOutlineColor) {
        const CCPoint min{std::min(pStart.x, pEnd.x), std::min(pStart.y, pEnd.y)};
        const CCPoint max{std::max(pStart.x, pEnd.x), std::max(pStart.y, pEnd.y)};
        
        createRect({min, max - min}, pColor, pOutlineThickness, pOutlineColor);
    }

    void SillyDrawNode::setTint(const ccColor4F& pColor) {
        m_tintColor = pColor;

        m_bDirty = true;
    }
    const ccColor4F& SillyDrawNode::getTint() const {
        return m_tintColor;
    }

    void SillyDrawNode::setUseTint(bool pTint) {
        m_useTint = pTint;

        m_bDirty = true;
    }
    bool SillyDrawNode::useTint() const {
        return m_useTint;
    }

    void SillyDrawNode::reserve(unsigned int pSize) {
        if (pSize > m_uBufferCapacity) {
            m_uBufferCapacity += std::max(m_uBufferCapacity, pSize - m_nBufferCount);
            m_pBuffer = static_cast<ccV2F_C4B_T2F*>(
                realloc(m_pBuffer, m_uBufferCapacity * sizeof(ccV2F_C4B_T2F))
            );
        }
    }
    void SillyDrawNode::reserveCount(unsigned int pCount) {
        reserve(m_nBufferCount + pCount);
    }
    SillyDrawNode::Triangle* SillyDrawNode::writeTriangles(unsigned int pCount) {
        pCount *= 3;

        reserveCount(pCount);

        auto ptr = m_pBuffer + m_nBufferCount;

        m_nBufferCount += pCount;
        m_bDirty = true;

        return reinterpret_cast<Triangle*>(ptr);
    }
    SillyDrawNode::Vertex* SillyDrawNode::writeVertices(unsigned int pCount) {
        reserveCount(pCount);
        
        auto ptr = m_pBuffer + m_nBufferCount;

        m_nBufferCount += pCount;
        m_bDirty = true;

        return reinterpret_cast<Vertex*>(ptr);
    }
}