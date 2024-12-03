grep -Eo "mul\([0-9]+,[0-9]+\)|do\(\)|don't\(\)" "$1" |
    sed -E "s/mul\(([0-9]+),([0-9]+)\)/\1,\2/" |
    sed -E "s/do\(\)/d/" | sed -E "s/don't\(\)/n/" > temp 
./main < temp
