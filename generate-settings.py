# i tried my best ok im a cpp dev not a python one but i wanted to try it out
#
# using:
# its pretty simple u just have to pass the path to ur mod.json
# optionally u can also pass a "reference" header file if u already have settings cache for some of ur mods settings
# the only flag u can pass rn is -t which tries to shorten variable names that are prefixed with a title name
#
# limitations rn: (ill fix atleast some of these in the future)
# - expects key to be in kebab-case and mod.json to be valid
# - expects mod.json to be valid
# - uses 4 spaces for indenting and indents every setting
# - brace initailizes settings
# - expects using namespace nwo5::settings::prelude
# - adds cocos2d:: infront of cocos types

import argparse
import json

from pathlib import Path

def find_settings_namespace(start: str) -> str | None:
    i = start.find("namespace settings {")

    if i == -1:
        i = start.find("namespace Settings {")

    return i + len("namespace Settings {") if i != -1 else None

DUMB_STUPID_GLOBAL_MAP_BECAUSE_PYTHON_DOESNT_HAVE_STATIC_VARIABLES = {
    "string": "std::string",
    "file": "std::filesystem::path",
    "color": "cocos2d::ccColor3B",
    "rgb": "cocos2d::ccColor3B",
    "rgba": "cocos2d::ccColor4B"
}
def setting_type_to_cpp(setting_type: str) -> str:
    return DUMB_STUPID_GLOBAL_MAP_BECAUSE_PYTHON_DOESNT_HAVE_STATIC_VARIABLES.get(setting_type, setting_type)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-t", "--trim",
        action="store_true",
        help="trim title suffixes from variable names, takes title if rawr-silly-setting is under title rawr, variable name will become sillySetting instead of rawrSillySetting"
    )
    parser.add_argument(
        "mod_json_path",
        type=Path,
    )
    parser.add_argument(
        "reference_path",
        type=Path,
        nargs="?",
        help="reference an existing settings file as a base"
    )
    args = parser.parse_args()

    should_trim: bool = args.trim
    mod_json: Path = args.mod_json_path
    reference: Path = args.reference_path

    IS_REFERENCING = (reference is not None) and reference.exists()

    if not mod_json.exists():
        print("invalid mod.json")

        return

    try:
        # json.load js wasnt "compiling" so i did this wtv
        json_obj = json.loads(mod_json.read_text())
    except json.JSONDecodeError:
        print("invalid mod.json")

        return

    out = reference.read_text() if IS_REFERENCING else """\
#pragma once

#include <nwo5.silly-api/include/settings/include.hpp>

using namespace nwo5::settings::prelude;

namespace Settings {
}
"""

    settings = json_obj.get("settings", {})

    i = find_settings_namespace(out)
    if i is None:
        print("invalid reference")

        return

    current_title: str | None = None
    for key, setting in settings.items():
        if should_trim and (current_title is not None):
            REPLACE_STRING = f"{current_title.lower()}-"

            if key.startswith(REPLACE_STRING):
                key = key.replace(REPLACE_STRING, "")

        SETTING_TYPE = setting_type_to_cpp(setting["type"])

        if SETTING_TYPE == "title":
            if current_title is not None:
                out = out[:i] + '\n' + out[i:]
                i += 1
                
            current_title = setting["name"]

            continue
        elif IS_REFERENCING and (find_res := out.find(key)) != -1:
            # its like wtv girl
            i = find_res + len(key) + len("\"};")

            continue
        elif SETTING_TYPE == "keybind":
            continue
        elif "custom" in SETTING_TYPE:
            continue

        SETTING_NAME = key[:1].lower() + (key.title().replace("-", ""))[1:]
        SETTING_STRING = f"\n    inline Setting<{SETTING_TYPE}> {SETTING_NAME}{{\"{key}\"}};"

        out = out[:i] + SETTING_STRING + out[i:]
        i += len(SETTING_STRING)

    print(f"\n{out}")
    
    return

if __name__ == "__main__":
    main()