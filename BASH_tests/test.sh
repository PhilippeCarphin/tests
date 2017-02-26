#!/bin/ksh

MICHAEL_JACKSON="KingOfPop"

#if [[ $MICHAEL_JACKSON == KingOfPop ]]; then
#  echo "dans le if"
#else
#  echo "dans le else"
#fi

if [ which s.jio-prof ]; then
  echo "Dans le if"
else
  echo "Dans le else"
fi
