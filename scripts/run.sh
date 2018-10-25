BINARY=$1

# test small file
python3 generate.py --output small.txt --lines_count 500 --max_length 50

echo "small file, 500 bytes RAM"
$BINARY small.txt small_out.txt 500
python3 check.py --result small_out.txt --source small.txt
echo "-------"

echo "small file, 50000 bytes RAM"
$BINARY small.txt small_out.txt 50000
python3 check.py --result small_out.txt --source small.txt
echo "-------"
rm -rf small.txt small_out.txt


python3 generate.py --output large.txt --lines_count 500000 --max_length 50

echo "large file, 50000 bytes RAM"
$BINARY large.txt large_out.txt 50000
python3 check.py --result large_out.txt --source large.txt
echo "-------"

echo "large file, 50000000 bytes RAM"
$BINARY large.txt large_out.txt 50000000
python3 check.py --result large_out.txt --source large.txt
echo "-------"
rm -rf large.txt large_out.txt


