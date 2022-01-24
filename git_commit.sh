find . -type f  -name *.h -exec git add {}   \;
find . -type f  -name *.cpp -exec git add {}   \;
find . -type f  -name Makefile -exec git add {}   \;
git commit -m $1
git push
