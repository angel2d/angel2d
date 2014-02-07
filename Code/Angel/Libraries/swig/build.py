#!/usr/bin/env python

# Builds our local version of SWIG on Mac and Linux

import os
import sys
import subprocess
import re
import shutil

BUILD_PREFIX = "install"

def findSWIG():
    swigVerFind = re.compile(r'^swig-([0-9\.]*).tar.gz$')
    for entry in os.listdir("."):
        result = swigVerFind.search(entry)
        if result:
            return (entry, result.groups()[0])
    return None

def findPCRE():
    pcreVerFind = re.compile(r'^pcre-([0-9\.]*).tar.gz$')
    for entry in os.listdir("."):
        result = pcreVerFind.search(entry)
        if result:
            return (entry, result.groups()[0])
    return None

# goofy, but useful for debugging
def do(cmd, real=True):
    if (real == None):
        real = True
        # real = False
    if real:
        subprocess.call(cmd)
    else:
        print cmd


def clean():
    killList = [BUILD_PREFIX]
    for entry in os.listdir("."):
        if   entry.startswith("swig-") and not entry.endswith(".tar.gz"):
            killList.append(entry)
        elif entry.startswith("pcre-") and not entry.endswith(".tar.gz"):
            killList.append(entry)
    for kill in killList:
        shutil.rmtree(kill, ignore_errors=True)

def build():
    swigDist = findSWIG()
    if swigDist == None:
        sys.stderr.write("Couldn't find a SWIG distribution. :(\n")
        sys.exit(1)
    pcreDist = findPCRE()
    if pcreDist == None:
        sys.stderr.write("Couldn't find a PCRE distribution. :(\n")
        sys.exit(1)

    # unzip swig
    swigDir = "swig-%s" % (swigDist[1])
    cmd = ["tar", "xzf", swigDist[0]]
    do(cmd, True)

    # copy pcre into the swig directory
    shutil.copy(pcreDist[0], swigDir)

    # get in there
    basePath = os.path.dirname(os.path.abspath( __file__ ))
    os.chdir(swigDir)

    # do the pcre compile dance
    cmd = ["./Tools/pcre-build.sh"]
    do(cmd)

    # config
    buildPath = os.path.join(basePath, BUILD_PREFIX)
    cmd = [
        "./configure",
        "--prefix=%s" % buildPath,
    ]
    do(cmd)

    # make; install
    cmd = ["make"]
    do(cmd)
    cmd = ["make", "install"]
    do(cmd)

    # get back home
    os.chdir(basePath)

    # clean out the libs we don't need
    excess = [
        "allegrocl",
        "chicken",
        "clisp",
        "csharp",
        "d",
        "gcj",
        "go",
        "guile",
        "java",
        "modula3",
        "mzscheme",
        "ocaml",
        "octave",
        "perl5",
        "php",
        "pike",
        "python",
        "r",
        "ruby",
        "tcl",
    ]
    sharePath = os.path.join(buildPath, "share", "swig", swigDist[1])
    for extra in excess:
        shutil.rmtree(os.path.join(sharePath, extra))

    # pack it up
    instPath = os.path.join(basePath, "angelSwig")
    if not os.path.exists(instPath):
        os.mkdir(instPath)
    if sys.platform.startswith("win32"):
        platformName = "windows"
    elif sys.platform.startswith("darwin"):
        platformName = "mac"
    elif sys.platform.startswith("linux"):
        platformName = "linux"

    binPath = os.path.join(instPath, platformName)
    if not os.path.exists(binPath):
        os.mkdir(binPath)

    shutil.move(
        os.path.join(buildPath, "bin", "swig"),
        os.path.join(binPath, "swig")
    )

    libPath = os.path.join(instPath, "swiglib")
    if os.path.exists(libPath):
        shutil.rmtree(libPath, ignore_errors=True)
    shutil.move(
        os.path.join(buildPath, "share", "swig", swigDist[1]),
        os.path.join(libPath)
    )

    # clean it up
    clean()




if __name__ == '__main__':
    doClean = False
    # doClean = True
    if (len(sys.argv) > 1 and sys.argv[1] == "clean") or doClean:
        clean()
    else:
        build()
