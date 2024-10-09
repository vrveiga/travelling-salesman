# set -e

gcc main.c lista.c -o exe
gcc extra.c lista.c -o extra
g++ ran_number.cxx -o gen

for ((i = 1; ; ++i)); do
    ./gen 4 100 20 > input_gen
    ./exe < input_gen > out_brute
    ./extra < input_gen > out_dp
    diff -Z out_brute out_dp > /dev/null || break
    echo "Passou o teste " $i
done

echo "WA no input:"
cat input_gen
echo "Resposta do brute:"
cat out_brute
echo "Resposta da dp:"
cat out_dp