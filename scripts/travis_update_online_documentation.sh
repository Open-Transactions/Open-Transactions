#!/bin/sh
# Travis script, don't execute manually
# Updates Open Transactions Documentation Github Page with the latest doxygen from master

git config --global user.email "travis@travis-ci.org"
git config --global user.name "travis-ci"

git clone https://${GH_TOKEN}@github.com/Open-Transactions/Documentation.git


# Commit and Push the Changes
MasterHEAD=$(git rev-parse HEAD)

#Checkout Open-Transactions/Open-Transactions master branch
git checkout master

#Generate Doxyfile, Version Name = master/LatestCommitHashFromUpstreamMaster
( cat Doxyfile ; echo "PROJECT_NUMBER= master/$MasterHEAD" ) | doxygen -  > /dev/null

cp -rf docs/html/* ./Documentation/

cd Documentation

git add -f .
git commit -q -m "Update for master/$MasterHEAD"
git push -f origin gh-pages > /dev/null
