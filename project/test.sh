#./theProgram < asdf.txt > qwerty.txt
declare -i place

make
mkdir filesTemp
cp files/* filesTemp -r
rm files/dailyUpdate.txt

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
            diff -q $file/outputs/out$place.txt $file/expectedOutputs/out$place.txt
            place=$place+1
        done
        rm -r $file/outputs
    fi
done

diff -q files/dailyUpdate.txt tests/expectedDay.txt

make clean      
cp filesTemp/* files
rm filesTemp -r