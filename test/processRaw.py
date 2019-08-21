#!/usr/bin/env python
# Simple data extraction processing script.
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
import codecs

export = "!-->"


def seperateBencmhmark(string):
    # Find start.
    benchmarks = string.split("==Start==")
    # Find end
    for benchmark in benchmarks:
        benchmark.replace("==End==\n", "")
    return benchmarks[1:]


def translate(bench):
    # Translate into dat format.
    s = ""
    c = []
    metaPos = bench.find(export)
    meta = bench[metaPos:].replace(export, "").replace("==End==", "").split(";")
    lines = bench[0:metaPos]

    for m in meta:
        if "Scene:" in m:
            i = m.find(":")
            scene = m[i + 1:]
    return lines, meta, scene.replace("\n", "").replace(" ", "")


def main(argv):
    if len(argv) != 2:
        sys.exit(1)

    # Get file to process.
    files = [os.path.abspath(path) for path in argv[1:]]
    dir = os.path.curdir

    for file in files:
        # Get each benchmark.
        filepath = file
        header = codecs.open(filepath, 'r', encoding='utf8')
        base = os.path.basename(file)
        # Read file.
        string = header.read()

        # Get benchmarks scenes.
        benches = seperateBencmhmark(string);
        for i, bench in enumerate(benches):
            # Translate and get result
            col, result, scene = translate(bench)

            filepath = "{}/{}".format(dir, "bench_{}_{}_{}.dat".format(base, scene, i))
            finalResult = "{}/{}".format(dir, "bench_{}_{}_{}_meta_result.txt".format(base, scene, i))
            with open(filepath, 'w') as f:
                f.write(col)
            with open(finalResult, 'w') as f:
                f.write(" ".join(result))


if __name__ == '__main__':
    main(sys.argv)
