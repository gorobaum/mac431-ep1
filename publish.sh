#!/bin/bash

outdir=ep1-thiago-wilson

if [ ! -d $outdir ]; then
  mkdir $outdir
fi

contents="Makefile fase1.c fase2.c fase3.c LEIAME relatorio.txt"
cp -r $contents $outdir

tar -caf $outdir.tar.gz $outdir

rm -rf $outdir

