# project-euler

[Project Euler](http://projecteuler.net/problems)

    http://projecteuler.net/problems

----------------------------------------------------------------------
## Python Code

Python code can be found in solutions/python

Run Python code as follows; e.g. Problem 1

    $ python problem-1.py

----------------------------------------------------------------------
## C Code

C code can be found in solutions/c.  The Scons build-system is used.

    http://www.scons.org/

Build everything as follows.

    $ scons

Run C programs as follows; e.g. Problem 8

    $ ./out/problem-8

----------------------------------------------------------------------
## Java Code

Java code can be found in solutions/java.  The maven build-system is used.

    $ mvn package

A single executable Fat JAR would be built.  Provide it with the problem
names to execute.  Problem 24, for example, would be executed as
follows.

    $ java -jar target/euler.jar 24
    Problem 24 completed in 0 milliseconds. Answer is 2783915460

----------------------------------------------------------------------
## Jupyter Notebooks

Jupyter Notebook can be found in solutions/jupyter. You can start the
Jupyter Notebook server as follows:

    $ jupyter notebook



[EOF]: end-of-file
