# Makefile for running grammar MERCH, see the tree and output tree
# built from Antlr4
# if having problems with which library antlr is trying to use run this
# export CLASSPATH=".:/usr/local/lib/antlr-4.7.1-complete.jar:$CLASSPATH"
all: python java

# Take things needed for python output and compile using specified
# library's
python: ParserV2.g4 testingMain.py
	java -jar /usr/local/lib/antlr-4.7.1-complete.jar -Dlanguage=Python2 ParserV2.g4

# Run python with single test file for confirmation it is working
runP: python
	cat Test | python testingMain.py

# Run the testing script
test: python
	./runTests.sh

# Take things needed for java output and compile java files
java: ParserV2.g4
	java -jar /usr/local/lib/antlr-4.7.1-complete.jar ParserV2.g4
	javac ParserV2*.java
	
# Run java side gui of the tree built from grammar and test file
runJ: java

	java org.antlr.v4.gui.TestRig ParserV2 startRule -gui Test&

# Remove unnecessary files
clean:
	rm -rf ParserV2*.java *.class *.tokens ParserV2*.py? ParserV2*.py *.interp

# unfinished testing for the grammar against edge cases
testAll: 

