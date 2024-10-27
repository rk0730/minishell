#!/bin/bash

# -=-=-=-=-	CLRS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_COLOR='\033[0;39m'
BLACK='\033[0;30m'
RED='\033[1;91m'
GREEN='\033[1;92m'
YELLOW='\033[0;93m'
BLUE='\033[0;94m'
MAGENTA='\033[0;95m'
CYAN='\033[0;96m'
GRAY='\033[0;90m'
WHITE='\033[0;97m'

printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};
printf ${YELLOW}"\n\t\tTEST CREATED BY: "${DEF_COLOR};
printf ${CYAN}"GEMARTIN\t\n"${DEF_COLOR};
printf ${BLUE}"\n-------------------------------------------------------------\n"${DEF_COLOR};

rm -rf traces.txt
rm -rf 0

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --sim-hints=lax-ioctls ./ft_fractal bonus 3 2
EXECUTE_FILE="../minishell"

R=$(valgrind --log-fd=1 $EXECUTE_FILE  | ls | grep -Ec 'no leaks are possible|ERROR SUMMARY: 0')
if [[ $R == 2 ]]; then
  printf "${GREEN}[MOK] ${DEF_COLOR}\n";
else
  printf "${RED} [KO LEAKS] ${DEF_COLOR}\n";
fi
