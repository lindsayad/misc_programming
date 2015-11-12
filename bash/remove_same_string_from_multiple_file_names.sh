#!/bin/bash

for file in *_dummy_name_to_prevent_accidental_overwrite_of_good_figs.svg; do
    mv "$file" "${file/_dummy_name_to_prevent_accidental_overwrite_of_good_figs/}"
done
