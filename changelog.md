## v1.5.1
**Fixed**

- added node ids dependency cuz lowk edit tab buttons depends on it but also kinda works without it
- editor::trigger issues 

## v1.5.0
**Added**

- a couple editor functions
- some documentation for editor funcs

**Fixed**

- fix a silly with get chroma when only including color.hpp
- some changelog typos
- setup id formating overload
- constexpr enum_cast

**Internal**

- added a lil python script for setting cache

## v1.4.1
fucked up the version oops

## v1.4.0
**Added**

- hsv/rgb utils !

**Fixed**

- defaults for ui::menu layout overload for it to make a bit more sense

## v1.3.0
**Added**

- a few more functions to setup
- disable ignore anchor for position for ccmenus/cclayers when setting anchor point with setup
- fixed togglewithcallback for togglers
- some more editor viewport utils
- silly draw node
- more editor initialized function
- editor tab button reload

**Fixed**

- numtostring rounding again
- setting cache again

**Removed**

- deprecated setupnode and some misc utils functions (still usable but will be removed when sillyedit is fully updated)

## v1.2.1
**Added**

- readme ui thing

**Fixed**

- fuck windows (im js stupid)

## v1.2.0
**Added**

- ui namespace (u can still in include old bad setup node stuff in nwo5::utils::setup)
- reorganized namespaces
- color/enum_cast

**Fixed**

- numtostring rounding
- some editor functions not being available in editorui::init
- made span ptrs const

## v1.1.0
**Added** 

- mod specific settings
- a bunch of trigger utils
- make (some) editor functions safer (remind me to do this for more of them)
- templated easing functions and made them copy cocos easing functions
- array utils rework
- renamed category decl macro
- some more editor color utils
- better edit highway robbery
- conditional editor tab button function

**Fixed** 

- editor tab buttons
- update editor updating duration lines
- str count
- editor::selection::get
- category macro

## v1.0.0
- initial release