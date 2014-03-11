#!/bin/bash


# Check for swig
if ! swig -version > /dev/null; then 
    echo Cannot find swig...
    exit 1
fi

for x in csharp java perl5 php python ruby tcl d go
do
    echo Generating for $x ...

    rm -rf glue/$x
    mkdir glue/$x

    # Remove existing temporary wrapper files
    for ext in cxx cpp h; do
	if [ -f otapi/OTAPI_wrap.$ext ]; then 'rm -f otapi/OTAPI_wrap.$ext'; fi
    done


    if [ "$x" != "java" ] && [ "$x" != "csharp" ] && [ "$x" != "go" ]; then
	echo swig -c++ -$x -outdir glue/$x otapi/OTAPI.i
	swig -c++ -$x -outdir glue/$x otapi/OTAPI.i
    fi

    if [ "$x" == "java" ]; then
	echo swig -c++ -$x -package org.opentransactions.otapi -outdir glue/$x otapi/OTAPI.i
	swig -c++ -$x -package org.opentransactions.otapi -outdir glue/$x otapi/OTAPI.i
    fi

    if [ "$x" == "csharp" ]; then
      echo swig -c++ -$x -namespace OpenTransactions.OTAPI -dllimport otapi-csharp -outdir glue/$x otapi/OTAPI.i
      swig -c++ -"$x" -namespace OpenTransactions.OTAPI -dllimport otapi-csharp -outdir glue/$x otapi/OTAPI.i
    fi

    if [ "$x" == "go" ]; then
	echo swig -c++ -$x -intgosize 64 -soname libotapi-go.so -outdir glue/$x otapi/OTAPI.i
        swig -c++ -$x -intgosize 64 -soname libotapi-go.so -outdir glue/$x otapi/OTAPI.i
    fi

    # Remove old and rename header wrapper files
    if [ -f otapi/OTAPI-$x.h ]; then rm otapi/OTAPI-$x.h; fi
    if [ -f otapi/OTAPI_wrap.h ]; then mv otapi/OTAPI_wrap.h otapi/OTAPI-$x.hpp; fi

    # Remove old, rename and clean up source wrapper files
    for ext in cxx cpp; do
        if [ -f otapi/OTAPI-$x.$ext ]; then rm otapi/OTAPI-$x.$ext; fi
        if [ -f otapi/OTAPI_wrap.$ext ]; then mv otapi/OTAPI_wrap.$ext otapi/OTAPI-$x.$ext; fi
	if [ -f otapi/OTAPI-$x.$ext ]; then printf '%s\n' "g/OTAPI_wrap\.h/s//OTAPI-$x.hpp/g" w | ed -s "otapi/OTAPI-$x.$ext"; fi
    done

done

echo Done!
