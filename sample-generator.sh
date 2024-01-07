#!/bin/bash

# 引数の検証
if [ "$#" -ne 1 ] || ! [[ "$1" =~ ^[1-9][0-9]*$ ]]; then
    echo "無効な引数です。0より大きい整数を1つ入力してください。"
    exit 1
fi

# 入力の取得
N=$1
range=100

# 利用した組み合わせを保持する配列
used_combinations=()

# N個の列を出力
for ((i = 1; i <= N; i++)); do
    # ランダムな整数a
    a=$((RANDOM % range + 1))
    
    # ランダムな整数b（aとは異なる値）
    while true; do
        b=$((RANDOM % range + 1))
        if [ "$a" -ne "$b" ]; then
            break
        fi
    done

    # ランダムな浮動小数点c（0.01から1.00の範囲）
    c=$(awk -v min=1 -v max=10000 -v seed=$RANDOM 'BEGIN{srand(seed); print int(min+rand()*(max-min+1))}')

    # 小数点以下2桁に丸める
    c=$(awk "BEGIN {printf \"%.2f\", $c / 100}")

    # 出力
    current_combination="$a,$b,$c"
    # すでに使用した組み合わせでないことを確認
    while [[ "${used_combinations[@]}" =~ "$current_combination" ]]; do
        # 再生成
        a=$((RANDOM % range + 1))
        while true; do
            b=$((RANDOM % range + 1))
            if [ "$a" -ne "$b" ]; then
                break
            fi
        done

        c=$(awk -v min=1 -v max=100 -v seed=$RANDOM 'BEGIN{srand(seed); print int(min+rand()*(max-min+1))}')
        c=$(awk "BEGIN {printf \"%.2f\", $c / 100}")
        
        current_combination="$a, $b, $c"
    done

    # 出力
    echo "$current_combination"

    # 使用した組み合わせを配列に追加
    used_combinations+=("$current_combination")
done
