#!/bin/sh
GREEN='\033[0;32m'
DC='\033[0m'

printf "${GREEN}\n"
printf "=============================================\n"
printf "=========== ${DC}PREPARING ENVIRONMENT${GREEN} ===========\n"
printf "=============================================\n"
printf "${DC}\n"

brew install cmake boost nlohmann-json

printf "${GREEN}\n"
printf "=============================================\n"
printf "========== ${DC}GENERATING BUILD FILES${GREEN} ===========\n"
printf "=============================================\n"
printf "${DC}\n"

cmake -S ./ -O build/

printf "${GREEN}\n"
printf "=============================================\n"
printf "============= ${DC}BUILDING PROJECT${GREEN} ==============\n"
printf "=============================================\n"
printf "${DC}\n"

cd build
make

printf "${GREEN}\n"
printf "=============================================\n"
printf "============== ${DC}BUILD FINISHED${GREEN} ===============\n"
printf "=============================================\n"
printf "${DC}"
