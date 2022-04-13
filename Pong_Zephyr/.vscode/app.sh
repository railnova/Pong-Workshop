#!/bin/bash

vscode_pwd="$PWD/.vscode"

echo This button helps you to choose the correct app to build.

let "deep=0"
while :
do
	echo Choose your app:
	let "index=1"
	echo 0 - ..
	cd zephyr_pong/
	for d in */ ; do
		if [[ -d $d && ! "$d" == build_* && ! "$d" == oas* && ! "$d" == tools* ]] ; then
			arr[$index]=${d%/*}
			echo $index - ${arr[$index]}
			let "index+=1"
		fi
	done

	echo Enter the selected app or directory number then press enter.
	read app_num

	re='^[0-9]+$'
	if ! [[ $app_num =~ $re ]] ; then
		echo "error: Not a number" >&2;
		continue
	fi

	if (( $app_num >= $index )) ; then
		echo Choice: $app_num is equal or greater than maximum value
		continue
	fi

	if [ $app_num = 0 ]
	then
		if [ $deep = 0 ]
		then
			echo You can\'t back here
		else
			let "deep=deep-1"
			cd ..
		fi
	else
		let "deep=deep+1"
		cd ${arr[$app_num]}
		if [[ -e CMakeLists.txt ]]
		then
			app_pwd=$PWD
			break;
		fi
	fi
done

app_line=$(grep -oEi "set\(APP_NAME \"(.*)\"" $app_pwd/CMakeLists.txt)
app_name=$(echo $app_line | sed -E 's/set\(APP_NAME \"(.*)\"/\1/' )

app_pwd="${app_pwd//\//\\/}"

sed -i 's/app_dir=\".*/app_dir="'"$app_pwd"'"/' $vscode_pwd/tasks.sh
sed -i 's/$(settings) .*  ",/$(settings) '"${arr[$app_num]}"'  ",/g' $vscode_pwd/tasks.json
