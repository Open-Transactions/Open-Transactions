#!/bin/sh
# Travis script, don't execute manually
# Updates Open Transactions Sample Mint Files


if [ "$TRAVIS_BRANCH" == "master" ]; then

  git config --global user.email "travis@travis-ci.org"
  git config --global user.name "travis-ci"
  
  #Set upstream remote
  git remote add upstream https://${GH_TOKEN}@github.com/Open-Transactions/Open-Transactions > /dev/null

  # Commit and Push the Changes
  MasterHEAD=$(git rev-parse HEAD)

  #Checkout Open-Transactions/Open-Transactions master branch
  git checkout master

  cp -rf ~/.ot/server_data/mints/r1fUoHwJOWCuK3WBAAySjmKYqsG6G2TYIxdqY6YNuuG/* ./sample-data/ot-sample-data/server_data/mints/r1fUoHwJOWCuK3WBAAySjmKYqsG6G2TYIxdqY6YNuuG/

  cd sample-data/ot-sample-data/server_data/mints/r1fUoHwJOWCuK3WBAAySjmKYqsG6G2TYIxdqY6YNuuG

  git add -f .
  git commit -q -m "Update sample Mint files/$MasterHEAD"
  git push -f upstream master > /dev/null
  git push -f upstream develop > /dev/null
  
fi
