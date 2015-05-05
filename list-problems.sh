for ((i=1; i<1000; ++i)); do
    for suffix in py c; do
	if [[ -f problem-$i.$suffix ]]; then
	    echo problem-$i.$suffix;
	fi
    done
done
