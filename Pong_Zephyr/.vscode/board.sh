#!/bin/bash

vscode_pwd="$PWD/.vscode"

echo This button helps you to choose the correct board to build.

echo Type board name:
read selected_board
echo Selected board = $selected_board

sed -i 's/board=.*/board='"$selected_board"'/' $vscode_pwd/tasks.sh
sed -i 's/$(circuit-board) .*  ",/$(circuit-board) '"$selected_board"'  ",/g' $vscode_pwd/tasks.json
