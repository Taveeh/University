BEGIN{
	nr=0
	sum=0
}
sum = sum + $2
nr = nr + 1
END{
	print sum / nr
}
