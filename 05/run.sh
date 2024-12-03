grep -Eo "mul\([0-9]+,[0-9]+\)" "$1" | sed -E "s/mul\(([0-9]+),([0-9]+)\)/\1,\2/" > temp
./main < temp
