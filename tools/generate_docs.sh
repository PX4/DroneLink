#!/usr/bin/env bash

# Run with argument `--skip-checks` to skip checks for clean build and removing install dir.

# exit on any error
set -e

# This script will
# 1. build and install the source,
# 2. run doxygen and create html and xml docs,
# 3. run script to generate markdown from xml

echo "Generating docs"

command -v doxygen >/dev/null 2>&1 || { echo "ERROR: 'doxygen' is required and was not found!"; exit 1; }

# Get current directory of script.
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

skip_checks=false
overwrite=false

if [ "$#" -ge 1 ]; then
    for arg in "$@"; do
        case "$arg" in
            --skip-checks)
                skip_checks=true
                ;;
            --overwrite)
                overwrite=true
                ;;
        esac
    done
fi

BUILD_DIR="${SCRIPT_DIR}/../build-docs"
INSTALL_DIR="${BUILD_DIR}/install"

if [ "$skip_checks" = false ]; then
    if [ -d ${BUILD_DIR} ] ; then
	printf "\"${BUILD_DIR}\" already exists! Aborting...\n"
	exit 1
    fi
fi

# Build and install locally.
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR} -B${BUILD_DIR} -H.
make -C${BUILD_DIR} install -j$(nproc --all)

return_result=0
# Doxygen likes to run where the source is (because INPUT in .doxygen is empty),
# so we cd there.
pushd ${INSTALL_DIR}/include/mavsdk

# If any warnings are thrown, we should not flag this as a success.
doxygen_output_file=".doxygen_output.tmp"
doxygen ${SCRIPT_DIR}/.doxygen &> $doxygen_output_file
cat $doxygen_output_file
if cat $doxygen_output_file | grep "warning" | grep -v "ignoring unsupported tag" | grep -v "operator"
then
    return_result=1
    echo "Please check doxygen warnings."
fi

# TODO (Jonas): is there a reason for generating markdown if doxygen failed above?
${SCRIPT_DIR}/generate_markdown_from_doxygen_xml.py ${INSTALL_DIR}/docs ${INSTALL_DIR}/docs
popd


if [ "$overwrite" = true ]; then
    # Clear folder first except index.md
    find ${SCRIPT_DIR}/../docs/en/cpp/api_reference/ -type f -not -name 'index.md' -delete
    cp ${INSTALL_DIR}/docs/markdown/* ${SCRIPT_DIR}/../docs/en/cpp/api_reference/
fi

exit $return_result
