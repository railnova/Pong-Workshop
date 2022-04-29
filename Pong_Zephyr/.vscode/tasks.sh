#!/bin/bash

app_dir="/home/geoffrey/Documents/repos/Pong-Workshop/Pong_Zephyr/zephyr_pong/app_example"
board=nucleo_g031k8
build_dir="build_$(basename $app_dir)_$(basename $board)"

function build {
	echo "Build in progress..."
	west build -d ${build_dir} -b ${board} ${app_dir}
	echo "Build done!"
}

function clean_build {
	echo "Deleting previous build if any..."
	rm -rf ${build_dir}
	echo "Done!"
}

function flash {
	echo "Start flashing..."
	west flash -d ${build_dir}
	echo "Done!"
}

if [ -z $1 ]
then
	echo "Need one argument"
	exit -1
elif [ $1 = "build" ]
then
	build
	exit 0
elif [ $1 = "clean" ]
then
	clean_build
	exit 0
elif [ $1 = "run" ]
then
	flash
	exit 0
else
	echo "Command not found"
	exit -1
fi