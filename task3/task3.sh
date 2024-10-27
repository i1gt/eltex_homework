for i in {1..20}
do
mkdir $i
touch $i/$i.txt
ln -s $i.txt ./$i/link.txt
done
find ! -name "*4*" -type d | xargs rm -r 
echo 123 > 14/14.txt