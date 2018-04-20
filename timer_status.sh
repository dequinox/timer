#!/bin/sh

project=$1
color=""
full_text="timer status $project"
answer="$(timer status $project)"
arr=($answer)
ms=${arr[1]}
ms=$(($ms+0))

if [[ (( $ms -lt 14400000 )) ]]
then
	color="#00897B"
fi
if [[ (( $ms -lt 12600000 )) ]]
then
	color="#43A047"
fi
if [[ (( $ms -lt 10800000 )) ]]
then
	color="#7CB342"
fi
if [[ (( $ms -lt 9000000 )) ]]
then
	color="#C0CA33"
fi
if [[ (( $ms -lt 7200000 )) ]]
then 
	color="#FDD835"
fi
if [[ (( $ms -lt 5400000 )) ]]
then
	color="#FFB300"
fi
if [[ (( $ms -lt 3600000 )) ]]
then
	color="#FB8C00"
fi
if [[ (( $ms -lt 1800000 )) ]]
then
	color="#F4511E"
fi

full_text="<span background=\"$color\" font_weight=\"bold\">  ${project^^} [$ms]  </span>"
short_text="$full_text"
echo "$full_text"
echo "$short_text"
echo "#ffffff"

