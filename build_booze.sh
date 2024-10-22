#!/bin/sh
SUCCESS='\033[0;32m'
WARNING='\033[0;33m'
DC='\033[0m'

# Function to check if a package is installed
check_and_install() {
    PACKAGE=$1
    if brew list --versions $PACKAGE > /dev/null; then
        printf "${WARNING}$PACKAGE is already installed.\n${DC}"
    else
        printf "${WARNING}$PACKAGE is not installed. Installing...\n${DC}"
        brew install $PACKAGE
    fi
}

if [ "$1" == "Q" ]; then
    printf "${WARNING}"
    printf "\n=============================================\n"
    printf "============== ${DC}SKIPPING SETUP${WARNING} ===============\n"
    printf "=============================================\n"
    printf "${DC}"
else
    printf "${SUCCESS}"
    printf "\n=============================================\n"
    printf "=========== ${DC}PREPARING ENVIRONMENT${SUCCESS} ===========\n"
    printf "=============================================\n"
    printf "${DC}"

    # Check and install dependencies
    check_and_install "cmake"
    check_and_install "boost"
    check_and_install "pkg-config"
    check_and_install "gtk4"
fi

printf "${SUCCESS}"
printf "\n=============================================\n"
printf "========== ${DC}GENERATING BUILD FILES${SUCCESS} ===========\n"
printf "=============================================\n"
printf "${DC}"

cmake -S ./ -O build/

printf "${SUCCESS}"
printf "\n=============================================\n"
printf "============= ${DC}BUILDING PROJECT${SUCCESS} ==============\n"
printf "=============================================\n"
printf "${DC}"

cd build
make

printf "${SUCCESS}"
printf "\n=============================================\n"
printf "============== ${DC}BUILD FINISHED${SUCCESS} ===============\n"
printf "=============================================\n"
printf "${DC}"
