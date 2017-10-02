#!/usr/bin/env bash
for i in test/*.c
do
	echo "gcc $i -o ${i%.c} -L. -lft_malloc"
	gcc "$i" -o "${i%.c}" -L. -lft_malloc
done
