#!/usr/bin/env bash
for i in test/*.c
do
	#echo "gcc $i -o ${i%.c} -L. -lft_malloc"
	echo "\033[36m"$i" ==> OK !\033[0m"
	gcc -w "$i" -o "${i%.c}" -L. -lft_malloc
done
echo "\n\033[32m==> SUCCESS !\033[0m\n"
