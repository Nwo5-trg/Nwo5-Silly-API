# stuff i can (should) do whenever
- fix next free group id or just remove it

# changes to make in 2.209
- rewrite edit button tab api (prolly make it its own namespace)
- view tab button api
- make setting categories actually have ids
- make saved setting event final
- separate query into its own file
- change nwo5 namespace to fei
- change createObject functions to just be create
- remove deprecated functions
- make all the trigger/editor constants inline constexpr
- rename object_ids to max_object_id
- finish trigger sprite colors and make a getter specifically for sprite color instead of weirdly mixing color/sprite color in trigger
- make custom nodes their own namespace (tooltip, drawnode, etc...) and also m_impl all of the old ones
- rename drawnode use tint to getUseTint
- rename tooltip isdynamicanchor to getUseDynamicAnchor
- make the selection get ccarray overloads check for m_selectedObject/m_selectedObjects instead of trusting robtop function cuz it doesnt work for orange teleportals !
- make geode prefixed functions in ui node to make all the circle buttons