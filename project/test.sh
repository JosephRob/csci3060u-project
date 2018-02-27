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
            ./theProgram < $test > $file"/outputs/asdf"$place".txt"
            place=$place+1
        done
    fi
done
<<<<<<< HEAD
make clean
=======
rm asdf.txt
make clean
>>>>>>> 3c14cf2a9e65f12a1d33a691ca5408f794194f8b
