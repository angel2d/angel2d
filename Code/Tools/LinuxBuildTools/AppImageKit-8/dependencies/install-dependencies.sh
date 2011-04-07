#!/bin/sh

export DIRNAME="$(dirname "$(readlink -f "${0}")")"
find "${DIRNAME}" -exec sudo dpkg -i {} \;
