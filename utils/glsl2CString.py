#!/usr/bin/env python
# Convert text to header files and c source file.
# Copyright (C) 2018  Valdemar Lindberg
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
import os
import sys
from os.path import isfile, join
from shutil import copyfile
import codecs

HEADERNAME = "shaders.h"
CNAME = "shaders.c"


def convert2CString(cpbuf):
    '''
    Converts text file into a c-string.
    :param cpbuf: text.
    :return: c-string text.
    :rtype str
    '''
    stringbuf = ""
    lines = cpbuf.split('\n')

    for line in lines:
        utf8line = line.decode("utf-8", "strict")
        stringbuf += "\"{}\\n\"\n".format(utf8line)

    return stringbuf[0:len(stringbuf) - 1]


def main(argv):
    if len(argv) != 2:
        sys.exit(1)

    dir = os.path.abspath(argv[1])
    print(dir)
    shadfiles = os.listdir(dir)

    #
    headpath = "./{}".format(HEADERNAME)
    cpath = "./{}".format(CNAME)

    #
    header = codecs.open(headpath, 'w', encoding='utf8')
    cfile = codecs.open(cpath, 'w', encoding='utf8')

    #
    cfile.write("#include\"shader.h\"\n")
    header.write("#ifndef _SPRITE_SHADER_\n#define _SPRITE_SHADER_ 1\n")

    # Iterate through each files.
    for file in shadfiles:
        filepath = "{}/{}".format(dir, file)
        if isfile(filepath) and file.endswith(".glsl"):
            with codecs.open(filepath, 'r', encoding='utf8') as f:
                # Convert text to c-string.
                glsl = convert2CString(f.read())
                cvariable = file.split('.')[0]
                cvariable.replace('.', '_')
                cvariable = "gc_shader_{}".format(cvariable)

                # update header.
                header.write("extern const char* {};\n".format(cvariable))

                # update c file.
                cfile.write("const char* {} = {};\n\n".format(cvariable, glsl))

                print("Converted: {}".format(filepath))

    # End header file.
    header.write("#endif")

    # Close file and flush the remaining content.
    cfile.close()
    header.close()

    # Copy file to directory.
    copyfile(headpath, "./include/{}".format(HEADERNAME))
    copyfile(cpath, "./src/{}".format(CNAME))

    print("Finish converting files from directory {} to {}:{}".format(argv[1], headpath, cpath))


if __name__ == '__main__':
    main(sys.argv)
