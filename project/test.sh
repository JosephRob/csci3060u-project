#./theProgram < asdf.txt > qwerty.txt
declare -i place

make

for file in ./tests/*
do
    if [[ -d $file ]]; then
        #echo $file
        place=1
        mkdir $file/outputs -p
        for test in $file/inputs/*
        do
            #echo $place
            echo $test
            ./theProgram < $test > $file"/outputs/out"$place".txt"
            rm $file/outputs/asdf$place.txt
            place=$place+1
        done
    fi
done

make clean