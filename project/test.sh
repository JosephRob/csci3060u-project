#./theProgram < asdf.txt > qwerty.txt
declare -i place
declare -i fails
make
rm filesTemp -r -s
mkdir filesTemp
cp files/* filesTemp -r
rm files/dailyUpdate.txt
echo "" > files/dailyUpdate.txt

fails=0
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
            ./auctionHouse < $test > $file"/outputs/out"$place".txt"
            diff  $file/outputs/out$place.txt $file/expectedOutputs/out$place.txt
            
            if [ "$?" -ne "0" ]; then
                fails=$fails+1
            fi
            place=$place+1
        done
        rm -r $file/outputs
    fi
done
echo "./files/dailyUpdate.txt"
diff  files/dailyUpdate.txt tests/expectedDay.txt
fails=$?+$fails
echo "$fails test(s) failed"

make clean
cp filesTemp/* files
rm filesTemp -r
