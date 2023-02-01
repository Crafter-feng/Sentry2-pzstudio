/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 #!/usr/bin/env python

# This pre-processor parses provided objects' c files for
# MP_REGISTER_MODULE(module_name, obj_module, enabled_define)
# These are used to generate a header with the required entries for
# "mp_rom_map_elem_t mp_builtin_module_table[]" in py/objmodule.c

from __future__ import print_function

import re
import io
import os
import argparse


pattern = re.compile(r"[\n;]\s*MP_REGISTER_MODULE\((.*?),\s*(.*?),\s*(.*?)\);", flags=re.DOTALL)


def find_c_file(obj_file, vpath):
    """Search vpaths for the c file that matches the provided object_file.

    :param str obj_file: object file to find the matching c file for
    :param List[str] vpath: List of base paths, similar to gcc vpath
    :return: str path to c file or None
    """
    c_file = None
    relative_c_file = os.path.splitext(obj_file)[0] + ".c"
    relative_c_file = relative_c_file.lstrip("/\\")
    for p in vpath:
        possible_c_file = os.path.join(p, relative_c_file)
        if os.path.exists(possible_c_file):
            c_file = possible_c_file
            break

    return c_file


def find_module_registrations(c_file):
    """Find any MP_REGISTER_MODULE definitions in the provided c file.

    :param str c_file: path to c file to check
    :return: List[(module_name, obj_module, enabled_define)]
    """
    global pattern

    if c_file is None:
        # No c file to match the object file, skip
        return set()

    with io.open(c_file, encoding="utf-8") as c_file_obj:
        return set(re.findall(pattern, c_file_obj.read()))


def generate_module_table_header(modules):
    """Generate header with module table entries for builtin modules.

    :param List[(module_name, obj_module, enabled_define)] modules: module defs
    :return: None
    """

    # Print header file for all external modules.
    mod_defs = []
    print("// Automatically generated by makemoduledefs.py.\n")
    for module_name, obj_module, enabled_define in modules:
        mod_def = "MODULE_DEF_{}".format(module_name.upper())
        mod_defs.append(mod_def)
        print(
            (
                "#if ({enabled_define})\n"
                "    extern const struct _mp_obj_module_t {obj_module};\n"
                "    #define {mod_def} {{ MP_ROM_QSTR({module_name}), MP_ROM_PTR(&{obj_module}) }},\n"
                "#else\n"
                "    #define {mod_def}\n"
                "#endif\n"
            ).format(
                module_name=module_name,
                obj_module=obj_module,
                enabled_define=enabled_define,
                mod_def=mod_def,
            )
        )

    print("\n#define MICROPY_REGISTERED_MODULES \\")

    for mod_def in mod_defs:
        print("    {mod_def} \\".format(mod_def=mod_def))

    print("// MICROPY_REGISTERED_MODULES")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--vpath", default=".", help="comma separated list of folders to search for c files in"
    )
    parser.add_argument("files", nargs="*", help="list of c files to search")
    args = parser.parse_args()

    vpath = [p.strip() for p in args.vpath.split(",")]

    modules = set()
    for obj_file in args.files:
        c_file = find_c_file(obj_file, vpath)
        modules |= find_module_registrations(c_file)

    generate_module_table_header(sorted(modules))


if __name__ == "__main__":
    main()
