#!/usr/bin/env bash
if [[ $1 == "" ]]; then
    echo "No new name specified."
    exit
fi
PATTERN=XXXXXXXXXXXX
FIND_ALL_FILES="find ./"
echo "Searching: ${FIND_ALL_FILES}"
ALL_FILES=`${FIND_ALL_FILES}`

for i in $ALL_FILES; do
    
    if [[ $i != ./build/* ]] && [[ $i == *${PATTERN}* ]]; then
        NEWNAME=${i/${PATTERN}/$1}
        MVCMD="mv -v ${i} ${NEWNAME}";
        echo "Need to rename ${MVCMD}";
        ${MVCMD}

    fi
done;

ALL_FILES=`find ./ -name "*"`
for i in $ALL_FILES; do
    if [[ $i != ./build* ]] && [[ $i != ./.* ]] && [[ $i != ./scripts* ]] && [[ -f $i ]]; then
        echo "Processing $i...";
        RESULT=`grep -e "${PATTERN}" $i`
        if [[ $? == 0 ]]; then
            echo "Need to rename strings in $i";
            SEDEDIT="sed -i s/${PATTERN}/$1/g $i"
            echo "SEDEDIT = ${SEDEDIT}"
            ${SEDEDIT}
        fi
    fi
done;
