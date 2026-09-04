#pragma once

#include "../export.hpp"
#include "color.hpp"

// the enum stuff is mainly template fun not rly for actual usage cuz of intellisense
namespace nwo5::utils {
    namespace impl {
        template<cocos2d::ccColor4B RGB>
        struct ColBase {
            constexpr auto operator*() const {
                return to3B();
            }
            
            template<IsColorHSV T>
            constexpr auto to() const {
                return color_cast<T>(RGB);
            }
            constexpr auto to3B() const {
                return color_cast<cocos2d::ccColor3B>(RGB);
            }
            constexpr operator cocos2d::ccColor3B() const {
                return to3B();
            }
            constexpr auto to4B() const {
                return color_cast<cocos2d::ccColor4B>(RGB);
            }
            constexpr operator cocos2d::ccColor4B() const {
                return to4B();
            }
            constexpr auto to4F() const {
                return color_cast<cocos2d::ccColor4F>(RGB);
            }
            constexpr operator cocos2d::ccColor4F() const {
                return to4F();
            }
            constexpr auto toHSV() const {
                return color_cast<SillyHSV>(RGB);
            }
            constexpr operator SillyHSV() const {
                return toHSV();
            }
        };
    }

    struct Col {
        static constexpr impl::ColBase<{ 0, 0, 0, 0 }> Clear;
        static constexpr impl::ColBase<{ 0, 0, 0, 255 }> Black;
        static constexpr impl::ColBase<{ 255, 255, 255, 255 }> White;
        static constexpr impl::ColBase<{ 100, 63, 50, 255 }> Brown;
        static constexpr struct : impl::ColBase<{ 166, 166, 166, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Gray;
            }
            constexpr operator geode::AccountBaseColor() const {
                return geode::AccountBaseColor::Gray;
            }
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Gray;
            }
        } Gray;
        static constexpr impl::ColBase<{ 200, 200, 200, 255 }> LightGray;
        static constexpr struct : impl::ColBase<{ 255, 0, 0, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::DarkGray;
            }
        } DarkGray;
        static constexpr struct : impl::ColBase<{ 255, 0, 0, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Red;
            }
        } Red;
        static constexpr struct : impl::ColBase<{ 255, 127, 0, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Orange;
            }
        } Orange;
        static constexpr struct : impl::ColBase<{ 255, 150, 127, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Salmon;
            }
        } Salmon;
        static constexpr impl::ColBase<{ 255, 255, 0, 255 }> Yellow;
        static constexpr struct : impl::ColBase<{ 0, 255, 0, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Green;
            }
            constexpr operator geode::CrossBaseColor() const {
                return geode::CrossBaseColor::Green;
            }
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Green;
            }
            constexpr operator geode::CategoryBaseColor() const {
                return geode::CategoryBaseColor::Green;
            }
        } Green;
        static constexpr struct : impl::ColBase<{ 63, 255, 63, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::BrightGreen;
            }
        } BrightGreen;
        static constexpr struct : impl::ColBase<{ 0, 192, 0, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::DimGreen;
            }
        } DimGreen;
        static constexpr struct : impl::ColBase<{ 0, 200, 192, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Teal;
            }
        } Teal;
        static constexpr struct : impl::ColBase<{ 100, 192, 255, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::LightBlue;
            }
        } LightBlue;
        static constexpr struct : impl::ColBase<{ 0, 200, 255, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Cyan;
            }
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Cyan;
            }
        } Cyan;
        static constexpr struct : impl::ColBase<{ 127, 150, 255, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Aqua;
            }
        } Aqua;
        static constexpr struct : impl::ColBase<{ 0, 0, 255, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Blue;
            }
            constexpr operator geode::AccountBaseColor() const {
                return geode::AccountBaseColor::Blue;
            }
            constexpr operator geode::LeaderboardBaseColor() const {
                return geode::LeaderboardBaseColor::Blue;
            }
        } Blue;
        static constexpr struct : impl::ColBase<{ 50, 80, 100, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::DarkAqua;
            }
        } DarkAqua;
        static constexpr struct : impl::ColBase<{ 200, 63, 255, 255 }> {
            constexpr operator geode::AccountBaseColor() const {
                return geode::AccountBaseColor::Purple;
            }
        } Purple;
        static constexpr struct : impl::ColBase<{ 80, 63, 80, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::DarkPurple;
            }
        } DarkPurple;
        static constexpr struct : impl::ColBase<{ 255, 100, 255, 255 }> {
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Magenta;
            }
        } Magenta;
        static constexpr struct : impl::ColBase<{ 255, 150, 200, 255 }> {
            constexpr operator geode::CircleBaseColor() const {
                return geode::CircleBaseColor::Pink;
            }
            constexpr operator geode::EditorBaseColor() const {
                return geode::EditorBaseColor::Pink;
            }
        } Pink;
    };
}