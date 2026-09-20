#pragma once

#include "editor.hpp"
#include "object.hpp"
#include "selection.hpp"
#include "constants.hpp"
#include "trigger.hpp"
#include "filter.hpp"
#include "events.hpp"

namespace nwo5::editor::prelude {
    namespace editor = nwo5::editor;
    namespace trigger = nwo5::editor::trigger;
    namespace selection = nwo5::editor::selection;
    namespace object = nwo5::editor::object;

    using editor::AUTO_CENTER;

    using editor::ObjectsSelectedEvent, editor::ObjectsDeselectedEvent, editor::ObjectsChangedEvent,
    editor::ObjectsCreatedEvent, editor::ObjectsDeletedEvent, editor::OnPlaytestEvent;
}