#when tests fail the old directory will be wrong this fixes it
make clean      
cp filesTemp/* files
rm filesTemp -r