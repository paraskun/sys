#!/bin/sh

src=$1

if [ -z "$src" ]
    then src="."
fi

if [ ! -d "$src" ]
    then echo "error: directory does not exists"; exit 1
fi

for dir in $(ls -d $src/*/ 2>/dev/null)
do
    if ls $dir*/ >/dev/null 2>/dev/null
        then echo $dir
    fi
done