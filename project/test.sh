#./theProgram < asdf.txt > qwerty.txt
for file in ./tests/*
do
    if [[ -d $file ]]; then
        #echo $file
        for test in $file/inputs/*
        do
            echo $test
            ./theProgram < $test #> asdf.txt
        done
    fi
done