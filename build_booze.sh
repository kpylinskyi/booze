#!/bin/bash
# Colors
SUCCESS='\033[0;32m'
WARNING='\033[0;33m'
DC='\033[0m'

# Default variable values
version=1.0.2
output_file=""
s_setup=false
s_cmake=false
verbose=false

usage() {
    printf "${SUCCESS}"
    printf "\n\n=============================================\n"
    printf "============ ${WARNING}BOOZE BUILD SCRIPT${SUCCESS} =============\n"
    printf "=============================================\n"
    printf "\nUsage: $0 [OPTIONS]\n"
    printf "Options:\n"
    printf " -h, --help      Display this help message.\n"
    printf " -v, --version   Display script version.\n"
    printf " -E, --skip-env  Skips environment preparation.\n"
    printf " -B, --no-cmake  Skips CMake build file generation.\n"
    printf " -V, --verbose   List the names of commands with category headers while installing.\n\n"
    printf "${DC}"
}

check_and_install() {
    PACKAGE=$1
    if brew list --versions $PACKAGE > /dev/null; then
        printf "🔰 ${WARNING}$PACKAGE is already installed.\n${DC}"
    else
        printf "🔰 ${WARNING}$PACKAGE is not installed. Installing...\n${DC}"
        if [ "$verbose" = true ]; then
            brew install $PACKAGE
        else
            brew install $PACKAGE -q
        fi
    fi
}

setup(){
    printf "${SUCCESS}"
    printf "\n=============================================\n"
    printf "=========== ${DC}PREPARING ENVIRONMENT${SUCCESS} ===========\n"
    printf "=============================================\n"
    printf "${DC}"

    check_and_install "cmake"
    check_and_install "boost"
    check_and_install "pkg-config"
    check_and_install "gtk4"
    check_and_install "gtkmm4"
}

skip_setup(){
    printf "${WARNING}"
    printf "\n=============================================\n"
    printf "============== ${DC}SKIPPING SETUP${WARNING} ===============\n"
    printf "=============================================\n"
    printf "${DC}"
}

generate(){
    printf "${SUCCESS}"
    printf "\n=============================================\n"
    printf "======= ${DC}DELETING PREVIOUS BUILD FILES${SUCCESS} =======\n"
    printf "=============================================\n"
    printf "${DC}"

    rm -rf ./build/

    printf "${WARNING}✅ Previous build successfully removed. ${DC}\n"

printf "${SUCCESS}"
    printf "\n=============================================\n"
    printf "========== ${DC}GENERATING BUILD FILES${SUCCESS} ===========\n"
    printf "=============================================\n"
    printf "${DC}"

    cmake -S ./ -O build/
}

skip_generate(){
    printf "${WARNING}"
    printf "\n=============================================\n"
    printf "====== ${DC}SKIPPING GENERATING BUILD FILES${WARNING} ======\n"
    printf "=============================================\n"
    printf "${DC}"
}

build(){
    printf "${SUCCESS}"
    printf "\n=============================================\n"
    printf "============= ${DC}BUILDING PROJECT${SUCCESS} ==============\n"
    printf "=============================================\n"
    printf "${DC}"

    cd build
    make
}

while [ $# -gt 0 ]; do
    case $1 in
        -h | --help)
            usage
            exit 0
            ;;
        -v | --version)
            printf "Booze build script: $version\n"
            exit 0
            ;;
        -E* | --skip-env)
            s_setup=true
            ;;
        -B* | --no-cmake)
            s_cmake=true
            ;;
        -V* | --verbose)
            verbose=true
            ;;
        *)
            printf "Invalid option: $1" >&2
            usage
            exit 1
            ;;
    esac
    shift
done

if [ "$s_setup" = true ]; then
    skip_setup
else
    setup
fi

if [ "$s_cmake" = true ]; then
    skip_generate
else
    generate
fi

build

printf "${SUCCESS}"
printf "\n=============================================\n"
printf "============== ${DC}BUILD FINISHED${SUCCESS} ===============\n"
printf "=============================================\n"
printf "${DC}"
