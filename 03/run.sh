./main $(cat "$1" | wc -l) $(head -n 1 "$1" | wc -w) < "$1"
