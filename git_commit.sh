find . -type f  -name *.h -exec git add {} \;
find . -type f  -name *.cpp -exec git add {} \;
find . -type f  -name *.pdf -exec git add {} \;
find . -type f  -name Makefile -exec git add {} \;
git commit
git push
