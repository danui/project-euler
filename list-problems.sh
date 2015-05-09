#!/bin/bash

function getNormalProblemIds {
    ls problem-* | cut -d . -f1 | cut -d- -f2
}

function getJavaProblemIds {
    ls src/euler/Problem*.java | cut -d. -f1 | cut -dm -f2
}

function getAllProblemIds {
    getNormalProblemIds
    getJavaProblemIds
}

function getProblemIds {
    getAllProblemIds | sort -n | uniq
}

function listProblems {
    for i in $(getProblemIds); do
	for j in c py scala; do
	    find . -name "problem-$i.$j"
	    find . -name "problem-$i-*.$j"
	done
	find ./src -name "Problem$i.java"
    done
}

listProblems
