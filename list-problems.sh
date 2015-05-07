#!/bin/bash

function getProblemIds {
    ls problem-* | cut -d . -f1 | cut -d- -f2 | sort -n | uniq
}

function listProblems {
    for i in $(getProblemIds); do
	for j in c py scala java; do
	    find . -name "problem-$i.$j"
	    find . -name "problem-$i-*.$j"
	done
    done
}

listProblems
